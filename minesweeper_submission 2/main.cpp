#include <iostream>

#include "src/Game.h"
#include "src/Configuration.h"

int main(){
    Configuration::initialize();
    Game game;

    game.run();

    return 0;
}