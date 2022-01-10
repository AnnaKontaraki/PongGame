#pragma once

#define ASSET_PATH "assets\\"
#define WIDTH 1200
#define HEIGHT 600
#define CANVAS_WIDTH 1000
#define CANVAS_HEIGHT 500
#define RANGE_PLAYER 400


//a struct which describes a disk and is used for collisions
struct Disk {
public: 
	float cx, cy;
	float radius;
};