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
    srand(time(0));
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            Board.push_back(std::make_unique<Block>());
            Board[index(j, i)]->SetXYOnBoard(i, j);
            int newValue = std::rand() % 5 + 1;
            Board[index(j, i)]->SetValue(newValue);
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

void DiamondBoard::FillingBoard()
{
    
    srand(time(0));
    for (int j = 0; j < width; ++j)
    {
        for (int i = height - 1; i >= 0; --i)
        {
            if (Board[index(j, i)]->GetValue() != 0)
                continue;
            else
            {
                int row = i;
                while (Board[index(j, row)]->GetValue() == 0 && row > 0)
                {
                    --row;
                }
                
                if (row == 0 && Board[index(j, row)]->GetValue() == 0)
                {
                    // Generate new tiles
                    while (i >= 0)
                    {
                        int newValue = std::rand() % 5 + 1;
                        Board[index(j, i)]->SetValue(newValue);
                        --i;
                    }
                    break;
                }
                else
                {
                    Board[index(j, i)]->SetValue(Board[index(j, row)]->GetValue());
                    Board[index(j, row)]->SetValue(0);
                }
            }
        }
    }
}

void DiamondBoard::FloodFill(int row, int col, bool &have_matches, std::vector<int> &horizontal, std::vector<int> &verical, std::vector<int> &matches)
{
    const int dr[] = {0, 0, 1, -1};
    const int dc[] = {1, -1, 0, 0};

    if (Board[index(col, row)] == nullptr || visited[row][col])
        return;

    visited[row][col] = true;
    /*int matchValue = Board[index(col, row)]->GetValue();

    if (horizontal.empty() || std::abs(index(col, row) - horizontal.back()) == 1)
    {
        if (horizontal.size() != 0)
        {
            //std::cout << horizontal.back() << " " << index(col, row) << std::endl;
        }
        horizontal.push_back(index(col, row));
    }

    if (horizontal.size() >= 3)
    {
        if (col + dc[0] >= width || (col + dc[0] < width && matchValue != Board[index(col + dc[0], row)]->GetValue()))
        have_matches = true;
        for (int i = 0; i < horizontal.size(); ++i)
        {
            //std::cout << Board[horizontal[i]]->GetValue() << " ";
           //Board[horizontal[i]]->SetValue(0);
           
           matches.push_back(horizontal[i]);
        }
        //std::cout << std::endl;
        horizontal.clear();
    }
    
    
    if (verical.empty() || std::abs(index(col, row) - verical.back()) == width)
    {
        verical.push_back(index(col, row));
    }

    if (verical.size() >= 3)
    {
        if (row + dr[2] >= height || (row + dr[2] < height && matchValue != Board[index(col, row + dr[2])]->GetValue()))
        {
            have_matches = true;
            for (int i = 0; i < verical.size(); ++i)
            {
                //Board[verical[i]]->SetValue(0);
                
                matches.push_back(verical[i]);
            }
            verical.clear();
        }
    }*/

    // Define directions: right, left, down, up
    for (int d = 0; d < 4; ++d)
    {
        int newRow = row + dr[d];
        int newCol = col + dc[d];
        if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width &&
            !visited[newRow][newCol] && Board[index(newCol, newRow)]->GetValue() == Board[index(col, row)]->GetValue())
        {
            if (d <= 1)
            {
                //if (horizontal.empty() || std::abs(index(newCol, newRow) - horizontal.back()) == 1)
                horizontal.push_back(index(newCol, newRow));
                
                /*if (verical.size() >= 3)
                {
                    for (int i = 0; i < verical.size(); ++i)
                    {
                        // Board[verical[i]]->SetValue(0);

                        matches.push_back(verical[i]);
                    }
                }*/
            }
            
            else
            {
                /*if (verical.empty() || std::abs(index(col, row) - verical.back()) == width)
                    verical.push_back(index(newCol, newRow));
                else
                {
                    verical.clear();
                    verical.push_back(index(col, row));
                    verical.push_back(index(newCol, newRow));
                }*/
                /*
                if (horizontal.size() >= 3)
                {
                    for (int i = 0; i < horizontal.size(); ++i)
                    {
                        // Board[verical[i]]->SetValue(0);

                        matches.push_back(horizontal[i]);
                    }
                    horizontal.clear();
                }*/
                if (horizontal.size() < 3)
                {
                    horizontal.clear();
                    horizontal.push_back(index(newCol, newRow));
                }
            }
            FloodFill(newRow, newCol, have_matches, horizontal, verical, matches);
        }
    }
}

bool DiamondBoard::FindAllMatches()
{
    std::vector<int> horizontal;
    std::vector<int> vertical;
    std::vector<int> matches;
    visited.assign(height, std::vector<bool>(width, false));

    bool have_matches = false;
   
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (!visited[i][j])
            {
                horizontal.push_back(index(j, i));
                vertical.push_back(index(j, i));
                FloodFill(i, j, have_matches, horizontal, vertical, matches);
                if (horizontal.size() >= 3)
                {
                    have_matches = true;
                    for (int i = 0; i < horizontal.size(); ++i)
                    {
                        std::cout << horizontal[i] << std::endl;
                        matches.push_back(horizontal[i]);
                    }
                }
                horizontal.clear();
                vertical.clear();
            }
        }
    }

    for (int i = 0; i < matches.size(); ++i)
    {
        Board[matches[i]]->SetValue(0);
        //std::cout << matches[i] << std::endl;
    }
    matches.clear();
    return have_matches;
}

void DiamondBoard::CheckRow(int row, int c)
{
    int matchValue = Board[index(c, row)]->GetValue();

    if (Board[index(c + 1, row)]->GetValue() == matchValue 
    && Board[index(c + 2, row)]->GetValue() == matchValue)
    {
        matches.push_back(index(c, row));
        matches.push_back(index(c + 1, row));
        matches.push_back(index(c + 2, row));
    }
}

void DiamondBoard::CheckColumn(int r, int column)
{
    int matchValue = Board[index(column, r)]->GetValue();

    if (Board[index(column, r + 1)]->GetValue() == matchValue 
    && Board[index(column, r + 2)]->GetValue() == matchValue)
    {
        matches.push_back(index(column, r));
        matches.push_back(index(column, r + 1));
        matches.push_back(index(column, r + 2));
    }
}

void DiamondBoard::Check3x3Square(int row, int col)
{
    for (int r = row; r <= row + 2; ++r)
    {
        CheckRow(r, col);
    }

    for (int c = col; c <= col + 2; ++c)
    {
        CheckColumn(row, c);
    }
}

bool DiamondBoard::CheckForMatches()
{
    bool isMatch = false;

    for (int row = 0; row < height - 2; ++row)
    {
        for (int col = 0; col < width - 2; ++col) 
        {
            Check3x3Square(row, col);
        }
    }

    if (matches.size() > 0)
    {
        for (int i = 0; i < matches.size(); ++i)
        {
            Board[matches[i]]->SetValue(0);
        }
        matches.clear();
        isMatch = true;
    }

    return isMatch;
}

std::vector<int> DiamondBoard::ExportBoard()
{
    //srand(time(0));
    std::vector<int> board;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j) 
        {
            /*
            if (Board[index(j, i)]->GetValue() == 0)
            {
                int newValue = std::rand() % 5 + 1;
                Board[index(j, i)]->SetValue(newValue);
            }*/
            board.push_back(Board[index(j, i)]->GetValue());
        }
    }
    return board;
}

int DiamondBoard::GetScore()
{
    return score;
}