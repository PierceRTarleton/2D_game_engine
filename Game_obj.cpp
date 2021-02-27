#include "Game_obj.h"

/*Game Object Constructor*/
Game_obj::Game_obj(const SDL_Rect Dest_Rect, int red, int green, int blue, SDL_Texture* TXR, const SDL_Rect* Src_Rect) {

	//set object color
	r = red;
	b = blue;
	g = green;
	is_rendered = true;

	//set Destination Rect, and Source Rect
	dest_rect = Dest_Rect;
	if (Src_Rect != NULL) {
		src_rect = *Src_Rect;
	}
	else {
		no_src_rect = true;
	}


	//set bounds of the object
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
	top_edge = dest_rect.y;
	bottom_edge = dest_rect.y + dest_rect.h;


	//set the texture
	if (TXR != NULL) {
		Texture = TXR;
	}
	else {
		rend_type = Color;
	}
}

/*Defalt Constructor*/
Game_obj::Game_obj(){}


/*Parameter: distance- Distance to subtract from objects current X position
  
  Moves the object a specified distance, then adjusts the Object boundaries accordingly*/
void Game_obj::Move_side(int distance) {
	dest_rect.x -= distance;
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
}


/*Returns the Source Rect for the Object*/
const SDL_Rect* Game_obj::get_SrcRect() {
	if (no_src_rect) {
		SDL_Rect* Null_src = (SDL_Rect*)nullptr;
		return Null_src;
	}
	else {
		return &src_rect;
	}
}


/*Returns the Destination Rect for the Object*/
const SDL_Rect* Game_obj::get_DestRect() {
	return &dest_rect;
}


/*Returns the Texture for the Object*/
SDL_Texture* Game_obj::get_TXR() {
	return Texture;
}


/*Returns the whether the object is Rendered or not*/
const bool Game_obj::get_is_Rendered() {
	return is_rendered;
}

/*Sets whether the object is Rendered or not*/
void Game_obj::set_is_Rendered(const bool render) {
	is_rendered = render;
}


/*Returns the whether the object is Textured or Colored*/
const int Game_obj::get_rend_type() {
	return rend_type;
}


/*Return the Color of the Object*/
const int Game_obj::get_r() {
	return r;
}

const int Game_obj::get_g() {
	return g;
}

const int Game_obj::get_b() {
	return b;
}


/*Returns the Boundaries of the Object*/
const int Game_obj::get_edge_L() {
	return left_edge;
}

const int Game_obj::get_edge_R() {
	return right_edge;
}

const int Game_obj::get_edge_T() {
	return top_edge;
}

const int Game_obj::get_edge_B() {
	return bottom_edge;
}