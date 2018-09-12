/*
 * File Input.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_INPUT_H
#define THREEENGINE_INPUT_H

#include <map>
#include <SDL2/SDL.h>
#include "Debug.h"
#include "GL/glew.h"
#include "Math/Vector2.h"

namespace ThreeEngine {

    enum SpecialKeys {
        F1 = SDLK_F1,
        F2 = SDLK_F2,
        F3 = SDLK_F3,
        F4 = SDLK_F4,
        F5 = SDLK_F5,
        F6 = SDLK_F6,
        F7 = SDLK_F7,
        F8 = SDLK_F8,
        F9 = SDLK_F9,
        F10 = SDLK_F10,
        F11 = SDLK_F11,
        F12 = SDLK_F12,
        LEFT_KEY = SDLK_LEFT,
        UP_KEY = SDLK_UP,
        RIGHT_KEY = SDLK_RIGHT,
        DOWN_KEY = SDLK_DOWN,
        PAGE_UP = SDLK_PAGEUP,
        PAGE_DOWN = SDLK_PAGEDOWN,
        HOME = SDLK_HOME,
        END = SDLK_END,
        INSERT = SDLK_INSERT,
        SHIFT,
        SHIFT_LEFT = SDLK_LSHIFT,
        SHIFT_RIGHT = SDLK_RSHIFT,
        CTRL,
        CTRL_LEFT = SDLK_LCTRL,
        CTRL_RIGHT = SDLK_RCTRL,
        ALT,
        ALT_LEFT = SDLK_LALT,
        ALT_RIGHT = SDLK_RALT,
    };

    enum MouseKeys {
        LEFT = SDL_BUTTON_LEFT,
        RIGHT = SDL_BUTTON_RIGHT,
        MIDDLE = SDL_BUTTON_MIDDLE,
        SCROLL_UP = 50,
        SCROLL_DOWN = 51,
    };

    enum MouseCursor {
        CURSOR_ARROW = SDL_SYSTEM_CURSOR_ARROW,
        CURSOR_IBEAM = SDL_SYSTEM_CURSOR_IBEAM,
        CURSOR_WAIT = SDL_SYSTEM_CURSOR_WAIT,
        CURSOR_CROSSHAIR = SDL_SYSTEM_CURSOR_CROSSHAIR,
        CURSOR_HAND = SDL_SYSTEM_CURSOR_HAND,
        CURSOR_INHERIT,
        CURSOR_NONE,
    };

    class Input {
        private:
            std::map<int, std::pair<bool, bool>> clickKeys;
            std::map<int, bool> specialKeys;
            std::map<int, bool> mouseKeys;

            Vector2 mouseScreenLocation;

            SDL_Cursor* cursor{};
        public:

            Input();

            virtual ~Input();

            void NormalKeysDown(int key);

            void NormalKeysUp(int key);

            void MouseButtonDown(int button);

            void MouseButtonUp(int button);

            void MouseMove(int x, int y);

            // Implement using value instead of bool
            void MouseScroll(int x, int y);

            /**
             * Check if key is pressed
             * @param key
             * @return True if key is pressed, false otherwise.
             */
            bool operator[](unsigned char key);

            bool operator[](SpecialKeys key);

            bool operator[](MouseKeys key);

            const Vector2& GetMouseScreenLocation() const;

            void SetMouseScreenLocation(SDL_Window* window, int const& x, int const& y);

            void SetMouseCursor(MouseCursor cursor);

            /**
             * Checks if the key was clicked this cycle.
             * If it was long pressed it will return false.
             * @param key Keyboard Key
             * @return True if key was pressed this cycle,
             *  false if not pressed or if pressed previous cycles back.
             */
            bool Click(unsigned char key);

            void Update();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_INPUT_H
