#pragma once
#include "Menu.h"
#include "Player.h"
#include "Ball.h"
#include <vector>

class Game {
	
	Menu menu; 

	//players
	Player* playerA = nullptr;
	Player* playerB = nullptr;
	bool playerA_initialized = false;
	bool playerB_initialized = false;
	int A = 0;
	int B = 0;

	bool debug_mode = false;

	//ball
	Ball* ball = nullptr;
	void CreateBall();
	void checkBall();
	
	//collisions
	bool checkLeftCollision();
	bool checkRightCollision();

	bool play_CollisionSound = false;
	bool play_Final = false;
	bool play_GameOver = false;
	int Once = 0;

	std::vector<Disk> disk1;
	std::vector<Disk> disk2;
	

public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	
	//Game's functions
	void update();
	void draw();
	Game();
	~Game();

	//For players
	void updateOnePlayer();
	void updateTwoPlayers();
	void drawOnePlayer();
	void drawTwoPlayers();

	void updateScore();

	//boolean viriables for collision result
	bool flagA;
	bool flagB;

	void LastSound();
};
