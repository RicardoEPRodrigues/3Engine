/*
 * File Tangram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TANGRAM_H
#define THREEENGINE_TANGRAM_H

#include "../Engine.h"
#include "../Shader/ShaderProgram.h"
#include "../IActor.h"

namespace ThreeEngine {

    class Tangram : public Engine {
        public:
            Tangram();

            ~Tangram() override;

            void Shapes();

            void SimpleTangram();

            void Heart();

            void Fish();

        protected:

            void OnInit() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TANGRAM_H
