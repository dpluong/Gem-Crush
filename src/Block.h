#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class Block {
    private:
        int x_coordinate;
        int y_coordinate;
        int diamond_value;

    public:
        Block();
        ~Block();
        int GetXOnBoard();
        int GetYOnBoard();
        int GetValue();
        void SetXYOnBoard(int, int);
        void SetValue(int);
};

#endif