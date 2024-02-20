#ifndef BOLTENG_VECTOR_H
#define BOLTENG_VECTOR_H

#include <ostream>
#include <type_traits>

namespace bolt {
    namespace maths {

        struct Vec2 {
            float x;
            float y;

            Vec2();
            Vec2(float tx, float ty);
            Vec2(Vec2 const &v);
            Vec2(Vec2 &&v);

            void normalise();

            Vec2 operator -() const;
            Vec2& operator=(Vec2 const &v);
            Vec2& operator=(Vec2 &&v);

            friend std::ostream& operator<< (std::ostream& stream, Vec2 const &v);
        };

        struct Vec3 {
            float x;
            float y;
            float z;

            Vec3();
            Vec3(float tx, float ty, float tz);
            Vec3(Vec3 const &v);
            Vec3(Vec3 &&v);

            void normalise();

            Vec3 operator -() const;
            Vec3& operator=(Vec3 const &v);
            Vec3& operator=(Vec3 &&v);

            friend std::ostream& operator<< (std::ostream& stream, Vec3 const &v);
        };

        float magnitude(Vec2 const &v);
        float magnitude(Vec3 const &v);

        Vec3 cross_product(Vec3 const &v1, Vec3 const &v2);
    }
}
#endif // BOLTENG
