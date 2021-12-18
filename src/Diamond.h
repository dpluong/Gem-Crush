#ifndef DIAMOND_H
#define DIAMOND_H
#include <SDL2/SDL.h>

const int IMAGE_WIDTH = 38;
const int IMAGE_HEIGHT = 37;

class Diamond 
{
    private:
        int x;
        int y;
        SDL_Texture *texture;
        SDL_Texture *match;
        SDL_Renderer *renderer;
        SDL_Rect dest;

    public:
        Diamond();
        ~Diamond();
        void loadTexture(char *filename);
        void blit();
        void SetX(int);
        void SetY(int);
        int GetX();
        int GetY();
        SDL_Texture *GetTexture();
        SDL_Rect GetDest() { return dest; }
        void SetDest(int, int);
        void RenderMatch();
        void ClearMatch();
};

#endif