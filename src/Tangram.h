/*
 * File Tangram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TANGRAM_H
#define THREEENGINE_TANGRAM_H

#include "Engine.h"
#include "Shader/ShaderProgram.h"

namespace ThreeEngine {

    class Tangram : public Engine {
        private:
            ShaderProgram* shaderProgram;
        public:
            Tangram();

            virtual ~Tangram();

        protected:
            void DrawScene() override;

            void OnInit() override;

            void OnCleanup() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TANGRAM_H
