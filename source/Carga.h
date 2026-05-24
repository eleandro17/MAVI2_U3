#pragma once

#include "raylib.h"
#include <box2d.h>

extern const float SCALE;

class Carga
{
public:
    b2Body* body;
    b2DistanceJoint* joint;

    float radius;
    Color color;

    Carga(b2World& world, b2Body* brazoBody, float offsetX, float centerY, Color col);

    void Draw(b2Body* brazoBody);
};
