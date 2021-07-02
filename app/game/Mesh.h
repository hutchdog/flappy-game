#pragma once

#include <vector>

namespace core {
    class Mesh {
    public:
        Mesh() = default;
        virtual ~Mesh() = default;

        virtual float* GetVertexData() = 0;
        virtual float* GetColorData() = 0;
        virtual int GetVertexCount() = 0;
    };

    class QuadMesh : public Mesh {
    public:
        QuadMesh(float x, float y, float width, float height) {
            m_vertexData = {
                    // X, Y, Z,
                    x,          y,          0,
                    x,          y + height, 0,
                    x + width,  y + height, 0,
                    x,          y,          0,
                    x + width,  y + height, 0,
                    x + width,  y,          0,
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

        float* GetVertexData() {
            return m_vertexData.data();
        };

        float* GetColorData() {
            return m_ColorData.data();
        }

        int GetVertexCount() {
            return 6;
        };

    private:
        std::vector<float> m_vertexData;
        std::vector<float> m_ColorData;
    };
}
