/*
 * File Quat.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_QUAT_H
#define THREEENGINE_QUAT_H

#include "Maths.h"
#include "Vector.h"
#include "Matrix.h"

namespace ThreeEngine {

    struct Quat {
        public:

            /** The quaternion's X-component. */
            number T;

            /** The quaternion's Y-component. */
            number X;

            /** The quaternion's Z-component. */
            number Y;

            /** The quaternion's W-component. */
            number Z;

            Quat();

            Quat(number InX, number InY, number InZ, number InW);

            /**
             * Copy constructor.
             *
             * @param Q A Quaternion object to use to create new quaternion from.
             */
            Quat(const Quat& Q);

            Quat(const Vector& v);

            virtual ~Quat();

            Quat& operator=(const Quat& Other);

            void Clean();

            number DistSquared() const;

            number Dist() const;

            Quat Normalize() const;

            Quat Conjugate() const;

            Quat Inverse() const;

            Quat operator*(number s) const;

            Quat operator*(const Quat& q) const;

            Quat operator+(const Quat& q) const;

            friend Quat operator*(const number& value, const Quat& quat);

            bool operator==(const Quat& q) const;

            Matrix ToMatrix();

            operator std::string();

            std::string ToStringAngleAxis();

            friend std::ostream& operator<<(std::ostream& os, const Quat& quat);

            static Quat FromAngleAxis(number theta, Vector axis);

            static void ToAngleAxis(const Quat& q, number& theta, Vector& axis);

            static Quat FromAngleAxis(number theta, Vector4 axis);

            static void ToAngleAxis(const Quat& q, number& theta, Vector4& axis);

            static Quat Lerp(const Quat& q0, const Quat& q1, number time);

            static Quat Slerp(const Quat& q0, const Quat& q1, number time);

            static bool Equals(const Quat& q0, const Quat& q1);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_QUAT_H
