//
// (c)2013-17 by Carlos Martinho, Ricardo Rodrigues
//

#include <iostream>
#include "Engine.h"

using namespace ThreeEngine;

#define CAPTION "Hello Blank World"

// NVIDIA Dedicated Graphics
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int main(int argc, char* argv[]) {
    Engine engine;
    engine.init(argc, argv);
    engine.run();
    exit(EXIT_SUCCESS);
}