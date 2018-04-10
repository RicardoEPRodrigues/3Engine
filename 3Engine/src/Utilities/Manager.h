/*
* File Manager.h in project ThreeEngine
*
* Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
*/
#ifndef THREEENGINE_MANAGER_H
#define THREEENGINE_MANAGER_H

#include <map>
#include <string>
#include "singleton.h"

namespace ThreeEngine {
    template<typename T>
    class Manager {
        SINGLETON_HEADER_ONLY(Manager)

        private:
            std::map<std::string, T> objects{};

        public:
            inline void Add(std::string name, T const& object) {
                objects[name] = object;
            }

            inline T Get(std::string name) {
                return objects[name];
            }

            inline void Clear() {
                objects.clear();
            }
    };

    template<typename T>
    SINGLETON_HEADER_ONLY_AFTERCLASS(Manager<T>)
}

#endif //THREEENGINE_MANAGER_H
