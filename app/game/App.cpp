#include <jni.h>

#include "App.h"

#include <memory>

using core::App;

namespace {
    bool tm_init = false;
    int64_t previousTime;
    int64_t currentTime;
}

App::App() {

}

App::~App() {

}

void App::Update() {
    auto getTime = []() -> int64_t {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        return (int64_t) now.tv_sec*1000000000LL + now.tv_nsec;
    };

    if(!tm_init) {
        previousTime = currentTime = getTime();
        tm_init = true;
    } else {
        previousTime = currentTime;
        currentTime = getTime();
    }

    auto delta = currentTime - previousTime;
    auto dt = delta / 1000000000.f;

    m_player.Update(dt);
    m_level.Update(dt);
    m_level.IntersectWithPlayer(m_player);
}