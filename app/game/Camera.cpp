#include "Camera.h"

using core::Camera;
using core::Vec2;

namespace {
    float viewMatrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
    };

    float projectionMatrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
    };
}

void Camera::SetViewport(Vec2 size) {
    m_size = size;

    float aspectFix = ((float)m_size.m_y / (float)m_size.m_x);

    projectionMatrix[0] = 2.f / 100.f * aspectFix;
    projectionMatrix[5] = 2.f / 100.f; //Design height
}

Vec2 Camera::GetViewport() const {
    return m_size;
}

void Camera::SetOffset(Vec2 offset) {
    m_offset = offset;

    viewMatrix[12] = offset.m_x;
    viewMatrix[13] = offset.m_y;
}

Vec2 Camera::GetOffset() const {
    return m_offset;
}

const float* Camera::GetViewMatrix() const {
    return viewMatrix;
}

const float* Camera::GetProjMatrix() const {
    return projectionMatrix;
}