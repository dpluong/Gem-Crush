#ifndef DIAMONDBOARD_H
#define DIAMONDBOARD_H
#include <SDL2/SDL.h>
#include "Block.h"
#include <vector>
#include <memory>




class DiamondBoard
{
private:
    std::vector< std::unique_ptr<Block> > Board;
    std::vector<std::vector<bool>> visited;
    std::vector<int> matches;
    
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
    bool CheckForMatches();
    void Check3x3Square(int, int);
    void CheckRow(int, int);
    void CheckColumn(int, int);
    void FillingBoard();
    void FloodFill(int, int, bool &, std::vector<int> &, std::vector<int>&, std::vector<int> &);
    bool FindAllMatches();
    std::vector<int> ExportBoard();
    int GetScore();
};

#endif