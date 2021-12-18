#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include "BoardController.h"
#include "DiamondBoard.h"
#include "BoardView.h"

class App {

public:
    SDL_Window *GetWindow();
    SDL_Renderer *GetRenderer();
    static App *GetApplication();
    void cleanup(void);
    void initSDL();
    void prepareScene();
    void presentScene();
    void Initialize();
    void BrowserGameLoop();
    void DesktopGameLoop();
    void QuitGame();
    int GetScore();

private:
    bool swap_back;
    bool _isRunning;
    static App Application;
    SDL_Renderer *renderer;
    SDL_Window *window;
    std::shared_ptr<DiamondBoard> Board;
    std::shared_ptr<BoardView> View;
    std::shared_ptr<BoardController> Controller;

};

#endif