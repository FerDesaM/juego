
#include <iostream>
#include "game.h"
#include "projectile.h"
#include <memory>
using namespace sf;
const int y=800;
const int x=1000;
int main(int argc , char * args[])
{
    Juego *partida;
    partida=new Juego(x, y, "Prueba");
    return 0;
}
