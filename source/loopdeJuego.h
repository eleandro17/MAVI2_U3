#pragma once

#include "raylib.h"
#include <box2d.h>
#include "ground.h"
#include "Brazo.h"
#include "Carga.h"

class LoopDeJuego
{
public:
    LoopDeJuego(int screenWidth, int screenHeight);

    void RunLoop(b2World& world, Ground& ground, Brazo& brazo, Carga& carga);

private:
    int screenWidth;
    int screenHeight;

    void HandleInput(Brazo& brazo, b2World& world);
        
    void Draw(Ground& ground, Brazo& brazo, Carga& carga);
};