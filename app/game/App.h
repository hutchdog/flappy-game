#pragma once

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

    protected:
        void Update();
    };
}

extern core::App* Application();