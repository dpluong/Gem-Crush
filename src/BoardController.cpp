#include "BoardController.h"
#include <iostream>

BoardController::BoardController(std::shared_ptr<DiamondBoard> board, std::shared_ptr<BoardView> view)
{
    m_Board = board;
    m_View = view;
}

void BoardController::Initialize()
{
    m_View->SetMappingBoard(m_Board->ExportBoard());
}

void BoardController::Update()
{
    if (m_View->_swapped)
    {
        
        m_Board->SwapValue(m_View->GetSelectedDiamondPositions()[0], m_View->GetSelectedDiamondPositions()[1]);
        if (m_Board->CheckForMatches())
        {

            m_View->SwapDiamond();

            m_View->ClearMouseInputQueue();

            m_View->UpdateMappingBoard(m_Board->ExportBoard());
            is_match = true;
            is_swapped_back = false;
        }
        else
        {
            m_Board->SwapValue(m_View->GetSelectedDiamondPositions()[0], m_View->GetSelectedDiamondPositions()[1]);
            m_View->SwapDiamond();
            m_View->UpdateMappingBoard(m_Board->ExportBoard());
            is_match = false;
            is_swapped_back = true;
        }
        
        m_View->_swapped = false;
    }
    else
    {
        if (m_Board->CheckForMatches())
        {
            is_match = true;
            //m_Board->FillingBoard();
            m_View->UpdateMappingBoard(m_Board->ExportBoard());
            //m_View->LoadImages();
        }
        else
            is_match = false;
    }
}

void BoardController::UpdateAfterMatch()
{
    if (is_match)
    {
        m_Board->FillingBoard();
        m_View->UpdateMappingBoard(m_Board->ExportBoard());
        m_View->LoadImages();
    }
}

void BoardController::SwapAgainIfNotMatch()
{
    if (m_Board != nullptr)
    {
        if (!is_match)
        {
            if (m_View != nullptr)
            {
                m_View->SwapDiamond();
                if (m_View->GetSelectedDiamondPositions().size() == 2)
                {
                    m_View->ClearMouseInputQueue();
                }
                //is_swapped_back = true;
            }
        }

    }
}