#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.hpp"
#include "Math.hpp"
#include "Vertex.hpp"

namespace rbs{

class Paddle : public Entity {
public:
    float m_width;
    float m_height;
    float m_angularSpeed;
public:

    Paddle(Vertex shape, float width, float height, float angularSpeed): Entity(shape), m_width(width), m_height(height), m_angularSpeed(angularSpeed) {};

    //should move this into entity (and do the same thing for the balls)
    void update(float deltatime) {
        rotateBy(m_angularSpeed * deltatime);
    }
};


}

#endif //PADDLE_H
