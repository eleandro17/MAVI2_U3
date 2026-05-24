#include "loopDeJuego.h"

LoopDeJuego::LoopDeJuego(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight)
{
}

void LoopDeJuego::RunLoop(b2World& world, Ground& ground, Brazo& brazo, Carga& carga)
{
    HandleInput(brazo, world);
    Draw(ground, brazo, carga);
}

void LoopDeJuego::HandleInput(Brazo& brazo, b2World& world)
{
    brazo.HandleInput(world);
}

void LoopDeJuego::Draw(Ground& ground, Brazo& brazo, Carga& carga)
{
    BeginDrawing();
    //ClearBackground({ 30, 30, 46, 55 });
    DrawRectangle(0, 0, 1000, 600, { 30, 30, 46, 65 });

    ground.Draw();
    brazo.Draw();
    carga.Draw(brazo.body);

    // HUD
    DrawRectangle(10, 10, 800, 80, Fade(DARKPURPLE, 0.8f));
    DrawText("  ------  Balero BOX - TP3: Joints - - - - -", 30, 10, 30, YELLOW);
    DrawText(" A y D :rotar    ESPACIO: impulso", 20, 50, 18, WHITE);
    DrawText(" F :fija el nuevo anchor, Mousehorizontal lo mueve, pero es influenciado por el balanceo", 20, 65, 18, WHITE);
    
   
    DrawText("Te desplazas por el espacio moviendo el pivot con el horizonal del mouse y el balanceo del balero", 20, screenHeight-50, 18, YELLOW);
    DrawText(u8"El impulso se aplica según el sentido del ultimo input de torque/rotación", 20, screenHeight - 30, 12, WHITE);
    
    Rectangle rect = { screenWidth - 150.0f, 10.0f, 160, 160 };
    DrawRectangleGradientEx(rect, Fade(PURPLE, 0.5f), Fade(DARKPURPLE, 0.8f), YELLOW, Fade(BLUE, 0.6f));
    DrawFPS(screenWidth - 80, 20);
    

    EndDrawing();
}