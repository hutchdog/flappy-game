#pragma once

#include "Mesh.h"
#include "Renderer.h"

namespace gameplay {
    class Player {
    public:
        //TODO: Remove hardcoded constants?
        //TODO: Derive from Renderable?
        Player();
        ~Player();

        void Update(float dt);

        void Draw(core::Renderer* renderer);

        core::Mesh& GetMesh();

        const core::Mesh& GetMesh() const;

        void Touch();

    private:
        core::CircleMesh m_playerMesh;

        float m_horizontalSpeed = 0;
    };
}
