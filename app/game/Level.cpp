#include "Level.h"

#include <cmath>
#include <cstdlib>

using namespace gameplay;

Level::Level() : m_randomDevice(m_seedDevice()) {
    Update(0);
}

void Level::Update(float) {
    std::uniform_int_distribution<int> uniform_dist(1, 3);

    //Initial fixed block
    if (m_blocks.empty())
        m_blocks.emplace_back(Block(0, -50, 15, 40));

    //Create new blocks
    while (m_blocks.size() < m_ForwardBlockCount) {
        static bool upBlock = false;
        auto& lastBlock = m_blocks.back();
        auto& lastMesh = lastBlock.GetMesh();

        int random = uniform_dist(m_randomDevice);
        float height = 30.f + 10.f * random;

        if (upBlock) {
            m_blocks.emplace_back(Block(lastMesh.GetPos().m_x + 50.f, 50.f - height, 15.f, height));
        } else {
            m_blocks.emplace_back(Block(lastMesh.GetPos().m_x + 50.f, -50.f, 15.f, height));
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

    try {

        auto &playerMesh = dynamic_cast<const CircleMesh &>(player.GetMesh());

        for (auto i = m_blocks.begin(), e = m_blocks.end(); i != e; ++i) {
            auto &block = *i;

            auto &blockMesh = dynamic_cast<const QuadMesh &>(block.GetMesh());

            core::Vec2 c = playerMesh.GetPos();

            auto quickIntersect = [&playerMesh](Vec2 c, Vec2 a, Vec2 b) -> bool {
                auto squareR = playerMesh.GetRadius() * playerMesh.GetRadius();
                const auto epsilon = std::numeric_limits<float>::epsilon();
                if (std::abs(a.m_x - b.m_x) < epsilon) {
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

                if (std::abs(a.m_y - b.m_y) < epsilon) {
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
            bool bc = quickIntersect(c, Vec2(pos.m_x, pos.m_y + size.m_y),
                                     Vec2(pos.m_x + size.m_x, pos.m_y + size.m_y));
            bool ad = quickIntersect(c, Vec2(pos.m_x, pos.m_y), Vec2(pos.m_x + size.m_x, pos.m_y));
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

    } catch (std::bad_cast&) {
        assert(false && "Mesh type of player or block mesh was changed!");
        return true;
    }

    return false;
}

void Level::CleanupBlocks(const gameplay::Player& player) {
    if (m_blocks.empty())
        return;

    /* As I see, there is a correct way to cleanup a block here...
     * Transform block coords by a camera matrix and remove blocks if their transformed coords are
     * out of [-1, 1] left border.
     * ...but I tried to avoid to write vector\matrix library from scratch and invented some sort of
     * heuristics: if our ball player avatar pass middle block, I remove most-left block and create
     * new in Update().
     */
    auto midBlockIterator = m_blocks.begin();
    std::advance(midBlockIterator, m_blocks.size() / 2);
    if (midBlockIterator == m_blocks.end()) {
        assert(false && "Malformed block queue in CleanupBlocks!");
        return;
    }

    auto& midBlock = *midBlockIterator;
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