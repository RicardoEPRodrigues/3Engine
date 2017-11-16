/*
 * File TangramAnimation.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "../../Engine/Engine.h"
#include "TangramAnimation.h"

namespace ThreeEngine {

    TangramAnimation::TangramAnimation() = default;

    TangramAnimation::~TangramAnimation() = default;

    void TangramAnimation::Init() {
        for (auto&& actor : actors) {
            initialTransform.push_back(actor->transform);
            finalTransform.push_back(actor->transform);
        }
    }

    void TangramAnimation::Update(milliseconds delta) {
        auto&& input = Engine::Instance()->input;

        if (input.Click('z')) {
            toogle = !toogle;
        }

        const number lstep = delta * speed;

        auto* transforms = &initialTransform;
        if (toogle) {
            transforms = &finalTransform;
        }

        for (unsigned int i = 0; i < actors.size(); ++i) {
            actors[i]->transform.translation =
                    Vector::Lerp(actors[i]->transform.translation,
                                 (*transforms)[i].translation, lstep);
            actors[i]->transform.scale =
                    Vector::Lerp(actors[i]->transform.scale,
                                 (*transforms)[i].scale, lstep);
            actors[i]->transform.rotation =
                    Quat::Lerp(actors[i]->transform.rotation,
                               (*transforms)[i].rotation, lstep);
        }
    }

} /* namespace ThreeEngine */