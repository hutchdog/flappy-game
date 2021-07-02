#include "AndroidRenderer.h"

#include <android/native_window_jni.h>

using core::AndroidRenderer;

AndroidRenderer::AndroidRenderer(JNIEnv* environment, jobject context, jobject view) : m_environment(environment), m_context(context), m_view(view) {
    Init();
}

AndroidRenderer::~AndroidRenderer() {
    //TODO: release refs
}

void AndroidRenderer::Init() {
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
}

void AndroidRenderer::Render() {
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(m_display, m_surface);
}
