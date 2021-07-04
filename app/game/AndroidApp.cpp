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

    bool tm_init = false;
    int64_t previousTime;
    int64_t currentTime;
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
    m_androidRenderer = renderer;
}

void AndroidApp::Pause() {

}

void AndroidApp::Resume() {

}

void AndroidApp::Draw() {
    Update();
    if (m_androidRenderer) {
        m_androidRenderer->BeginFrame();

        m_player.Draw(m_androidRenderer);
        m_level.Draw(m_androidRenderer);

        m_androidRenderer->EndFrame();
    }
}

void AndroidApp::Touch() {
    m_player.Touch();
}

void AndroidApp::Update() {
    auto getTime = []() -> int64_t {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        return (int64_t) now.tv_sec*1000000000LL + now.tv_nsec;
    };

    if(!tm_init) {
        previousTime = currentTime = getTime();
        tm_init = true;
    } else {
        previousTime = currentTime;
        currentTime = getTime();
    }

    App::Update();
    if (m_androidRenderer) {

        auto delta = currentTime - previousTime;
        auto dt = delta / 1000000000.f;
        m_androidRenderer->Update(dt);
    }
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
    Application()->Draw();
}

JNIEXPORT void JNICALL
Java_com_example_angrygeom_GameView_applicationOnTouch(JNIEnv *env, jobject thiz) {
    Application()->Touch();
}

}