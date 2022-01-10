#include "Ball.h"
#include "graphics.h"
#include "form.h"
#include "Game.h"
#include <random>
#include "vecmath.h"

void Ball::update(){
	
	float ball_future_center_x = posX + ball_direction_x * speed;
	float ball_future_center_y = posY + ball_direction_y * speed;
	
	//ball changes direction if it has collision with a player
	if (game.flagB) {
		math::vec2 dir{ ball_direction_x, ball_direction_y };
		math::vec2 normal = { -1.0f, 0.0f };
		math::vec2 reflection = math::reflect(dir, normal);
		ball_direction_x = reflection.x;
		ball_direction_y = reflection.y;
	}
	else if (game.flagA) {
		math::vec2 dir{ ball_direction_x, ball_direction_y };
		math::vec2 normal = { 1.0f, 0.0f };
		math::vec2 reflection = math::reflect(dir, normal);
		ball_direction_x = reflection.x;
		ball_direction_y = reflection.y;
	}

	//ball changes direction if it hits to window's edge
	if ((ball_future_center_y + ball_radius) >= CANVAS_HEIGHT) {
		math::vec2 dir{ ball_direction_x, ball_direction_y };
		math::vec2 normal = { 0.0f, -1.0f };
		math::vec2 reflection = math::reflect(dir, normal);
		ball_direction_x = reflection.x;
		ball_direction_y = reflection.y;
	}
	else if ((ball_future_center_y - ball_radius) <= 0.0f) {
		math::vec2 dir{ ball_direction_x, ball_direction_y };
		math::vec2 normal = { 0.0f, 1.0f };
		math::vec2 reflection = math::reflect(dir, normal);
		ball_direction_x = reflection.x;
		ball_direction_y = reflection.y;
	}

	posX += ball_direction_x * speed;
	posY += ball_direction_y * speed;

	//currentY is used for pc player
	currentY = posY;

	//if ball is out of range is not active any more
	if (posX < 0 || posX > CANVAS_WIDTH)
		active = false; 
}

void Ball::draw(){
	graphics::Brush brush;

	brush.outline_opacity = 0.0f;
	brush.texture = std::string(ASSET_PATH) + "ball.png";
	graphics::drawRect(posX,posY,size,size,brush);

	//disk around the ball for collision with players
	if (game.getDebugMode()) {
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 255.0f;
		br.fill_color[1] = 255.0f;
		br.fill_color[2] = 255.0f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk disk = getCollision();
		graphics::drawDisk(disk.cx, disk.cy, disk.radius, br);
	}
}

void Ball::init() {
	speed = 3.0f;
	//starting position of ball
	posX = CANVAS_WIDTH /2; 
	posY = CANVAS_HEIGHT /2;
	size = 10.0f;

	std::random_device seed;
	std::default_random_engine generator(seed());
	std::uniform_real_distribution<float> distribution(-1.0, 1.0);

	ball_direction_x = distribution(generator);
	ball_direction_y = distribution(generator);

	// Normalize
	float length = std::sqrt(ball_direction_x * ball_direction_x + ball_direction_y * ball_direction_y);
	ball_direction_x /= length;
	ball_direction_y /= length;
}

Ball::Ball(const class Game& mygame) :GameObject(mygame) {
	init();
}



Disk Ball::getCollision() const
{
	Disk disk;
	disk.cx = posX;
	disk.cy = posY;
	disk.radius = size * 0.75f ; 
	return disk;
}
