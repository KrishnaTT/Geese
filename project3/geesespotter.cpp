// By: Krishna. T
// Written: Oct 28, 2021

#include <iostream>
#include "geesespotter_lib.h"

char * createBoard(std::size_t xdim, std::size_t ydim)
{
    char * board {new char[xdim*ydim] {}};

    for(int i = 0; i < xdim*ydim; ++i)
    {
        board[i] = 0x00;
    }
    
    return board;
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim)
{
    int num{};
    int xloc{};
    int yloc{};

    for(int position = 0; position < xdim*ydim; ++position)
    {
        if (board[position] == 9)
        {
            for(int y = -1; y < 2; ++y)
            {
                for(int x = -1; x < 2; ++x)
                {
                    xloc = position%xdim;
                    yloc = position/xdim;
                    num = xdim*y + x;

                    if ((xloc + x >= 0) && (xloc + x < xdim) && (yloc + y >= 0) && (yloc + y < ydim))
                    {
                        if (board[position + num] != 9)
                        {
                            board[position + num] += 1;
                        }
                    }
                    
                }
            }
        }
    }
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim)
{
    for(int i = 0; i < xdim*ydim; ++i)
    {
        board[i] = board[i] | hiddenBit();
    }
}

void cleanBoard(char * board)
{
    delete[] board;
    board = nullptr;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim)
{   
    int x{}; // counts the index of the array
    for(int i = 0; i < ydim; ++i)
    {
        for(int i = 0; i < xdim; ++i)
        {
            if ((board[x] & hiddenBit()) == 0) // the field value is displayed
            {
                char board2[3]{};
                board2[0] += (48 + (board[x] & valueMask()));
                std::cout << board2[0];
            }

            else if ((board[x] & markedBit()) > 0) // marked bit
            {
                std::cout << "M";
            }

            else if (board[x] == (board[x] | hiddenBit())) // if hidden bit
            {
                std::cout << "*";
            }

            x++;
        }

        std::cout << "\n";
    }
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    if ((board[xdim*yloc + xloc] & markedBit()) > 0) // check if its marked
    {
        return 1;
    }

    if ((board[xdim*yloc + xloc] & hiddenBit()) == 0) // if hidden
    {
        return 2;
    }

    if ((board[xdim*yloc + xloc] ^ hiddenBit()) == 9) // if field contains goose
    {
        board[xdim*yloc + xloc] &= valueMask();
        return 9;
    }

    else // if empty field
    {
        board[xdim*yloc + xloc] &= valueMask();
        int a = xdim*yloc + xloc;
    
        if ((board[xdim*yloc + xloc] & valueMask()) == 0)
        {
            int num{};

            for(int y = -1; y < 2; ++y)
            {
                for(int x = -1; x < 2; ++x)
                {
                    num = xdim*y + x;
                    if ((xloc + x >= 0) && (xloc + x < xdim) && (yloc + y >= 0) && (yloc + y < ydim))
                    {
                        if ((board[num+a] & valueMask()) != 9 && (board[num+a] & markedBit()) == 0)
                        {
                            board[num+a] &= valueMask();
                        }
                    }
                            
                }
            }
        }
    }

    return 0;
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    if ((board[xdim*yloc + xloc] & markedBit()) > 0) // check if its marked
    {
        board[xdim*yloc + xloc] = board[xdim*yloc + xloc] ^  markedBit(); // unmark it
        return 2;
    }

    if ((board[xdim*yloc + xloc] & hiddenBit()) > 0) // if hidden
    {
        board[xdim*yloc + xloc] = board[xdim*yloc + xloc] | markedBit(); // mark it
    }

    return 0;
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim)
{
    bool win{true};
    for(int i = 0; i < xdim*ydim; i++)
    {
        if ((board[i] & hiddenBit()) > 0 && (board[i] & valueMask()) != 9)
        {
            win = false;
        }
    }
    
    if (win == false)
    {
        return false;
    }

    else
    {
        return true;
    }
}

// End
