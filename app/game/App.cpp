#include <jni.h>

#include "App.h"

#include <memory>

using core::App;

App::App() {

}

App::~App() {

}

void App::Update() {
    m_player.Update(0);
}