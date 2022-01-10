#pragma once
#include "graphics.h"


using namespace std;
#define maxNum 3

class Menu {

	int mainMenuSelected;
	string mainMenu[maxNum];
	string name;

public:
	Menu();
	~Menu();
	void init();
	void draw();
	void update();

	//in order to know the current status of the game
	enum class GameState{ STATUS_MENU, STATUS_GAMEFOR1, STATUS_GAMEFOR2,STATUS_GAMEOVER, STATUS_END };
	GameState status = GameState::STATUS_MENU;

	void setGameState(GameState s) { status = s; }
	GameState getGameState() { return status; }

	
};




