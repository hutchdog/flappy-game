#include <jni.h>

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

void AndroidApp::NativeInit(JNIEnv *env, jobject context, jobject view) {
    m_environment = env;
    m_context = env->NewGlobalRef(context);
    m_nativeView = env->NewGlobalRef(view);
}

void AndroidApp::Pause() {

}

void AndroidApp::Resume() {

}

void AndroidApp::Draw() {

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