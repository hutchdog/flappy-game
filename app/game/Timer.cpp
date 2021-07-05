#include "Timer.h"

#include <ctime>

using core::Timer;

Timer::Timer() {
    m_previousTime = m_currentTime = GetTime();
}

void Timer::Pause() {

}

void Timer::Resume() {
    m_previousTime = m_currentTime = GetTime();
}

float Timer::GetDelta() {
    m_previousTime = m_currentTime;
    m_currentTime = GetTime();

    auto delta = m_currentTime - m_previousTime;
    auto dt = delta / 1000000000.f;

    return dt;
}

int64_t Timer::GetTime() {
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (int64_t) now.tv_sec*1000000000LL + now.tv_nsec;
}