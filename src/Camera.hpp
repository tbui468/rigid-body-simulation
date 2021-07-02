#ifndef CAMERA_H
#define CAMERA_H

#include "CoordinateTransformer.hpp"
#include "Drawable.hpp"
#include "Math.hpp"

namespace rbs {

class Camera {
private:
    CoordinateTransformer m_CT;
    Vec2 m_translation;
    Vec2 m_scale;
    float m_angle;
public:
    Camera(CoordinateTransformer ct) : m_CT(ct), m_translation({0.0f, 0.0f}), m_scale({1.0f, 1.0f}), m_angle(0.0f) {};

    //view transforms
    void draw(Drawable&& drawable) {
        drawable.applyTransformation(Mat3::rotate(-m_angle) * Mat3::scale(m_scale) * Mat3::translate(m_translation * (-1)));
        m_CT.draw(drawable); //passes to coordinate transform
    }

    void scaleTo(float zoom) {
        m_scale.x = zoom;
        m_scale.y = zoom;
    }

    void scaleBy(float zoom) {
        m_scale.x += zoom;
        m_scale.y += zoom;
    }

    void moveTo(Vec2 location) {
        m_translation.x = location.x;
        m_translation.y = location.y;
    }

    //translate camera taking camera rotation into account
    void moveBy(Vec2 distance) {
        float cosTheta = cos(m_angle);
        float sinTheta = sin(m_angle);
        m_translation.x += distance.x * cosTheta -sinTheta * distance.y;
        m_translation.y += distance.y * cosTheta + sinTheta * distance.x;
    }

    void rotateBy(float angle) {
        m_angle += angle;
    }
};


}

#endif //CAMERA_H
