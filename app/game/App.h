#pragma once

#include "Player.h"
#include "Level.h"
#include "Timer.h"

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
        virtual void Touch() = 0;

    protected:
        gameplay::Player m_player;
        gameplay::Level m_level;
        core::Timer m_timer;

        Renderer* m_renderer;

        virtual void Update();
    };
}

extern core::App* Application();