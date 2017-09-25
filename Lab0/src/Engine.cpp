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
#include "json.hpp"

using json = nlohmann::json;

namespace ThreeEngine {

    Engine* Engine::instance = nullptr;

    Engine::Engine() {
        instance = this;
        windowCaption = "Hello World 3Engine";
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

            json windowInfo = config["window"];
            if (windowInfo != nullptr) {
                WinX = windowInfo["x"];
                WinY = windowInfo["y"];
                windowCaption = windowInfo["caption"];
            }

            json openglOptions = config["opengl"];
            if (openglOptions != nullptr) {
                openGLMajorVersion = openglOptions["major"];
                openGLMinorVersion = openglOptions["minor"];
            }

            json viewportOptions = config["viewport"];
            if (viewportOptions != nullptr) {
                int i = 0;
                for (json::iterator it = viewportOptions["clearColor"].begin();
                     it != viewportOptions["clearColor"].end(); ++it) {
                    clearColor[i] = *it;
                    ++i;
                }
                i = 0;
                for (json::iterator it = viewportOptions["depthRange"].begin();
                     it != viewportOptions["depthRange"].end(); ++it) {
                    depthRange[i] = *it;
                    ++i;
                }
                clearDepth = viewportOptions["clearDepth"];
            }
        }
    }

    void Engine::setupGLUT(int argc, char* argv[]) {
        glutInit(&argc, argv);

        glutInitContextVersion(openGLMajorVersion, openGLMinorVersion);
        glutInitContextProfile(GLUT_CORE_PROFILE);
        //glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
        glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
        //glutInitContextFlags(GLUT_DEBUG);

        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

        glutInitWindowSize(WinX, WinY);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        WindowHandle = glutCreateWindow(windowCaption.c_str());
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
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);
        glDepthRange(depthRange[0], depthRange[1]);
        glClearDepth(clearDepth);
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
        instance->WinX = w;
        instance->WinY = h;
        glViewport(0, 0, instance->WinX, instance->WinY);
    }

    void Engine::timer(int) {
        // Update Window Title
        std::ostringstream oss;
        oss << instance->windowCaption << ": " << instance->FrameCount << " FPS @ ("
            << instance->WinX << "x"
            << instance->WinY << ")";
        std::string s = oss.str();
        glutSetWindow(instance->WindowHandle);
        glutSetWindowTitle(s.c_str());
        instance->FrameCount = 0;
        glutTimerFunc(1000, timer, 0);
    }

} /* namespace Divisaction */