#pragma once
#include "GameObject.h"

class Ball :public GameObject,public BallCollision {

	float posX;
	float posY;
	float speed;
	float size;
	bool active = true;

	float ball_direction_x = 1.0f;
	float ball_direction_y = 0.0f;
	float ball_radius = 4.0f;

	//currentY is used for pc player
	float currentY;

public:

	void update() override ;
	void draw() override;
	void init() override;

	bool isActive() { return active; }

	void setPosX(float x) { posX = x; }
	float getPosX() { return posX; }

	void setPosY(float y) { posY = y; }
	float getPosY() { return posY; }

	float  getCurrentY() const { return currentY; }
	Ball(const class Game& mygame);

	Disk getCollision() const override;
};