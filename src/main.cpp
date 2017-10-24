//
// (c)2013-17 by Carlos Martinho, Ricardo Rodrigues
//

#include <iostream>
#include "Tangram3D/Tangram3D.h"

using namespace ThreeEngine;

// NVIDIA Dedicated Graphics
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(0)));

    {
        Tangram3D engine;
        engine.shapeToShow = Tangram3D::ShapeType3D::CUBE;
        engine.Init(argc, argv);
        engine.Run();
    }
    
    exit(EXIT_SUCCESS);
}