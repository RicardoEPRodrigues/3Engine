/*
 * File Texture.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "../OpenGLUtils.h"
#include "Texture.h"

namespace ThreeEngine {

    Texture::Texture() = default;

    Texture::~Texture() {
        glBindTexture(GL_TEXTURE_2D, id);
        {
            glDeleteTextures(1, &id);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Init() {
        if (!imageData.data) {
            Debug::Warn("No image data in Texture init");
            return;
        }

        glActiveTexture(texUnit);
        glGenTextures(1, &id);
        UpdateTexture();

        CheckOpenGLError("Could not create Texture.");
    }

    void Texture::UpdateTexture() const {// Load Image
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageData.width,
                     imageData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     imageData.data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        CheckOpenGLError("Could not update Texture.");
    }

    void Texture::Draw() {
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::Unbind() {
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


} /* namespace ThreeEngine */