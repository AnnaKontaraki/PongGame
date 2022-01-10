#include "graphics.h"
#include "Game.h"
#include "form.h"

//creates new balls
void Game::CreateBall(){
    if (!ball && !(menu.status == Menu::GameState::STATUS_MENU)) {
        ball = new Ball(*this);
    }
}

//delete balls that are out of range
void Game::checkBall(){   
    if (ball && !ball->isActive()) {
        delete ball;
        ball = nullptr;
    }
}

//collision for playerA and ball
bool Game::checkLeftCollision(){
    if (!playerA || !ball) {
        return false;
    }
       playerA->setPlayer(0); //captain america
       Disk d = playerA->getHeadCollision() ;
       disk1.push_back(d);
       Disk d3 = playerA-> getHandCollision();
       disk1.push_back(d3);
       Disk  d4 = playerA->getBodyCollision() ;
       disk1.push_back(d4);
       Disk d5 = playerA->getLegCollision() ;
       disk1.push_back(d5);

       Disk d2 = ball->getCollision();

       for (int i = 0; i < disk1.size(); i++) {
           Disk d1 = disk1.at(i);

           float dxA = d1.cx - d2.cx;
           float dyA = d1.cy - d2.cy;

           if (sqrt(dxA * dxA + dyA * dyA) < d1.radius + d2.radius) {
               play_CollisionSound = true;
               return true;
           }
           
       }
       disk1.clear();
       return false;
}

//collision for playerB and ball
bool Game::checkRightCollision() {
    if (!playerB || !ball) {
        return false;
    }

    if (menu.status == Menu::GameState::STATUS_GAMEFOR1) {
        playerB->setPlayer(2); //ultron
    }
    else if (menu.status == Menu::GameState::STATUS_GAMEFOR2) {
        playerB->setPlayer(1); //iron man
    }
    
    Disk d1 = playerB->getHeadCollision();
    disk2.push_back(d1);
    Disk d3 = playerB->getHandCollision();
    disk2.push_back(d3);
    Disk  d4 = playerB->getBodyCollision();
    disk2.push_back(d4);
    Disk d5 = playerB->getLegCollision();
    disk2.push_back(d5);

    Disk d2 = ball->getCollision();

    for (int i = 0; i < disk2.size(); i++) {
        Disk d = disk2.at(i);

        float dxB = d.cx - d2.cx;
        float dyB = d.cy - d2.cy;

        if (sqrt(dxB * dxB + dyB * dyB) < d.radius + d2.radius) {
            play_CollisionSound = true;
            return true;
        }
        
    }
    disk2.clear();
    return false;
}

void Game::update(){
    //sounds
    if (play_CollisionSound) {
        std::string mp3 = std::string(ASSET_PATH) + "hit1.wav";
        graphics::playSound(mp3, 0.5f,false);
        play_CollisionSound = false;

    }

    if (play_Final) {
        std::string mp3 = std::string(ASSET_PATH) + "Final Round.mp3";
        graphics::playSound(mp3, 0.5f);
        play_Final = false;
    
    }

    //calling current update function 
    if (menu.status == Menu::GameState::STATUS_MENU) {
          menu.update();
    }
    else if (menu.status == Menu::GameState::STATUS_GAMEFOR1) {
        updateOnePlayer();
    }
    else if (menu.status == Menu::GameState::STATUS_GAMEFOR2) {
        updateTwoPlayers();
    }

    //ball's functions
    checkBall();
    CreateBall();
    
    if (ball){
        ball->update();
  
        //update score
         updateScore();
     } 
    
    if ((A == 10 && B == 10) && Once == 0){
        play_Final = true;
        Once++;
    }

    //GAME OVER
     if ((playerA && playerA->getScoreA() == 11) || (playerB && playerB->getScoreB() == 11)) {
         play_GameOver = true;
         LastSound();
         menu.setGameState(Menu::GameState::STATUS_GAMEOVER);
         menu.init(); 
     }    
 
}

void Game::LastSound() {
    if (play_GameOver) {
        std::string mp3 = std::string(ASSET_PATH) + "GameOver -sound.mp3";
        graphics::playSound(mp3, 0.5f, false);
        play_GameOver = false;
    }
}

void Game::updateOnePlayer() {
    graphics::stopMusic();

    //Creates Left player --> Captain America
    if (!playerA_initialized) {
        playerA = new Player(*this);
        playerA_initialized = true;
    }
    if (playerA) {
        playerA->update();
        playerA->updateA();
    }

    //Creates pc player --> Ultron
    if (!playerB_initialized) {
        playerB = new Player(*this);
        playerB_initialized = true;
    }
    if (playerB&& ball) {
        float Y = ball->getCurrentY();
        playerB->setCurrentY(Y);
        playerB->update();
        playerB->updatePC();
    }
   
    //boolean variables to save collision's result
    flagA = checkLeftCollision();
    flagB = checkRightCollision();
    
}

void Game::updateTwoPlayers() {
    graphics::stopMusic();

    //Creates Left player --> Captain America
    if (!playerA_initialized) {
        playerA = new Player(*this);
        playerA_initialized = true;
    }
    if (playerA) {
        playerA->update();
        playerA->updateA();
    }

    //Creates Right player --> Iron Man
    if (!playerB_initialized) {
        playerB = new Player(*this);
        playerB_initialized = true;
    }
    if (playerB) {
        playerB->update();
        playerB->updateB();
    }

    //boolean variables to save collision's result
    flagA = checkLeftCollision();    
    flagB = checkRightCollision();
}

void Game::draw() {

    graphics::Brush br;
    
    //draw menu && players
   if (menu.status == Menu::GameState::STATUS_MENU || menu.status == Menu::GameState::STATUS_GAMEOVER) {
       menu.draw();
   }

   if (menu.status == Menu::GameState::STATUS_GAMEFOR1) {
        drawOnePlayer();
   }
   else if (menu.status == Menu::GameState::STATUS_GAMEFOR2) {
        drawTwoPlayers();
   }

   //draw score 
    if (menu.status == Menu::GameState::STATUS_GAMEFOR1 || menu.status == Menu::GameState::STATUS_GAMEFOR2) {

       if (playerA) {
           string sA = std::to_string(playerA->getScoreA());
           graphics::drawText(CANVAS_WIDTH/2 - RANGE_PLAYER, CANVAS_HEIGHT/2 - 200, 40.0f,sA,br);
       }
       if (playerB) {
           string sB = std::to_string(playerB->getScoreB());
           graphics::drawText(CANVAS_WIDTH / 2 + RANGE_PLAYER, CANVAS_HEIGHT / 2 - 200, 40.0f, sB, br);
       }

       //draw ball
       if (ball)
           ball->draw();
    }      
}


void Game::drawOnePlayer() {

    //background for game screen
    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "sky.png";
    br.outline_opacity = 0.0f;
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
    br.texture = ""; 

    //draw left player --> Captain America
    if (playerA) {
        playerA->drawA();
    }

    //draw PC player --> Ultron
    if(playerB) {
        playerB->draw();
    }

}

void Game::drawTwoPlayers() {

    //background for game screen
    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "sky.png";
    br.outline_opacity = 0.0f;
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
    br.texture = "";

    //draw left player --> Captain America
    if (playerA) {
        playerA->drawA();
    }

    //draw right player --> Iron Man
    if (playerB) {
        playerB->drawB();
    }

}

void Game::updateScore(){
    if (playerA && ball->getPosX() < 0) {
        B++;
        playerB->setScoreB(B);
    }

    if (playerB && ball->getPosX() > CANVAS_WIDTH) {
        A++;
        playerA->setScoreA(A);
    }
}


Game::Game(){
    flagA = false;
    flagB = false;
}

Game::~Game() {
    if (playerA) {
        delete playerA;
    }
    if (playerB) {
        delete playerB;
    }
    if (ball) {
        delete ball;
    }
    
}