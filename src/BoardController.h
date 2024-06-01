#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "BoardView.h"
#include "DiamondBoard.h"

class BoardController {
    private:
        std::shared_ptr<DiamondBoard> m_Board;
        std::shared_ptr<BoardView> m_View; 
    public:
        bool is_match = false;
        bool is_swapped_back = false;
    public:
        BoardController(std::shared_ptr<DiamondBoard>, std::shared_ptr<BoardView> );
        void Initialize();
        void Update();
        void UpdateAfterMatch();
        void SwapAgainIfNotMatch();
};

#endif