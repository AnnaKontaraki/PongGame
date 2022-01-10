#include <iostream>
#include "Menu.h"
#include "graphics.h"
#include "form.h"

	Menu::Menu() {
		mainMenu[0] = "1-Player (press 1)";
		mainMenu[1] = "2-Players (press 2)";
		mainMenu[2] = "Exit (press esc)";
		mainMenuSelected = 0;
		init();
	}

	Menu::~Menu() {
		
	}

	void Menu:: init() {
		if (!(status == GameState::STATUS_GAMEOVER)) {
			graphics::setFont("assets\\Adoring.ttf");
			graphics::playMusic(std::string(ASSET_PATH) + "The Avengers.mp3", 0.5f, true, 4000);
		}
		else if (status == GameState::STATUS_GAMEOVER) {
			graphics::setFont("assets\\Jellies.ttf");
		}
		
	}

	void Menu::update() {

		if (graphics::getKeyState(graphics::SCANCODE_1)) {
			status = GameState::STATUS_GAMEFOR1;
		}
		else if (graphics::getKeyState(graphics::SCANCODE_2)) {
			status = GameState::STATUS_GAMEFOR2;
			
		} 
		else if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) {
			status = GameState::STATUS_END;
		}

	}

	void Menu::draw() {

		if (status == GameState::STATUS_MENU) {
			graphics::Brush br;

			//background for menu screen
			br.texture = std::string(ASSET_PATH) + "marvel2.png";
			br.outline_opacity = 0.0f;
			graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
			br.texture = "";

			graphics::Brush brush;
			brush.texture = std::string(ASSET_PATH) + "logo-marvel-removebg.png";
			brush.outline_opacity = 0.0f;
			graphics::drawRect(CANVAS_WIDTH -70, CANVAS_HEIGHT - 350, 120, 120, brush);
			brush.texture = "";

			//menu
			graphics::drawText(CANVAS_WIDTH  - 250, CANVAS_HEIGHT / maxNum + 200 , 30, mainMenu[0], br);	
			graphics::drawText(CANVAS_WIDTH -250 , (CANVAS_HEIGHT/ maxNum) + 250 , 30, mainMenu[1], br);
			graphics::drawText(CANVAS_WIDTH -250 , (CANVAS_HEIGHT/ maxNum) + 300 , 30, mainMenu[2], br);
		
		} else if (status == GameState::STATUS_GAMEOVER) {
			graphics::Brush br;

			//background for game over screen
			br.texture = std::string(ASSET_PATH) + "sky.png";
			graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
			br.texture = "";

			//Message
			graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT / 2, 50, "GAME OVER", br);
		}
	}

