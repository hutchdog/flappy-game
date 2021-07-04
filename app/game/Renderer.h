#pragma once

namespace core {
    class Mesh;

    class Renderer {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;

        virtual void BeginFrame() = 0;
        virtual void Render(const Mesh& mesh) = 0;
        virtual void EndFrame() = 0;
    };
}
