/*
* File Managers.h in project ThreeEngine
*
* Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
*/
#ifndef THREEENGINE_MANAGERS_H
#define THREEENGINE_MANAGERS_H

#include <memory>
#include "Manager.h"
#include "../Shader/ShaderProgram.h"
#include "../Shapes/Mesh.h"
#include "../Shader/ITexture.h"

namespace ThreeEngine {
    typedef Manager<std::shared_ptr<ShaderProgram>> ShaderProgramManager;
    typedef Manager<std::shared_ptr<Mesh>> MeshManager;
    typedef Manager<std::shared_ptr<ITexture>> TextureManager;
}

#endif //THREEENGINE_MANAGERS_H
