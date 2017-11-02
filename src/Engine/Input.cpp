/*
 * File Input.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Input.h"

using namespace std;

namespace ThreeEngine {

    Input::Input() : clickKeys(), specialKeys(), modifierKeys(), mouseKeys() { }

    Input::~Input() = default;

    void Input::updateModifierKeys() {
        for (auto&& modifierKey : modifierKeys) {
            modifierKey.second = false;
        }
        int mod = glutGetModifiers();
        if (mod != 0) {
            modifierKeys[mod] = true;
        }

    }

    void Input::Update() {
        for (auto&& clickKey : clickKeys) {
            if (clickKey.second.first) {
                clickKey.second.second = true;
            }
        }
    }

    void Input::NormalKeysDown(unsigned char key, int, int) {
        clickKeys[key].first = true;
        updateModifierKeys();
    }

    void Input::NormalKeysUp(unsigned char key, int, int) {
        clickKeys[key].first = false;
        clickKeys[key].second = false;
    }

    bool Input::Click(unsigned char key) {
        return clickKeys[key].first && !clickKeys[key].second;
    }

    void Input::SpecialKeysDown(int key, int, int) {
        specialKeys[key] = true;
        updateModifierKeys();
    }

    void Input::SpecialKeysUp(int key, int, int) {
        specialKeys[key] = false;
    }

    bool Input::operator[](unsigned char key) {
        return clickKeys[key].first;
    }

    bool Input::operator[](SpecialKeys key) {
        return specialKeys[key];
    }

    bool Input::operator[](ModifierKeys key) {
        return modifierKeys[key];
    }

    bool Input::operator[](MouseKeys key) {
        return mouseKeys[key];
    }

    void Input::MouseClick(int button, int state, int, int) {
        mouseKeys[button] = state == GLUT_DOWN;
    }

    void Input::MouseMove(int x, int y) {
        mouseScreenLocation.X = (number) x;
        mouseScreenLocation.Y = (number) y;
    }

    const Vector2& Input::GetMouseScreenLocation() const {
        return mouseScreenLocation;
    }

    void Input::SetMouseScreenLocation(int const & x, int const & y) {
        glutWarpPointer(x, y);
    }

    void Input::SetMouseCursor(MouseCursor cursor) {
        glutSetCursor(cursor);
    }

} /* namespace Divisaction */