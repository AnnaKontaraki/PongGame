#include "Player.h"
#include "graphics.h"
#include"Game.h"

Player::Player(const Game& mygame):GameObject(mygame) {
	init();
}


Disk Player::getHand() const {
	Disk hand;
	if (CurrentPlayer == 0) {
		hand.cx = posX - RANGE_PLAYER + 25;
		hand.cy = posY - 20;
		hand.radius = 25.0f;
		return hand;
	}
	else if (CurrentPlayer == 1) {
		hand.cx = posX + RANGE_PLAYER - 46;
		hand.cy = posY - 15;
		hand.radius = 13.0f;
		return hand;
	}
	else if (CurrentPlayer == 2) {
		hand.cx = posX + RANGE_PLAYER - 55;
		hand.cy = posY - 10;
		hand.radius = 10.0f;
		return hand;
	}
}

Disk Player::getHead() const {
	Disk head;
	if (CurrentPlayer == 0) {
		head.cx = posX - RANGE_PLAYER + 20;
		head.cy = posY - 50;
		head.radius = 10.0f;
		return head;
	}
	else if (CurrentPlayer == 1) {
		head.cx = posX + RANGE_PLAYER - 35;
		head.cy = posY - 50;
		head.radius = 10.0f;
		return head;
	}
	else if (CurrentPlayer == 2) {
		head.cx = posX + RANGE_PLAYER - 4 ;
		head.cy = posY - 35;
		head.radius = 10.0f;
		return head;
	}
}

Disk Player::getBody() const {
		Disk body;
		if (CurrentPlayer == 0) {
			body.cx = posX - RANGE_PLAYER + 20;
			body.cy = posY + 20;
			body.radius = 15.0f;
			return body;
		}
		else if (CurrentPlayer == 1) {
			body.cx = posX + RANGE_PLAYER - 15;
			body.cy = posY + 5;
			body.radius = 20.0f;
			return body;
			
		}
		else if (CurrentPlayer == 2) {
			body.cx = posX + RANGE_PLAYER + 10;
			body.cy = posY - 10;
			body.radius = 25.0f;
			return body;
		}
}


Disk Player::getLeg() const {
	Disk leg;
	if (CurrentPlayer == 0) {
		leg.cx = posX - RANGE_PLAYER + 25;
		leg.cy = posY + 50;
		leg.radius = 15.0f;
		return leg;
	}
	else if (CurrentPlayer == 1) {
		leg.cx = posX + RANGE_PLAYER - 25;
		leg.cy = posY + 35;
		leg.radius = 15.0f;
		return leg;
	}
	else if (CurrentPlayer == 2) {
		leg.cx = posX + RANGE_PLAYER +  35;
		leg.cy = posY + 35;
		leg.radius = 15.0f;
		return leg;
	}
	
}


void Player::update()
{
	//common positions
	if (posX < 0) posX = 0;
	if (posX > CANVAS_WIDTH) posX = CANVAS_WIDTH;
	if (posY < 0) posY = 0;
	if (posY > CANVAS_HEIGHT) posY = CANVAS_HEIGHT;
}

void Player::draw(){

	//draw Pc player --> Ultron
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "Ultron.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(posX + RANGE_PLAYER, posY, 120,120, br);
	setPlayer(2);

	init();

	drawDiskForCollision();
	
}

void Player::init()
{
	speed = 10.0f;
	float posX = CANVAS_WIDTH / 2;
	float posY = CANVAS_HEIGHT / 2;
}

//update function for PC player
void Player::updatePC() {

	while (posY > positionOfBall)
		moveUp();

	moveDown();
}

//for pc player
void Player::moveUp() {
		posY--;
}

void Player::moveDown() {
		posY++;
}

//update function for left player
void Player::updateA() {
	
	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		posY -= speed * graphics::getDeltaTime() / 14.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		posY += speed * graphics::getDeltaTime() / 14.0f;
	}	
}

//update function for right player
void Player::updateB() {
	
	if (graphics::getKeyState(graphics::SCANCODE_UP)) {
		posY -= speed * graphics::getDeltaTime() / 14.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		posY += speed * graphics::getDeltaTime() / 14.0f;
	}
}
 
//draw function for left player
void Player::drawA() {
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "Captain.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(posX - RANGE_PLAYER, posY, 100, 120, br);
	setPlayer(0);
	
	drawDiskForCollision();
}

//draw function for right player
void Player::drawB() {
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "Iron.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(posX + RANGE_PLAYER, posY,120, 120, br);
	setPlayer(1);

	drawDiskForCollision();
}


Disk Player::getHeadCollision() const
{
		Disk disk;
		disk.cx = getHead().cx;
		disk.cy = getHead().cy;
		disk.radius = getHead().radius;
		return disk;
	
}

Disk Player::getHandCollision() const
{
	Disk disk;
	disk.cx = getHand().cx;
	disk.cy = getHand().cy;
	disk.radius = getHand().radius;
	return disk;

}

Disk Player::getBodyCollision() const
{
	Disk disk;
	disk.cx = getBody().cx;
	disk.cy = getBody().cy;
	disk.radius = getBody().radius;
	return disk;

}

Disk Player::getLegCollision() const
{
	Disk disk;
	disk.cx = getLeg().cx;
	disk.cy = getLeg().cy;
	disk.radius = getLeg().radius;
	return disk;

}


void Player::drawDiskForCollision() {
	graphics::Brush br;

	if (game.getDebugMode()) {
		
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.gradient = false;
		br.fill_opacity = 0.4f;
		br.outline_opacity = 0.4f;

	
		Disk head = getHead();
		graphics::drawDisk(head.cx, head.cy, head.radius, br);

		Disk shield = getHand();
		graphics::drawDisk(shield.cx, shield.cy, shield.radius, br);

		Disk knee = getBody();
		graphics::drawDisk(knee.cx, knee.cy, knee.radius, br);

		Disk boot = getLeg();
		graphics::drawDisk(boot.cx, boot.cy, boot.radius, br);
	}
}
