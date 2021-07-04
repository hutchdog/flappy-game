#pragma once

#include <vector>
#include "Block.h"
#include "Renderer.h"
#include "Player.h"

namespace gameplay {
    class Level {
    public:
        Level();
        ~Level();

        void Update(float dt);

        void Draw(core::Renderer* renderer);

        bool IntersectWithPlayer(const gameplay::Player& player);

    private:
        std::vector<gameplay::Block> m_blocks;

        const int m_ForwardBlockCount = 10;
    };
}
