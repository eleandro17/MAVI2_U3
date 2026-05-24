#include "Brazo.h"
#include <algorithm>

static constexpr float TORQUE = 80.0f;
static constexpr float IMPULSO = 100.0f;
static constexpr float LIMIT = b2_pi; // 180°

Brazo::Brazo(b2World& world, b2Body* pivoteBody, float centerX, float centerY, Color col)
    : halfW(100.0f), halfH(10.0f), color(col), direction(1)
{
    // Body dinámico centrado en el pivote
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(centerX / SCALE, centerY / SCALE);
    body = world.CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(halfW / SCALE, halfH / SCALE);

    b2FixtureDef fix;
    fix.shape = &shape;
    fix.density = 1.0f;
    fix.friction = 0.3f;
    body->CreateFixture(&fix);

    // Revolute Joint 

    b2RevoluteJointDef jointDef;
    //jointDef.Initialize(pivoteBody, body, pivoteBody->GetWorldCenter());

    b2Vec2 anchor = body->GetWorldPoint(b2Vec2(anchorFijo / SCALE, 0.0f));
    jointDef.Initialize(pivoteBody, body, anchor);
   
    jointDef.enableLimit = true;
    jointDef.lowerAngle = -LIMIT;
    jointDef.upperAngle = LIMIT;
    jointDef.enableMotor = false; // el input aplica torque manualmente
    jointDef.collideConnected = false;//colision en false para que no colsiones con el ´pivote

    joint = (b2RevoluteJoint*)world.CreateJoint(&jointDef);

    anchorOffset = 0.0f;// nuevo para setearel offset
    this->pivoteBody = pivoteBody;//

    anchorFijo = 0.0f;//
}

void Brazo::HandleInput(b2World& world)
{
    if (IsKeyDown(KEY_D))
    {
        direction = 1;
        body->ApplyTorque(TORQUE, true);
    }
    if (IsKeyDown(KEY_A))
    {
        direction = -1;
        body->ApplyTorque(-TORQUE, true);
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        body->ApplyAngularImpulse(direction * IMPULSO, true);
    }
    // Actualiza offset según mouse
    float mouseX = (float)GetMouseX();
    float brazoScreenX = body->GetPosition().x * SCALE;
    anchorOffset = mouseX - brazoScreenX;
    anchorOffset = std::clamp(anchorOffset, -halfW, halfW); // el Clamp de raylib no me anduvo,tuve que usar el de algorithm

    // Fijar anchor
    if (IsKeyPressed(KEY_F))
        RecrearJoint(world); // tego que pasar world como parámetro
}

void Brazo::Draw()
{
    b2Vec2  pos = body->GetPosition();
    float   angle = body->GetAngle();

    float cx = pos.x * SCALE;
    float cy = pos.y * SCALE;

    // Rectángulo rotado
    Rectangle rect = { cx, cy, halfW * 2, halfH * 2 };
    Vector2   origin = { halfW, halfH }; // centro del rect

    DrawRectanglePro(rect, origin, angle * RAD2DEG, color);// este usa el anguloen grados, por eso se convierte. como siempre
    DrawRectanglePro(rect, origin, angle * RAD2DEG, Fade(DARKGRAY, 0.5f)); // borde

    // Punto de pivoteo
    // 
    //b2Vec2 anchor = body->GetWorldPoint(b2Vec2(-halfW * 0.5f / SCALE, 0.0f));
    //DrawCircle((int)(anchor.x * SCALE), (int)(anchor.y * SCALE), 5.0f, YELLOW);
    
    //DrawCircle((int)cx, (int)cy, 5.0f, YELLOW);
    
    // Preview - que sigue al mouse
    b2Vec2 preview = body->GetWorldPoint(b2Vec2(anchorOffset / SCALE, 0.0f));
    DrawCircle((int)(preview.x * SCALE), (int)(preview.y * SCALE), 5.0f, Fade(ORANGE, 0.4f));

    // Anchor fijado
    b2Vec2 fijo = body->GetWorldPoint(b2Vec2(anchorFijo / SCALE, 0.0f));
    DrawCircle((int)(fijo.x * SCALE), (int)(fijo.y * SCALE), 5.0f, YELLOW);

    b2Vec2 punta = body->GetWorldPoint(b2Vec2(halfW / SCALE, 0.0f));
    DrawCircle((int)(punta.x * SCALE), (int)(punta.y * SCALE), 6.0f, RED);
}

void Brazo::RecrearJoint(b2World& world)
{
    world.DestroyJoint(joint);

    b2RevoluteJointDef jointDef;
    b2Vec2 anchor = body->GetWorldPoint(b2Vec2(anchorOffset / SCALE, 0.0f));
    jointDef.Initialize(pivoteBody, body, anchor);
    jointDef.enableLimit = true;
    jointDef.lowerAngle = -b2_pi;
    jointDef.upperAngle = b2_pi;
    jointDef.collideConnected = false;

    joint = (b2RevoluteJoint*)world.CreateJoint(&jointDef);

    anchorFijo = anchorOffset;// f ijar el anchor nuevo
}