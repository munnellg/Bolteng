#ifndef BOLTENG_VECTOR_H
#define BOLTENG_VECTOR_H

#include "common.h"

#include <ostream>

namespace bolt {
    namespace maths {
        struct Vec2 {
            union { Real x; Real r; Real s; };
            union { Real y; Real g; Real t; };

            Vec2();
            Vec2(Real tx, Real ty);
            Vec2(Vec2 const &v);
            Vec2(Vec2 &&v);

            void normalise();
            void zero();

            // copying / moving
            Vec2& operator  = (Vec2 const &v);
            Vec2& operator  = (Vec2 &&v);

            // equivalence comparisons
            bool operator == (Vec2 const &v) const;
            bool operator != (Vec2 const &v) const;

            // basic vector operations -- note piecewise vector multiplication and division
            Vec2  operator  - () const;
            Vec2  operator  + (Vec2 const &v) const;
            Vec2  operator  - (Vec2 const &v) const;
            Vec2  operator  * (Vec2 const &v) const;
            Vec2  operator  / (Vec2 const &v) const;
            Vec2& operator += (Vec2 const &v);
            Vec2& operator -= (Vec2 const &v);
            Vec2& operator *= (Vec2 const &v);
            Vec2& operator /= (Vec2 const &v);

            // basic scalar operations -- note piecewise addition and subtraction
            Vec2  operator  + (Real const k) const;
            Vec2  operator  - (Real const k) const;
            Vec2  operator  * (Real const k) const;
            Vec2  operator  / (Real const k) const;
            Vec2& operator += (Real const k);
            Vec2& operator -= (Real const k);
            Vec2& operator *= (Real const k);
            Vec2& operator /= (Real const k);

            // needed for symmetry when multiplying -- scalar on the left
            friend Vec2 operator+ (Real const k, Vec2 const &v);
            friend Vec2 operator- (Real const k, Vec2 const &v);
            friend Vec2 operator* (Real const k, Vec2 const &v);
            friend Vec2 operator/ (Real const k, Vec2 const &v);

            // input / output
            friend std::ostream& operator<< (std::ostream& stream, Vec2 const &v);
        };

        struct Vec3 {
            union { Real x; Real r; Real s; };
            union { Real y; Real g; Real t; };
            union { Real z; Real b; Real p; };

            Vec3();
            Vec3(Real tx, Real ty, Real tz);
            Vec3(Vec3 const &v);
            Vec3(Vec3 &&v);

            void normalise();
            void zero();

            // copying / moving
            Vec3& operator  = (Vec3 const &v);
            Vec3& operator  = (Vec3 &&v);

            // equivalence comparisons
            bool operator == (Vec3 const &v) const;
            bool operator != (Vec3 const &v) const;

            // basic vector operations -- note piecewise vector multiplication and division
            Vec3  operator  - () const;
            Vec3  operator  + (Vec3 const &v) const;
            Vec3  operator  - (Vec3 const &v) const;
            Vec3  operator  * (Vec3 const &v) const;
            Vec3  operator  / (Vec3 const &v) const;
            Vec3& operator += (Vec3 const &v);
            Vec3& operator -= (Vec3 const &v);
            Vec3& operator *= (Vec3 const &v);
            Vec3& operator /= (Vec3 const &v);

            // basic scalar operations -- note piecewise addition and subtraction
            Vec3  operator  + (Real const k) const;
            Vec3  operator  - (Real const k) const;
            Vec3  operator  * (Real const k) const;
            Vec3  operator  / (Real const k) const;
            Vec3& operator += (Real const k);
            Vec3& operator -= (Real const k);
            Vec3& operator *= (Real const k);
            Vec3& operator /= (Real const k);

            // needed for symmetry when multiplying -- scalar on the left
            friend Vec3 operator+ (Real const k, Vec3 const &v);
            friend Vec3 operator- (Real const k, Vec3 const &v);
            friend Vec3 operator* (Real const k, Vec3 const &v);
            friend Vec3 operator/ (Real const k, Vec3 const &v);

            // input / output
            friend std::ostream& operator<< (std::ostream& stream, Vec3 const &v);
        };

        struct Vec4 {
            union { Real x; Real r; Real s; };
            union { Real y; Real g; Real t; };
            union { Real z; Real b; Real p; };
            union { Real w; Real a; Real q; };

            Vec4();
            Vec4(Real tx, Real ty, Real tz, Real tw);
            Vec4(Vec4 const &v);
            Vec4(Vec4 &&v);

            void normalise();
            void zero();

            // copying / moving
            Vec4& operator  = (Vec4 const &v);
            Vec4& operator  = (Vec4 &&v);

            // equivalence comparisons
            bool operator == (Vec4 const &v) const;
            bool operator != (Vec4 const &v) const;

            // basic vector operations -- note piecewise vector multiplication and division
            Vec4  operator  - () const;
            Vec4  operator  + (Vec4 const &v) const;
            Vec4  operator  - (Vec4 const &v) const;
            Vec4  operator  * (Vec4 const &v) const;
            Vec4  operator  / (Vec4 const &v) const;
            Vec4& operator += (Vec4 const &v);
            Vec4& operator -= (Vec4 const &v);
            Vec4& operator *= (Vec4 const &v);
            Vec4& operator /= (Vec4 const &v);

            // basic scalar operations -- note piecewise addition and subtraction
            Vec4  operator  + (Real const k) const;
            Vec4  operator  - (Real const k) const;
            Vec4  operator  * (Real const k) const;
            Vec4  operator  / (Real const k) const;
            Vec4& operator += (Real const k);
            Vec4& operator -= (Real const k);
            Vec4& operator *= (Real const k);
            Vec4& operator /= (Real const k);

            // needed for symmetry when multiplying -- scalar on the left
            friend Vec4 operator+ (Real const k, Vec4 const &v);
            friend Vec4 operator- (Real const k, Vec4 const &v);
            friend Vec4 operator* (Real const k, Vec4 const &v);
            friend Vec4 operator/ (Real const k, Vec4 const &v);

            // input / output
            friend std::ostream& operator<< (std::ostream& stream, Vec4 const &v);
        };

        [[nodiscard]] Real magnitude(Vec2 const &v);
        [[nodiscard]] Real magnitude(Vec3 const &v);
        [[nodiscard]] Real magnitude(Vec4 const &v);

        [[nodiscard]] Real dot_product(Vec2 const &v1, Vec2 const &v2);
        [[nodiscard]] Real dot_product(Vec3 const &v1, Vec3 const &v2);
        [[nodiscard]] Real dot_product(Vec4 const &v1, Vec4 const &v2);

        [[nodiscard]] Real distance(Vec2 const &v1, Vec2 const &v2);
        [[nodiscard]] Real distance(Vec3 const &v1, Vec3 const &v2);
        [[nodiscard]] Real distance(Vec4 const &v1, Vec4 const &v2);

        [[nodiscard]] Vec3 cross_product(Vec3 const &v1, Vec3 const &v2);
    }
}

#endif // BOLTENG_VECTOR_H
