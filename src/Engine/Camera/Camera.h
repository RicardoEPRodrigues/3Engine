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

    class Camera : public IDrawable {
        private:
            GLuint vaoId, vboId;

            Matrix* projection, * view;
        public:
            Matrix transform = Matrix::IdentityMatrix();

            GLuint uniformBlockBidingID;

            Camera();

            explicit Camera(GLuint uniformBlockBidingID);

            Camera(GLuint uniformBlockBidingID, Matrix* projection, Matrix* view);

            ~Camera() override;

            void Init() override;

            void Draw() override;

            Matrix* getProjection() const;

            void SetProjection(Matrix* projection);

            void SetProjection(Matrix const& projection);

            Matrix* GetView() const;

            void SetView(Matrix* view);

            void SetView(Matrix const& view);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CAMERA_H
