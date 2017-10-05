/*
 * File ThreeEngine.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_ENGINE_H
#define THREEENGINE_ENGINE_H

#include <string>
#include "json.hpp"

namespace ThreeEngine {

    class Engine {
        private:
            // GLUT needs static method for it's callback functions.
            static Engine* instance;

            int WindowHandle = 0;
            unsigned int FrameCount = 0;
        protected:

            void checkSystemInfo();

            void setupConfig();

            void setupRuntimeConfig();

            void setupGLUT(int argc, char* argv[]);

            void setupGLEW();

            void setupOpenGL();

            void checkOpenGLInfo();

            void setupCallbacks();

            static void cleanup();

            static void display();

            static void idle();

            static void reshape(int w, int h);

            static void timer(int value);

        public:
            Engine();

            virtual ~Engine();

            void init(int argc, char* argv[]);

            void run();

            nlohmann::json config = {
                    {"window", {
                                       {"x", 800},
                                       {"y" , 600},
                                       {"caption", "Hello World"}
                               }},
                    {"opengl", {
                                       {"major", 4},
                                       {"minor", 3}
                               }},
                    {"viewport", {
                                       {"clearColor",{0.1f, 0.1f, 0.1f, 1.0f}},
                                       {"depthRange",{0.0f, 1.0f}},
                                       {"clearDepth", 1.0f}
                               }}
            };

            nlohmann::json runtimeConfig;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_ENGINE_H
