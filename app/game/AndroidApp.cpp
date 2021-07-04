#include <jni.h>

#include "AndroidApp.h"
#include "AndroidRenderer.h"
#include "Mesh.h"

#include <memory>

using core::App;
using core::AndroidApp;
using core::AndroidRenderer;

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

void AndroidApp::Init(Renderer* renderer) {
    m_renderer = renderer;
}

void AndroidApp::Pause() {

}

void AndroidApp::Resume() {

}

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationInit(JNIEnv *env, jobject thiz, jobject context,
                                                    jobject view) {
    Instantiate();
    Application()->Init(new AndroidRenderer(env, context, view));
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
    Application()->Update();
    Application()->Draw();
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationOnTouch(JNIEnv *env, jobject thiz) {
    Application()->Touch();
}

}