/*
 * File Tangram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TANGRAM_H
#define THREEENGINE_TANGRAM_H

#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderProgram.h"
#include "../../Engine/IActor.h"

namespace ThreeEngine {

    class Tangram : public Engine {
        public:
            Tangram();

            ~Tangram() override;

            enum ShapeType {
                SAMPLE,
                TANGRAM,
                HEART,
                FISH
            };

            ShapeType shapeToShow;

        protected:

            void OnInit() override;

            void Shapes();

            void SimpleTangram();

            void Heart();

            void Fish();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TANGRAM_H
