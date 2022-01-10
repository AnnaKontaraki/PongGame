#pragma once
#include "GameObject.h"
#include "Ball.h"
#include "form.h"


class Player : public GameObject, public PlayerCollision {
	//in order to know the current player
	enum class Plays { Captain = 0, Iron = 1, Ultron = 2 };

	float speed = 10.0f;
	float posX = CANVAS_WIDTH / 2; 
	float posY = CANVAS_HEIGHT/2;

	int scorePlayerA = 0;
	int scorePlayerB = 0;

	//for pc player
	float positionOfBall;

	int CurrentPlayer;

public:
	
	Player(const class Game& mygame);

	void update() override;
	void draw() override;
	void init() override;

	void updateA();
	void updateB();
	void updatePC();
	void drawA();
	void drawB();

	void setScoreA(int s) { scorePlayerA = s; }
	int getScoreA() { return scorePlayerA; }

	void setScoreB(int s) { scorePlayerB = s; }
	int getScoreB() { return scorePlayerB; }


	void setPlayer(int p) { CurrentPlayer = p ; }
	int getPlayer() { return CurrentPlayer; }

	//collisions
	Disk getHeadCollision() const override;
	Disk getHandCollision() const override;
	Disk getBodyCollision() const override;
	Disk getLegCollision() const override;

	//functions drawing disks to players
	Disk getHead()const;
	Disk getHand()const;
	Disk getBody()const;
	Disk getLeg() const;
	void drawDiskForCollision();
	
	//for pc player
	void setCurrentY(float y) { positionOfBall = y; }
	float getcurrentY() { return posY; }
	void moveUp();
	void moveDown();

};