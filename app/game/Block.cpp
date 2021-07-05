#include "Block.h"

using gameplay::Block;

Block::Block(float x, float y, float width, float height) : m_blockMesh(x, y, width, height) {
    m_blockMesh.SetPos(core::Vec2(x, y));
};

void Block::Draw(core::Renderer* renderer) {
    if (!renderer)
        return;

    renderer->Render(m_blockMesh);
}

const core::Mesh& Block::GetMesh() const {
    return m_blockMesh;
}
