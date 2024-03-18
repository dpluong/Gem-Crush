#include "App.h"
#include <SDL2/SDL_image.h>
#include <iostream>
App App::Application;

void App::initSDL()
{
    int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("Diamond Match", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void App::cleanup (void)
{
    SDL_DestroyRenderer(renderer);
	
	SDL_DestroyWindow(window);
	
	SDL_Quit();
}

void App::prepareScene()
{
    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_RenderClear(renderer);
}

void App::presentScene()
{
    SDL_RenderPresent(renderer);
}



SDL_Window* App::GetWindow()
{
    return window;
}

SDL_Renderer* App::GetRenderer()
{
    return renderer;
}

App* App::GetApplication()
{
    return &App::Application;
}

void App::Initialize()
{
	swap_back = false;
    _isRunning = true;
    initSDL();
    View = std::make_unique<BoardView>(8, 10);
    Board = std::make_unique<DiamondBoard>(8, 10);
    Controller = std::make_unique<BoardController>(Board, View);

    Board->Initialize();
    while (Board->CheckMatch())
    {
        Board->FillingBoard();
    }
    
    Controller->Initialize();
    View->InitBoardView();
    View->LoadImages();
}

void App::BrowserGameLoop()
{
    prepareScene();

    SDL_Event event;    
    // Polling input from mouse/keyboard
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            _isRunning = false;
            break;
        default:
            View->HandleMouseEvent(&event);
            break;
        }
    }
    // Running the game logic such as matches, swapping and generating new diamonds
    Controller->Update();
    // Rendering the diamond board
    View->Render();

    // Swapping the diamonds back if there is no match
    if (swap_back)
    {
        SDL_Delay(100);
    }

    presentScene();

    if (Controller != nullptr)
    {
        Controller->SwapAgainIfNotMatch();
        swap_back = true;
    }

    View->ClearDiamondMatch();
    SDL_Delay(16);
}

void App::DesktopGameLoop()
{
    while (_isRunning)
    {
        prepareScene();

        SDL_Event event;
        // Polling input from mouse/keyboard
        while (SDL_PollEvent(&event))
	    {
		    switch (event.type)
		    {
			    case SDL_QUIT:
                    _isRunning = false;
                    break;
                default:
                    View->HandleMouseEvent(&event);
                    break;
            }
            
	    }
        // Running the game logic such as matches, swapping and generating new diamonds
        Controller->Update();
        
        // Rendering the diamond board
        View->Render();

        // Swapping the diamonds back if there is no match
        if (Controller->is_swapped_back)
        {
            SDL_Delay(100);
        }
        presentScene();
        if (Controller->is_match)
        {
            SDL_Delay(200);
        }
        
        Controller->SwapAgainIfNotMatch();
        
        View->ClearDiamondMatch();
        Controller->UpdateAfterMatch();
        SDL_Delay(16);
    }
}

void App::QuitGame()
{
	cleanup();
}

int App::GetScore()
{
    return Board->GetScore();
}