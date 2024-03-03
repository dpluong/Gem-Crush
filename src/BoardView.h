#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>
#include "Diamond.h"

class BoardView {
    private:
        std::vector< std::unique_ptr<Diamond> > boardView;
        std::vector<int> selected_positions;
        std::vector<int> mapping_board;

    public:
        int width;
        int height;
        bool _swapped;

    public:
        BoardView(int, int);
        ~BoardView();
        int index(int x, int y) const { return x + width * y; }
        void InitBoardView();
        void SwapDiamond();
        void LoadImages();
        void Render();
        void HandleMouseEvent(SDL_Event *);
        int GetSelectedDiamondPosition(int, int);
        std::vector<int> GetSelectedDiamondPositions();
        void SetMappingBoard(std::vector<int>);
        bool CheckAdjacentCell();
        void ClearMouseInputQueue();
        void UpdateMappingBoard(std::vector<int>);
        void ClearDiamondMatch();
};

#endif