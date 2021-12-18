#ifndef DIAMONDBOARD_H
#define DIAMONDBOARD_H
#include <SDL2/SDL.h>
#include "Block.h"
#include <vector>
#include <memory>




class DiamondBoard
{
private:
    std::vector< std::shared_ptr<Block> > Board;
    int x_position;
    int y_positionl;
public: 
    int width;
    int height;
    int score;
public:
    DiamondBoard(int, int);
    ~DiamondBoard();
    void Initialize();
    int index(int x, int y) const { return x + width * y; }
    void SwapValue(int, int);
    bool CheckMatch();
    bool Check3x3Square(int, int);
    bool CheckRow(int, int);
    bool CheckColumn(int, int);
    std::vector<int> ExportBoard();
    int GetScore();
};

#endif