/*
 * File Vector4.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Vector4.h"

namespace ThreeEngine {


    const Vector4 Vector4::ZeroVector = Vector4(0);

    const Vector4 Vector4::OneVector = Vector4(1);

    const Vector4 Vector4::UpVector = Vector4(0, 0, 1);

    const Vector4 Vector4::ForwardVector = Vector4(1, 0, 0);

    const Vector4 Vector4::LeftVector = Vector4(0, 1, 0);

    Vector4::Vector4() : Vector4(0) {}

    Vector4::Vector4(number in) : Vector4(in, in, in, in) {}

    Vector4::Vector4(number inX, number inY, number inZ, number inW) : X(inX), Y(inY), Z(inZ),
                                                                       W(inW) {}

    Vector4::Vector4(const Vector2& other, number inZ, number inW) : Vector4(other.X, other.Y,
                                                                             inZ, inW) {}

    Vector4::Vector4(const Vector& other, number inW) : Vector4(other.X, other.Y, other.Z, inW) {}

    Vector4::Vector4(const Vector4& other) {
        operator=(other);
    }

    Vector4& Vector4::operator=(const Vector4& other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;

        return *this;
    }

    Vector4 Vector4::GetRandom(const number& max) {
        number X = Maths::GetRandom(-max, 2 * max);
        number Y = Maths::GetRandom(-max, 2 * max);
        number Z = Maths::GetRandom(-max, 2 * max);
        number W = Maths::GetRandom(-max, 2 * max);
        return Vector4(X, Y, Z, W);
    }

    Vector4 Vector4::operator^(const Vector4& V) const {
        return Vector4((Y * V.Z) - (Z * V.Y), (Z * V.X) - (X * V.Z), (X * V.Y) - (Y * V.X), 0.0f);
    }

    Vector4 Vector4::CrossProduct(const Vector4& A, const Vector4& B) {
        return A ^ B;
    }

    number Vector4::operator|(const Vector4& V) const {
        return (X * V.X) + (Y * V.Y) + (Z * V.Z) + (W * V.W);
    }

    number Vector4::DotProduct(const Vector4& A, const Vector4& B) {
        return A | B;
    }

    number Vector4::DotProduct3(const Vector4& A, const Vector4& B) {
        return (A.X * B.X) + (A.Y * B.Y) + (A.Z * B.Z);
    }

    Vector4 Vector4::operator+(const Vector4& V) const {
        return Vector4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
    }

    Vector4 Vector4::operator-(const Vector4& V) const {
        return Vector4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
    }

    Vector4 Vector4::operator-(number value) const {
        return Vector4(X - value, Y - value, Z - value, W - value);
    }

    Vector4 Vector4::operator+(number value) const {
        return Vector4(X + value, Y + value, Z + value, W + value);
    }

    Vector4 Vector4::operator*(number scale) const {
        return Vector4(X * scale, Y * scale, Z * scale, W * scale);
    }

    Vector4 Vector4::operator/(number scale) const {
        return Vector4(X / scale, Y / scale, Z / scale, W / scale);
    }

    Vector4 Vector4::operator*(const Vector4& V) const {
        return Vector4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
    }

    Vector4 Vector4::operator/(const Vector4& V) const {
        return Vector4(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
    }

    Vector4 operator-(const number& value, const Vector4& vector) {
        return Vector4(value - vector.X, value - vector.Y, value - vector.Z, value - vector.W);
    }

    Vector4 operator+(const number& value, const Vector4& vector) {
        return vector + value;
    }

    Vector4 operator*(const number& value, const Vector4& vector) {
        return vector * value;
    }

    Vector4 operator/(const number& value, const Vector4& vector) {
        return Vector4(value / vector.X, value / vector.Y, value / vector.Z, value / vector.W);
    }

    bool Vector4::operator==(const Vector4& V) const {
        // http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
        bool XValid = std::abs(X - V.X) < Epsilon + Epsilon * std::abs(X + V.X) * ULP;
        bool YValid = std::abs(Y - V.Y) < Epsilon + Epsilon * std::abs(Y + V.Y) * ULP;
        bool ZValid = std::abs(Z - V.Z) < Epsilon + Epsilon * std::abs(Z + V.Z) * ULP;
        bool WValid = std::abs(W - V.W) < Epsilon + Epsilon * std::abs(W + V.W) * ULP;
        return XValid && YValid && ZValid && WValid;
    }

    bool Vector4::operator!=(const Vector4& V) const {
        return !(*this == V);
    }

    Vector4 Vector4::operator-() const {
        return Vector4(-X, -Y, -Z, -W);
    }

    Vector4 Vector4::operator+=(const Vector4& V) {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        W += V.W;
        return *this;
    }

    Vector4 Vector4::operator+=(number in) {
        X += in;
        Y += in;
        Z += in;
        W += in;
        return *this;
    }

    Vector4 Vector4::operator-=(const Vector4& V) {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        W -= V.W;
        return *this;
    }

    Vector4 Vector4::operator-=(number in) {
        X -= in;
        Y -= in;
        Z -= in;
        W -= in;
        return *this;
    }

    Vector4 Vector4::operator*=(number in) {
        X *= in;
        Y *= in;
        Z *= in;
        W *= in;
        return *this;
    }

    Vector4 Vector4::operator/=(number in) {
        X /= in;
        Y /= in;
        Z /= in;
        W /= in;
        return *this;
    }

    Vector4 Vector4::operator*=(const Vector4& V) {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        W *= V.W;
        return *this;
    }

    Vector4 Vector4::operator/=(const Vector4& V) {
        X /= V.X;
        Y /= V.Y;
        Z /= V.Z;
        W /= V.W;
        return *this;
    }

    Vector4& Vector4::operator++() {
        ++X;
        ++Y;
        ++Z;
        ++W;
        return *this;
    }

    Vector4& Vector4::operator--() {
        --X;
        --Y;
        --Z;
        --W;
        return *this;
    }

    void Vector4::Set(const number& inX, const number& inY, const number& inZ) {
        X = inX;
        Y = inY;
        Z = inZ;
    }

    void Vector4::Set(const number& inX, const number& inY, const number& inZ, const number& inW) {
        X = inX;
        Y = inY;
        Z = inZ;
        W = inW;
    }

    number Vector4::Dist() const {
        return sqrtf(DistSquared());
    }

    number Vector4::DistSquared() const {
        return (X * X) + (Y * Y) + (Z * Z) + (W * W);
    }

    number Vector4::Dist3() const {
        return sqrtf(DistSquared3());
    }

    number Vector4::DistSquared3() const {
        return (X * X) + (Y * Y) + (Z * Z);
    }

    Vector4 Vector4::ProjectOnTo(const Vector4& A) const {
        return A * (((*this) | A) / (A | A));
    }

} /* namespace Divisaction */