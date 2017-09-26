/*
 * File ThreeEngine.cpp in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <sstream>
#include <fstream>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Engine.h"
#include "Debug.h"

using json = nlohmann::json;

namespace ThreeEngine {

    Engine* Engine::instance = nullptr;

    Engine::Engine() {
        instance = this;
    }

    Engine::~Engine() = default;

    /////////////////////////////////////////////////////////////////////// SETUP

    void Engine::init(int argc, char* argv[]) {
        checkSystemInfo();
        setupConfig();
        setupGLUT(argc, argv);
        setupGLEW();
        checkOpenGLInfo();
        setupOpenGL();
        setupCallbacks();
    }

    void Engine::checkSystemInfo() {
#if OS_WIN
        Debug::Log("3Engine running in Windows.");
#elif OS_MAC
        Debug::Log("3Engine running in Mac.");
#elif OS_LINUX
        Debug::Log("3Engine running in Linux.");
#endif
    }

    void Engine::setupConfig() {
        // Assuming always the same path config/SetupConfig.json
        std::ifstream file("config/SetupConfig.json");
        if (file.good()) {

            Debug::Log("Using SetupConfig JSON file.");

            json config;
            file >> config;

            this->config = json::merge(this->config, config);
        }
    }

    void Engine::setupRuntimeConfig() {
        // Assuming always the same path config/SetupConfig.json
        std::ifstream file("config/RuntimeConfig.json");
        if (file.good()) {
            json runtimeConfig;
            file >> runtimeConfig;

            if (this->runtimeConfig != runtimeConfig)
            {
                this->runtimeConfig = json::merge(this->runtimeConfig, runtimeConfig);

                if (this->runtimeConfig["viewport"].is_object() && this->runtimeConfig["viewport"]["clearColor"].is_array())
                {
                    glClearColor(this->runtimeConfig["viewport"]["clearColor"][0], this->runtimeConfig["viewport"]["clearColor"][1], this->runtimeConfig["viewport"]["clearColor"][2], this->runtimeConfig["viewport"]["clearColor"][3]);
                }
            }
        }
    }

    void Engine::setupGLUT(int argc, char* argv[]) {
        glutInit(&argc, argv);

        glutInitContextVersion(config["opengl"]["major"], config["opengl"]["minor"]);
        glutInitContextProfile(GLUT_CORE_PROFILE);
        //glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
        glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
        //glutInitContextFlags(GLUT_DEBUG);

        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

        glutInitWindowSize(config["window"]["x"], config["window"]["y"]);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        WindowHandle = glutCreateWindow(config["window"]["caption"].dump().c_str());
        if (WindowHandle < 1) {
            Debug::Error("ERROR: Could not create a new rendering window.");
            exit(EXIT_FAILURE);
        }
    }

    void Engine::setupGLEW() {
        glewExperimental = GL_TRUE;
        // Allow extension entry points to be loaded even if the extension isn't
        // present in the driver's extensions string.
        GLenum result = glewInit();
        if (result != GLEW_OK) {
            Debug::Error("ERROR glewInit: %s", glewGetString(result));
            exit(EXIT_FAILURE);
        }
        GLenum err_code;
        while ((err_code = glGetError()) != GL_NO_ERROR) {
            Debug::GLError(err_code);
        }
        // You might get GL_INVALID_ENUM when loading GLEW.
    }

    void Engine::setupOpenGL() {
        glClearColor(config["viewport"]["clearColor"][0], config["viewport"]["clearColor"][1], config["viewport"]["clearColor"][2], config["viewport"]["clearColor"][3]);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);
        glDepthRange(config["viewport"]["depthRange"][0], config["viewport"]["depthRange"][1]);
        glClearDepth(config["viewport"]["clearDepth"]);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void Engine::checkOpenGLInfo() {
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
        Debug::Log("OpenGL Renderer: %s ( %s )", renderer, vendor);
        Debug::Log("OpenGL version: %s", version);
        Debug::Log("GLSL version: %s", glslVersion);
    }

    void Engine::setupCallbacks() {
        glutCloseFunc(cleanup);
        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutReshapeFunc(reshape);
        glutTimerFunc(0, timer, 0);
    }

    void Engine::run() {
        glutMainLoop();
    }

    /////////////////////////////////////////////////////////////////////// CALLBACKS

    void Engine::cleanup() {
    }

    void Engine::display() {
        ++instance->FrameCount;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Draw something
        glutSwapBuffers();
    }

    void Engine::idle() {
        glutPostRedisplay();
    }

    void Engine::reshape(int w, int h) {
        instance->config["window"]["x"] = w;
        instance->config["window"]["y"] = h;
        glViewport(0, 0, instance->config["window"]["x"], instance->config["window"]["y"]);
    }

    void Engine::timer(int) {
        instance->setupRuntimeConfig();

        // Update Window Title
        std::ostringstream oss;
        oss << instance->config["window"]["caption"] << ": " << instance->FrameCount << " FPS @ ("
            << instance->config["window"]["x"] << "x"
            << instance->config["window"]["y"] << ")";
        std::string s = oss.str();
        glutSetWindow(instance->WindowHandle);
        glutSetWindowTitle(s.c_str());
        instance->FrameCount = 0;
        glutTimerFunc(1000, timer, 0);
    }

} /* namespace Divisaction */