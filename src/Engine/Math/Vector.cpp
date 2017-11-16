/*
 * File Vector.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Vector.h"
#include "../Debug.h"

namespace ThreeEngine {

    const Vector Vector::ZeroVector = Vector(0);

    const Vector Vector::OneVector = Vector(1);

    const Vector Vector::UpVector = Vector(0, 0, 1);

    const Vector Vector::ForwardVector = Vector(1, 0, 0);

    const Vector Vector::LeftVector = Vector(0, 1, 0);

    Vector::Vector() : Vector(0) {}

    Vector::Vector(number in) : Vector(in, in, in) {}

    Vector::Vector(number inX, number inY, number inZ) : X(inX), Y(inY), Z(inZ) {}

    Vector::Vector(const Vector2& other, number inZ) : Vector(other.X, other.Y, inZ) {}

    Vector::Vector(const Vector& other) {
        operator=(other);
    }

    Vector& Vector::operator=(const Vector& other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;

        return *this;
    }

    Vector Vector::GetRandom(const number& max) {
        number X = Maths::GetRandom(-max, 2 * max);
        number Y = Maths::GetRandom(-max, 2 * max);
        number Z = Maths::GetRandom(-max, 2 * max);
        return Vector(X, Y, Z);
    }

    Vector Vector::operator^(const Vector& V) const {
        return Vector((Y * V.Z) - (Z * V.Y), (Z * V.X) - (X * V.Z), (X * V.Y) - (Y * V.X));
    }

    Vector Vector::CrossProduct(const Vector& A, const Vector& B) {
        return A ^ B;
    }

    number Vector::operator|(const Vector& V) const {
        return (X * V.X) + (Y * V.Y) + (Z * V.Z);
    }

    number Vector::DotProduct(const Vector& A, const Vector& B) {
        return A | B;
    }

    Vector Vector::operator+(const Vector& V) const {
        return Vector(X + V.X, Y + V.Y, Z + V.Z);
    }

    Vector Vector::operator-(const Vector& V) const {
        return Vector(X - V.X, Y - V.Y, Z - V.Z);
    }

    Vector Vector::operator-(number value) const {
        return Vector(X - value, Y - value, Z - value);
    }

    Vector Vector::operator+(number value) const {
        return Vector(X + value, Y + value, Z + value);
    }

    Vector Vector::operator*(number scale) const {
        return Vector(X * scale, Y * scale, Z * scale);
    }

    Vector Vector::operator/(number scale) const {
        return Vector(X / scale, Y / scale, Z / scale);
    }

    Vector Vector::operator*(const Vector& V) const {
        return Vector(X * V.X, Y * V.Y, Z * V.Z);
    }

    Vector Vector::operator/(const Vector& V) const {
        return Vector(X / V.X, Y / V.Y, Z / V.Z);
    }

    Vector operator-(const number& value, const Vector& vector) {
        return Vector(value - vector.X, value - vector.Y, value - vector.Z);
    }

    Vector operator+(const number& value, const Vector& vector) {
        return vector + value;
    }

    Vector operator*(const number& value, const Vector& vector) {
        return vector * value;
    }

    Vector operator/(const number& value, const Vector& vector) {
        return Vector(value / vector.X, value / vector.Y, value / vector.Z);
    }

    bool Vector::operator==(const Vector& V) const {
        // http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
        bool XValid = std::abs(X - V.X) < Epsilon + Epsilon * std::abs(X + V.X) * ULP;
        bool YValid = std::abs(Y - V.Y) < Epsilon + Epsilon * std::abs(Y + V.Y) * ULP;
        bool ZValid = std::abs(Z - V.Z) < Epsilon + Epsilon * std::abs(Z + V.Z) * ULP;
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

    Vector Vector::operator+=(number in) {
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

    Vector Vector::operator-=(number in) {
        X -= in;
        Y -= in;
        Z -= in;
        return *this;
    }

    Vector Vector::operator*=(number in) {
        X *= in;
        Y *= in;
        Z *= in;
        return *this;
    }

    Vector Vector::operator/=(number in) {
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

    Vector& Vector::operator++() {
        ++X;
        ++Y;
        ++Z;
        return *this;
    }

    Vector& Vector::operator--() {
        --X;
        --Y;
        --Z;
        return *this;
    }

    bool Vector::Normalize() {
        const float squaredSum = DistSquared();
        if (squaredSum < Epsilon) {
            return false;
        }

        const float scale = 1.f / sqrtf(squaredSum);
        X *= scale;
        Y *= scale;
        Z *= scale;
        return true;
    }

    bool Vector::IsNormalized() const {
        return (std::abs(1.0f - DistSquared()) < Epsilon);
    }

    Vector Vector::Normalize(Vector v) {
        Vector vNorm = v;
        vNorm.Normalize();
        return vNorm;
    }

    float& Vector::operator[](int Index) {
        switch (Index) {
            case 0:
                return X;
            case 1:
                return Y;
            case 2:
                return Z;
            default:
                Debug::Error("Invalid Index");
                return Z;
        }
    }

    float Vector::operator[](int Index) const {
        switch (Index) {
            case 0:
                return X;
            case 1:
                return Y;
            case 2:
                return Z;
            default:
                Debug::Error("Invalid Index");
                return Z;
        }
    }

    void Vector::Set(const number& inX, const number& inY, const number& inZ) {
        X = inX;
        Y = inY;
        Z = inZ;
    }

    number Vector::Dist() const {
        return sqrtf(DistSquared());
    }

    number Vector::DistSquared() const {
        return (X * X) + (Y * Y) + (Z * Z);
    }

    Vector Vector::ProjectOnTo(const Vector& A) const {
        return A * (((*this) | A) / (A | A));
    }


    Vector Vector::Lerp(const Vector& v0, const Vector& v1, number time) {
        return ((1 - time) * v0) + (time * v1);
    }
} /* namespace Divisaction */