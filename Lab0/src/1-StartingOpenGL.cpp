///////////////////////////////////////////////////////////////////////
//
// Assignment 1 consists in the following:
//
// - Update your graphics drivers to their latest versions.
// - Download the libraries: Glew and FreeGlut for your system.
// - Create a project to compile, link and run the code provided in this 
//   section in your favourite programming environment 
//   (course will use VS2017 Community Edition).
// - Verify what OpenGL contexts your computer can support, a minimum of 
//   OpenGL 3.3 support is required for this course.
//
// Further suggestions to verify your understanding of the concepts explored:
// - Change the program so display is called at 60 FPS.
// - Create an abstract class for an OpenGL application.
//
// (c)2013-17 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "GL/freeglut.h"

#define CAPTION "Hello Blank World"

// NVIDIA Dedicated Graphics
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup() {
}

void display() {
    ++FrameCount;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Draw something
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void reshape(int w, int h) {
    WinX = w;
    WinY = h;
    glViewport(0, 0, WinX, WinY);
}

void timer(int value) {
    std::ostringstream oss;
    oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
    std::string s = oss.str();
    glutSetWindow(WindowHandle);
    glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

/////////////////////////////////////////////////////////////////////// SETUP

void setupCallbacks() {
    glutCloseFunc(cleanup);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
}

void checkOpenGLInfo() {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
    std::cout << "OpenGL version " << version << std::endl;
    std::cout << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL() {
    checkOpenGLInfo();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glDepthRange(0.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void setupGLEW() {
    glewExperimental = GL_TRUE;
    // Allow extension entry points to be loaded even if the extension isn't 
    // present in the driver's extensions string.
    GLenum result = glewInit();
    if (result != GLEW_OK) {
        std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
        exit(EXIT_FAILURE);
    }
    GLenum err_code = glGetError();
    // You might get GL_INVALID_ENUM when loading GLEW.
}

void setupGLUT(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    //glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    //glutInitContextFlags(GLUT_DEBUG);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    glutInitWindowSize(WinX, WinY);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    WindowHandle = glutCreateWindow(CAPTION);
    if (WindowHandle < 1) {
        std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void init(int argc, char* argv[]) {
    setupGLUT(argc, argv);
    setupGLEW();
    setupOpenGL();
    setupCallbacks();
}

int main(int argc, char* argv[]) {
    init(argc, argv);

#if OS_WIN
    std::cout << "Engine running in Windows." << std::endl;
#elif OS_MAC
    std::cout << "Engine running in Mac." << std::endl;
#elif OS_LINUX
    std::cout << "Engine running in Linux." << std::endl;
#endif

    glutMainLoop();
    exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////