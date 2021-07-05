#pragma once

#include <vector>

namespace core {
    //Lazy coding here, only required functions are implemented!

    struct Vec2 {
        Vec2() = default;
        Vec2(float x, float y) : m_x(x), m_y(y) {}

        float m_x = 0;
        float m_y = 0;
    };

    class Mesh {
    public:
        Mesh() = default;
        Mesh(const Vec2& pos);
        virtual ~Mesh() = default;

        virtual const float* GetVertexData() const = 0;
        virtual const float* GetColorData() const = 0;
        virtual const int GetVertexCount() const = 0;

        void SetPos(const Vec2& pos);

        Vec2 GetPos() const;

        virtual Vec2 GetSize() const = 0;

    protected:
        Vec2 m_pos;
    };

    class QuadMesh : public Mesh {
    public:
        QuadMesh(float x, float y, float width, float height);

        const float* GetVertexData() const override;

        const float* GetColorData() const override;

        const int GetVertexCount() const override;

        Vec2 GetSize() const;

    private:
        std::vector<float> m_vertexData;
        std::vector<float> m_ColorData;

        Vec2 m_size;
    };

    class CircleMesh : public Mesh {
    public:
        CircleMesh(float x, float y, float radius, float segments);

        const float* GetVertexData() const override;

        const float* GetColorData() const override;

        const int GetVertexCount() const override;

        float GetRadius() const;

        Vec2 GetSize() const override;

    private:
        std::vector<float> m_vertexData;
        std::vector<float> m_ColorData;

        float m_radius;
    };
}
