#pragma once

#include "Mesh.h"

namespace gameplay {
    class Block {
    public:
        //TODO: Remove hardcoded constants?
        //TODO: Derive from Renderable?
        Block(float x, float y, float width, float height) : m_blockMesh(0, 0, width, height) {

        };
        ~Block() {};

        void Update(float dt) {};

        const core::Mesh& GetMesh() const {
            return m_blockMesh;
        }

    private:
        core::QuadMesh m_blockMesh;
    };
}
