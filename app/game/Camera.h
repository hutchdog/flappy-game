#pragma once

#include "Mesh.h"

namespace core {
    class Camera {
    public:
        void SetViewport(Vec2 size);
        Vec2 GetViewport() const;

        void SetOffset(Vec2 offset);
        Vec2 GetOffset() const;

        const float* GetViewMatrix() const;
        const float* GetProjMatrix() const;

    private:
        Vec2 m_size;
        Vec2 m_offset;
    };
}
