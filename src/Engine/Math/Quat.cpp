/*
 * File Quat.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Quat.h"

using namespace std;

namespace ThreeEngine {

    Quat::Quat() = default;

    Quat::~Quat() = default;

    Quat::Quat(number InX, number InY, number InZ, number InW) : T(InX), X(InY), Y(InZ), Z(InW) { }

    Quat::Quat(const Quat& Q) {
        operator=(Q);
    }

    Quat& Quat::operator=(const Quat& Other) = default;

    Quat::Quat(const Vector& v) : T(0), X(v.X), Y(v.Y), Z(v.Z) { }

    void Quat::Clean() {
        if (abs(T) < Epsilon) { T = 0; }
        if (abs(X) < Epsilon) { X = 0; }
        if (abs(Y) < Epsilon) { Y = 0; }
        if (abs(Z) < Epsilon) { Z = 0; }
    }

    number Quat::DistSquared() const {
        return T * T + X * X + Y * Y + Z * Z;
    }

    number Quat::Dist() const {
        return sqrt(DistSquared());
    }

    Quat Quat::Normalize() const {
        number s = 1 / Dist();
        return (*this) * s;
    }

    Quat Quat::Conjugate() const {
        return Quat(T, -X, -Y, -Z);
    }

    Quat Quat::Inverse() const {
        return Conjugate() * (1.0f / DistSquared());
    }

    Quat Quat::operator*(const number s) const {
        return Quat(
                T * s,
                X * s,
                Y * s,
                Z * s
        );
    }

    Quat Quat::operator*(const Quat& q) const {
        return Quat(
                T * q.T - X * q.X - Y * q.Y - Z * q.Z,
                T * q.X + X * q.T + Y * q.Z - Z * q.Y,
                T * q.Y + Y * q.T + Z * q.X - X * q.Z,
                T * q.Z + Z * q.T + X * q.Y - Y * q.X
        );
    }

    Quat Quat::operator+(const Quat& q) const {
        return Quat(
                T + q.T,
                X + q.X,
                Y + q.Y,
                Z + q.Z
        );
    }

    Quat operator*(const number& value, const Quat& quat) {
        return quat * value;
    }

    bool Quat::operator==(const Quat& q) const {
        return (abs(T - q.T) < Epsilon && abs(X - q.X) < Epsilon &&
                abs(Y - q.Y) < Epsilon && abs(q.Z - q.Z) < Epsilon);
    }

    Matrix Quat::ToMatrix() {

        Quat qN = Normalize();

        number xx = qN.X * qN.X;
        number xy = qN.X * qN.Y;
        number xz = qN.X * qN.Z;
        number xt = qN.X * qN.T;
        number yy = qN.Y * qN.Y;
        number yz = qN.Y * qN.Z;
        number yt = qN.Y * qN.T;
        number zz = qN.Z * qN.Z;
        number zt = qN.Z * qN.T;

        return {
                1.0f - 2.0f * (yy + zz), 2.0f * (xy - zt), 2.0f * (xz + yt), 0,
                2.0f * (xy + zt), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xt), 0,
                2.0f * (xz - yt), 2.0f * (yz + xt), 1.0f - 2.0f * (xx + yy), 0,
                0, 0, 0, 1
        };
    }

    Quat Quat::FromAngleAxis(number theta, Vector axis) {
        Vector axisN = Vector::Normalize(axis);

        Quat q;
        number angle = Maths::ToRadians(theta);
        q.T = cos(angle / 2.0f);
        number s = sin(angle / 2.0f);
        q.X = axisN.X * s;
        q.Y = axisN.Y * s;
        q.Z = axisN.Z * s;
        q.Clean();

        return q.Normalize();
    }

    Quat Quat::FromAngleAxis(number theta, Vector4 axis) {
        Vector v = axis;
        return FromAngleAxis(theta, v);
    }

    void Quat::ToAngleAxis(const Quat& q, number& theta, Vector& axis) {
        Quat qN = q.Normalize();
        theta = Maths::ToDegrees(2.0f * acos(qN.T));

        number s = sqrt(1.0f - qN.T * qN.T);
        if (s < Epsilon) {
            axis.X = 1.0f;
            axis.Y = 0.0f;
            axis.Z = 0.0f;
        } else {
            axis.X = qN.X / s;
            axis.Y = qN.Y / s;
            axis.Z = qN.Z / s;
        }
    }

    void Quat::ToAngleAxis(const Quat& q, number& theta, Vector4& axis) {
        Quat qN = q.Normalize();
        theta = Maths::ToDegrees(2.0f * acos(qN.T));

        number s = sqrt(1.0f - qN.T * qN.T);
        if (s < Epsilon) {
            axis.X = 1.0f;
            axis.Y = 0.0f;
            axis.Z = 0.0f;
            axis.W = 1.0f;
        } else {
            axis.X = qN.X / s;
            axis.Y = qN.Y / s;
            axis.Z = qN.Z / s;
            axis.W = 1.0f;
        }
    }

    Quat Quat::Lerp(const Quat& q0, const Quat& q1, number time) {
        number cos_angle = q0.X * q1.X + q0.Y * q1.Y + q0.Z * q1.Z + q0.T * q1.T;
        number t1 = (cos_angle > 0) ? time : -time;

        return ((1 - time) * q0 + t1 * q1).Normalize();
    }

    Quat Quat::Slerp(const Quat& q0, const Quat& q1, number time) {
        number angle = acos(q0.X * q1.X + q0.Y * q1.Y + q0.Z * q1.Z + q0.T * q1.T);
        number t0 = sin((1 - time) * angle) / sin(angle);
        number t1 = sin(time * angle) / sin(angle);

        return (t0 * q0 + t1 * q1);
    }

    bool Quat::Equals(const Quat& q0, const Quat& q1) {
        return q0 == q1;
    }

    Quat::operator std::string() {
        return "(" + to_string(T) + ", " + to_string(X) + ", " + to_string(Y) + ", " +
               to_string(Z) + ")";
    }

    std::string Quat::ToStringAngleAxis() {

        float thetaf;
        Vector axis_f;
        ToAngleAxis(*this, thetaf, axis_f);

        return "[ angle = " + to_string(thetaf) + " axis = " + static_cast<string>(axis_f) + " ]";
    }

    std::ostream& operator<<(std::ostream& os, const Quat& quat) {
        os << "(" << quat.T << ", " << quat.X << ", " << quat.Y << ", " << quat.Z << ")";
        return os;
    }

} /* namespace Divisaction */