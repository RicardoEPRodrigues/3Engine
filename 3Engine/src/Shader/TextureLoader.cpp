/*
 * File TextureLoader.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "../Debug.h"
#include "TextureLoader.h"
#include <SDL2/SDL_image.h>

namespace ThreeEngine {

    SINGLETON_IMPLEMENTATION(TextureLoader)

    void TextureLoader::LoadImageData(std::string const& filepath,
                                      ImageData& imageData) {

//        SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
        SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
        SDL_Surface* optimizedSurface = nullptr;

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
        if (loadedSurface == nullptr) {
            Debug::Error("Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError());
            return;
        }

        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, format, 0);
        if (optimizedSurface == nullptr) {
            Debug::Error("Unable to optimize image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
            return;
        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);

        imageData.data = static_cast<unsigned char*>(malloc(optimizedSurface->h * optimizedSurface->pitch));
        SDL_memcpy(imageData.data, optimizedSurface->pixels, optimizedSurface->h * optimizedSurface->pitch);

        imageData.height = optimizedSurface->h;
        imageData.width = optimizedSurface->w;

        SDL_FreeSurface(optimizedSurface);
    }

    std::shared_ptr<Texture>
    TextureLoader::LoadTexture(std::string const& filepath) {
        auto texture = std::make_shared<Texture>();
        LoadImageData(filepath, texture->imageData);
        if (!texture->imageData.data) {
            Debug::Log("Image file could not be loaded");
        }
        return texture;
    }

    std::shared_ptr<Cubemap>
    TextureLoader::LoadCubemap(std::string const& front,
                               std::string const& back,
                               std::string const& top,
                               std::string const& bottom,
                               std::string const& left,
                               std::string const& right) {
        auto cubemap = std::make_shared<Cubemap>();
        LoadImageData(front, cubemap->imagesData[0]);
        LoadImageData(back, cubemap->imagesData[1]);
        LoadImageData(top, cubemap->imagesData[2]);
        LoadImageData(bottom, cubemap->imagesData[3]);
        LoadImageData(left, cubemap->imagesData[4]);
        LoadImageData(right, cubemap->imagesData[5]);

        for (auto&& data : cubemap->imagesData) {
            if (!data.data) {
                Debug::Warn("A Cubemap Image file could not be loaded");
            }
        }
        return cubemap;
    }

} /* namespace ThreeEngine */