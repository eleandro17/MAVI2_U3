#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include "ground.h"
#include "Brazo.h"
#include "Carga.h"
#include "Init.h"
#include "loopdeJuego.h"

const float SCALE = 30.0f;

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    Init::InitVentana(screenWidth, screenHeight, "MAVI II - TP Unidad3. Joints. Gomez Viera Emilio Leandro", 60);

    b2Vec2  gravity(0.0f, 9.8f);
    b2World world(gravity);

    // Pivote . Antes era estático, ahora es modificable en el loopdeJuego
    b2BodyDef pivoteDef;
    pivoteDef.type = b2_staticBody;
    pivoteDef.position.Set((screenWidth / 2.0f) / SCALE, (screenHeight / 2.0f) / SCALE);
    b2Body* pivote = world.CreateBody(&pivoteDef);

    Ground ground(world, screenWidth, screenHeight, Fade(DARKGREEN, 0.7f));
    Brazo  brazo(world, pivote, screenWidth / 2.0f, screenHeight / 2.0f, Fade(SKYBLUE, 0.9f));
    Carga  carga(world, brazo.body, 100.0f, screenHeight / 2.0f, Fade(ORANGE, 0.9f));

    LoopDeJuego loop(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        world.Step(1.0f / 60.0f, 8, 3);
        loop.RunLoop(world, ground, brazo, carga);
    }

    Init::Cerrar();
    return 0;
}