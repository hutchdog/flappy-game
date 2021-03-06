#pragma once

#include "App.h"

namespace core {
    class AndroidApp : public App {
    public:
        AndroidApp();
        ~AndroidApp() override;

        void Init(Renderer*) override;
        void Pause() override;
        void Resume() override;
        void Draw() override;

    private:
        Renderer* m_androidRenderer;
    };
}
