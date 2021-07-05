#pragma once

#include <list>
#include <random>

#include "Block.h"
#include "Renderer.h"
#include "Player.h"

namespace gameplay {
    class Level {
    public:
        Level();
        ~Level() = default;

        void Update(float dt);

        void Draw(core::Renderer* renderer);

        bool IntersectWithPlayer(const gameplay::Player& player);
        void CleanupBlocks(const gameplay::Player& player);
        void Reset();

    private:
        std::list<gameplay::Block> m_blocks;

        std::random_device m_seedDevice;
        std::mt19937 m_randomDevice;

        const int m_ForwardBlockCount = 10;
    };
}
