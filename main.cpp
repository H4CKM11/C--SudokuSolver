#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

// Initialize ROW and COL Globally to remember how to do it and for convienence
const int ROW = 9;
const int COL = 9;

class sudoku
{

private:
    // Hardcode the board since this is a simple program for algo practice
    int board[ROW][COL] = {
        {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 6, 0, 0, 0, 0, 0},
        {0, 7, 0, 0, 9, 0, 2, 0, 0},
        {0, 5, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 4, 5, 7, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 3, 0},
        {0, 0, 1, 0, 0, 0, 0, 6, 8},
        {0, 0, 8, 5, 0, 0, 0, 1, 0},
        {0, 9, 0, 0, 0, 0, 4, 0, 0}};

    // Temp array to store the each Row and Col
    int tempArray[9];
    int rowPosition = 0;

    // Checks to see if any zeros are in the board
    bool isBoardSolved()
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if (board[i][j] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isValid(int row, int col, int possibility)
    {
        if (!checkRow(row, possibility))
        {
            return false;
        }

        if (!checkCol(col, possibility))
        {
            return false;
        }

        if (!check3x3Grid(row, col, possibility))
        {
            return false;
        }

        return true;
    }

    bool check3x3Grid(int row, int col, int posibility)
    {
        int startRow = row - row % 3;
        int startCol = col - col % 3;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[startRow + i][startCol + j] == posibility)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool checkCol(int col, int posibility)
    {
        for (int i = 0; i < 9; i++)
        {
            if (posibility == board[i][col])
            {
                return false;
            }
        }

        return true;
    }

    bool checkRow(int row, int posibility)
    {
        for (int i = 0; i < 9; i++)
        {
            if (posibility == board[row][i])
            {
                return false;
            }
        }

        return true;
    }

public:
    // Print the board function
    void print_board()
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if (j == 3 || j == 6)
                {
                    std::cout << std::setw(2) << "|";
                }

                std::cout << std::setw(2) << board[i][j] << "";
            }
            if (i == 2 || i == 5)
            {
                std::cout << std::endl;
                for (int k = 0; k < ROW; k++)
                {
                    if (k == 3 || k == 6)
                    {
                        std::cout << "-+";
                    }

                    std::cout << "--";
                }
            }
            std::cout << std::endl;
        }
    }

    bool solvePuzzle()
    {
        for (int rowPosition = 0; rowPosition < ROW; rowPosition++)
        {
            for (int colPosition = 0; colPosition < COL; colPosition++)
            {
                // Check to see if the slot needs to fill
                if (board[rowPosition][colPosition] == 0)
                {
                    // Recursion Start, Starting all posibilities from 1-9
                    for (int posibility = 1; posibility <= 9; posibility++)
                    {
                        if (isValid(rowPosition, colPosition, posibility))
                        {
                            board[rowPosition][colPosition] = posibility;
                            if (solvePuzzle())
                            {
                                return true;
                            }
                            board[rowPosition][colPosition] = 0;
                        }
                    }
                    return false;
                }
            }
        }

        return true;
    }
};

int main()
{
    sudoku game;

    system("cls");
    std::cout << "Initial Game Board \n----------------------" << std::endl;
    game.print_board();

    game.solvePuzzle();

    if (game.solvePuzzle())
    {

        std::string input;
        std::cout << "Press Enter to continue...";
        std::getline(std::cin, input);
        std::cout << "\n\n\nSolved Game Board \n----------------------" << std::endl;
        game.print_board();
    }
    return 0;
}
