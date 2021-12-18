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
    View = std::make_shared<BoardView>(4, 4);
    Board = std::make_shared<DiamondBoard>(4, 4);
    
    Board->Initialize();
    View->InitBoardView();
    View->LoadImages();
    Controller = std::make_shared<BoardController>(Board, View);
    Controller->Initialize();
}

void App::BrowserGameLoop()
{
	//bool swap_back = false;
   
    //Board->Debug();

    //while (_isRunning)
    //{
        
        prepareScene();

        SDL_Event event;
	
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

        Controller->Update();

        //diamond->blit(diamond->GetX(), diamond->GetY());
        //std::cout << diamond->GetDest().h << std::endl;
        
        View->Render();
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
        //std::cout << Board->GetScore() << std::endl;
        SDL_Delay(16);
    //}
}

void App::DesktopGameLoop()
{
    while (_isRunning)
    {
        
        prepareScene();

        SDL_Event event;
	
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

        Controller->Update();

        //diamond->blit(diamond->GetX(), diamond->GetY());
        //std::cout << diamond->GetDest().h << std::endl;
        
        View->Render();
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
        //std::cout << Board->GetScore() << std::endl;
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