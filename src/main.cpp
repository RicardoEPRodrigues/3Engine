//
// (c)2013-17 by Carlos Martinho, Ricardo Rodrigues
//

#include <iostream>
#include "Engine.h"

#include "Math/Vector.h"
#include "Debug.h"

using namespace ThreeEngine;

// NVIDIA Dedicated Graphics
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int main(int argc, char* argv[]) {
    Vector vector = Vector::ZeroVector;
    Debug::Log(vector);
    vector = 1.0f - vector;
    vector = 1.0f * vector;
    vector = 1.0f / vector;
    vector = 1.0f + vector;
    vector += 1.0f;
    vector -= 1.0f;
    vector *= 1.0f;
    vector /= 1.0f;
    Debug::Log(vector);
    Debug::Log(std::to_string(vector.DistSquared()));
    Debug::Log(std::to_string(vector.Dist()));

    Vector vector1 = Vector::ForwardVector;
    float contribution = vector1 | vector1;
    Debug::Log(std::to_string(contribution));
    Debug::Log(Vector::ForwardVector.ProjectOnTo(Vector::OneVector));

    Debug::Log(Vector::ForwardVector ^ Vector::LeftVector);
    Debug::Log(Vector::LeftVector ^ Vector::ForwardVector);

    Vector additionInversion = -(Vector::ForwardVector + Vector::LeftVector);

    std::cout << vector << std::endl;
    //std::cin >> vector;


    Engine engine;
    engine.init(argc, argv);
    engine.run();
    exit(EXIT_SUCCESS);
}