#include "Player_obj.h"

/*Defalt constructor*/
Player_obj::Player_obj(){
	/*//set object color
	r = 0;
	b = 0;
	g = 0;

	//set rects
	//dest_rect = Dest_Rect;
	//src_rect = *Src_Rect;

	//set bounds of the object
	left_edge = 0;
	right_edge = 0;
	top_edge = 0;
	bottom_edge = 0;*/
}


/*Player Constructor*/
Player_obj::Player_obj(const SDL_Rect Dest_Rect, int red, int green, int blue, SDL_Texture* TXR, const SDL_Rect* Src_Rect) {

	//set object color
	r = red;
	b = blue;
	g = green;

	//set Destination Rect, and Source Rect
	dest_rect = Dest_Rect;
	if (Src_Rect != NULL) {
		src_rect = *Src_Rect;
	}
	else {
		no_src_rect = true;
	}

	//set bounds of the Player
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
	top_edge = dest_rect.y;
	bottom_edge = dest_rect.y + dest_rect.h;

	//set the texture
	if (TXR != NULL) {
		Texture = TXR;
	}
}



/*Returns the Source Rect for the Player*/
const SDL_Rect* Player_obj::get_SrcRect() {
	if (no_src_rect) {
		SDL_Rect* Null_src = (SDL_Rect*)nullptr;
		return Null_src;
	}
	else {
		return &src_rect;
	}
}


/*Returns the Destination Rect for the Player*/
const SDL_Rect* Player_obj::get_DestRect() {
	return &dest_rect;
}

/*Returns the Texture for the Player*/
SDL_Texture* Player_obj::get_TXR() {
	return Texture;
}


/*Return the Color of the Player*/
const int Player_obj::get_r() {
	return r;
}

const int Player_obj::get_g() {
	return g;
}

const int Player_obj::get_b() {
	return b;
}


/*Returns the Boundaries of the Player*/
const int Player_obj::get_edge_L() {
	return left_edge;
}

const int Player_obj::get_edge_R() {
	return right_edge;
}

const int Player_obj::get_edge_T() {
	return top_edge;
}

const int Player_obj::get_edge_B() {
	return bottom_edge;
}


/*Parameters: edge - The edge that the Player collided with
* 
* Adjust Player Position Based on Colition type
*	Distance of Adjustment = Differce between the colliding boundary Positions
*/
void Player_obj::col_bot(const int edge) {
	Vel_y = 0;
	dest_rect.y -= bottom_edge - edge;
	top_edge = dest_rect.y;
	bottom_edge = dest_rect.y + dest_rect.h;
	if (State != Slide && State != Run) {
		State = Idle;
	}
}

void Player_obj::col_top(const int edge) {
	Vel_y = 0;
	dest_rect.y += edge - top_edge;
	top_edge = dest_rect.y;
	bottom_edge = dest_rect.y + dest_rect.h;
}

void Player_obj::col_right(const int edge) {
	Vel_x = 0;
	dest_rect.x -= right_edge - edge;
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
}

void Player_obj::col_left(const int edge) {
	Vel_x = 0;
	dest_rect.x += edge - left_edge;
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
}

void Player_obj::cam_col_left(const int edge) {
	dest_rect.x += edge - left_edge;
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
}

void Player_obj::cam_col_right(const int edge) {
	dest_rect.x -= right_edge - edge;
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
}



/*Returns the State that the Player is in*/
const int Player_obj::get_State() {
	return State;
}


/*Sets the State the Player is in*/
void Player_obj::set_State(int state) {
	State = state;
}


/*Returns the Player's Velocity in the x direction*/
const int Player_obj::get_Vel_x() {
	return Vel_x;
}


/*Returns the Player's Velocity in the x direction*/
const int Player_obj::get_Vel_y() {
	return Vel_y;
}


/*Player Movement*/

/*Changes the Players Y positoin*/
void Player_obj::jump() {

	
	// Sets Vertical velocity, and Player state to Jump
	if (Jump_Frame == 0 && State != Jump) {
		Jump_Start = SDL_GetTicks()/ Jump_FR;
		Vel_y = -5;
		State = Jump;
	}
	
	/*Increases the Y velocity when Jump_Frame modulus 7 = 0,
	  and the Y velocity is less then or equal to 4*/
	else if (Jump_Frame < (SDL_GetTicks() / Jump_FR - Jump_Start) && Vel_y <=4) {
		Jump_Frame = (SDL_GetTicks() / Jump_FR - Jump_Start);
		Vel_y += Gravity;
	}

	//Adjust Player position and boundaries based on the X and Y velocity
	dest_rect.y += Vel_y;
	top_edge = dest_rect.y;
	bottom_edge = dest_rect.y + dest_rect.h;
	dest_rect.x += Vel_x;
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
}

/*Stops the Jump state*/
void Player_obj::stop_jump() {

	//if Player has Sliding Rect dementions Set state = Slide
	if (dest_rect.h == half_Player_hight) {
		State = Slide;
	}

	//else if the player Velocity X = 0 Set state = Idle
	else if (Vel_x == 0) {
		State = Idle;
	}

	//else set state = Run
	else {
		State = Run;
	}
	Jump_Frame = 0;
	Jump_Start = 0;
}


/*set Player State = Run, and Player X velocity = 4*/
void Player_obj::Run_R() {
	if (State != Slide) {
		State = Run;
		Vel_x = 4;
	}
}


/*set Player State = Run, and Player X velocity = -4*/
void Player_obj::Run_L() {
	if (State != Slide) {
		State = Run;
		Vel_x = -4;
	}
}


/*Update Player position based on Player X velocity*/
void Player_obj::run() {
	dest_rect.x += Vel_x;
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
}


/*Stops Run State, Set Player state to Idle, and X velocity = 0*/
void Player_obj::stop_run() {
	if (State != Slide) {
		Vel_x = 0;
		State = Idle;
	}
}


/*Set Player State to Slide, Adjust Player Dementions*/
void Player_obj::slide() {

		//Invert Player hight and width and sets the time the slide started
		if (Slide_Frame == 0 && State != Slide) {
			Slide_Start = SDL_GetTicks() / Slide_FR;
			dest_rect.h = half_Player_hight;
			dest_rect.y += half_Player_hight;
			dest_rect.w += half_Player_hight;
			top_edge = dest_rect.y;
			bottom_edge = dest_rect.y + dest_rect.h;
		}

		
		//Decrease Player X velocity by 1, after every frame (Frame rate Specified by Slide_FR)
		else if (Vel_x > 0 && Slide_Frame < (SDL_GetTicks() / Slide_FR - Slide_Start)) {
			Vel_x -= Friction;
			Slide_Frame = SDL_GetTicks() / Slide_FR - Slide_Start;
		}
		else if (Vel_x < 0 && Slide_Frame < (SDL_GetTicks() / Slide_FR - Slide_Start)) {
			Vel_x += Friction;
			Slide_Frame = SDL_GetTicks() / Slide_FR - Slide_Start;
		}

		//Adjust Player Position and Boundaries based on Player X velocity
		dest_rect.x += Vel_x;
		left_edge = dest_rect.x;
		right_edge = dest_rect.x + dest_rect.w;
		State = Slide;
}


/*End Player Slide State*/
void Player_obj::stop_slide() {

	//Invert Player hight adn width
	dest_rect.y -= half_Player_hight;
	dest_rect.h += half_Player_hight;
	dest_rect.w -= half_Player_hight;
	top_edge = dest_rect.y;
	bottom_edge = dest_rect.y + dest_rect.h;

	//Update Player Position based on Player X velocity
	dest_rect.x += Vel_x;
	left_edge = dest_rect.x;
	right_edge = dest_rect.x + dest_rect.w;
	Slide_Start = 0;
	Slide_Frame = 0;

	//If not in Jump State, Set Player State = Run
	if (State != Jump) {
		State = Run;
	}
}


/*Perform Idle animation*/
void Player_obj::idle() {}