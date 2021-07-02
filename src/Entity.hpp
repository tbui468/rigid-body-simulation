#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "Drawable.hpp"
#include "Math.hpp"
#include "Vertex.hpp"

namespace paint {

class Entity {
private:
    const std::vector<Vec2> m_vertexBuffer;
    const std::vector<Vec2> m_normalArray;
    const std::vector<Index> m_indexBuffer;
    std::vector<Vec2> m_tVertices;
    Vec2 m_scale;
    float m_angle;
    Vec2 m_translation;
    uint32_t m_color;
public:
    Entity(Vertex vertex) :
            m_vertexBuffer(vertex.vertexArray),
            m_normalArray(vertex.normalArray),
            m_indexBuffer(vertex.indexArray),
            m_scale({1.0f, 1.0f}),
            m_angle (0.0f),
            m_translation({0.0f, 0.0f}),
            m_color(0x000000ff)
            {};

    
    void transformVertices() {
        m_tVertices.clear();
        for(const Vec2& v : getVertexArray()) {
            Vec3 tv = {v.x, v.y, 1.0f};
            tv = Mat3::translate(m_translation) * Mat3::rotate(m_angle) * Mat3::scale(m_scale) * tv;
            m_tVertices.push_back({tv.x, tv.y});
        }
    }

    const std::vector<Vec2>& getTransformedArray() const {
        return m_tVertices;
    }

    //these are all the model transforms
    Drawable getDrawable() {
        Drawable d(m_vertexBuffer, m_indexBuffer, m_color);
        d.applyTransformation(Mat3::translate(m_translation) * Mat3::rotate(m_angle) * Mat3::scale(m_scale));
        return d;
    }

    void setScale(Vec2 scale) {
        m_scale.x = scale.x;
        m_scale.y = scale.y;
    }

    void scaleBy(Vec2 scale) {
        m_scale.x += scale.x;
        m_scale.y += scale.y;
    }

    void rotateTo(float angle) {
        m_angle = angle;
    }

    void rotateBy(float angle) {
        m_angle += angle;
    }

    void moveTo(Vec2 position) {
        m_translation.x = position.x;
        m_translation.y = position.y;
    }

    void moveBy(Vec2 translation) {
        m_translation.x += translation.x;
        m_translation.y += translation.y;
    }

    void setColor(uint32_t color) {
        m_color = color;
    }

    Vec2 getPosition() const {
        return m_translation;
    }

    float getAngle() const {
        return m_angle;
    }

    Vec2 getScale() const {
        return m_scale;
    }

    const std::vector<Vec2>& getVertexArray() const {
        return m_vertexBuffer;
    }

    const std::vector<Vec2>& getNormalArray() const {
        return m_normalArray;
    }

    const std::vector<Index>& getIndexArray() const {
        return m_indexBuffer;
    }

};


}


#endif //ENTITY_H