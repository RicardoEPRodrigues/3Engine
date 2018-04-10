/*
 * File SceneGraph.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "../Debug.h"
#include "SceneGraph.h"

namespace ThreeEngine {

    SceneGraph::SceneGraph() : root(nullptr), camera(nullptr) { }

    SceneGraph::~SceneGraph() {
        delete camera;
        delete root;
    }

    void SceneGraph::Init() {
        if (!camera) {
            Debug::Log("No Camera found in Scene Graph. Using default Camera.");
            camera = new Camera();
        }
        camera->Init();
        if (!root) {
            Debug::Log("No root found in Scene Graph. Using default actor.");
            root = new Actor();
        }
        root->Init();
    }

    void SceneGraph::Draw() {
        camera->Draw();
        root->Draw();
    }

    Actor* SceneGraph::GetRoot() const {
        return root;
    }

    void SceneGraph::SetRoot(Actor* root) {
        if (SceneGraph::root != root) {
            delete SceneGraph::root;
        }
        SceneGraph::root = root;
    }

    Camera* SceneGraph::GetCamera() const {
        return camera;
    }

    void SceneGraph::SetCamera(Camera* camera) {
        if (SceneGraph::camera != camera) {
            delete SceneGraph::camera;
        }
        SceneGraph::camera = camera;
    }

} /* namespace ThreeEngine */