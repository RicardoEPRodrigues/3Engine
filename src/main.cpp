//
// (c)2013-17 by Carlos Martinho, Ricardo Rodrigues
//

#include <iostream>
#include "Engine.h"

#include "Math/Vector.h"
#include "Debug.h"

#include <ctime>

using namespace ThreeEngine;

// NVIDIA Dedicated Graphics
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

int main(int argc, char* argv[]) {
    /*Vector vector = Vector::ZeroVector;
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

    std::cout << vector << std::endl;*/
    //std::cin >> vector;

    srand(static_cast <unsigned> (time(0)));

    number max = 1000;
    for (int w = 0; w < 10; w++)
    {
        Vector i = Vector::GetRandom(max);
        Debug::Log(i);
        Vector j = Vector::GetRandom(max);
        Debug::Log(j);
        Vector k = Vector::GetRandom(max);
        Debug::Log(k);
        Vector rightSide = i ^ (j ^ k);
        Debug::Log(rightSide);
        Vector leftSide = (j * (i | k)) - (k * (i | j));
        Debug::Log(leftSide);
        rightSide == leftSide ? Debug::Log("The vectors are equal.") : Debug::Error("The vector are different!");
    }

    Engine engine;
    engine.init(argc, argv);
    engine.run();
    exit(EXIT_SUCCESS);
}