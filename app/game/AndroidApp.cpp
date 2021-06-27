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

}

void AndroidApp::Init() {

}

void AndroidApp::Pause() {

}

void AndroidApp::Resume() {

}

void AndroidApp::Draw() {

}

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationInit(JNIEnv *env, jobject thiz) {
    Instantiate();
    Application()->Init();
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