/*
 * File Vector2.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Vector2.h"
#include <cmath>

namespace ThreeEngine {

    const Vector2 Vector2::ZeroVector = Vector2(0);

    const Vector2 Vector2::OneVector = Vector2(1);

    const Vector2 Vector2::UpVector = Vector2(0, 1);

    const Vector2 Vector2::RightVector = Vector2(1, 0);

    Vector2::Vector2() : Vector2(0) {}

    Vector2::Vector2(float in) : Vector2(in, in) {}

    Vector2::Vector2(float inX, float inY) : X(inX), Y(inY) {}

    Vector2::Vector2(const Vector2& other) {
        operator=(other);
    }

    Vector2& Vector2::operator=(const Vector2& other) {
        X = other.X;
        Y = other.Y;

        return *this;
    }

    float Vector2::operator|(const Vector2& V) const {
        return (X * V.X) + (Y * V.Y);
    }

    float Vector2::DotProduct(const Vector2& A, const Vector2& B) {
        return A | B;
    }

    Vector2 Vector2::operator+(const Vector2& V) const {
        return Vector2(X + V.X, Y + V.Y);
    }

    Vector2 Vector2::operator-(const Vector2& V) const {
        return Vector2(X - V.X, Y - V.Y);
    }

    Vector2 Vector2::operator-(float value) const {
        return Vector2(X - value, Y - value);
    }

    Vector2 Vector2::operator+(float value) const {
        return Vector2(X + value, Y + value);
    }

    Vector2 Vector2::operator*(float scale) const {
        return Vector2(X * scale, Y * scale);
    }

    Vector2 Vector2::operator/(float scale) const {
        return Vector2(X / scale, Y / scale);
    }

    Vector2 Vector2::operator*(const Vector2& V) const {
        return Vector2(X * V.X, Y * V.Y);
    }

    Vector2 Vector2::operator/(const Vector2& V) const {
        return Vector2(X / V.X, Y / V.Y);
    }

    Vector2 operator-(const float& value, const Vector2& vector) {
        return Vector2(value - vector.X, value - vector.Y);
    }

    Vector2 operator+(const float& value, const Vector2& vector) {
        return vector + value;
    }

    Vector2 operator*(const float& value, const Vector2& vector) {
        return vector * value;
    }

    Vector2 operator/(const float& value, const Vector2& vector) {
        return Vector2(value / vector.X, value / vector.Y);
    }

    bool Vector2::operator==(const Vector2& V) const {
        return X == V.X && Y == V.Y;
    }

    bool Vector2::operator!=(const Vector2& V) const {
        return !(*this == V);
    }

    Vector2 Vector2::operator-() const {
        return Vector2(-X, -Y);
    }

    Vector2 Vector2::operator+=(const Vector2& V) {
        X += V.X;
        Y += V.Y;
        return *this;
    }

    Vector2 Vector2::operator+=(float in) {
        X += in;
        Y += in;
        return *this;
    }

    Vector2 Vector2::operator-=(const Vector2& V) {
        X -= V.X;
        Y -= V.Y;
        return *this;
    }

    Vector2 Vector2::operator-=(float in) {
        X -= in;
        Y -= in;
        return *this;
    }

    Vector2 Vector2::operator*=(float in) {
        X *= in;
        Y *= in;
        return *this;
    }

    Vector2 Vector2::operator/=(float in) {
        X /= in;
        Y /= in;
        return *this;
    }

    Vector2 Vector2::operator*=(const Vector2& V) {
        X *= V.X;
        Y *= V.Y;
        return *this;
    }

    Vector2 Vector2::operator/=(const Vector2& V) {
        X /= V.X;
        Y /= V.Y;
        return *this;
    }

    void Vector2::Set(const float& inX, const float& inY) {
        X = inX;
        Y = inY;
    }

    float Vector2::Dist() const {
        return sqrtf(DistSquared());
    }

    float Vector2::DistSquared() const {
        return (X * X) + (Y * Y);
    }

    Vector2 Vector2::ProjectOnTo(const Vector2& A) const {
        return A * (((*this) | A) / (A | A));
    }

} /* namespace Divisaction */