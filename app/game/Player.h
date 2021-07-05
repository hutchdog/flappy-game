#pragma once

#include "Mesh.h"
#include "Renderer.h"

namespace gameplay {
    class Player {
    public:
        Player();
        ~Player() = default;

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
