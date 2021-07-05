#pragma once

#include "App.h"

namespace core {
    class AndroidApp : public App {
    public:
        AndroidApp() = default;
        ~AndroidApp() = default;

        void Init(Renderer*) override;
        void Pause() override;
        void Resume() override;
    };
}
