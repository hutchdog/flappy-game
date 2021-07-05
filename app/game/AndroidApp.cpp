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

void AndroidApp::Init(Renderer* renderer) {
    m_renderer = renderer;
}

void AndroidApp::Pause() {
    App::Pause();
}

void AndroidApp::Resume() {
    App::Resume();
}

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationInit(JNIEnv *env, jobject, jobject context,
                                                    jobject view) {
    Instantiate();
    Application()->Init(new AndroidRenderer(env, view));
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationPause(JNIEnv*, jobject) {
    Application()->Pause();
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationResume(JNIEnv*, jobject) {
    Application()->Resume();
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationDraw(JNIEnv*, jobject) {
    Application()->Update();
    Application()->Draw();
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationOnTouch(JNIEnv*, jobject) {
    Application()->Touch();
}

}