/*
 * File MoveController.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "../../Engine/Engine.h"
#include "MoveController.h"

namespace ThreeEngine {

    MoveController::MoveController() : angle(0), front(), actor(nullptr) { }

    MoveController::~MoveController() = default;

    void MoveController::Update(milliseconds delta) {
        if (!actor) {
            return;
        }
        Input& input = Engine::Instance()->input;

        number astep = delta * 0.05f;
        number vstep = delta * .005f;

        if (input['a']) {
            actor->transform.rotation =
                    Quat::FromAngleAxis(astep, Vector(0, 1, 0)) *
                    actor->transform.rotation;
            angle += astep;
        }
        if (input['d']) {
            actor->transform.rotation =
                    Quat::FromAngleAxis(-astep, Vector(0, 1, 0)) *
                    actor->transform.rotation;
            angle -= astep;
        }
        if (input['q']) {
            actor->transform.rotation =
                    Quat::FromAngleAxis(astep, Vector(0, 0, 1)) *
                    actor->transform.rotation;
        }
        if (input['e']) {
            actor->transform.rotation =
                    Quat::FromAngleAxis(-astep, Vector(0, 0, 1)) *
                    actor->transform.rotation;
        }
        if (input['w']) {
            actor->transform.translation += front * vstep;
        }
        if (input['s']) {
            actor->transform.translation -= front * vstep;
        }


        Quat qr = Quat::FromAngleAxis(angle, Vector(0, 1, 0));
        Quat qi(0, 0, 0, -1);
        Quat qf = qr * qi * qr.Inverse();
        front = Vector(qf.X, qf.Y, qf.Z);
    }
} /* namespace ThreeEngine */