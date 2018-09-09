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
        int mod = 0; // TODO Inputs glutGetModifiers();
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
        mouseKeys[SCROLL_UP] = false;
        mouseKeys[SCROLL_DOWN] = false;
    }

    void Input::NormalKeysDown(unsigned char key) {
        clickKeys[tolower(key)].first = true;
        updateModifierKeys();
    }

    void Input::NormalKeysUp(unsigned char key) {
        clickKeys[tolower(key)].first = false;
        clickKeys[tolower(key)].second = false;
    }

    bool Input::Click(unsigned char key) {
        return clickKeys[tolower(key)].first && !clickKeys[tolower(key)].second;
    }

    void Input::SpecialKeysDown(int key) {
        specialKeys[key] = true;
        updateModifierKeys();
    }

    void Input::SpecialKeysUp(int key) {
        specialKeys[key] = false;
    }

    bool Input::operator[](unsigned char key) {
        return clickKeys[tolower(key)].first;
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

    void Input::MouseButtonDown(int button) {
        mouseKeys[button] = true;
    }

    void Input::MouseButtonUp(int button) {
        mouseKeys[button] = false;
    }

    void Input::MouseMove(int x, int y) {
        mouseScreenLocation.X = (number) x;
        mouseScreenLocation.Y = (number) y;
    }

    const Vector2& Input::GetMouseScreenLocation() const {
        return mouseScreenLocation;
    }

    void Input::SetMouseScreenLocation(int const & x, int const & y) {
//        glutWarpPointer(x, y);
    }

    void Input::SetMouseCursor(MouseCursor cursor) {
//        glutSetCursor(cursor);
    }

} /* namespace Divisaction */