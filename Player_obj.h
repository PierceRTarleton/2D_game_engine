#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

//Player States
static const int Idle = 0;
static const int Run = 1;
static const int Jump = 2;
static const int Slide = 3;

class Player_obj {
private:

	//Player Velocity
	int Vel_y = 0;
	int Vel_x = 0;
	int Gravity = 1;
	int Friction = 1;

	//Render Settings
	SDL_Rect dest_rect, src_rect;
	SDL_Texture* Texture;
	int rend_type, r, g, b;

	//Player state
	int State = Idle;
	int Run_direc;

	//Player bounds
	int left_edge, right_edge, top_edge, bottom_edge;
	int half_Player_hight = 30;

	/*Frame Controls*/
	//Jump
	int Jump_FR = 150;  // FR = Frame rate
	int Jump_Start = 0;
	int Jump_Frame = 0;

	//Idle
	int Idle_Frame = 0;

	//Slide
	int Slide_FR = 245;
	int Slide_Start = 0;
	int Slide_Frame = 0;

	bool no_src_rect = false;

public:

	//constructors
	Player_obj();
	Player_obj(const SDL_Rect Dest_Rect, int red, int green, int blue, SDL_Texture* TXR = NULL, const SDL_Rect* Src_Rect = NULL);

	//Rendering getters
	const SDL_Rect* get_SrcRect();
	const SDL_Rect* get_DestRect();
	SDL_Texture* get_TXR();

	//Color getters
	const int get_r();
	const int get_g();
	const int get_b();

	//Bounds Getters
	const int get_edge_L();
	const int get_edge_R();
	const int get_edge_T();
	const int get_edge_B();

	//Colliitons
	void col_bot(const int edge);
	void col_top(const int edge);
	void col_right(const int edge);
	void col_left(const int edge);
	void cam_col_left(const int edge);
	void cam_col_right(const int edge);

	//Player Getter Functions
	const int get_State();
	const int get_Vel_x();
	const int get_Vel_y();

	//Set State
	void set_State(int state);

	//Player Movment Functions
	void jump();
	void stop_jump();
	void Run_L();
	void Run_R();
	void run();
	void stop_run();
	void slide();
	void stop_slide();
	void idle();
};