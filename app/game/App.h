#pragma once

#include "Player.h"

namespace core {
    class Renderer;

    class App {
    public:
        App();
        virtual ~App();

        virtual void Init(Renderer*) = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;
        virtual void Draw() = 0;

    protected:
        gameplay::Player m_player;

        void Update();
    };
}

extern core::App* Application();