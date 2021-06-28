#pragma once

#include "App.h"

namespace core {
    class AndroidApp : public App {
    public:
        AndroidApp();
        ~AndroidApp() override;

        void Init() override;
        void Pause() override;
        void Resume() override;
        void Draw() override;

        void NativeInit(JNIEnv *env, jobject, jobject);

    private:
        JNIEnv* m_environment   = nullptr;
        jobject m_context       = nullptr;
        jobject m_nativeView    = nullptr;

        EGLDisplay m_display;
        EGLSurface m_surface;
    };
}
