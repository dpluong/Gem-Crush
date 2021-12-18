#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class Block {
    private:
        /*int block_width;
        int block_height;
        int block_x;
        int block_y;*/
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
       /* void SetBlockPosition(int, int);
        
        int GetXBlock() { return block_x; }
        int GetYBlock() { return block_y; }
        int GetBlockWidth() { return block_width; }
        int GetBlockHeight() { return block_height;  }
        */
};

#endif