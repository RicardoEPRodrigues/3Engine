/*
 * File Camera.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CAMERA_H
#define THREEENGINE_CAMERA_H

#include <GL/glew.h>
#include "../IDrawable.h"

namespace ThreeEngine {

    class CameraMatrix : public Matrix {
        public:
            CameraMatrix() : Matrix() {}

            explicit CameraMatrix(const Matrix& other) : Matrix(other) {}

            virtual void OnReshape(int, int) {}
    };

    class PerspectiveCameraMatrix : public CameraMatrix {
        private:
            number FOVy{30};
            number zNear{1};
            number zFar{1000};
        public:
            PerspectiveCameraMatrix();

            PerspectiveCameraMatrix(number FOVy, number width, number height, number zNear,
                                    number zFar);

            explicit PerspectiveCameraMatrix(const CameraMatrix& other) : CameraMatrix(other) {}

            void OnReshape(int w, int h) override;
    };

    class Camera : public IDrawable {
        private:
            GLuint vboId{};

            CameraMatrix* projection, * view;

        public:

            GLuint uniformBlockBidingID;

            Camera();

            explicit Camera(GLuint uniformBlockBidingID);

            Camera(GLuint uniformBlockBidingID, CameraMatrix* projection, CameraMatrix* view);

            ~Camera() override;

            void Init() override;

            void Draw() override;

            CameraMatrix* getProjection() const;

            void SetProjection(CameraMatrix* matrix);

            void SetProjection(CameraMatrix const& matrix);

            CameraMatrix* GetView() const;

            void SetView(CameraMatrix* matrix);

            void SetView(CameraMatrix const& matrix);

            void OnReshape(int w, int h);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CAMERA_H
