#include "vector.h"
#include <cmath>
#include <utility>

namespace bolt {
    namespace maths {

        // ===================================================================
        // Vec2
        // ===================================================================

        Vec2::Vec2() : 
            x(0.0), 
            y(0.0) 
        {}

        Vec2::Vec2(Real tx, Real ty) : 
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
            Real mag   = magnitude(*this);
            Real recip = 1.0 / mag;
            x *= recip;
            y *= recip;
        }

        void Vec2::zero() {
            x = y = 0.0;
        }

        // -------------------------------------------------------------------
        // copying / moving
        // -------------------------------------------------------------------

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

        // -------------------------------------------------------------------
        // equivalence comparisons
        // -------------------------------------------------------------------

        bool Vec2::operator==(Vec2 const &v) const {
            return x == v.x && y == v.y;
        }

        bool Vec2::operator!=(Vec2 const &v) const {
            return x != v.x || y != v.y;
        }

        // -------------------------------------------------------------------
        // basic vector operations -- note piecewise vector multiplication and division
        // -------------------------------------------------------------------

        Vec2 Vec2::operator-() const {
            return Vec2(-x, -y);
        }

        Vec2 Vec2::operator+(Vec2 const &v) const {
            return Vec2(x + v.x, y + v.y);
        }

        Vec2 Vec2::operator-(Vec2 const &v) const {
            return Vec2(x - v.x, y - v.y);
        }

        Vec2 Vec2::operator*(Vec2 const &v) const {
            return Vec2(x * v.x, y * v.y);
        }

        Vec2 Vec2::operator/(Vec2 const &v) const {
            return Vec2(x / v.x, y / v.y);
        }

        Vec2& Vec2::operator+=(Vec2 const &v) {
            x += v.x; y += v.y;
            return *this;
        }

        Vec2& Vec2::operator-=(Vec2 const &v) {
            x -= v.x; y -= v.y;
            return *this;
        }

        Vec2& Vec2::operator*=(Vec2 const &v) {
            x *= v.x; y *= v.y;
            return *this;
        }

        Vec2& Vec2::operator/=(Vec2 const &v) {
            x /= v.x; y /= v.y;
            return *this;
        }
        
        // -------------------------------------------------------------------
        // basic scalar operations -- note piecewise addition and subtraction
        // -------------------------------------------------------------------

        Vec2 Vec2::operator+(Real const k) const {
            return Vec2(x + k, y + k);
        }

        Vec2 Vec2::operator-(Real const k) const {
            return Vec2(x - k, y - k);
        }

        Vec2 Vec2::operator*(Real const k) const {
            return Vec2(x * k, y * k);
        }

        Vec2 Vec2::operator/(Real const k) const {
            float recip = 1.0 / k;
            return Vec2(x * recip, y * recip);
        }

        Vec2& Vec2::operator+=(Real const k) {
            x += k; y += k;
            return *this;
        }

        Vec2& Vec2::operator-=(Real const k) {
            x -= k; y -= k;
            return *this;
        }

        Vec2& Vec2::operator*=(Real const k) {
            x *= k; y *= k;
            return *this;
        }

        Vec2& Vec2::operator/=(Real const k) {
            float recip = 1.0 / k;
            x *= recip; y *= recip;
            return *this;
        }

        // -------------------------------------------------------------------
        // needed for symmetry when multiplying -- scalar on the left
        // -------------------------------------------------------------------

        Vec2 operator+ (Real const k, Vec2 const &v) {
            return Vec2(k + v.x, k + v.y);
        }

        Vec2 operator- (Real const k, Vec2 const &v) {
            return Vec2(k - v.x, k - v.y);
        }

        Vec2 operator* (Real const k, Vec2 const &v) {
            return Vec2(k * v.x, k * v.y);
        }

        Vec2 operator/ (Real const k, Vec2 const &v) {
            return Vec2(k / v.x, k / v.y);
        }
        
        // -------------------------------------------------------------------
        // input/output
        // -------------------------------------------------------------------

        std::ostream& operator<<(std::ostream& os, bolt::maths::Vec2 const &v) {
            os << "[" << v.x << ", " << v.y << "]";
            return os;
        }

        // ===================================================================
        // Vec3
        // ===================================================================

        Vec3::Vec3() : 
            x(0.0), 
            y(0.0), 
            z(0.0) 
        {}

        Vec3::Vec3(Real tx, Real ty, Real tz) :
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
            Real mag = magnitude(*this);
            Real recip = 1.0 / mag;
            x *= recip;
            y *= recip;
            z *= recip;
        }

        void Vec3::zero() {
            x = y = z = 0.0;
        }
        
        // -------------------------------------------------------------------
        // copying / moving
        // -------------------------------------------------------------------

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

        // -------------------------------------------------------------------
        // equivalence comparisons
        // -------------------------------------------------------------------

        bool Vec3::operator==(Vec3 const &v) const {
            return x == v.x && y == v.y && z == v.z;
        }

        bool Vec3::operator!=(Vec3 const &v) const {
            return x != v.x || y != v.y || z != v.z;
        }

        // -------------------------------------------------------------------
        // basic vector operations -- note piecewise vector multiplication and division
        // -------------------------------------------------------------------

        Vec3 Vec3::operator-() const {
            return Vec3(-x, -y, -z);
        }

        Vec3 Vec3::operator+(Vec3 const &v) const {
            return Vec3(x + v.x, y + v.y, z + v.z);
        }

        Vec3 Vec3::operator-(Vec3 const &v) const {
            return Vec3(x - v.x, y - v.y, z - v.z);
        }

        Vec3 Vec3::operator*(Vec3 const &v) const {
            return Vec3(x * v.x, y * v.y, z * v.z);
        }

        Vec3 Vec3::operator/(Vec3 const &v) const {
            return Vec3(x / v.x, y / v.y, z / v.z);
        }

        Vec3& Vec3::operator+=(Vec3 const &v) {
            x += v.x; y += v.y; z += v.z;
            return *this;
        }

        Vec3& Vec3::operator-=(Vec3 const &v) {
            x -= v.x; y -= v.y; z -= v.z;
            return *this;
        }

        Vec3& Vec3::operator*=(Vec3 const &v) {
            x *= v.x; y *= v.y; z *= v.z;
            return *this;
        }

        Vec3& Vec3::operator/=(Vec3 const &v) {
            x /= v.x; y /= v.y; z /= v.z;
            return *this;
        }
        
        // -------------------------------------------------------------------
        // basic scalar operations -- note piecewise addition and subtraction
        // -------------------------------------------------------------------

        Vec3 Vec3::operator+(Real const k) const {
            return Vec3(x + k, y + k, z + k);
        }

        Vec3 Vec3::operator-(Real const k) const {
            return Vec3(x - k, y - k, z - k);
        }

        Vec3 Vec3::operator*(Real const k) const {
            return Vec3(x * k, y * k, z * k);
        }

        Vec3 Vec3::operator/(Real const k) const {
            Real recip = 1.0 / k;
            return Vec3(x * recip, y * recip, z * recip);
        }

        Vec3& Vec3::operator+=(Real const k) {
            x += k; y += k; z += k;
            return *this;
        }

        Vec3& Vec3::operator-=(Real const k) {
            x -= k; y -= k; z -= k;
            return *this;
        }

        Vec3& Vec3::operator*=(Real const k) {
            x *= k; y *= k; z *= k;
            return *this;
        }

        Vec3& Vec3::operator/=(Real const k) {
            Real recip = 1.0 / k;
            x *= recip; y *= recip; z *= recip;
            return *this;
        }

        // -------------------------------------------------------------------
        // needed for symmetry when multiplying -- scalar on the left
        // -------------------------------------------------------------------

        Vec3 operator+ (Real const k, Vec3 const &v) {
            return Vec3(k + v.x, k + v.y, k + v.z);
        }

        Vec3 operator- (Real const k, Vec3 const &v) {
            return Vec3(k - v.x, k - v.y, k - v.z);
        }

        Vec3 operator* (Real const k, Vec3 const &v) {
            return Vec3(k * v.x, k * v.y, k * v.z);
        }

        Vec3 operator/ (Real const k, Vec3 const &v) {
            return Vec3(k / v.x, k / v.y, k / v.z);
        }
        
        // -------------------------------------------------------------------
        // input/output
        // -------------------------------------------------------------------

        std::ostream& operator<< (std::ostream& os, bolt::maths::Vec3 const &v) {
            os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
            return os;
        }
        
        // ===================================================================
        // Vec4
        // ===================================================================

        Vec4::Vec4() : 
            x(0.0), 
            y(0.0), 
            z(0.0),
            w(0.0)
        {}

        Vec4::Vec4(Real tx, Real ty, Real tz, Real tw) :
            x(tx),
            y(ty),
            z(tz),
            w(tw)
        {}

        Vec4::Vec4(Vec4 const &v) : 
            x(v.x),
            y(v.y),
            z(v.z),
            w(v.w)
        {}

        Vec4::Vec4(Vec4 &&v) :
            x(std::exchange(v.x, 0.0)),
            y(std::exchange(v.y, 0.0)),
            z(std::exchange(v.z, 0.0)),
            w(std::exchange(v.w, 0.0))
        {}

        void Vec4::normalise() {
            Real mag   = magnitude(*this);
            Real recip = 1.0 / mag;
            x *= recip;
            y *= recip;
            z *= recip;
            w *= recip;
        }

        void Vec4::zero() {
            x = y = z = w = 0.0;
        }

        // -------------------------------------------------------------------
        // copying / moving
        // -------------------------------------------------------------------

        Vec4& Vec4::operator=(Vec4 const &v) {
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
            return *this;
        }

        Vec4& Vec4::operator=(Vec4 &&v) {
            x = std::exchange(v.x, 0.0);
            y = std::exchange(v.y, 0.0);
            z = std::exchange(v.z, 0.0);
            w = std::exchange(v.w, 0.0);
            return *this;
        }
        
        // -------------------------------------------------------------------
        // equivalence comparisons
        // -------------------------------------------------------------------

        bool Vec4::operator==(Vec4 const &v) const {
            return x == v.x && y == v.y && z == v.z && w == v.w;
        }

        bool Vec4::operator!=(Vec4 const &v) const {
            return x != v.x || y != v.y || z != v.z || w != v.w;
        }

        // -------------------------------------------------------------------
        // basic vector operations -- note piecewise vector multiplication and division
        // -------------------------------------------------------------------

        Vec4 Vec4::operator-() const {
            return Vec4(-x, -y, -z, -w);
        }

        Vec4 Vec4::operator+(Vec4 const &v) const {
            return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        }

        Vec4 Vec4::operator-(Vec4 const &v) const {
            return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
        }

        Vec4 Vec4::operator*(Vec4 const &v) const {
            return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
        }

        Vec4 Vec4::operator/(Vec4 const &v) const {
            return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
        }

        Vec4& Vec4::operator+=(Vec4 const &v) {
            x += v.x; y += v.y; z += v.z; w += v.w;
            return *this;
        }

        Vec4& Vec4::operator-=(Vec4 const &v) {
            x -= v.x; y -= v.y; z -= v.z; w -= v.w;
            return *this;
        }

        Vec4& Vec4::operator*=(Vec4 const &v) {
            x *= v.x; y *= v.y; z *= v.z; w *= v.w;
            return *this;
        }

        Vec4& Vec4::operator/=(Vec4 const &v) {
            x /= v.x; y /= v.y; z /= v.z; w /= v.w;
            return *this;
        }
        
        // -------------------------------------------------------------------
        // basic scalar operations -- note piecewise addition and subtraction
        // -------------------------------------------------------------------

        Vec4 Vec4::operator+(Real const k) const {
            return Vec4(x + k, y + k, z + k, w + k);
        }

        Vec4 Vec4::operator-(Real const k) const {
            return Vec4(x - k, y - k, z - k, w - k);
        }

        Vec4 Vec4::operator*(Real const k) const {
            return Vec4(x * k, y * k, z * k, w * k);
        }

        Vec4 Vec4::operator/(Real const k) const {
            Real recip = 1.0 / k;
            return Vec4(x * recip, y * recip, z * recip, w * recip);
        }

        Vec4& Vec4::operator+=(Real const k) {
            x += k; y += k; z += k; w += k;
            return *this;
        }

        Vec4& Vec4::operator-=(Real const k) {
            x -= k; y -= k; z -= k; w -= k;
            return *this;
        }

        Vec4& Vec4::operator*=(Real const k) {
            x *= k; y *= k; z *= k; w *= k;
            return *this;
        }

        Vec4& Vec4::operator/=(Real const k) {
            Real recip = 1.0 / k;
            x *= recip; y *= recip; z *= recip; w *= recip;
            return *this;
        }

        // -------------------------------------------------------------------
        // needed for symmetry when multiplying -- scalar on the left
        // -------------------------------------------------------------------

        Vec4 operator+ (Real const k, Vec4 const &v) {
            return Vec4(k + v.x, k + v.y, k + v.z, k + v.w);
        }

        Vec4 operator- (Real const k, Vec4 const &v) {
            return Vec4(k - v.x, k - v.y, k - v.z, k - v.w);
        }

        Vec4 operator* (Real const k, Vec4 const &v) {
            return Vec4(k * v.x, k * v.y, k * v.z, k * v.w);
        }

        Vec4 operator/ (Real const k, Vec4 const &v) {
            return Vec4(k / v.x, k / v.y, k / v.z, k / v.w);
        }

        // -------------------------------------------------------------------
        // input/output
        // -------------------------------------------------------------------

        std::ostream& operator<< (std::ostream& os, bolt::maths::Vec4 const &v) {
            os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
            return os;
        }

        // ===================================================================
        // Nonmember functions
        // ===================================================================

        Real magnitude(Vec2 const &v) {
            return std::sqrt(v.x * v.x + v.y * v.y);
        }

        Real magnitude(Vec3 const &v) {
            return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        }

        Real magnitude(Vec4 const &v) {
            return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
        }

        Real dot_product(Vec2 const &v1, Vec2 const &v2) {
            return v1.x * v2.x + v1.y * v2.y;
        }

        Real dot_product(Vec3 const &v1, Vec3 const &v2) {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        }

        Real dot_product(Vec4 const &v1, Vec4 const &v2) {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
        } 

        Real distance(Vec2 const &v1, Vec2 const &v2) {
            Real dx = v1.x - v2.x;
            Real dy = v1.y - v2.y;
            return std::sqrt(dx * dx + dy * dy);
        }

        Real distance(Vec3 const &v1, Vec3 const &v2) {
            Real dx = v1.x - v2.x;
            Real dy = v1.y - v2.y;
            Real dz = v1.z - v2.z;
            return std::sqrt(dx * dx + dy * dy + dz * dz);
        }

        Real distance(Vec4 const &v1, Vec4 const &v2) {
            Real dx = v1.x - v2.x;
            Real dy = v1.y - v2.y;
            Real dz = v1.z - v2.z;
            Real dw = v1.w - v2.w;
            return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
        }

        Vec3 cross_product(Vec3 const &v1, Vec3 const &v2) {
            Real x = v1.y * v2.z - v1.z * v2.y;
            Real y = v1.z * v2.x - v1.x * v2.z;
            Real z = v1.x * v2.y - v1.y * v2.x;
            return Vec3(x, y, z);
        }
    }
}


