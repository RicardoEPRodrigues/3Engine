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
            GLuint vboId{};

            Matrix* projection, * view;
        public:

            GLuint uniformBlockBidingID;

            Camera();

            explicit Camera(GLuint uniformBlockBidingID);

            Camera(GLuint uniformBlockBidingID, Matrix* projection, Matrix* view);

            ~Camera() override;

            void Init() override;

            void Draw() override;

            Matrix* getProjection() const;

            void SetProjection(Matrix* matrix);

            void SetProjection(Matrix const& matrix);

            Matrix* GetView() const;

            void SetView(Matrix* matrix);

            void SetView(Matrix const& matrix);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CAMERA_H
