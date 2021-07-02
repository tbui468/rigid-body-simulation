#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.hpp"
#include "Math.hpp"
#include "Shape.hpp"

namespace paint{

class Paddle : public Entity {
private:
    float m_width;
    float m_height;
    float m_angularSpeed;
public:

    Paddle(float width, float height, float angularSpeed): Entity(Shape::makeStar(60.0f, 60.0f, 3)), m_width(width), m_height(height), m_angularSpeed(angularSpeed) {};
    //Paddle(float width, float height, float angularSpeed): Entity(Shape::makeTriangle(60.0f)), m_width(width), m_height(height), m_angularSpeed(angularSpeed) {};
//Paddle(float width, float height, float angularSpeed): Entity(Shape::makeRectangle(width, height)), m_width(width), m_height(height), m_angularSpeed(angularSpeed) {};
    float getWidth() const {
        return m_width;
    }
    float getHeight() const {
        return m_height;
    }
    void update() {
        rotateBy(m_angularSpeed);
    }

    float getAngularSpeed() const {
        return m_angularSpeed;
    }
};


}

#endif //PADDLE_H
