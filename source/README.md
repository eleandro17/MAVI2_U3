# MAVI II - Unidad 3: JOINTS
**Gomez Viera Emilio Leandro**

## 
Esquema BALERO BoX:

## Controles

-Tecla A → torque (si se puede llamar así) continuo en sentido horario
-Tecla D → torque continuo en sentido antihorario
-Spacebar → impulso angular brusco en la última dirección usada
-El brazo tiene límite de ±180°
-El moov horizontal del mouse mueve la posición del próximo pivot dentro del brazo del balero.(punto naranja)
-Tecla  F fija un punto de pivot(punto amarillo)
 
La carga cuelga libre del extremo del brazo y se mueve por físicas del box2D

Joints utilizados:

RevoluteJoint → conecta el brazo al pivote central, permite rotación con límites
DistanceJoint → conecta la carga (círculo) al extremo del brazo, simula el cable




## ESTRUCTURA

main.cpp
├── crea b2World 
├── crea b2Body* pivote (se inicializa en centro )
├── Ground      
├── Brazo       
│   ├── b2Body*         dinamic body rectangular
│   ├── b2RevoluteJoint* joint  → anclado al pivote
│   ├── float anchorOffset      → posición del mouse (en x) proyectada sobre el eje del brazo
│   ├── float anchorFijo        → último anchor (fijado con la tecla F)
│   ├── b2Body* pivoteBody      → guardo referencia para recrear el joint
│   ├── HandleInput(world)      → torque (flechas) + impulso (space) + actualiza anchorOffset
│   ├── RecrearJoint(world)     → destruye y crea RevoluteJoint en anchorFijo
│   └── Draw()                  → rectángulo + círculo preview (semitransparente) + círculo fijo (amarillo) + punta roja
├── Carga       
│   ├── b2Body*          dinamic body circular
│   ├── b2DistanceJoint* joint  → anclado al extremo del brazo
│   └── Draw(brazo.body) → dibuja cable + círculo
└── LoopDeJuego 
    ├── RunLoop
    ├── HandleInput
    └── Draw(ground, brazo, carga)

Ground
└── b2Body* estático (piso)


## Problemas que surgieron
- En principio se me ocurrió poder manipular el pivote del brazo en la ejecución del gameloop. Pero no se puede(o no es tan sencillo). Hay que destruir y crear el joint cada vez que elijo un pto nuevo, sino es problemático. Entonces simplemente previsualizo un pivot nuevo con el getMousex() y confirmo con F y el joint se destruye y se crea uno nuevo.
- El clamp() de raylib no pude hacerlo funcionar. Estamos usando raylib 4.2 y no encuentro la docu de esta versión. Solo estan accesibles las del ultimo release de raylib. Use std algorithm


##Notas

#Init es mas bien una inicialización de ventana, típica de raylib, pero también pensada para inicializar audio y tal vez otras cosas.

## Detalles






