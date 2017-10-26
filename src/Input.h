/*
 * File Input.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_INPUT_H
#define THREEENGINE_INPUT_H

#include <map>
#include "Debug.h"
#include <GL/freeglut.h>
#include "Math/Vector2.h"

namespace ThreeEngine {

    enum SpecialKeys {
        F1 = GLUT_KEY_F1,
        F2 = GLUT_KEY_F2,
        F3 = GLUT_KEY_F3,
        F4 = GLUT_KEY_F4,
        F5 = GLUT_KEY_F5,
        F6 = GLUT_KEY_F6,
        F7 = GLUT_KEY_F7,
        F8 = GLUT_KEY_F8,
        F9 = GLUT_KEY_F9,
        F10 = GLUT_KEY_F10,
        F11 = GLUT_KEY_F11,
        F12 = GLUT_KEY_F12,
        LEFT_KEY = GLUT_KEY_LEFT,
        UP_KEY = GLUT_KEY_UP,
        RIGHT_KEY = GLUT_KEY_RIGHT,
        DOWN_KEY = GLUT_KEY_DOWN,
        PAGE_UP = GLUT_KEY_PAGE_UP,
        PAGE_DOWN = GLUT_KEY_PAGE_DOWN,
        HOME = GLUT_KEY_HOME,
        END = GLUT_KEY_END,
        INSERT = GLUT_KEY_INSERT
    };

    enum ModifierKeys {
        SHIFT = GLUT_ACTIVE_SHIFT,
        CTRL = GLUT_ACTIVE_CTRL,
        ALT = GLUT_ACTIVE_ALT
    };

    enum MouseKeys {
        LEFT = GLUT_LEFT_BUTTON,
        RIGHT = GLUT_RIGHT_BUTTON,
        MIDDLE = GLUT_MIDDLE_BUTTON
    };

    class Input {
        private:
            std::map<unsigned char, std::pair<bool, bool>> clickKeys;
            std::map<int, bool> specialKeys;
            std::map<int, bool> modifierKeys;
            std::map<int, bool> mouseKeys;

            void updateModifierKeys();

            Vector2 mouseScreenLocation;
        public:

            Input();

            virtual ~Input();

            void NormalKeysDown(unsigned char key, int x, int y);

            void NormalKeysUp(unsigned char key, int x, int y);

            void SpecialKeysDown(int key, int x, int y);

            void SpecialKeysUp(int key, int x, int y);

            void MouseClick(int button, int state, int x, int y);

            void MouseMove(int x, int y);

            /**
             * Check if key is pressed
             * @param key
             * @return True if key is pressed, false otherwise.
             */
            bool operator[](unsigned char key);

            bool operator[](SpecialKeys key);

            bool operator[](ModifierKeys key);

            bool operator[](MouseKeys key);

            const Vector2& GetMouseScreenLocation();

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
