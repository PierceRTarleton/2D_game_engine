#include "Game_Engine.h"

/*Constructs the Game Engine*/
Game_Engine::Game_Engine() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

	IMG_Init(IMG_INIT_PNG);

	game_window = SDL_CreateWindow("Sliding man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	game_renderer = SDL_CreateRenderer(game_window, -1, 0);

	Window_Rect.x = 0;
	Window_Rect.y = 0;
	Window_Rect.w = 640;
	Window_Rect.h = 480;
}


/* Calls Level init
   Then loops through the Game Engine Functions while Run_game = ture
 */
int Game_Engine::Game_loop() {
	int hold_duration, LST; // LST = Loop Start time

	Level_init();
	Run_game = true;
	while (Run_game) {
		LST = SDL_GetTicks();
		Handle_Events();
		Update_Mechanics();
		Render();

		//Hold until current frame finishes
		hold_duration = SDL_GetTicks() - LST;
		if (hold_duration < frame_duration) {
			SDL_Delay(frame_duration - hold_duration);
		}
	}
	return 0;
}


/* Constructs Objects in the Level
   Objects Include:
		- Level Boundary Rect
		- Background Rect
		- Wall Rects
		- Player
*/
int Game_Engine::Level_init() {
	SDL_Rect DestRect;

	//Level bound
	DestRect.x = 0;
	DestRect.y = 0;
	DestRect.h = 0;
	DestRect.w = SCREEN_WIDTH * Level_length;
	int r = 0;
	int g = 0;
	int b = 0;
	Level = Game_obj(DestRect, r, g, b);

	//Background
	temp = IMG_Load("Background.png");
	texture = SDL_CreateTextureFromSurface(game_renderer, temp);
	SDL_FreeSurface(temp);
	DestRect.x = 0;
	DestRect.y = 0;
	DestRect.h = SCREEN_HEIGHT;
	DestRect.w = SCREEN_WIDTH * Level_length;
	Background = Game_obj(DestRect, r, g, b, texture);


	//Enviormental Creation: Wall Creation

	//Ground rect
	DestRect.x = 0;
	DestRect.y = 450;
	DestRect.h = 30;
	DestRect.w = 1280;
	r = 22;
	g = 158;
	b = 0;
	Objects.push_back(Game_obj(DestRect, r, g, b));

	//Top level bound rect
	DestRect.x = 0;
	DestRect.y = 0;
	DestRect.h = 30;
	DestRect.w = 1280;
	Objects.push_back(Game_obj(DestRect, r, g, b));

	//Level edge rects
	DestRect.x = 0;
	DestRect.y = 0;
	DestRect.h = 480;
	DestRect.w = 30;
	Objects.push_back(Game_obj(DestRect, r, g, b));
	DestRect.x = 1250;
	DestRect.y = 0;
	DestRect.h = 480;
	DestRect.w = 30;
	Objects.push_back(Game_obj(DestRect, r, g, b));

	//Level platforms and walls
	DestRect.x = 610;
	DestRect.y = 0;
	DestRect.h = 410;
	DestRect.w = 30;
	Objects.push_back(Game_obj(DestRect, r, g, b));
	DestRect.x = 170;
	DestRect.y = 360;
	DestRect.h = 20;
	DestRect.w = 100;
	Objects.push_back(Game_obj(DestRect, r, g, b));


	//Player Character
	DestRect.x = 170;
	DestRect.y = 391;
	DestRect.h = 60;
	DestRect.w = 30;
	r = 252;
	g = 0;
	b = 0;
	Player = Player_obj(DestRect, r, g, b);


	return 0;
}


/* Closes the Game Down*/
int Game_Engine::Quit() {
	SDL_DestroyRenderer(game_renderer);
	SDL_DestroyWindow(game_window);

	IMG_Quit();
	SDL_Quit();
	return 0;
}


/* Clears Last Render
   Then Renders:
		- Objects
		- Background
		- Player

   Putes the Resulting image to the window
*/
int Game_Engine::Render() {

	//clear last Render
	SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
	SDL_RenderClear(game_renderer);

	//Render all of the objects in their current positions
	SDL_RenderCopy(game_renderer, Background.get_TXR(), NULL, Background.get_DestRect());

	//Loop Through Objects to Render
	for (int i = 0; i < Objects.size(); i++) {
		if (Objects[i].get_is_Rendered()) {
			if (Objects[i].get_rend_type() == 1) {
				SDL_RenderCopy(game_renderer, Objects[i].get_TXR(), Objects[i].get_SrcRect(), Objects[i].get_DestRect());
			}
			else {
				SDL_SetRenderDrawColor(game_renderer, Objects[i].get_r(), Objects[i].get_g(), Objects[i].get_b(), 255);
				SDL_RenderFillRect(game_renderer, Objects[i].get_DestRect());
			}
		}
	}
	SDL_SetRenderDrawColor(game_renderer, Player.get_r(), Player.get_g(), Player.get_b(), 255);
	SDL_RenderFillRect(game_renderer, Player.get_DestRect());

	// Put the Image from the game_renderer to the screen
	SDL_RenderPresent(game_renderer);
	return 0;
}

// Handles all user Input
int Game_Engine::Handle_Events() {
	SDL_Event input;
	SDL_PollEvent(&input);

	if (input.type == SDL_QUIT) Run_game = false;

	/* Calls Player movemet Functions when a key is pressed
		Slide : Left Shift
		Jump : Space
		Run Left : A
		Run Right : D
		
		Calls Player Functions to end end actions when there repective Key is relesed
	*/

	if (input.type == SDL_KEYDOWN) {
		switch (input.key.keysym.sym) {
		case SDLK_LSHIFT:
			Player.slide();
			break;

		case SDLK_a:
			Player.Run_L();
			break;

		case SDLK_d:
			Player.Run_R();
			break;

		case SDLK_SPACE:
			Player.jump();
			break;
		}
	}
	if (input.type == SDL_KEYUP) {
		switch (input.key.keysym.sym) {
		case SDLK_LSHIFT:
			Player.stop_slide();
			break;

		case SDLK_a:
			if (Player.get_Vel_x() < 0){
				Player.stop_run();
			}
			break;

		case SDLK_d:
			if (Player.get_Vel_x() > 0) {
				Player.stop_run();
			}
			break;
		}
	}
	return 0;
}


/* Updates the Player and Game Object Positions
   Checks For collitions between the Player Character and:
		-Gmae objects
		-Camera boundaries
*/
int Game_Engine::Update_Mechanics() {

	// Get Player State and call the coresponding Player Position update function
	switch (Player.get_State()) {
	case Jump:
		Player.jump();
		break;

	case Run:
		Player.run();
		break;

	case Idle:
		Player.idle();
		break;

	case Slide:
		Player.slide();
		break;
	}

	//move camera based on Player collitions with Camera Bounds
	int Camera_move_dist;

	// Check for collitions with Left Camera Bound
	if (Player.get_edge_L() < LEFT_CAM_BOUND && Level.get_edge_L() != Window_Rect.x) {
		if (Player.get_Vel_x() <= Level.get_edge_L()) {
			Camera_move_dist = Window_Rect.x - Level.get_edge_L();
			Level.Move_side(Camera_move_dist);
			Background.Move_side(Camera_move_dist);
			Player.cam_col_left(LEFT_CAM_BOUND);
		}
		else {
			Camera_move_dist = Player.get_edge_L() - LEFT_CAM_BOUND;
			Level.Move_side(Camera_move_dist);
			Background.Move_side(Camera_move_dist);
			Player.cam_col_left(LEFT_CAM_BOUND);
		}
		for (int i = 0; i < Objects.size(); i++) {
			Objects[i].Move_side(Camera_move_dist);
		}
		Camera_move_dist = 0;
	}

	// Check for collition with Right Camera Bound
	else if (Player.get_edge_R() > RIGHT_CAM_BOUND && Objects[1].get_edge_R() != Window_Rect.w) {
		if (Player.get_Vel_x() > Level.get_edge_R() - Window_Rect.w) {
			Camera_move_dist = Level.get_edge_R() - Window_Rect.w;
			Level.Move_side(Camera_move_dist);
			Background.Move_side(Camera_move_dist);
			Player.cam_col_right(RIGHT_CAM_BOUND);
		}
		else {
			Camera_move_dist = Player.get_edge_R() - RIGHT_CAM_BOUND;
			Level.Move_side(Camera_move_dist);
			Background.Move_side(Camera_move_dist);
			Player.cam_col_right(RIGHT_CAM_BOUND);
		}
		for (int i = 0; i < Objects.size(); i++) {
			Objects[i].Move_side(Camera_move_dist);
		}
		Camera_move_dist = 0;
	}

	//checks if an object is within the window
	for (int i = 0; i < Objects.size(); i++) {
		bool render = SDL_HasIntersection(Objects[i].get_DestRect(), &Window_Rect);
		Objects[i].set_is_Rendered(render);
	}
	

	/*Collitions*/
	char collition = col_non;
	SDL_Rect Collition;

	//Loop through Objects Checking Checking for collitions with the Player
	for (int i = 0; i < Objects.size(); i++) {
		if (Objects[i].get_is_Rendered()) {
			if (SDL_IntersectRect(Player.get_DestRect(), Objects[i].get_DestRect(), &Collition)) {

				//Case Collition with Top or Bottom of Player, Object width is less then Player width
				if (Collition.w + Collition.x == Objects[i].get_edge_R() && Collition.x == Objects[i].get_edge_L()) {
					if (Collition.y == Player.get_edge_T()) {
						collition = col_top;
					}
					if (Collition.y + Collition.h == Player.get_edge_B()) {
						collition = col_bot;
					}
				}

				//Case Collition with Top or Bottom of Player, Player width is less then Object width
				else if (Collition.w + Collition.x == Player.get_edge_R() && Collition.x == Player.get_edge_L()) {
					if (Collition.y == Objects[i].get_edge_T()) {
						collition = col_bot;
					}
					if (Collition.y + Collition.h == Objects[i].get_edge_B()) {
						collition = col_top;
					}
				}

				//Case Corner Collitions with left side of the Player
				else if (Collition.x == Objects[i].get_edge_L()) {
					if (Collition.y + Collition.h + Player.get_Vel_y() <= Objects[i].get_edge_T()) {
						collition = col_top;
					}
					else if (Collition.y + Player.get_Vel_y() >= Objects[i].get_edge_B()) {
						collition = col_bot;
					}
					else {
						collition = col_right;
					}
				}

				//Case Corner Collitions with Right side of the Player
				else if (Collition.w + Collition.x == Objects[i].get_edge_R()) {
					if (Collition.y + Collition.h + Player.get_Vel_y() <= Objects[i].get_edge_T()) {
						collition = col_top;
					}
					else if (Collition.y + Player.get_Vel_y() >= Objects[i].get_edge_B()) {
						collition = col_bot;
					}
					else {
						collition = col_left;
					}
				}
			}

			//Call Player functions to addjust for the type of collition that occured
			switch (collition) {
			case col_left:
				Player.col_left(Objects[i].get_edge_R());
				collition = col_non;
				break;

			case col_right:
				Player.col_right(Objects[i].get_edge_L());
				collition = col_non;
				break;

			case col_top:
				Player.col_top(Objects[i].get_edge_B());
				collition = col_non;
				break;

			case col_bot:
				Player.stop_jump();
				Player.col_bot(Objects[i].get_edge_T());
				collition = col_non;
				break;

			default:
				if (Player.get_edge_B() != Ground) {
					Player.set_State(Jump);
				}
			}

		}
	}
	return 0;
}