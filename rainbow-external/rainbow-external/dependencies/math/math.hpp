#pragma once

#define M_PI 3.14159265358979323846f
#define M_RADPI 57.295779513082f

#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))

struct vector2_t
{
    float x, y;

    vector2_t(float x_val = 0.0f, float y_val = 0.0f);

    vector2_t operator+(const vector2_t& v) const;
    vector2_t operator-(const vector2_t& v) const;
    vector2_t operator*(float scalar) const;
    vector2_t operator/(float scalar) const;

    vector2_t& operator+=(const vector2_t& v);
    vector2_t& operator-=(const vector2_t& v);

    bool operator==(const vector2_t& v) const;
    bool operator!=(const vector2_t& v) const;

    float dot(const vector2_t& v) const;
    bool empty() const;
    float magnitude() const;
    vector2_t normalize() const;
    float distance(const vector2_t& v) const;
};

struct vector3_t
{
    float x, y, z;

    vector3_t(float x_val = 0.0f, float y_val = 0.0f, float z_val = 0.0f);

    float& operator[](int i);
    const float& operator[](int i) const;

    vector3_t operator+(const vector3_t& v) const;
    vector3_t operator-(const vector3_t& v) const;
    vector3_t operator*(float scalar) const;
    vector3_t operator/(float scalar) const;

    vector3_t& operator+=(const vector3_t& v);
    vector3_t& operator-=(const vector3_t& v);
    vector3_t& operator/=(float scalar);

    vector3_t operator-() const;

    bool operator==(const vector3_t& v) const;
    bool operator!=(const vector3_t& v) const;

    float dot(const vector3_t& v) const;
    float magnitude() const;
    float distance(const vector3_t& v) const;
    vector3_t cross(const vector3_t& v) const;
    vector3_t normalize() const;

    bool empty() const;
    std::string to_string() const;
};

struct matrix4_t {
    float m[16];
};