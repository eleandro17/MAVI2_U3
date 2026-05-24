#include "Init.h"

namespace Init //esto iba a ser un fichero de inicializacion con constructor/ destructor pero se me hace larga la firma
{
    void InitVentana(int screenWidth, int screenHeight, const char* title, int fps)
    {
        InitWindow(screenWidth, screenHeight, title);
        SetTargetFPS(fps);
    }

    void Cerrar()
    {
        CloseWindow();
    }
}