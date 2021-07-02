#ifndef MATH_H
#define MATH_H

#include <iostream>

namespace paint
{

    struct Index
    {
        unsigned int x;
        unsigned int y;
        unsigned int z;

        Index(unsigned int x, unsigned int y, unsigned int z) :
            x(x),
            y(y),
            z(z)
            {};
    };

    struct Vec2
    {
        float x;
        float y;

        Vec2() : x(0.0f), y(0.0f){};
        Vec2(float x, float y) : x(x), y(y){};

        //add another Vec2
        Vec2 operator+(const Vec2 &other) const
        {
            return {this->x + other.x, this->y + other.y};
        }

        //subtract vector
        Vec2 operator-(const Vec2 &other) const
        {
            return {this->x - other.x, this->y - other.y};
        }

        //multiple by scaler
        Vec2 operator*(float other) const
        {
            return {this->x * other, this->y * other};
        }

        //dot product
        float operator*(const Vec2 &other) const
        {
            return {this->x * other.x + this->y * other.y};
        }

        float magnitude() const {
            return sqrt(this->x * this->x + this->y * this->y);
        }
    };

    //print Vec2
    /*
std::ostream &operator<<(std::ostream &os, const Vec2& other)
{
    os << "[ " << other.x << std::endl;
    os << "  " << other.y << " ]";
    return os;
}*/

    struct Mat2
    {
        Vec2 leftCol;
        Vec2 rightCol;

        //add another Mat2
        Mat2 operator+(const Mat2 &other) const
        {
            return {this->leftCol + other.leftCol, this->rightCol + other.rightCol};
        }

        //sub another Mat2
        Mat2 operator-(const Mat2 &other) const
        {
            return {this->leftCol - other.leftCol, this->rightCol - other.rightCol};
        }

        //multiply by scalar
        Mat2 operator*(float other) const
        {
            return {this->leftCol * other, this->rightCol * other};
        }

        //multiply with Vec2
        Vec2 operator*(const Vec2 &other) const
        {
            return {this->leftCol.x * other.x + this->rightCol.x * other.y,
                    this->leftCol.y * other.x + this->rightCol.y * other.y};
        }

        //multiply with Mat2
        Mat2 operator*(const Mat2 &other) const
        {
            return {*this * other.leftCol, *this * other.rightCol};
        }
    };

    /*
std::ostream& operator<<(std::ostream& os, const Mat2& mat) {
    os << "[ " << mat.leftCol.x << "  " << mat.rightCol.x << std::endl;
    os << "  " << mat.leftCol.y << "  " << mat.rightCol.y << " ]";
    return os;
}*/

    struct Vec3
    {
        float x;
        float y;
        float z;

        //add another Vec3
        Vec3 operator+(const Vec3 &other) const
        {
            return {this->x + other.x, this->y + other.y, this->z + other.z};
        }

        //subtract Vec3
        Vec3 operator-(const Vec3 &other) const
        {
            return {this->x - other.x, this->y - other.y, this->z - other.z};
        }

        //multiple by scaler
        Vec3 operator*(float other) const
        {
            return {this->x * other, this->y * other, this->z * other};
        }

        //dot product
        float operator*(const Vec3 &other) const
        {
            return {this->x * other.x + this->y * other.y + this->z * other.z};
        }
    };

    /*
//print Vec3
std::ostream &operator<<(std::ostream &os, const Vec3& other)
{
    os << "[ " << other.x << std::endl;
    os << "  " << other.y << std::endl;
    os << "  " << other.z << " ]";
    return os;
}*/

    struct Mat3
    {
        Vec3 leftCol = {1.0f, 0.0f, 0.0f};
        Vec3 midCol = {0.0f, 1.0f, 0.0f};
        Vec3 rightCol = {0.0f, 0.0f, 1.0f};

        //add another Mat3
        Mat3 operator+(const Mat3 &other) const
        {
            return {this->leftCol + other.leftCol, this->midCol + other.midCol, this->rightCol + other.rightCol};
        }

        //sub another Mat3
        Mat3 operator-(const Mat3 &other) const
        {
            return {this->leftCol - other.leftCol, this->midCol - other.midCol, this->rightCol - other.rightCol};
        }

        //multiply by scalar
        Mat3 operator*(float other) const
        {
            return {this->leftCol * other, this->midCol * other, this->rightCol * other};
        }

        //multiply with Vec3
        Vec3 operator*(const Vec3 &other) const
        {
            return {this->leftCol.x * other.x + this->midCol.x * other.y + this->rightCol.x * other.z,
                    this->leftCol.y * other.x + this->midCol.y * other.y + this->rightCol.y * other.z,
                    this->leftCol.z * other.x + this->midCol.z * other.y + this->rightCol.z * other.z};
        }

        //multiply with Mat3
        Mat3 operator*(const Mat3 &other) const
        {
            return {*this * other.leftCol, *this * other.midCol, *this * other.rightCol};
        }

        //Matrix transforms
        //translate Mat3
        static Mat3 translate(Vec2 translation) {
            Mat3 m; //identity matrix
            m.rightCol.x = translation.x;
            m.rightCol.y = translation.y;
            return m;
        }
        //scale Mat3 (scale all translations too)
        static Mat3 scale(Vec2 scale) {
            Mat3 m; //identity matrix
            m.leftCol.x = scale.x;
            m.midCol.y = scale.y;
            return m;
        }
        //rotate Mat3 (rotate all translations too)
        static Mat3 rotate(float angle) {
            Mat3 m; //identity matrix
            //precalculate sine and cosine of angle
            float cosTheta = cos(angle);
            float sinTheta = sin(angle);
            //
            m.leftCol.x = cosTheta;
            m.leftCol.y = sinTheta;
            m.midCol.x = -sinTheta;
            m.midCol.y = cosTheta;
            return m;
        }
    };

} // namespace paint

#endif //MATH_H