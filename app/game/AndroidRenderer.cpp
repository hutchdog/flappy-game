#include "AndroidRenderer.h"
#include "Mesh.h"
#include "Common.h"

#include <android/native_window_jni.h>

using core::AndroidRenderer;
using common::PlayerSpeed;

AndroidRenderer::AndroidRenderer(JNIEnv* environment, jobject view) : m_environment(environment), m_view(view) {
    DisplayInit();
    CreateVS();
    CreatePS();
    ShaderProgramInit();
}

void AndroidRenderer::DisplayInit() {
    m_display = eglGetDisplay( EGL_DEFAULT_DISPLAY);
    if (m_display == EGL_NO_DISPLAY) {
        assert(false && "Can't get display!");
        return;
    }

    EGLint major = 0;
    EGLint minor = 1;
    eglInitialize(m_display, &major, &minor);

    EGLint configAttributes[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_STENCIL_SIZE, 0,
        EGL_NONE
    };

    EGLint numConfig = 0;
    EGLConfig eglConfig;
    eglChooseConfig(m_display, configAttributes, &eglConfig, 1, &numConfig);

    auto window = ANativeWindow_fromSurface(m_environment, m_view);
    if ((m_surface = eglCreateWindowSurface(m_display, eglConfig, (EGLNativeWindowType) window, nullptr)) == EGL_NO_SURFACE) {
        assert(false && "Can't get native surface!");
        return;
    }

    EGLContext eglContext = nullptr;
    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    if ((eglContext = eglCreateContext(m_display, eglConfig, EGL_NO_CONTEXT, contextAttributes)) == EGL_NO_CONTEXT) {
        assert(false && "Can't create context!");
        return;
    }

    if (!eglMakeCurrent(m_display, m_surface, m_surface, eglContext)) {
        assert(false && "Can't set current context!");
        return;
    }

    int windowWidth = ANativeWindow_getWidth(window);
    int windowHeight = ANativeWindow_getHeight(window);

    glViewport(0, 0, windowWidth, windowHeight);

    m_defaultCamera.SetViewport(Vec2(windowWidth, windowHeight));
    m_defaultCamera.SetOffset(Vec2(0, 0));
}

void AndroidRenderer::CreateVS() {
    const GLchar* vertexShaderSource[] = {
            "uniform mat4 u_projMatrix;     ",
            "uniform mat4 u_viewMatrix;     ",
            "uniform mat4 u_modelMatrix;    ",

            "attribute vec4 a_Position;     ",
            "attribute vec4 a_Color;        ",

            "varying vec4 v_Color;          ",

            "void main()                    ",
            "{                              ",
            "   v_Color = a_Color;          ",
            "   gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * a_Position;   ",
            "}                              "
    };

    m_vertexProgram = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexProgram, 11, vertexShaderSource, nullptr);
    glCompileShader(m_vertexProgram);

    int compileStatus[1];
    glGetShaderiv(m_vertexProgram, GL_COMPILE_STATUS, compileStatus);

    if (compileStatus[0] == 0) {
        glDeleteShader(m_vertexProgram);
        m_vertexProgram = 0;

        assert(false && "Can't compile vertex shader!");
    }
}

void AndroidRenderer::CreatePS() {
    const GLchar* fragmentShaderSource[] = {
        "precision mediump float;       ",

        "varying vec4 v_Color;          ",

        "void main()                    ",
        "{                              ",
        "   gl_FragColor = v_Color;     ",
        "}                              "
    };

    m_fragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentProgram, 6, fragmentShaderSource, nullptr);
    glCompileShader(m_fragmentProgram);

    int compileStatus[1];
    glGetShaderiv(m_fragmentProgram, GL_COMPILE_STATUS, compileStatus);

    if (compileStatus[0] == 0) {
        glDeleteShader(m_fragmentProgram);
        m_fragmentProgram = 0;
        assert(false && "Can't compile pixel shader!");
    }
}

void AndroidRenderer::ShaderProgramInit() {
    m_program = glCreateProgram();

    if (m_program != 0)
    {
        glAttachShader(m_program, m_vertexProgram);
        glAttachShader(m_program, m_fragmentProgram);

        glLinkProgram(m_program);

        int linkStatus[1];
        glGetProgramiv(m_program, GL_LINK_STATUS, linkStatus);

        if (linkStatus[0] == 0)
        {
            glDeleteProgram(m_program);
            m_program = 0;
            assert(false && "Can't link program!");
        }
    }

    m_projMatrixAttribute = glGetUniformLocation(m_program, "u_projMatrix");
    m_viewMatrixAttribute = glGetUniformLocation(m_program, "u_viewMatrix");
    m_modelMatrixAttribute = glGetUniformLocation(m_program, "u_modelMatrix");
    m_posAttribute = glGetAttribLocation(m_program, "a_Position");
    m_colorAttribute = glGetAttribLocation(m_program, "a_Color");

    glUseProgram(m_program);
}

void AndroidRenderer::BeginFrame() {
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void AndroidRenderer::Update(float dt) {
    auto offset = m_defaultCamera.GetOffset();
    offset.m_x -= PlayerSpeed * dt;
    m_defaultCamera.SetOffset(offset);
}

void AndroidRenderer::Render(const Mesh& mesh) {

    glVertexAttribPointer(m_posAttribute, 3, GL_FLOAT, false,
                          0, mesh.GetVertexData());

    glEnableVertexAttribArray(m_posAttribute);

    glVertexAttribPointer(m_colorAttribute, 4, GL_FLOAT, false,
                          0, mesh.GetColorData());

    glEnableVertexAttribArray(m_colorAttribute);

    auto pos = mesh.GetPos();
    float modelMatrix[] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            pos.m_x, pos.m_y, 0, 1,
    };

    glUniformMatrix4fv(m_modelMatrixAttribute, 1, false, modelMatrix);

    glUniformMatrix4fv(m_viewMatrixAttribute, 1, false, m_defaultCamera.GetViewMatrix());
    glUniformMatrix4fv(m_projMatrixAttribute, 1, false, m_defaultCamera.GetProjMatrix());

    int vertexCount = mesh.GetVertexCount();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount / 3);
}

void AndroidRenderer::EndFrame() {
    eglSwapBuffers(m_display, m_surface);
}
