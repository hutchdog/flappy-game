#include "Camera.h"
#include "Common.h"

using core::Camera;
using core::Vec2;

void Camera::SetViewport(Vec2 size) {
    m_size = size;

    //Sanity check
    if (size.m_x == 0 || size.m_y == 0) {
        assert(false && "Viewport sizes set incorrect!");
        return;
    }

    float aspectFix = ((float)m_size.m_y / (float)m_size.m_x);

    m_projectionMatrix[0] = 2.f / common::ScreenDesignHeight * aspectFix;
    m_projectionMatrix[5] = 2.f / common::ScreenDesignHeight;
}

Vec2 Camera::GetViewport() const {
    return m_size;
}

void Camera::SetOffset(Vec2 offset) {
    m_offset = offset;

    m_viewMatrix[12] = offset.m_x;
    m_viewMatrix[13] = offset.m_y;
}

Vec2 Camera::GetOffset() const {
    return m_offset;
}

const float* Camera::GetViewMatrix() const {
    return m_viewMatrix;
}

const float* Camera::GetProjMatrix() const {
    return m_projectionMatrix;
}