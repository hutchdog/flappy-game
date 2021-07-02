#include "AndroidRenderer.h"
#include "Mesh.h"

#include <android/native_window_jni.h>

#include <string>

using core::AndroidRenderer;

namespace {
    float projectionMatrix[] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
    };
}

AndroidRenderer::AndroidRenderer(JNIEnv* environment, jobject context, jobject view) : m_environment(environment), m_context(context), m_view(view) {
    DisplayInit();
    CreateVS();
    CreatePS();
    CreateProgram();
}

AndroidRenderer::~AndroidRenderer() {
    //TODO: release refs
}

void AndroidRenderer::DisplayInit() {
    m_display = eglGetDisplay( EGL_DEFAULT_DISPLAY);
    if (m_display == EGL_NO_DISPLAY)
        return;

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

    // Create a surface for the main window
    auto window = ANativeWindow_fromSurface(m_environment, m_view);

    if ((m_surface = eglCreateWindowSurface(m_display, eglConfig, (EGLNativeWindowType) window, nullptr)) == EGL_NO_SURFACE)
        return;

    EGLContext eglContext = nullptr;
    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    // Create an OpenGL ES context
    if ((eglContext = eglCreateContext(m_display, eglConfig, EGL_NO_CONTEXT, contextAttributes)) == EGL_NO_CONTEXT)
        return;
    // Make the context and surface current
    if (!eglMakeCurrent(m_display, m_surface, m_surface, eglContext))
        return;

    int windowWidth = ANativeWindow_getWidth(window);
    int windowHeight = ANativeWindow_getHeight(window);

    glViewport(0, 0, windowWidth, windowHeight);
    glDisable(GL_CULL_FACE);

    projectionMatrix[0] = 2.f / windowWidth;
    projectionMatrix[5] = 2.f / windowHeight;
}

void AndroidRenderer::CreateVS() {
    const GLchar* vertexShaderSource[] = {
        "uniform mat4 u_viewProjMatrix; ",
        "uniform mat4 u_modelMatrix;    ",

        "attribute vec4 a_Position;     ",
        "attribute vec4 a_Color;        ",

        "varying vec4 v_Color;          ",

        "void main()                    ",
        "{                              ",
        "   v_Color = a_Color;          ",
        "   gl_Position = u_viewProjMatrix * u_modelMatrix *",
        "                 a_Position;   ",
        "}                              "
    };

    m_vertexProgram = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexProgram, 11, vertexShaderSource, 0);
    glCompileShader(m_vertexProgram);

    int compileStatus[1];
    glGetShaderiv(m_vertexProgram, GL_COMPILE_STATUS, compileStatus);

    if (compileStatus[0] == 0)
    {
        glDeleteShader(m_vertexProgram);
        m_vertexProgram = 0;
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
    glShaderSource(m_fragmentProgram, 6, fragmentShaderSource, 0);
    glCompileShader(m_fragmentProgram);

    int compileStatus[1];
    glGetShaderiv(m_fragmentProgram, GL_COMPILE_STATUS, compileStatus);

    if (compileStatus[0] == 0)
    {
        glDeleteShader(m_fragmentProgram);
        m_fragmentProgram = 0;
    }
}

void AndroidRenderer::CreateProgram() {
    m_program = glCreateProgram();

    if (m_program != 0)
    {
        glAttachShader(m_program, m_vertexProgram);
        glAttachShader(m_program, m_fragmentProgram);

        glLinkProgram(m_program);

        // Get the link status.
        int linkStatus[1];
        glGetProgramiv(m_program, GL_LINK_STATUS, linkStatus);

        // If the link failed, delete the program.
        if (linkStatus[0] == 0)
        {
            glDeleteProgram(m_program);
            m_program = 0;
        }
    }

    m_viewMatrixAttribute = glGetUniformLocation(m_program, "u_viewProjMatrix");
    m_modelMatrixAttribute = glGetUniformLocation(m_program, "u_modelMatrix");
    m_posAttribute = glGetAttribLocation(m_program, "a_Position");
    m_colorAttribute = glGetAttribLocation(m_program, "a_Color");

    glUseProgram(m_program);
}

void AndroidRenderer::Render(Mesh* mesh) {
    if (!mesh)
        return;

    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glVertexAttribPointer(m_posAttribute, 3, GL_FLOAT, false,
                          0, mesh->GetVertexData());

    glEnableVertexAttribArray(m_posAttribute);

    glVertexAttribPointer(m_colorAttribute, 4, GL_FLOAT, false,
                          0, mesh->GetColorData());

    glEnableVertexAttribArray(m_colorAttribute);

    auto pos = mesh->GetPos();
    float modelMatrix[] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            pos.m_x, pos.m_y, 0, 1,
    };

    glUniformMatrix4fv(m_modelMatrixAttribute, 1, false, modelMatrix);
    glUniformMatrix4fv(m_viewMatrixAttribute, 1, false, projectionMatrix);

    glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertexCount());

    eglSwapBuffers(m_display, m_surface);
}
