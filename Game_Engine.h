#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include "Game_obj.h"
#include "Player_obj.h"

//Window Size in Pixels
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

//Camera movement Boundaries
static const int RIGHT_CAM_BOUND = 480;
static const int LEFT_CAM_BOUND = 160;

static const int fps = 60;
static const int frame_duration = 1000 / fps;
static const int event_duration = 1000 / fps;
static const int update_duration = 1000 / fps;

//Collition types
static const char col_left = 'L';
static const char col_top = 'T';
static const char col_bot = 'B';
static const char col_right = 'R';
static const char col_non = 'N';

//Gournd level
static const int Ground = 450;

class Game_Engine {
private:
	SDL_Window* game_window = NULL;
	SDL_Renderer* game_renderer = NULL;
	SDL_Event input;
	SDL_Rect Window_Rect;
	SDL_Texture* texture = NULL;
	SDL_Surface* temp;
	
	//Number of Screen size widths the level is
	int Level_length = 2;

	//Game Objects
	std::vector <Game_obj> Objects;
	Game_obj Level;
	Game_obj Background;
	Player_obj Player;
	bool Run_game = true;

	//Game Engin Functions
	int Render();
	int Handle_Events();
	int Update_Mechanics();
	int Quit();
	int Level_init();

public:
	Game_Engine();
	int Game_loop();
};