#include "Player.h"
#include "Common.h"

using gameplay::Player;
using namespace common;

Player::Player() : m_playerMesh(PlayerStartPos.m_x, PlayerStartPos.m_y, PlayerSize, 24) {

}

void Player::Update(float dt) {
    auto currentPos = m_playerMesh.GetPos();
    currentPos.m_x += PlayerSpeed * dt;

    m_horizontalSpeed -= PlayerGravity * dt;
    currentPos.m_y += m_horizontalSpeed;

    m_playerMesh.SetPos(currentPos);
};

void Player::Draw(core::Renderer* renderer) {
    if (!renderer)
        return;

    renderer->Render(m_playerMesh);
}

core::Mesh& Player::GetMesh() {
    return m_playerMesh;
}

const core::Mesh& Player::GetMesh() const {
    return m_playerMesh;
}

void Player::Touch() {
    m_horizontalSpeed = PlayerBoostOnTouch;
}
