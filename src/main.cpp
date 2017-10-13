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

    Vector v1 = { 1,0,0 };
    Vector v2 = { 0,2,0 };
    Vector v3 = { 0,0,3 };

    Matrix3 v1Rot = Matrix3::RotationMatrix(v1, 90.0f);
    Matrix3 v2Rot = Matrix3::RotationMatrix(v2, 90.0f);
    Matrix3 v3Rot = Matrix3::RotationMatrix(v3, 90.0f);

    std::cout << v1 << " rotated by 90 on axis " << std::endl << v1Rot << " results in " << (v1Rot * v1) << std::endl;
    std::cout << v1 << " rotated by 90 on axis " << std::endl << v2Rot << " results in " << (v2Rot * v1) << std::endl;
    std::cout << v1 << " rotated by 90 on axis " << std::endl << v3Rot << " results in " << (v3Rot * v1) << std::endl;

    std::cout << v2 << " rotated by 90 on axis " << std::endl << v1Rot << " results in " << (v1Rot * v2) << std::endl;
    std::cout << v2 << " rotated by 90 on axis " << std::endl << v2Rot << " results in " << (v2Rot * v2) << std::endl;
    std::cout << v2 << " rotated by 90 on axis " << std::endl << v3Rot << " results in " << (v3Rot * v2) << std::endl;

    std::cout << v3 << " rotated by 90 on axis " << std::endl << v1Rot << " results in " << (v1Rot * v3) << std::endl;
    std::cout << v3 << " rotated by 90 on axis " << std::endl << v2Rot << " results in " << (v2Rot * v3) << std::endl;
    std::cout << v3 << " rotated by 90 on axis " << std::endl << v3Rot << " results in " << (v3Rot * v3) << std::endl;

    Engine engine;
    engine.init(argc, argv);
    engine.run();
    exit(EXIT_SUCCESS);
}