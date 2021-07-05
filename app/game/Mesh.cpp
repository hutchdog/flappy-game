#include "Mesh.h"

using core::Mesh;
using core::CircleMesh;
using core::QuadMesh;
using core::Vec2;

Mesh::Mesh(const Vec2& pos) : m_pos(pos) {
}

void Mesh::SetPos(const Vec2& pos) {
    m_pos = pos;
}

Vec2 Mesh::GetPos() const {
    return m_pos;
}

QuadMesh::QuadMesh(float x, float y, float width, float height) : Mesh(Vec2(x, y)), m_size(width, height) {
    m_vertexData = {
            // X, Y, Z,
            0, 0, 0,
            0, 0 + height, 0,
            0 + width, 0 + height, 0,
            0, 0, 0,
            0 + width, 0 + height, 0,
            0 + width, 0, 0,
    };

    m_ColorData = {
            // R, G, B, A
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
    };
}

const float* QuadMesh::GetVertexData() const {
    return m_vertexData.data();
}

const float* QuadMesh::GetColorData() const {
    return m_ColorData.data();
}

const int QuadMesh::GetVertexCount() const {
    return m_vertexData.size();
}

Vec2 QuadMesh::GetSize() const {
    return m_size;
}

CircleMesh::CircleMesh(float x, float y, float radius, float segments) : Mesh(Vec2(x, y)), m_radius(radius) {

    float segment = M_PI * 2 / segments;
    for (int i = 0; i < segments; ++i) {
        float angle1 = segment * i;
        float tx1 = radius * cosf(angle1);
        float ty1 = radius * sinf(angle1);

        float angle2 = segment * (i + 1);
        float tx2 = radius * cosf(angle2);
        float ty2 = radius * sinf(angle2);

        m_vertexData.push_back(0);
        m_vertexData.push_back(0);
        m_vertexData.push_back(0);

        m_ColorData.push_back(0.f);
        m_ColorData.push_back(0.f);
        m_ColorData.push_back(1.0f);
        m_ColorData.push_back(1.0f);

        m_vertexData.push_back(tx1);
        m_vertexData.push_back(ty1);
        m_vertexData.push_back(0);

        m_ColorData.push_back(0.f);
        m_ColorData.push_back(0.f);
        m_ColorData.push_back(1.0f);
        m_ColorData.push_back(1.0f);

        m_vertexData.push_back(tx2);
        m_vertexData.push_back(ty2);
        m_vertexData.push_back(0);

        m_ColorData.push_back(0.f);
        m_ColorData.push_back(0.f);
        m_ColorData.push_back(1.0f);
        m_ColorData.push_back(1.0f);
    }
}

const float* CircleMesh::GetVertexData() const {
    return m_vertexData.data();
};

const float* CircleMesh::GetColorData() const {
    return m_ColorData.data();
}

const int CircleMesh::GetVertexCount() const {
    return m_vertexData.size();
};

float CircleMesh::GetRadius() const {
    return m_radius;
}

Vec2 CircleMesh::GetSize() const {
    return Vec2(m_radius, m_radius);
}
