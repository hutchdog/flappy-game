#pragma once

#include "Camera.h"

namespace core {
    class Mesh;

    class Renderer {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;

        virtual void BeginFrame() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render(const Mesh& mesh) = 0;
        virtual void EndFrame() = 0;

        Camera& GetCamera() {
            return m_defaultCamera;
        }

    protected:
        Camera m_defaultCamera;
    };
}
