#pragma once

namespace core {
    class Mesh;

    class Renderer {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;

        virtual void Render(const Mesh& mesh) = 0;
    };
}
