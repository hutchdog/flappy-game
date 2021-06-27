#pragma once

namespace core {
    class App {
    public:
        App();
        virtual ~App();

        virtual void Init() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;
        virtual void Draw() = 0;
    };
}

extern core::App* Application();