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
#include "Time/GlutTimeCalculator.h"
#include "OpenGLUtils.h"

using json = nlohmann::json;

namespace ThreeEngine {

    Engine* Engine::instance = nullptr;

    Engine::Engine() {
        instance = this;
    }

    Engine::~Engine() = default;

    Engine* Engine::Instance() {
        return instance;
    }

    /////////////////////////////////////////////////////////////////////// SETUP

    void Engine::Init(int argc, char** argv) {
        CheckSystemInfo();
        SetupConfig();
        SetupGLUT(argc, argv);
        SetupGLEW();
        CheckOpenGLInfo();
        SetupOpenGL();
        Time::SetTimeCalculator(new GlutTimeCalculator());
        OnInit();
        SetupCallbacks();
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

    void Engine::SetupGLUT(int argc, char** argv) {
        glutInit(&argc, argv);

        glutInitContextVersion(config["opengl"]["major"], config["opengl"]["minor"]);
        glutInitContextProfile(GLUT_CORE_PROFILE);
        //glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
        glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
        //glutInitContextFlags(GLUT_DEBUG);

        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

        glutInitWindowSize(config["window"]["x"], config["window"]["y"]);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        std::string caption = config["window"]["caption"];
        WindowHandle = glutCreateWindow(caption.c_str());
        if (WindowHandle < 1) {
            Debug::Error("ERROR: Could not create a new rendering window.");
            exit(EXIT_FAILURE);
        }
    }

    void Engine::SetupGLEW() {
        glewExperimental = GL_TRUE;
        // Allow extension entry points to be loaded even if the extension isn't
        // present in the driver's extensions string.
        GLenum result = glewInit();
        if (result != GLEW_OK) {
            Debug::Error("ERROR glewInit: %s", glewGetString(result));
            exit(EXIT_FAILURE);
        }
        CheckOpenGLError("Failed to setup GLEW.");
    }

    void Engine::SetupOpenGL() {
        glClearColor(config["viewport"]["clearColor"][0], config["viewport"]["clearColor"][1], config["viewport"]["clearColor"][2], config["viewport"]["clearColor"][3]);
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

    void Engine::SetupCallbacks() {
        glutCloseFunc(Cleanup);
        glutDisplayFunc(Display);
        glutIdleFunc(Idle);
        glutReshapeFunc(Reshape);
        glutTimerFunc(0, Timer, 0);

        // Keyboard Input
        glutKeyboardFunc(NormalKeysDown);
        glutKeyboardUpFunc(NormalKeysUp);
        glutSpecialFunc(SpecialKeysDown);
        glutSpecialUpFunc(SpecialKeysUp);

        // Mouse Input
        glutMouseFunc(MouseClick);
        glutMotionFunc(MouseMove);
        glutPassiveMotionFunc(MouseMove);
    }

    void Engine::Run() {
        glutMainLoop();
    }

    void Engine::Exit() {
        glutLeaveMainLoop();
    }

    /////////////////////////////////////////////////////////////////////// CALLBACKS

    void Engine::Cleanup() {
        glUseProgram(0);
        glBindVertexArray(0);
        instance->OnCleanup();
        for (auto& actor : instance->actors) {
            delete actor;
        }
    }

    void Engine::Display() {
        ++instance->FrameCount;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Time::Update();
        instance->PreDraw();
        for (auto& actor : instance->actors) {
            actor->Draw();
        }
        instance->PostDraw();
        glutSwapBuffers();
    }

    void Engine::Idle() {
        // TODO Insert Updates here
        instance->input.Update();
        glutPostRedisplay();
    }

    void Engine::Reshape(int w, int h) {
        instance->config["window"]["x"] = w;
        instance->config["window"]["y"] = h;
        glViewport(0, 0, instance->config["window"]["x"], instance->config["window"]["y"]);
        instance->OnReshape(w, h);
    }

    void Engine::Timer(int) {
        instance->SetupRuntimeConfig();

        std::string caption = instance->config["window"]["caption"];
        // Update Window Title
        std::ostringstream oss;
        oss << caption << ": " << instance->FrameCount << " FPS @ ("
            << instance->config["window"]["x"] << "x"
            << instance->config["window"]["y"] << ")";
        std::string s = oss.str();
        glutSetWindow(instance->WindowHandle);
        glutSetWindowTitle(s.c_str());
        instance->FrameCount = 0;
        glutTimerFunc(1000, Timer, 0);
    }

    void Engine::NormalKeysDown(unsigned char key, int x, int y) {
        instance->input.NormalKeysDown(key, x, y);
    }

    void Engine::NormalKeysUp(unsigned char key, int x, int y) {
        instance->input.NormalKeysUp(key, x, y);
    }

    void Engine::SpecialKeysDown(int key, int x, int y) {
        instance->input.SpecialKeysDown(key, x, y);
    }

    void Engine::SpecialKeysUp(int key, int x, int y) {
        instance->input.SpecialKeysUp(key, x, y);
    }

    void Engine::MouseClick(int button, int state, int x, int y) {
        instance->input.MouseClick(button, state, x, y);
    }

    void Engine::MouseMove(int x, int y) {
        instance->input.MouseMove(x,y);
    }

} /* namespace Divisaction */