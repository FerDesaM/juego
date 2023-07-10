
#include <iostream>
#include "game.h"
#include "projectile.h"
#include <memory>
using namespace sf;
const int y=600;
const int x=800;
int main(int argc , char * args[])
{
    Juego juego(x, y, "Prueba");
    juego.GameLoop();
    return 0;
}
