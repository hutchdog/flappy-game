#pragma once

#include "Mesh.h"
#include "Renderer.h"

namespace gameplay {
    class Block {
    public:
        Block(float x, float y, float width, float height);
        ~Block() = default;

        void Draw(core::Renderer* renderer);

        const core::Mesh& GetMesh() const;

    private:
        core::QuadMesh m_blockMesh;
    };
}
