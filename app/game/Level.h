#pragma once

#include <vector>
#include "Block.h"

namespace gameplay {
    class Level {
    public:
        Level();
        ~Level();

        void Update(float dt);

    private:
        std::vector<gameplay::Block> m_blocks;
    };
}
