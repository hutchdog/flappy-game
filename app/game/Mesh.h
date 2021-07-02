#pragma once

#include <vector>

namespace core {
    //Lazy coding here, only required functions implemented!

    struct Vec2 {
        Vec2() = default;

        Vec2(float x, float y) : m_x(x), m_y(y) {

        }

        float m_x = 0;
        float m_y = 0;
    };

    class Mesh {
    public:
        Mesh() = default;
        Mesh(const Vec2& pos) {
            m_pos = pos;
        }
        virtual ~Mesh() = default;

        virtual const float* GetVertexData() const = 0;
        virtual const float* GetColorData() const = 0;
        virtual const int GetVertexCount() const = 0;

        void SetPos(const Vec2& pos) {
            m_pos = pos;
        }

        Vec2 GetPos() const {
            return m_pos;
        }

    protected:
        Vec2 m_pos;
    };

    class QuadMesh : public Mesh {
    public:
        QuadMesh(float x, float y, float width, float height) : Mesh(Vec2(x, y)) {
            m_vertexData = {
                    // X, Y, Z,
                    0,          0,          0,
                    0,          0 + height, 0,
                    0 + width,  0 + height, 0,
                    0,          0,          0,
                    0 + width,  0 + height, 0,
                    0 + width,  0,          0,
            };

            m_ColorData = {
                    // R, G, B, A
                    1.0f, 1.0f, 1.0f, 1.0f,
                    0.8f, 0.8f, 1.0f, 1.0f,
                    0.8f, 0.8f, 1.0f, 1.0f,
                    0.8f, 0.8f, 1.0f, 1.0f,
                    0.8f, 0.8f, 1.0f, 1.0f,
                    0.8f, 0.8f, 1.0f, 1.0f,
            };
        }

        const float* GetVertexData() const {
            return m_vertexData.data();
        };

        const float* GetColorData() const {
            return m_ColorData.data();
        }

        const int GetVertexCount() const {
            return 6;
        };

    private:
        std::vector<float> m_vertexData;
        std::vector<float> m_ColorData;
    };

    class CircleMesh : public Mesh {
    public:
        CircleMesh(float x, float y, float radius, float segments) {

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

                m_ColorData.push_back(0.8f);
                m_ColorData.push_back(0.8f);
                m_ColorData.push_back(1.0f);
                m_ColorData.push_back(1.0f);

                m_vertexData.push_back(tx1);
                m_vertexData.push_back(ty1);
                m_vertexData.push_back(0);

                m_ColorData.push_back(0.8f);
                m_ColorData.push_back(0.8f);
                m_ColorData.push_back(1.0f);
                m_ColorData.push_back(1.0f);

                m_vertexData.push_back(tx2);
                m_vertexData.push_back(ty2);
                m_vertexData.push_back(0);

                m_ColorData.push_back(0.8f);
                m_ColorData.push_back(0.8f);
                m_ColorData.push_back(1.0f);
                m_ColorData.push_back(1.0f);
            }
        }

        const float* GetVertexData() const {
            return m_vertexData.data();
        };

        const float* GetColorData() const {
            return m_ColorData.data();
        }

        const int GetVertexCount() const {
            return m_vertexData.size() / 3;
        };

    private:
        std::vector<float> m_vertexData;
        std::vector<float> m_ColorData;
    };
}
