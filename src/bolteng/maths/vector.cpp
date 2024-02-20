#include "vector.h"
#include <cmath>
#include <utility>

namespace bolt {
    namespace maths {

        Vec2::Vec2() : 
            x(0.0), 
            y(0.0) 
        {}

        Vec2::Vec2(float tx, float ty) : 
            x(tx), 
            y(ty) 
        {}

        Vec2::Vec2(Vec2 const &v) : 
            x(v.x),
            y(v.y)
        {}

        Vec2::Vec2(Vec2 &&v) :
            x(std::exchange(v.x, 0.0)),
            y(std::exchange(v.y, 0.0))
        {}

        void Vec2::normalise() {
            float sum = magnitude(*this);
            x /= sum;
            y /= sum;
        }

        Vec2 Vec2::operator -() const {
            return Vec2(-x, -y);
        }

        Vec2& Vec2::operator=(Vec2 const &v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        Vec2& Vec2::operator=(Vec2 &&v) {
            x = std::exchange(v.x, 0.0);
            y = std::exchange(v.y, 0.0);
            return *this;
        }

        Vec3::Vec3() : 
            x(0.0), 
            y(0.0), 
            z(0.0) 
        {}

        Vec3::Vec3(float tx, float ty, float tz) :
            x(tx),
            y(ty),
            z(tz)
        {}

        Vec3::Vec3(Vec3 const &v) : 
            x(v.x),
            y(v.y),
            z(v.z)
        {}

        Vec3::Vec3(Vec3 &&v) :
            x(std::exchange(v.x, 0.0)),
            y(std::exchange(v.y, 0.0)),
            z(std::exchange(v.z, 0.0))
        {}

        void Vec3::normalise() {
            float sum = magnitude(*this);
            x /= sum;
            y /= sum;
            z /= sum;
        }

        Vec3 Vec3::operator -() const {
            return Vec3(-x, -y, -z);
        }

        Vec3& Vec3::operator=(Vec3 const &v) {
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }

        Vec3& Vec3::operator=(Vec3 &&v) {
            x = std::exchange(v.x, 0.0);
            y = std::exchange(v.y, 0.0);
            z = std::exchange(v.z, 0.0);
            return *this;
        }

        float magnitude(Vec2 const &v) {
            return std::sqrt(v.x * v.x + v.y * v.y);
        }

        float magnitude(Vec3 const &v) {
            return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        }

        Vec3 cross_product(Vec3 const &v1, Vec3 const &v2) {
            float x = v1.y * v2.z - v1.z * v2.y;
            float y = v1.z * v2.x - v1.x * v2.z;
            float z = v1.x * v2.y - v1.y * v2.x;
            return Vec3(x, y, z);
        }

        std::ostream& operator<< (std::ostream& os, bolt::maths::Vec2 const &v) {
            os << "[" << v.x << ", " << v.y << "]";
            return os;
        }

        std::ostream& operator<< (std::ostream& os, bolt::maths::Vec3 const &v) {
            os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
            return os;
        }
    }
}


