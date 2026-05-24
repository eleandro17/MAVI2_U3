#include "Carga.h"

static constexpr float LARGO_CABLE = 80.0f; // largo del cable en pixels

Carga::Carga(b2World& world, b2Body* brazoBody, float offsetX, float centerY, Color col)
    : radius(15.0f), color(col)
{
    // Spawn debajo del extremo del brazo
    b2Vec2 extremo = brazoBody->GetWorldPoint(b2Vec2(offsetX / SCALE, 0.0f));

    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(extremo.x, extremo.y + LARGO_CABLE / SCALE);
    body = world.CreateBody(&def);

    b2CircleShape shape;
    shape.m_radius = radius / SCALE;

    b2FixtureDef fix;
    fix.shape = &shape;
    fix.density = 1.5f;
    fix.friction = 0.3f;
    fix.restitution = 0.2f;
    body->CreateFixture(&fix);

    // Distance Joint entre extremo del brazo y la carga
    b2DistanceJointDef jointDef;
    jointDef.Initialize(
        brazoBody, body,
        extremo,
        body->GetPosition()
    );
    jointDef.minLength = LARGO_CABLE / SCALE;
    jointDef.maxLength = LARGO_CABLE / SCALE;
    jointDef.collideConnected = true;// colision de la carga 

    joint = (b2DistanceJoint*)world.CreateJoint(&jointDef);
}

void Carga::Draw(b2Body* brazoBody)
{
    b2Vec2 pos = body->GetPosition();
    float cx = pos.x * SCALE;
    float cy = pos.y * SCALE;

    // Extremo del brazo en screen coords
    b2Vec2 extremo = brazoBody->GetWorldPoint(b2Vec2(100.0f / SCALE, 0.0f));
    float ex = extremo.x * SCALE;
    float ey = extremo.y * SCALE;

    // Cable
    DrawLineEx({ ex, ey }, { cx, cy }, 2.0f, GRAY);

    // Carga
    DrawCircle((int)cx, (int)cy, radius, color);
    DrawCircleLines((int)cx, (int)cy, radius, DARKGRAY);
}