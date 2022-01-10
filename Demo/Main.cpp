#include "graphics.h"
#include "form.h"
#include "Game.h"

void update(float ms){
    Game* g = (Game*)graphics::getUserData();
    g->update();
}
void draw() {
    Game* g = (Game*)graphics::getUserData();
    g->draw();
}

    
int main(){

    graphics::createWindow(WIDTH, HEIGHT, "Arcade Pong");

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    graphics::setFullScreen(true);
   
    Game g;
    g.setDebugMode(false);
    graphics::setUserData(&g);
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
   
    graphics::startMessageLoop();
    graphics::destroyWindow();

    return 0;
}