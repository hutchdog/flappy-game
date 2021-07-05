#pragma once

#include <vector>
#include <random>

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
        void CleanupBlocks(const gameplay::Player& player);
        void Reset();

    private:
        std::vector<gameplay::Block> m_blocks;

        std::default_random_engine m_randomDevice;

        const int m_ForwardBlockCount = 10;
    };
}
