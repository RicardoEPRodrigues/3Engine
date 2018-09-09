/*
 * File ThreeEngine.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_ENGINE_H
#define THREEENGINE_ENGINE_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include "Utilities/json.hpp"
#include "IDrawable.h"
#include "Input.h"
#include "Time/Time.h"

namespace ThreeEngine {

    class Engine {
        private:
            //The window we'll be rendering to
            SDL_Window* gWindow = NULL;

            //OpenGL context
            SDL_GLContext gContext;

            bool isRunning = 0;

            int WindowHandle = 0;
            unsigned int FrameCount = 0;

            void Cleanup();

            void Display();

            void Idle();

            void Reshape(int w, int h);

            void Timer(int value);

        protected:

            std::vector<IDrawable*> actors;

            void CheckSystemInfo();

            void SetupConfig();

            void SetupRuntimeConfig();

            void SetupSDL(int argc, char** argv);

            void SetupGLEW();

            void SetupOpenGL();

            void CheckOpenGLInfo();

            /**
             * Called when a new frame is to be drawn, before Actors are drawn.
             */
            virtual void PreDraw() { }

            /**
             * Called when a new frame is to be drawn, after Actors are drawn.
             */
            virtual void PostDraw() { }

            /**
             * Called when OpenGL has been prepared, yet before the initialization of the Actors
             */
            virtual void OnInit() { }

            /**
             * Called when before when no rendering is being done.
             */
            virtual void Update() { }

            /**
             * Called when cleaning OpenGL. Any OpenGL related cleaning needs to be done here.
             * This is called before deleting Actors
             */
            virtual void OnCleanup() { }

            /**
             * Called when the window changes size.
             *
             * @param w window width
             * @param h window height
             */
            virtual void OnReshape(int, int) { }

        public:


            Input input;

            Engine();

            virtual ~Engine();

            void Init(int argc, char** argv);

            void Run();

            void Exit();

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

            SDL_Window* GetWindow();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_ENGINE_H
