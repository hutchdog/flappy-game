#include <jni.h>

#include "App.h"

#include <memory>

using core::App;

App::App() {

}

App::~App() {

}

void App::Update() {
    auto dt = m_timer.GetDelta();

    m_player.Update(dt);
    m_level.Update(dt);
    m_level.IntersectWithPlayer(m_player);

    if (m_renderer)
        m_renderer->Update(dt);

    if (m_renderer) {
        m_renderer->BeginFrame();

        m_player.Draw(m_renderer);
        m_level.Draw(m_renderer);

        m_renderer->EndFrame();
    }
}