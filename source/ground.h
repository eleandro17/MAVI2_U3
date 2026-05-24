#pragma once

#include "raylib.h"
#include <box2d.h>

extern const float SCALE;

class Ground
{
public:
    b2Body* body;
    int screenWidth;
    int screenHeight;
    

    Ground(b2World& world, int screenWidth, int screenHeight, Color col)
        : screenWidth(screenWidth), screenHeight(screenHeight)
    {
        b2BodyDef groundDef;
        groundDef.type = b2_staticBody;
        groundDef.position.Set((screenWidth / 2.0f) / SCALE, (screenHeight - 40.0f) / SCALE);
        body = world.CreateBody(&groundDef);

        b2PolygonShape groundShape;
        groundShape.SetAsBox((screenWidth / 2.0f) / SCALE, 20.0f / SCALE);
        body->CreateFixture(&groundShape, 0.0f);
    }

  void Draw()
    {
        b2Vec2 velcaida = body->GetLinearVelocity();

        DrawRectangle(0, screenHeight - 60, screenWidth, 60, BLACK);
        
    }
  //void Drawground(b2Vec2 velProyectil)
  //    
  //{
  //    
  //    float speed = velProyectil.Length();//Length sería la hipotenusa del triángulo 
  //    int tileSize = 10 + (int)(speed * 4.0f);

  //    for (int x = 0; x < screenWidth; x += tileSize)
  //    {
  //        DrawRectangleLines(x, screenHeight - 60, 10, tileSize, YELLOW);
  //    }
  //}
  
};