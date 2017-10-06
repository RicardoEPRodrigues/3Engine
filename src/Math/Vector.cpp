/*
 * File Vector.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Vector.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

namespace ThreeEngine {

    const Vector Vector::ZeroVector = Vector(0);

    const Vector Vector::OneVector = Vector(1);

    const Vector Vector::UpVector = Vector(0, 0, 1);

    const Vector Vector::ForwardVector = Vector(1, 0, 0);

    const Vector Vector::LeftVector = Vector(0, 1, 0);

    Vector::Vector() : Vector(0) {}

    Vector::Vector(float in) : Vector(in, in, in) {}

    Vector::Vector(float inX, float inY, float inZ) : X(inX), Y(inY), Z(inZ) {}

    Vector::Vector(const Vector2& other, float inZ) : Vector(other.X, other.Y, inZ) {}

    Vector::Vector(const Vector& other) {
        operator=(other);
    }

    Vector& Vector::operator=(const Vector& other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;

        return *this;
    }

    Vector Vector::GetRandom(const float& max) {
        float X = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * max)))) - max;
        float Y = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * max)))) - max;
        float Z = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * max)))) - max;
        //float X = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //float Y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //float Z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        return Vector(X, Y, Z);
    }

    Vector Vector::operator^(const Vector& V) const {
        return Vector((Y * V.Z) - (Z * V.Y), (Z * V.X) - (X * V.Z), (X * V.Y) - (Y * V.X));
    }

    Vector Vector::CrossProduct(const Vector& A, const Vector& B) {
        return A ^ B;
    }

    float Vector::operator|(const Vector& V) const {
        return (X * V.X) + (Y * V.Y) + (Z * V.Z);
    }

    float Vector::DotProduct(const Vector& A, const Vector& B) {
        return A | B;
    }

    Vector Vector::operator+(const Vector& V) const {
        return Vector(X + V.X, Y + V.Y, Z + V.Z);
    }

    Vector Vector::operator-(const Vector& V) const {
        return Vector(X - V.X, Y - V.Y, Z - V.Z);
    }

    Vector Vector::operator-(float value) const {
        return Vector(X - value, Y - value, Z - value);
    }

    Vector Vector::operator+(float value) const {
        return Vector(X + value, Y + value, Z + value);
    }

    Vector Vector::operator*(float scale) const {
        return Vector(X * scale, Y * scale, Z * scale);
    }

    Vector Vector::operator/(float scale) const {
        return Vector(X / scale, Y / scale, Z / scale);
    }

    Vector Vector::operator*(const Vector& V) const {
        return Vector(X * V.X, Y * V.Y, Z * V.Z);
    }

    Vector Vector::operator/(const Vector& V) const {
        return Vector(X / V.X, Y / V.Y, Z / V.Z);
    }

    Vector operator-(const float& value, const Vector& vector) {
        return Vector(value - vector.X, value - vector.Y, value - vector.Z);
    }

    Vector operator+(const float& value, const Vector& vector) {
        return vector + value;
    }

    Vector operator*(const float& value, const Vector& vector) {
        return vector * value;
    }

    Vector operator/(const float& value, const Vector& vector) {
        return Vector(value / vector.X, value / vector.Y, value / vector.Z);
    }

    bool Vector::operator==(const Vector& V) const {
        static float IGNORE = (float)1.0e-5;
        bool XValid = std::abs(X - V.X) < IGNORE;
        bool YValid = std::abs(Y - V.Y) < IGNORE;
        bool ZValid = std::abs(Z - V.Z) < IGNORE;
        //static float ULP = 3;
        //bool XValid = std::abs(X - V.X) < std::numeric_limits<float>::epsilon() * std::abs(X + V.X) * ULP;
        //bool YValid = std::abs(Y - V.Y) < std::numeric_limits<float>::epsilon() * std::abs(Y + V.Y) * ULP;
        //bool ZValid = std::abs(Z - V.Z) < std::numeric_limits<float>::epsilon() * std::abs(Z + V.Z) * ULP;
        return XValid && YValid && ZValid;
    }

    bool Vector::operator!=(const Vector& V) const {
        return !(*this == V);
    }

    Vector Vector::operator-() const {
        return Vector(-X, -Y, -Z);
    }

    Vector Vector::operator+=(const Vector& V) {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        return *this;
    }

    Vector Vector::operator+=(float in) {
        X += in;
        Y += in;
        Z += in;
        return *this;
    }

    Vector Vector::operator-=(const Vector& V) {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        return *this;
    }

    Vector Vector::operator-=(float in) {
        X -= in;
        Y -= in;
        Z -= in;
        return *this;
    }

    Vector Vector::operator*=(float in) {
        X *= in;
        Y *= in;
        Z *= in;
        return *this;
    }

    Vector Vector::operator/=(float in) {
        X /= in;
        Y /= in;
        Z /= in;
        return *this;
    }

    Vector Vector::operator*=(const Vector& V) {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        return *this;
    }

    Vector Vector::operator/=(const Vector& V) {
        X /= V.X;
        Y /= V.Y;
        Z /= V.Z;
        return *this;
    }

    void Vector::Set(const float& inX, const float& inY, const float& inZ) {
        X = inX;
        Y = inY;
        Z = inZ;
    }

    float Vector::Dist() const {
        return sqrtf(DistSquared());
    }

    float Vector::DistSquared() const {
        return (X * X) + (Y * Y) + (Z * Z);
    }

    Vector Vector::ProjectOnTo(const Vector& A) const {
        return A * (((*this) | A) / (A | A));
    }
} /* namespace Divisaction */