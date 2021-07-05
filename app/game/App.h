#pragma once

#include "Player.h"
#include "Level.h"
#include "Timer.h"

namespace core {
    class Renderer;

    enum class GameplayState : int {
        StartGame = 0,
        Play,
        Pause,
        GameOver
    };

    class App {
    public:
        App() = default;

        virtual ~App() = default;

        virtual void Init(Renderer *) = 0;

        virtual void Pause();
        virtual void Resume();
        virtual void Update();
        virtual void Draw();
        virtual void Touch();

        virtual void ResetGame();

    protected:
        gameplay::Player m_player;
        gameplay::Level m_level;
        core::Timer m_timer;

        Renderer *m_renderer = nullptr;

        GameplayState m_gameplayState = GameplayState::StartGame;
    };
}

extern core::App* Application();