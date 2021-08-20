/*
 * File CubemapTexture.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "../OpenGLUtils.h"
#include "Cubemap.h"

namespace ThreeEngine {

    Cubemap::Cubemap() = default;

    Cubemap::~Cubemap() {
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);
        {
            glDeleteTextures(1, &id);
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void Cubemap::Init() {
        for (auto&& data : imagesData) {
            if (!data.data) {
                Debug::Warn("Missing image data in Cubemap Texture init");
                return;
            }
        }

        glActiveTexture(texUnit);
        glGenTextures(1, &id);
        UpdateTexture();

        CheckOpenGLError("Could not create Cubemap Texture.");
    }

    void Cubemap::UpdateTexture() const {// Load Image
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);
        LoadMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, imagesData[0]);
        LoadMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, imagesData[1]);
        LoadMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, imagesData[2]);
        LoadMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, imagesData[3]);
        LoadMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, imagesData[4]);
        LoadMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X, imagesData[5]);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        CheckOpenGLError("Could not update Cubemap Texture.");
    }

    void Cubemap::Draw() {
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    }

    void Cubemap::Unbind() {
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void
    Cubemap::LoadMapSide(GLenum sideTarget,
                         const ImageData& imageData) {
        // copy image data into 'target' side of cube map
        glTexImage2D(sideTarget, 0, GL_RGBA, imageData.width, imageData.height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data);
    }
} /* namespace ThreeEngine */