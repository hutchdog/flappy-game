#pragma once

#include "Mesh.h"
#include "Renderer.h"

namespace gameplay {
    class Player {
    public:
        //TODO: Remove hardcoded constants?
        //TODO: Derive from Renderable?
        Player() : m_playerMesh(10, 30, 10, 24) {

        };
        ~Player() {};

        void Update(float dt) {
            auto currentPos = m_playerMesh.GetPos();
            currentPos.m_x += 6 * dt;

            m_horizontalSpeed -= 0.5f * dt;
            currentPos.m_y += m_horizontalSpeed;

            m_playerMesh.SetPos(currentPos);
        };

        void Draw(core::Renderer* renderer) {
            if (!renderer)
                return;

            renderer->Render(m_playerMesh);
        }

        const core::Mesh& GetMesh() const {
            return m_playerMesh;
        }

        void Touch() {
            m_horizontalSpeed = 0.7f;
        }

    private:
        core::CircleMesh m_playerMesh;

        float m_horizontalSpeed = 0;
    };
}
