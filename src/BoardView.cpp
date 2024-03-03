#include "BoardView.h"
#include<iostream>
#include <cmath>

BoardView::BoardView(int w, int h)
{
    width = w;
    height = h;
    _swapped = false;
}

BoardView::~BoardView() { }

void BoardView::InitBoardView()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            boardView.push_back(std::make_unique<Diamond>());
            int cell_x = 100 + boardView[index(j, i)]->GetDest().w * j;
            int cell_y = 100 + boardView[index(j, i)]->GetDest().h * i; 
            boardView[index(j, i)]->SetDest(cell_x, cell_y);
        }
    }
}



void BoardView::SwapDiamond()
{
        if (selected_positions.size() >= 2)
        {
            int x0 = boardView[selected_positions[0]]->GetDest().x;
            int y0 = boardView[selected_positions[0]]->GetDest().y;
            int x1 = boardView[selected_positions[1]]->GetDest().x;
            int y1 = boardView[selected_positions[1]]->GetDest().y;
        
            boardView[selected_positions[0]]->SetDest(x1, y1);
            boardView[selected_positions[1]]->SetDest(x0, y0);
            std::swap(boardView[selected_positions[0]], boardView[selected_positions[1]]);
        }
}

void BoardView::LoadImages()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (j == 2)
            {
                boardView[index(j, i)]->loadTexture((char *)"assets/2.png");
            } else
            {
                boardView[index(j, i)]->loadTexture((char *)"assets/1.png");
            }
        }
    }
}

void BoardView::Render()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (mapping_board[index(j, i)] == 0)
            {
                boardView[index(j, i)]->RenderMatch();
            } else
            {
                boardView[index(j, i)]->blit();
            }
        }
    }
}

void BoardView::HandleMouseEvent(SDL_Event *e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool is_inside = true;

        int top_left_x = 100;
        int top_left_y = 100;

        int board_width = width * boardView[index(0, 0)]->GetDest().w;
        int board_height = height * boardView[index(0, 0)]->GetDest().h;

        if( x < top_left_x)
		{
            is_inside = false;
        }
        
		else if( x > top_left_x + board_width )
		{
			is_inside = false;
		}
		
		else if( y < top_left_y )
		{
			is_inside = false;
		}
		
		else if( y > top_left_y + board_height )
		{
			is_inside = false;
		}

        if (!is_inside && e->type == SDL_MOUSEBUTTONUP)
        {
            ClearMouseInputQueue();
        }

        if (is_inside)
        {
            switch (e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                selected_positions.push_back(GetSelectedDiamondPosition(x, y));
                break;
            case SDL_MOUSEBUTTONUP:
                selected_positions.push_back(GetSelectedDiamondPosition(x, y));
                break;
            }
        }

        if (selected_positions.size() == 2)
        {
            if (CheckAdjacentCell())
            {
                _swapped = true;
            }
            else
            {
                ClearMouseInputQueue();
            }
        }


        
    }
}

int BoardView::GetSelectedDiamondPosition(int mouse_x, int mouse_y)
{
    int cell_width = boardView[index(0, 0)]->GetDest().w;
    int cell_height = boardView[index(0, 0)]->GetDest().h;
    int top_left_x = boardView[index(0, 0)]->GetDest().x;
    int top_left_y = boardView[index(0, 0)]->GetDest().y;
    int j = (mouse_x - top_left_x) / cell_width;
    int i = (mouse_y - top_left_y) / cell_height;
    if (j == width)
    {
        j -= 1;
    }
    if (i == height)
    {
        i -= 1;
    }
    std::cout<< "Mouse x: " << mouse_x << ", " << " Mouse y: " << mouse_y <<std::endl;
    std::cout<< i << ", "<< j << std::endl;
    return index(j, i);
}

std::vector<int> BoardView::GetSelectedDiamondPositions()
{
    return selected_positions;
}

void BoardView::SetMappingBoard(std::vector<int> board)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j) 
        {
            mapping_board.push_back(board[index(j, i)]);
        }
    }
}

bool BoardView::CheckAdjacentCell()
{
    if (abs (selected_positions[0] - selected_positions[1]) == 1 || abs (selected_positions[0] - selected_positions[1]) == width)
    {
        return true;
    }
    return false;
}

void BoardView::ClearMouseInputQueue()
{
    if (selected_positions.size() != 0)
    {
        selected_positions.clear();
    }
}

void BoardView::UpdateMappingBoard(std::vector<int> board)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j) 
        {
            mapping_board[index(j, i)] = board[index(j, i)];
        }
    }
}

void BoardView::ClearDiamondMatch()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j) 
        {
            if (mapping_board[index(j, i)] == 0)
            {
                boardView[index(j, i)]->ClearMatch();
            }
        }
    }
}