/*
 * File ThreeEngine.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_ENGINE_H
#define THREEENGINE_ENGINE_H

#include <string>
#include "json.hpp"
#include "IActor.h"

namespace ThreeEngine {

    class Engine {
        private:
            // GLUT needs static method for it's callback functions.
            static Engine* instance;

            int WindowHandle = 0;
            unsigned int FrameCount = 0;
        protected:
            std::vector<IActor*> actors;

            void CheckSystemInfo();

            void SetupConfig();

            void SetupRuntimeConfig();

            void SetupGLUT(int argc, char** argv);

            void SetupGLEW();

            void SetupOpenGL();

            void CheckOpenGLInfo();

            void SetupCallbacks();

            static void Cleanup();

            static void Display();

            static void Idle();

            static void Reshape(int w, int h);

            static void Timer(int value);

            /**
             * Called when a new frame is to be drawn, before Actors are drawn.
             */
            virtual void PreDraw() {}

            /**
             * Called when a new frame is to be drawn, after Actors are drawn.
             */
            virtual void PostDraw() {}

            /**
             * Called when OpenGL has been prepared, yet before the initialization of the Actors
             */
            virtual void OnInit() {}

            /**
             * Called when cleaning OpenGL. Any OpenGL related cleaning needs to be done here.
             * This is called before deleting Actors
             */
            virtual void OnCleanup() {}

        public:
            Engine();

            virtual ~Engine();

            void Init(int argc, char** argv);

            void Run();

            nlohmann::json config = {
                    {"window",   {
                                         {"x",          800},
                                         {"y",          600},
                                         {"caption",    "Hello World"}
                                 }},
                    {"opengl",   {
                                         {"major",      4},
                                         {"minor",      3}
                                 }},
                    {"viewport", {
                                         {"clearColor", {0.1f, 0.1f, 0.1f, 1.0f}},
                                         {"depthRange", {0.0f, 1.0f}},
                                         {"clearDepth", 1.0f}
                                 }}
            };

            nlohmann::json runtimeConfig;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_ENGINE_H
