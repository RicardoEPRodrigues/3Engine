//
// (c)2013-17 by Carlos Martinho, Ricardo Rodrigues
//

#include <iostream>
#include <cstdlib>
#include "Engine.h"
#include "Math/Matrix.h"
#include "Debug.h"

using namespace ThreeEngine;

// NVIDIA Dedicated Graphics
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(0)));

    Engine engine;
    engine.init(argc, argv);
    engine.run();
    exit(EXIT_SUCCESS);
}