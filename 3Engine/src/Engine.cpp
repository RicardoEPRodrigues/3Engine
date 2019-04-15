/*
 * File ThreeEngine.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <sstream>
#include <fstream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL_image.h>

#include "Engine.h"
#include "Time/SDLTimeCalculator.h"
#include "OpenGLUtils.h"

using json = nlohmann::json;

// NVIDIA Dedicated Graphics (Optimus)
#if OS_WIN
#include <windows.h>
extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

#if OS_LINUX
//#define GAMEMODE_AUTO

#include "Utilities/gamemode_client.h"

#endif

namespace ThreeEngine {

    Engine::Engine() = default;

    Engine::~Engine() = default;

    /////////////////////////////////////////////////////////////////////// SETUP

    void Engine::Init(int argc, char** argv) {
        CheckSystemInfo();
        SetupConfig();
        SetupGamemode();
        SetupSDL(argc, argv);
        SetupGLEW();
        CheckOpenGLInfo();
        SetupOpenGL();
        Time::SetTimeCalculator(new SDLTimeCalculator());
        OnInit();
    }

    void Engine::CheckSystemInfo() {
#if OS_WIN
        Debug::Log("3Engine running in Windows.");
#elif OS_MAC
        Debug::Log("3Engine running in Mac.");
#elif OS_LINUX
        Debug::Log("3Engine running in Linux.");
#endif
    }

    void Engine::SetupConfig() {
        // Assuming always the same path config/SetupConfig.json
        std::ifstream file("config/SetupConfig.json");
        if (file.good()) {

            Debug::Log("Using SetupConfig JSON file.");

            json config;
            file >> config;

            this->config = json::merge(this->config, config);
        }
    }

    void Engine::SetupRuntimeConfig() {
        // Assuming always the same path config/SetupConfig.json
        std::ifstream file("config/RuntimeConfig.json");
        if (file.good()) {
            json runtimeConfig;
            file >> runtimeConfig;

            if (this->runtimeConfig != runtimeConfig) {
                this->runtimeConfig = json::merge(this->runtimeConfig, runtimeConfig);

                if (this->runtimeConfig["viewport"].is_object() &&
                    this->runtimeConfig["viewport"]["clearColor"].is_array()) {
                    glClearColor(this->runtimeConfig["viewport"]["clearColor"][0],
                                 this->runtimeConfig["viewport"]["clearColor"][1],
                                 this->runtimeConfig["viewport"]["clearColor"][2],
                                 this->runtimeConfig["viewport"]["clearColor"][3]);
                }
            }
        }
    }

    void Engine::SetupGamemode() const {
#ifdef OS_LINUX
        if (gamemode_request_start() != 0) {
            Debug::Warn("Gamemode failed to start: %s\n", gamemode_error_string());
        }

        int status = gamemode_query_status();
        if (status > 0) {
            Debug::Log("Gamemode is running. Status %d", status);
        }
#endif
    }

    void Engine::CleanupGamemode() const {
#ifdef OS_LINUX
        if (gamemode_request_end() != 0) {
            Debug::Warn("Gamemode failed to end: %s\n", gamemode_error_string());
        }
#endif
    }

    void Engine::SetupSDL(int, char**) {

        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            Debug::Error("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        int glMajor = config["opengl"]["major"];
        int glMinor = config["opengl"]["minor"];

#if OS_MAC
        if (glMajor == 4) {
            glMinor = glMinor > 1 ? 1 : glMinor;
        }
#endif

        Debug::Log("Running OpenGL %d.%d", glMajor, glMinor);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glMajor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glMinor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        //Create window
        std::string caption = config["window"]["caption"];
        gWindow = SDL_CreateWindow(caption.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, config["window"]["x"],
                                   config["window"]["y"], SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            Debug::Error("Window could not be created! SDL Error: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        //Initialize PNG loading
        unsigned imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!((unsigned) IMG_Init(imgFlags) & imgFlags)) {
            Debug::Error("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            exit(EXIT_FAILURE);
        }

        //Create context
        gContext = SDL_GL_CreateContext(gWindow);
        if (gContext == nullptr) {
            Debug::Error("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        //Use Vsync
        if (SDL_GL_SetSwapInterval(config["window"]["vsync"]) < 0) {
            Debug::Warn("Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        }

    }

    void Engine::SetupGLEW() {
        glewExperimental = GL_TRUE;
        // Allow extension entry points to be loaded even if the extension isn't
        // present in the driver's extensions string.
        GLenum result = glewInit();
        if (result != GLEW_OK) {
            Debug::Error("ERROR GLEW Init: %s", glewGetString(result));
            exit(EXIT_FAILURE);
        }
        CheckOpenGLError("Failed to setup GLEW.");
    }

    void Engine::SetupOpenGL() {
        glClearColor(config["viewport"]["clearColor"][0], config["viewport"]["clearColor"][1],
                     config["viewport"]["clearColor"][2], config["viewport"]["clearColor"][3]);
        // Z Test
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);
        glDepthRange(config["viewport"]["depthRange"][0], config["viewport"]["depthRange"][1]);
        glClearDepth(config["viewport"]["clearDepth"]);
        // Backface culling with front face detected using Counter Clockwise hand
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        // Transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Engine::CheckOpenGLInfo() {
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
        Debug::Log("OpenGL Renderer: %s ( %s )", renderer, vendor);
        Debug::Log("OpenGL version: %s", version);
        Debug::Log("GLSL version: %s", glslVersion);
    }

    void Engine::Run() {
        isRunning = true;

        //Event handler
        SDL_Event e;

        //While application is running
        while (isRunning) {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit
                if (e.type == SDL_QUIT) {
                    isRunning = false;
                }
                //Keyboard Events
                if (e.type == SDL_KEYDOWN) {
                    input.NormalKeysDown(e.key.keysym.sym);
                }
                if (e.type == SDL_KEYUP) {
                    input.NormalKeysUp(e.key.keysym.sym);
                }
                // Mouse Events
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    input.MouseButtonDown(e.button.button);
                }
                if (e.type == SDL_MOUSEBUTTONUP) {
                    input.MouseButtonUp(e.button.button);
                }
                if (e.type == SDL_MOUSEMOTION) {
                    input.MouseMove(e.motion.x, e.motion.y);
                }
                if (e.type == SDL_MOUSEWHEEL) {
                    input.MouseScroll(e.wheel.x, e.wheel.y);
                }
                //Window event occured
                if (e.type == SDL_WINDOWEVENT) {
                    switch (e.window.event) {
                        //Get new dimensions and repaint on window size change
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            Reshape(e.window.data1, e.window.data2);
                            break;
                        default:
                            break;
                    }
                }
            }
            Display();
            Idle();
            Timer();
        }

        Cleanup();
    }

    void Engine::Exit() {
        isRunning = false;
    }

    /////////////////////////////////////////////////////////////////////// CALLBACKS

    void Engine::Cleanup() {
        glUseProgram(0);
        glBindVertexArray(0);
        OnCleanup();
        for (auto& actor : actors) {
            delete actor;
        }
        CleanupGamemode();
    }

    void Engine::Display() {
        ++FrameCount;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        PreDraw();
        for (auto& actor : actors) {
            actor->Draw();
        }
        PostDraw();
        //Update screen
        SDL_GL_SwapWindow(gWindow);
    }

    void Engine::Idle() {
        Time::Update();
        Update();
        input.Update();
        // TODO return bool, if true redisplay, don't if false.
    }

    void Engine::Reshape(int w, int h) {
        config["window"]["x"] = w;
        config["window"]["y"] = h;
        glViewport(0, 0, config["window"]["x"], config["window"]["y"]);
        OnReshape(w, h);
    }

    milliseconds counter = 0;

    void Engine::Timer() {
        if (counter < 1000) {
            counter += Time::Delta();
            return;
        }
        counter = 0;

        SetupRuntimeConfig();

        std::string caption = config["window"]["caption"];
        // Update Window Title
        std::stringstream oss;
        oss << caption << ": " << FrameCount << " FPS @ ("
            << config["window"]["x"] << "x"
            << config["window"]["y"] << ")";
        std::string s = oss.str();
        FrameCount = 0;
        SDL_SetWindowTitle(gWindow, s.c_str());
    }

    SDL_Window* Engine::GetWindow() {
        return this->gWindow;
    }

} /* namespace Divisaction */