#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

static const int Color = 0;
static const int Texture = 1;

class Game_obj {
private:
	//Render Settings
	SDL_Rect dest_rect, src_rect;
	SDL_Texture* Texture;
	int rend_type, r, g, b;

	//Object Boundaries
	int left_edge, right_edge, top_edge, bottom_edge;
	

	//Indicates if Object Apperes in the window.
	bool is_rendered;
	bool no_src_rect = false;

public:

	//Constructors
	Game_obj(const SDL_Rect Dest_Rect, int red, int green, int blue, SDL_Texture* TXR = NULL, const SDL_Rect* Src_Rect = NULL);
	Game_obj();

	//Moves Level Side to Side
	void Move_side(int distance);

	//Rendering Getters and Setters
	const SDL_Rect* get_SrcRect();
	const SDL_Rect* get_DestRect();
	SDL_Texture* get_TXR();
	const bool get_is_Rendered();
	void set_is_Rendered(const bool render);
	const int get_rend_type();

	//Color getters
	const int get_r();
	const int get_g();
	const int get_b();

	//Bounds Getters
	const int get_edge_L();
	const int get_edge_R();
	const int get_edge_T();
	const int get_edge_B();
};