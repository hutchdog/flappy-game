#include <jni.h>

#include "App.h"

using core::App;

App::App() {

}

App::~App() {

}

void App::Update() {
    auto dt = m_timer.GetDelta();

    if (m_gameplayState == GameplayState::Play) {
        m_player.Update(dt);
        m_level.Update(dt);

        bool isGameOver = m_level.IntersectWithPlayer(m_player);
        if (isGameOver)
            m_gameplayState = GameplayState::GameOver;

        if (m_renderer)
            m_renderer->Update(dt);
    }
}

void App::Draw() {
    if (m_renderer) {
        m_renderer->BeginFrame();

        m_player.Draw(m_renderer);
        m_level.Draw(m_renderer);

        m_renderer->EndFrame();
    }
}

void App::Touch() {
    //Waiting for first touch to start a game
    if (m_gameplayState == GameplayState::StartGame) {
        m_gameplayState = GameplayState::Play;
    }

    if (m_gameplayState == GameplayState::Play) {
        m_player.Touch();
    }

    if (m_gameplayState == GameplayState::GameOver) {
        //TODO: Reset GS and score here!
    }
}