#pragma once

#include "Player.h"
#include "Level.h"
#include "Timer.h"

namespace core {
    class Renderer;

    enum class GameplayState : int {
        StartGame = 0,
        Play,
        GameOver
    };

    class App {
    public:
        App();
        virtual ~App();

        virtual void Init(Renderer*) = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void Update();
        virtual void Draw();

        virtual void Touch();

    protected:
        gameplay::Player m_player;
        gameplay::Level m_level;
        core::Timer m_timer;

        Renderer* m_renderer;

        GameplayState m_gameplayState = GameplayState::StartGame;
    };
}

extern core::App* Application();