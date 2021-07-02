#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <math.h>
#include <vector>
#include "Math.hpp"
#include "Screen.hpp"


namespace paint {

//stack all translations and scaling 
class Drawable {
private:
    const std::vector<Vec2>* m_vertexBuffer;
    const std::vector<Index>* m_indexBuffer;
    Mat3 m_transformation;
    Uint32 m_color;
public:
    Drawable(const std::vector<Vec2>& vertexBuffer, const std::vector<Index>& indexBuffer, uint32_t color):  
                m_vertexBuffer(&vertexBuffer),
                m_indexBuffer(&indexBuffer),
                m_color (color)
    {};

    void scale(Vec2 scale) {
        m_transformation = Mat3::scale(scale) * m_transformation;
    }

    void rotate(float angle) {
        m_transformation = Mat3::rotate(angle) * m_transformation;
    }

    void translate(Vec2 vec) {
        m_transformation = Mat3::translate(vec) * m_transformation;
    }

    void applyTransformation(Mat3 transformation) {
        m_transformation = transformation * m_transformation;
    }

    void render(Screen &screen)
    {
        //perform transformation here, and pass reference to transformed vertex buffer
        //CAN I USE THE GPU (like the CUDA API) here for faster parallel computations??????
        std::vector<Vec2> transformedModel;
        for (const Vec2& v : *m_vertexBuffer)
        {
            Vec3 v3 = {v.x, v.y, 1.0f}; //change Vec2 to Vec3
            v3 = m_transformation * v3;
            transformedModel.emplace_back(v3.x, v3.y);
        }
        screen.drawPolygon(transformedModel, *m_indexBuffer);
    }
};

} // namespace paint

#endif //DRAWABLE_H