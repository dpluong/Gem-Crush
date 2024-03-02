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
        if (m_Board->CheckMatch())
        {

            m_View->SwapDiamond();

            m_View->ClearMouseInputQueue();
        }
        else
        {
            m_Board->SwapValue(m_View->GetSelectedDiamondPositions()[0], m_View->GetSelectedDiamondPositions()[1]);
            m_View->SwapDiamond();
        }
        m_View->UpdateMappingBoard(m_Board->ExportBoard());
        m_View->_swapped = false;
    }

}

void BoardController::SwapAgainIfNotMatch()
{
    if (m_Board != nullptr)
    {
        if (!m_Board->CheckMatch())
        {
            if (m_View != nullptr)
            {

                m_View->SwapDiamond();
                if (m_View->GetSelectedDiamondPositions().size() == 2)
                {
                    m_View->ClearMouseInputQueue();
                }
            }
        }
    }
}