#include "Player.h"

using gameplay::Player;

Player::Player() : m_playerMesh(-40, 0, 10, 24) {

}
Player::~Player() {};

void Player::Update(float dt) {
    auto currentPos = m_playerMesh.GetPos();
    currentPos.m_x += 6 * dt;

    m_horizontalSpeed -= 0.5f * dt;
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
    m_horizontalSpeed = 0.7f;
}