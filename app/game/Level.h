#pragma once

#include <vector>
#include "Block.h"
#include "Renderer.h"

namespace gameplay {
    class Level {
    public:
        Level();
        ~Level();

        void Update(float dt);

        void Draw(core::Renderer* renderer);

    private:
        std::vector<gameplay::Block> m_blocks;

        const int m_ForwardBlockCount = 10;
    };
}
