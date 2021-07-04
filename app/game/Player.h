#pragma once

#include "Mesh.h"

namespace gameplay {
    class Player {
    public:
        //TODO: Remove hardcoded constants?
        //TODO: Derive from Renderable?
        Player() : m_playerMesh(10, 50, 10, 24) {

        };
        ~Player() {};

        void Update(float dt) {
            auto currentPos = m_playerMesh.GetPos();
            currentPos.m_x += 1;
            m_playerMesh.SetPos(currentPos);
        };

        const core::Mesh& GetMesh() const {
            return m_playerMesh;
        }

    private:
        core::CircleMesh m_playerMesh;
    };
}
