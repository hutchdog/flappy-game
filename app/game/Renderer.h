#pragma once

namespace core {
    class Renderer {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;

        virtual void Render() = 0;
    };
}
