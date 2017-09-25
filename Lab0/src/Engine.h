/*
 * File ThreeEngine.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_ENGINE_H
#define THREEENGINE_ENGINE_H

namespace ThreeEngine {

    class Engine {
        private:
            // GLUT needs static method for it's callback functions.
            static Engine* instance;

            int WinX = 640, WinY = 480;
            std::string windowCaption;
            int WindowHandle = 0;
            unsigned int FrameCount = 0;

            int openGLMajorVersion = 4;
            int openGLMinorVersion = 3;

            float clearColor[4] = {0.1, 0.1, 0.1, 1.0};
            float depthRange[2] = {0.0, 1.0};
            float clearDepth = 1.0;
        public:
            Engine();

            virtual ~Engine();

            void init(int argc, char* argv[]);

            void checkSystemInfo();

            void setupConfig();

            void setupGLUT(int argc, char* argv[]);

            void setupGLEW();

            void setupOpenGL();

            void checkOpenGLInfo();

            void setupCallbacks();

            void run();

            static void cleanup();

            static void display();

            static void idle();

            static void reshape(int w, int h);

            static void timer(int value);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_ENGINE_H
