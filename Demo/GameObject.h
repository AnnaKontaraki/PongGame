#pragma once
#include "form.h"

//class for creating ball's collision function
class BallCollision{
public:
	virtual Disk getCollision() const = 0;
};

//class for creating player's collision function
class PlayerCollision {
public:
	virtual Disk getHeadCollision() const = 0;
	virtual Disk getHandCollision() const = 0;
	virtual Disk getBodyCollision() const = 0;
	virtual Disk getLegCollision() const = 0;
};

class GameObject {
protected:
	const class Game& game;
public:
	GameObject(const class Game& mygame);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};
