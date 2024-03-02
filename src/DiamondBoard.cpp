#include "DiamondBoard.h"
#include <iostream>
#include <fstream>  

DiamondBoard::DiamondBoard(int w, int h)
{
    width = w;
    height = h;
    score = 0;
    //Board = new Block [height * width];
}

DiamondBoard::~DiamondBoard()
{
    //delete[] Board;
}

void DiamondBoard::Initialize()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            Board.push_back(std::make_unique<Block>());
            Board[index(j, i)]->SetXYOnBoard(i, j);
            if (j != 2)
            {
                Board[index(j, i)]->SetValue(1);
            } else 
            {
                Board[index(j, i)]->SetValue(2);
            }
            //int block_x = 100 + Board[index(j, i)]->GetBlockWidth() * j;
            //int block_y = 100 + Board[index(j, i)]->GetBlockHeight() * i; 
            //Board[index(j, i)]->SetBlockPosition(block_x, block_y);
        }
    }
}

void DiamondBoard::SwapValue(int cell0, int cell1)
{
    //std::cout << "Try to swap " << Board[cell0]->GetValue() << " and " << Board[cell1]->GetValue() << std::endl;
    int temp_val = Board[cell0]->GetValue();
    Board[cell0]->SetValue(Board[cell1]->GetValue());
    Board[cell1]->SetValue(temp_val);
    //std::cout << "Swapped " << Board[cell0]->GetValue() << " and " << Board[cell1]->GetValue() << std::endl;
}

bool DiamondBoard::CheckRow(int x, int row)
{

    if (Board[index(x, row)]->GetValue() == 0 || Board[index(x + 1, row)]->GetValue() == 0 || Board[index(x + 2, row)]->GetValue() == 0)
    {
        return false;
    }
    if(Board[index(x, row)]->GetValue() == Board[index(x + 1, row)]->GetValue() && Board[index(x, row)]->GetValue() == Board[index(x + 2, row)]->GetValue())
    {
        
        Board[index(x, row)]->SetValue(0);
        Board[index(x + 1, row)]->SetValue(0);
        Board[index(x + 2, row)]->SetValue(0);
        return true;
    }
    return false;
}

bool DiamondBoard::CheckColumn(int x, int collumn)
{
    if (Board[index(collumn, x)]->GetValue() == 0 || Board[index(collumn ,x + 1)]->GetValue() == 0 || Board[index(collumn, x + 2)]->GetValue() == 0)
    {
        return false;
    }
    if (Board[index(collumn, x)]->GetValue() == Board[index(collumn, x + 1)]->GetValue() && Board[index(collumn, x)]->GetValue() == Board[index(collumn, x + 2)]->GetValue())
    {
        
        Board[index(collumn, x)]->SetValue(0);
        Board[index(collumn, x + 1)]->SetValue(0);
        Board[index(collumn, x + 2)]->SetValue(0);
        return true;
    }
    return false;
}

bool DiamondBoard::Check3x3Square(int x, int y)
{
    int first_collumn = x;
    int first_row = y;
    int middle_collumn = x + 1;
    int middle_row = y + 1;
    int last_column = x + 2;
    int last_row = y + 2;
    bool _firstRow;
    bool _middleRow;
    bool _lastRow;
    _firstRow = CheckRow(first_collumn, first_row);
    _middleRow = CheckRow(first_collumn, middle_row);
    _lastRow = CheckRow(first_collumn, last_row);
    bool _firstColumn = false;
    bool _middleCollumn = false;
    bool _lastCollumn = false;
    
    /*if (!_firstRow && !_middleRow && !_lastRow)
    {
        _firstColumn = CheckColumn(first_row, first_collumn);
        _middleCollumn = CheckColumn(first_row, middle_collumn);
        _lastCollumn = CheckColumn(first_row, last_column);
    }*/
    return _firstRow || _middleRow || _lastRow || _firstColumn || _middleCollumn || _lastCollumn ;
}

bool DiamondBoard::CheckMatch()
{
    bool is_match = false;
    for (int i = 0; i < height - 2; ++i)
    {
        for (int j = 0; j < width - 2; ++j) 
        {
            if (Check3x3Square(j, i))
            {
                is_match = true;
                score += 1;
            }
        }
    }
    return is_match;
}

std::vector<int> DiamondBoard::ExportBoard()
{
    std::vector<int> board;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j) 
        {
            board.push_back(Board[index(j, i)]->GetValue());
        }
    }
    return board;
}

int DiamondBoard::GetScore()
{
    return score;
}