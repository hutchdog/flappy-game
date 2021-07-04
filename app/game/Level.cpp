#include "Level.h"

using namespace gameplay;

Level::Level() {

}

Level::~Level() {

}

void Level::Update(float dt) {
    if (m_blocks.empty()) {
        m_blocks.emplace_back(Block(50, 0, 10, 50));
    }
}

void Level::Draw(core::Renderer *renderer) {
    if (!renderer)
        return;

    std::for_each(m_blocks.begin(), m_blocks.end(), [renderer](Block& block) {
        block.Draw(renderer);
    });
}