#include "Diamond.h"
#include "App.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Diamond::Diamond() : renderer(App::GetApplication()->GetRenderer()) 
{
	dest.w = IMAGE_WIDTH;
	dest.h = IMAGE_HEIGHT;
}

Diamond::~Diamond()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }

}

void Diamond::loadTexture(char *filename)
{

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(renderer, filename);
	match = IMG_LoadTexture(renderer, "assets/match.png");
}

void Diamond::blit()
{
	
	//dest.x = x;
	//dest.y = y;
	//SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Diamond::RenderMatch()
{
	if (texture != nullptr && match != nullptr)
	{
		int render_succes = SDL_RenderCopy(renderer, texture, NULL, &dest);
		//std::cout << "render success ? " << render_succes << std::endl;

		SDL_RenderCopy(renderer, match, NULL, &dest);
	}
	
}

void Diamond::ClearMatch()
{
	if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	if (match != nullptr)
    {
        SDL_DestroyTexture(match);
		match = nullptr;
	}
}

SDL_Texture* Diamond::GetTexture()
{
	return texture;
}

void Diamond::SetX(int x) 
{
	this->x = x;
}

void Diamond::SetY(int y) 
{
	this->y = y;
}

void Diamond::SetDest(int x, int y)
{
	dest.x = x;
	dest.y = y;
}

int Diamond::GetX()
{
	return x;
}

int Diamond::GetY()
{
	return y;
}