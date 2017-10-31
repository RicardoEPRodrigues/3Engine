//
// (c)2013-17 by Carlos Martinho, Ricardo Rodrigues
//

#include <iostream>
#include "Examples/Quaternion/Quaternion.h"
#include "Engine/Math/Quat.h"

using namespace ThreeEngine;

// NVIDIA Dedicated Graphics
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(0)));

    {
        Quat q = Quat::FromAngleAxis(90, Vector(0, 0, 1));
        Quat qi = q.Inverse();
        Vector4 v = {1, 0, 0, 0};
        Quat r = q * Quat(v) * qi;
        Debug::Log(r);

        Quaternion engine;
        engine.shapeToShow = Quaternion::ShapeType3D::CUBE;
        engine.Init(argc, argv);
        engine.Run();
    }

    exit(EXIT_SUCCESS);
}