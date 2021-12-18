#include "Block.h"
#include<iostream>

Block::Block() { }
Block::~Block() { }
/*
void Block::SetBlockPosition(int x, int y) 
{
    block_x = x;
    block_y = y;
    
}*/

int Block::GetValue()
{
    return diamond_value;
}

void Block::SetValue(int val)
{
    diamond_value = val;
}

void Block::SetXYOnBoard(int X, int Y)
{
    x_coordinate = X;
    y_coordinate = Y;
}


