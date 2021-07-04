#pragma once

#include "Mesh.h"
#include "Renderer.h"

namespace gameplay {
    class Block {
    public:
        //TODO: Remove hardcoded constants?
        //TODO: Derive from Renderable?
        Block(float x, float y, float width, float height) : m_blockMesh(x, y, width, height) {
            m_blockMesh.SetPos(core::Vec2(x, y));
        };
        ~Block() {};

        void Update(float dt) {};

        void Draw(core::Renderer* renderer) {
            if (!renderer)
                return;

            renderer->Render(m_blockMesh);
        }

        const core::Mesh& GetMesh() const {
            return m_blockMesh;
        }

    private:
        core::QuadMesh m_blockMesh;
    };
}
