/*
 * File ITexture.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_ITEXTURE_H
#define THREEENGINE_ITEXTURE_H

#include "../IDrawable.h"

namespace ThreeEngine {

    struct ImageData {
        unsigned char* data{nullptr};
        int width{}, height{};

        virtual ~ImageData() {
            delete[] data;
        }
    };

    class ITexture : public IDrawable {
        public:
            virtual void Unbind() = 0;

            virtual void UpdateTexture() const = 0;
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_ITEXTURE_H
