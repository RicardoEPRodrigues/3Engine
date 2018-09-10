/*
 * File Input.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Input.h"

using namespace std;

namespace ThreeEngine {

    Input::Input() : clickKeys(), specialKeys(), mouseKeys() {}

    Input::~Input() {
        if (cursor) {
            SDL_FreeCursor(cursor);
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

    void Input::NormalKeysDown(int key) {
        clickKeys[tolower(key)].first = true;
    }

    void Input::NormalKeysUp(int key) {
        clickKeys[tolower(key)].first = false;
        clickKeys[tolower(key)].second = false;
    }

    bool Input::Click(unsigned char key) {
        return clickKeys[tolower(key)].first && !clickKeys[tolower(key)].second;
    }

    bool Input::operator[](unsigned char key) {
        return clickKeys[tolower(key)].first;
    }

    bool Input::operator[](SpecialKeys key) {
        switch (key) {
            case SHIFT:
                return clickKeys[SHIFT_LEFT].first || clickKeys[SHIFT_RIGHT].first;
            case CTRL:
                return clickKeys[CTRL_LEFT].first || clickKeys[CTRL_RIGHT].first;
            case ALT:
                return clickKeys[ALT_LEFT].first || clickKeys[ALT_RIGHT].first;
            default:
                return clickKeys[key].first;
        }
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

    void Input::MouseScroll(int, int y) {
        mouseKeys[SCROLL_UP] = y > 0;
        mouseKeys[SCROLL_DOWN] = y < 0;
    }

    void Input::MouseMove(int x, int y) {
        mouseScreenLocation.X = (number) x;
        mouseScreenLocation.Y = (number) y;
    }

    const Vector2& Input::GetMouseScreenLocation() const {
        return mouseScreenLocation;
    }

    void Input::SetMouseScreenLocation(SDL_Window* window, int const& x, int const& y) {
        SDL_WarpMouseInWindow(window, x, y);
    }

    void Input::SetMouseCursor(MouseCursor cursorDesign) {
        if (cursorDesign == CURSOR_NONE) {
            SDL_ShowCursor(false);
            return;
        }
        SDL_ShowCursor(true);

        if (cursorDesign == CURSOR_INHERIT) {
            if (cursor) {
                SDL_SetCursor(cursor);
                return;
            }
            cursorDesign = CURSOR_ARROW;
        }
        if (cursor) {
            SDL_FreeCursor(cursor);
        }
        cursor = SDL_CreateSystemCursor((SDL_SystemCursor) cursorDesign);
        SDL_SetCursor(cursor);
    }

} /* namespace Divisaction */