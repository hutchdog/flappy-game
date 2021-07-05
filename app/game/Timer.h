#pragma once

#include <cstdint>

namespace core {
    class Timer {
    public:
        Timer();

        void Pause();
        void Resume();

        float GetDelta();

    private:
        int64_t m_previousTime = 0;
        int64_t m_currentTime = 0;

        int64_t GetTime();
    };
}
