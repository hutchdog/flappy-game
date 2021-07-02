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
        jobject m_view          = nullptr;

        EGLDisplay m_display;
        EGLSurface m_surface;

        GLint m_vertexProgram       = 0;
        GLint m_fragmentProgram     = 0;
        GLint m_program             = 0;

        int m_matrixAttribute       = 0;
        int m_posAttribute          = 0;
        int m_colorAttribute        = 0;

        void DisplayInit();
        void CreateVS();
        void CreatePS();
        void CreateProgram();
    };
}
