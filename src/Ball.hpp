#ifndef BALL_H
#define BALL_H

#include "Math.hpp"
#include "Drawable.hpp"
#include "Entity.hpp"
#include "Paddle.hpp"
#include "Shape.hpp"
#include <math.h>


namespace rbs {


struct LinearCoefficients {
    float a;
    float b;
    float c;
};

class Ball : public Entity{
private:
    inline static const float g = -0.03f;
    float m_radius;
    Vec2 m_velocity;
public:
    Ball(float radius, Vec2 velocity) : Entity(Shape::makeCircle(radius)),
                                        m_radius (radius),
                                        m_velocity (velocity) {};

    void update(float deltaTime) {
        m_velocity.y += g;
        m_velocity.x *= 0.99f;
        Vec2 pos = getPosition();
        moveBy(m_velocity * deltaTime);
        if(pos.y > 300.0f) {
            moveTo({pos.x, -300.0f});
        }
        if(pos.x < -400.0f) {
            moveTo({400.0f, pos.y});
        }
        if(pos.x > 400.0f) {
            moveTo({-400.0f, pos.y});
        }
        if(pos.y < -300.0f) {
            float r = ((float)rand())/RAND_MAX;
            r -= 0.5f;
            moveTo({150.0f * r, 300.0f});
            setVelocity({0.0f, 0.0f});
        }

    }

    void setVelocity(Vec2 velocity) {
        m_velocity.x = velocity.x;
        m_velocity.y = velocity.y;
    }

    Vec2 getVelocity() const {
        return m_velocity;
    }

    float getRadius() const {
        return m_radius;
    }

    std::optional<Vec2> entityCollision(const Entity& entity) {
        std::vector<Vec2> vertexPos = entity.getTransformedArray();
        std::vector<Index> indexArray = entity.getIndexArray();
        for(const Index& index: indexArray) {
            Vec2 start = vertexPos.at(index.x);
            Vec2 end = vertexPos.at(index.y);
            if(lineCollision(start, end)) {
                std::vector<Vec2> normalArray = entity.getNormalArray();        
                Vec2 normal2 = normalArray.at(index.z);
                Vec3 normal3 = {normal2.x, normal2.y, 1.0f};
                normal3 = Mat3::rotate(entity.getAngle()) * normal3;
                //rotate normal
                return std::optional<Vec2>({normal3.x, normal3.y});
            }
        }
        return std::nullopt;
    }

    //check collision with line
    bool lineCollision(Vec2 start, Vec2 end)
    {
        //check colllision with line < r
        LinearCoefficients lc = getCoefficients(start, end);
        float dis = pointLineDistance(getPosition(), lc);
        //check collision with perp. line  < s + r
        Vec2 mid = midpoint(start, end);
        LinearCoefficients plc = getPerpCoefficients(lc, mid);
        float dis2 = pointLineDistance(getPosition(), plc);
        float s = distance(mid, start);

        return dis < getRadius() && dis2 < (getRadius() + s);
    }

    //add paddle spin force to ball velocity
    void bounce(const Paddle& paddle, Vec2 normal)
    {
        //set ball to outside of paddle if necessary
        //THis fixed everything!!!!!!!
        while(entityCollision(paddle)) {
            moveBy(normal);
        }

        Mat2 rot = {{0.0f, 1.0f}, {-1.0f, 0.0f}};
        Vec2 side = rot * normal;

        side = side * (1.0f/side.magnitude());
        Mat2 rot180 = {{-1.0f, 0.0f},{0.0f, -1.0f}};
        Vec2 intersection = getPosition() + (rot180 * normal) * m_radius; 

        Vec2 radius = intersection - paddle.getPosition();
        Vec2 rHat = radius * (1.0f/radius.magnitude());
        rHat = paddle.getAngularSpeed() > 0.000f ? rot * rHat : rot *  rHat;
        float rMag = radius.magnitude() * paddle.getAngularSpeed();
        Vec2 rotVector = rHat * rMag;

        Vec2 term1 = side * ((rotVector + getVelocity()) * side) * 0.5f; //side velocity
        Vec2 term2 = normal * ((rotVector - getVelocity()) * normal) * 0.5f; //perpendicular velocity

        if(term2 * normal < 0 || (term2 * normal > 0 && term2.magnitude() < rotVector * normal)) {
            term2 = normal * (rotVector * normal);
        }

        setVelocity({term1 + term2});
    }

private:

    //distance between two points
    float distance(Vec2 start, Vec2 end)
    {
        float xs = (end.x - start.x) * (end.x - start.x);
        float ys = (end.y - start.y) * (end.y - start.y);
        return sqrt(xs + ys);
    }

    //midpoint between two points
    Vec2 midpoint(Vec2 start, Vec2 end)
    {
        float xAv = (start.x + end.x) / 2.0f;
        float yAv = (start.y + end.y) / 2.0f;
        return {xAv, yAv};
    }

    //coefficients of line described by two points
    LinearCoefficients getCoefficients(Vec2 start, Vec2 end)
    {
        float a = start.y - end.y;
        float b = end.x - start.x;
        float c = start.x * end.y - end.x * start.y;
        return {a, b, c};
    }

    //get linear coefficients of line perpendicular to give line, that passes through 'point'
    LinearCoefficients getPerpCoefficients(LinearCoefficients lc, Vec2 point)
    {
        float a = lc.b;
        float b = -lc.a;
        float c = lc.a * point.y - lc.b * point.x;

        return {a, b, c};
    }

    //distance between a point and line described by two points
    float pointLineDistance(Vec2 pos, LinearCoefficients lc)
    {
        float num = abs(lc.a * pos.x + lc.b * pos.y + lc.c);
        float den = sqrt(lc.a * lc.a + lc.b * lc.b);
        return num / den;
    }

};

} // namespace paint

#endif //BALL_H
