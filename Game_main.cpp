#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include "Game_Engine.h"

int main()
{
    //Start SDL
    SDL_SetMainReady();

    //Initialize and Run the Game
    Game_Engine Game = Game_Engine();
    Game.Game_loop();

    return 0;
}

