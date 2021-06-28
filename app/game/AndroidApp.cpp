#include <jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <EGL/egl.h>

#include <android/native_window_jni.h>

#include "AndroidApp.h"

#include <memory>

using core::App;
using core::AndroidApp;

namespace {
    std::unique_ptr<core::App> application;

    void Instantiate() {
        if (application == nullptr)
            application.reset(new AndroidApp());
    }
}

core::App *Application() {
    return application.get();
}

AndroidApp::AndroidApp() {

}

AndroidApp::~AndroidApp() {
    //TODO: release refs
}

void AndroidApp::Init() {

}

void AndroidApp::NativeInit(JNIEnv *env, jobject context, jobject nativeSurface) {
    m_environment = env;
    m_context = env->NewGlobalRef(context);
    //m_nativeView = env->NewGlobalRef(nativeSurface);

    m_display = eglGetDisplay( EGL_DEFAULT_DISPLAY);
    if (m_display == EGL_NO_DISPLAY)
        return;

    EGLint major = 0;
    EGLint minor = 1;
    eglInitialize(m_display, &major, &minor);

    EGLint configAttribs[] = {
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
    eglChooseConfig(m_display, configAttribs, &eglConfig, 1, &numConfig);

    // Create a surface for the main window
    auto window = ANativeWindow_fromSurface(m_environment, nativeSurface);

    if ((m_surface = eglCreateWindowSurface(m_display, eglConfig, (EGLNativeWindowType) window, nullptr)) == EGL_NO_SURFACE)
        return;

    EGLContext eglContext = nullptr;
    EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    // Create an OpenGL ES context
    if ((eglContext = eglCreateContext(m_display, eglConfig, EGL_NO_CONTEXT, ai32ContextAttribs)) == EGL_NO_CONTEXT)
        return;
    // Make the context and surface current
    if (!eglMakeCurrent(m_display, m_surface, m_surface, eglContext))
        return;
}

void AndroidApp::Pause() {

}

void AndroidApp::Resume() {

}

void AndroidApp::Draw() {
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(m_display, m_surface);
}

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationInit(JNIEnv *env, jobject thiz, jobject context, jobject view) {
    Instantiate();
    Application()->Init();
    AndroidApp* nativeApp = dynamic_cast<AndroidApp*>(Application());
    nativeApp->NativeInit(env, context, view);
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationPause(JNIEnv *env, jobject thiz) {
    Application()->Pause();
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationResume(JNIEnv *env, jobject thiz) {
    Application()->Resume();
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationDraw(JNIEnv *env, jobject thiz) {
    Application()->Draw();
}

}