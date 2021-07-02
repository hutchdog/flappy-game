#pragma once

#include "Renderer.h"

#include <jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

namespace core {

    class AndroidRenderer : public Renderer {
    public:
        AndroidRenderer(JNIEnv* environment, jobject context, jobject view);
        ~AndroidRenderer() override;

        void Render() override;
    private:
        JNIEnv* m_environment   = nullptr;
        jobject m_context       = nullptr;
        jobject m_view    = nullptr;

        EGLDisplay m_display;
        EGLSurface m_surface;

        void Init();
    };
}
