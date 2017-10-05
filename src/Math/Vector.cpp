/*
 * File Vector.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Vector.h"
#include <cmath>

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
        return X == V.X && Y == V.Y && Z == V.Z;
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