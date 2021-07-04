#pragma once

#include "Mesh.h"
#include "Renderer.h"

namespace gameplay {
    class Block {
    public:
        //TODO: Remove hardcoded constants?
        //TODO: Derive from Renderable?
        Block(float x, float y, float width, float height);
        ~Block();

        void Update(float dt);

        void Draw(core::Renderer* renderer);

        const core::Mesh& GetMesh() const;

    private:
        core::QuadMesh m_blockMesh;
    };
}
