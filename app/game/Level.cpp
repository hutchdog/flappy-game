#include "Level.h"

#include <cmath>
#include <cstdlib>


using namespace gameplay;

Level::Level() {
    Update(0);
}

Level::~Level() {

}

void Level::Update(float dt) {
    std::uniform_int_distribution<int> uniform_dist(1, 3);

    //Initial block
    if (m_blocks.empty())
        m_blocks.emplace_back(Block(0, -50, 15, 40));

    //Create new blocks
    while (m_blocks.size() < m_ForwardBlockCount) {
        static bool upBlock = false;
        auto& lastBlock = m_blocks.back();

        int random = uniform_dist(m_randomDevice);
        int height = 30 + 10 * random;

        if (upBlock) {
            m_blocks.push_back(Block(m_blocks.back().GetMesh().GetPos().m_x + 50, 50 - height, 15, height));
        } else {
            m_blocks.push_back(Block(m_blocks.back().GetMesh().GetPos().m_x + 50, -50, 15, height));
        }

        upBlock = !upBlock;
    }
}

void Level::Draw(core::Renderer *renderer) {
    if (!renderer)
        return;

    std::for_each(m_blocks.begin(), m_blocks.end(), [renderer](Block& block) {
        block.Draw(renderer);
    });
}

bool Level::IntersectWithPlayer(const gameplay::Player& player) {
    using namespace core;

    auto& playerMesh = static_cast<const CircleMesh&>(player.GetMesh());

    for(auto i = m_blocks.begin(), e = m_blocks.end(); i != e; ++i){
        auto& block = *i;

        auto& blockMesh = static_cast<const QuadMesh&>(block.GetMesh());

        core::Vec2 c = playerMesh.GetPos();

        auto quickIntersect = [&playerMesh](Vec2 c, Vec2 a, Vec2 b) -> bool {
            auto squareR = playerMesh.GetRadius() * playerMesh.GetRadius();
            if (a.m_x == b.m_x) {
                auto squareX = (a.m_x - c.m_x) * (a.m_x - c.m_x);
                if (squareX > squareR)
                    return false;

                auto intersectY = sqrtf(squareR - squareX);

                auto min = std::min(a.m_y, b.m_y);
                auto max = std::max(a.m_y, b.m_y);

                if ((c.m_y + intersectY) >= min && (c.m_y + intersectY) <= max)
                    return true;

                if ((c.m_y - intersectY) >= min && (c.m_y + intersectY) <= max)
                    return true;
            }

            if (a.m_y == b.m_y) {
                auto squareY = (a.m_y - c.m_y) * (a.m_y - c.m_y);
                auto intersectX = sqrtf(squareR - squareY);
                if (squareY > squareR)
                    return false;

                auto min = std::min(a.m_x, b.m_x);
                auto max = std::max(a.m_x, b.m_x);

                if ((c.m_x + intersectX) >= min && (c.m_x + intersectX) <= max)
                    return true;

                if ((c.m_x - intersectX) >= min && (c.m_x - intersectX) <= max)
                    return true;
            }
            return false;
        };

        core::Vec2 pos = blockMesh.GetPos();
        core::Vec2 size = blockMesh.GetSize();

        //Micro-optimization, intersect AB & BC & AD - do not need to check back lines by design
        bool ab = quickIntersect(c, pos, Vec2(pos.m_x, pos.m_y + size.m_y));
        bool bc = quickIntersect(c, Vec2(pos.m_x, pos.m_y + size.m_y) , Vec2(pos.m_x + size.m_x, pos.m_y + size.m_y));
        bool ad = quickIntersect(c, Vec2(pos.m_x, pos.m_y) , Vec2(pos.m_x + size.m_x, pos.m_y));
        if (ab || bc || ad) {
            return true;
        }
    }

    //TODO: Design height from constants
    //Check for floor-ceiling intersections
    if (playerMesh.GetPos().m_y - playerMesh.GetRadius() <= -50)
        return true;

    if (playerMesh.GetPos().m_y + playerMesh.GetRadius() >= 50)
        return true;

    return false;
}

void Level::CleanupBlocks(const gameplay::Player& player) {
    if (m_blocks.empty())
        return;

    auto& midBlock = *(m_blocks.begin() + 5);
    auto& blockMesh = midBlock.GetMesh();

    float eraseCoordinate = blockMesh.GetPos().m_x + blockMesh.GetSize().m_x;
    if (eraseCoordinate <= player.GetMesh().GetPos().m_x) {
        m_blocks.erase(m_blocks.begin());
    }
}

void Level::Reset() {
    m_blocks.clear();
    Update(0);
}