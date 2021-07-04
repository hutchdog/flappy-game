#include "Level.h"

#include <cmath>

using namespace gameplay;

Level::Level() {
    Update(0);
}

Level::~Level() {

}

void Level::Update(float dt) {
    if (m_blocks.empty()) {
        m_blocks.emplace_back(Block(0, -50, 10, 50));
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

        auto intersectWithLine = [playerMesh](Vec2 c, Vec2 a, Vec2 b) -> bool {
            Vec2 tx;
            if (a.m_x == b.m_x) {
                tx.m_x = a.m_x;
                tx.m_y = c.m_y;
            }

            if (a.m_y == b.m_y) {
                tx.m_x = c.m_x;
                tx.m_y = a.m_y;
            }

            Vec2 delta(tx.m_x - c.m_x, tx.m_y - c.m_y);
            float dx2 = powf(delta.m_x, 2);
            float dy2 = powf(delta.m_y, 2);
            float length = sqrtf(dx2 + dy2);
            return length <= playerMesh.GetRadius();
        };

        core::Vec2 pos = blockMesh.GetPos();
        core::Vec2 size = blockMesh.GetSize();

        //Intersect AB & BC - do not need to check other lines by design
        bool ab = intersectWithLine(c, pos, Vec2(pos.m_x, pos.m_y + size.m_y));
        bool bc = intersectWithLine(c, pos, Vec2(pos.m_x + size.m_x, pos.m_y + size.m_y));
        if (ab || bc) {
            return true;
        }
    }

    return false;
}