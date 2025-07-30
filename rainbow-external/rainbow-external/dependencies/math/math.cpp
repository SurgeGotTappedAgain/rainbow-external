#include "includes.hpp"

vector2_t::vector2_t(float x_val, float y_val) : x(x_val), y(y_val) {}

vector2_t vector2_t::operator+(const vector2_t& v) const { 
    return { x + v.x, y + v.y };
}

vector2_t vector2_t::operator-(const vector2_t& v) const { 
    return { x - v.x, y - v.y };
}

vector2_t vector2_t::operator*(float scalar) const {
    return { x * scalar, y * scalar }; 
}

vector2_t vector2_t::operator/(float scalar) const { 
    return { x / scalar, y / scalar }; 
}

vector2_t& vector2_t::operator+=(const vector2_t& v) {
    x += v.x; y += v.y; 
    return *this; 
}

vector2_t& vector2_t::operator-=(const vector2_t& v) {
    x -= v.x; y -= v.y;
    return *this; 
}

bool vector2_t::operator==(const vector2_t& v) const {
    return x == v.x && y == v.y;
}

bool vector2_t::operator!=(const vector2_t& v) const {
    return !(*this == v);
}

float vector2_t::dot(const vector2_t& v) const {
    return x * v.x + y * v.y;
}

bool vector2_t::empty() const {
    return x == 0.0f && y == 0.0f;
}

float vector2_t::magnitude() const {
    return std::sqrt(x * x + y * y); 
}

vector2_t vector2_t::normalize() const {
    float mag = magnitude();
    return (mag == 0) ? vector2_t{ 0, 0 } : vector2_t{ x / mag, y / mag };
}

float vector2_t::distance(const vector2_t& v) const { 
    return (*this - v).magnitude(); 
}

// vector3_t implementations

vector3_t::vector3_t(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {}

float& vector3_t::operator[](int i) {
    return (&x)[i]; 
}

const float& vector3_t::operator[](int i) const {
    return (&x)[i]; 
}

vector3_t vector3_t::operator+(const vector3_t& v) const { 
    return { x + v.x, y + v.y, z + v.z }; 
}

vector3_t vector3_t::operator-(const vector3_t& v) const { 
    return { x - v.x, y - v.y, z - v.z }; 
}

vector3_t vector3_t::operator*(float scalar) const { 
    return { x * scalar, y * scalar, z * scalar };
}

vector3_t vector3_t::operator/(float scalar) const { 
    return { x / scalar, y / scalar, z / scalar }; 
}

vector3_t& vector3_t::operator+=(const vector3_t& v) {
    x += v.x; y += v.y; z += v.z; 
    return *this;
}

vector3_t& vector3_t::operator-=(const vector3_t& v) {
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

vector3_t& vector3_t::operator/=(float scalar) {
    x /= scalar; y /= scalar; z /= scalar; 
    return *this;
}

vector3_t vector3_t::operator-() const {
    return { -x, -y, -z };
}

bool vector3_t::operator==(const vector3_t& v) const { 
    return x == v.x && y == v.y && z == v.z; 
}

bool vector3_t::operator!=(const vector3_t& v) const { 
    return !(*this == v);
}

float vector3_t::dot(const vector3_t& v) const { 
    return x * v.x + y * v.y + z * v.z; 
}

float vector3_t::magnitude() const { 
    return std::sqrt(x * x + y * y + z * z);
}

float vector3_t::distance(const vector3_t& v) const {
    return (*this - v).magnitude(); 
}

vector3_t vector3_t::cross(const vector3_t& v) const {
    return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    };
}

vector3_t vector3_t::normalize() const {
    float len = magnitude();
    return (len == 0.0f) ? vector3_t{ 0.0f, 0.0f, 0.0f } : (*this / len);
}

bool vector3_t::empty() const {
    return x == 0.0f && y == 0.0f && z == 0.0f;
}