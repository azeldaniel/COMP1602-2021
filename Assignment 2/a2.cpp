#include <iostream>
#include <fstream>

using namespace std;

struct Tile
{
    int data;
    bool isEditable;
};

struct Board
{
    Tile tiles[4][4];
    int size;
};

Tile makeTile(int data, bool isEditable);
Board loadAndMakeBoard();
bool isUniqueForQuadrant(Board board, int row, int column, int guess);
bool isValidGuess(Board board, int row, int column, int guess);
bool isBoardComplete(Board board);
void printBoard(Board board);

int main()
{

    int wins = 0, quits = 0, correctGuesses = 0, incorrectGuesses = 0, option = 1;
    int row, column, guess = 1;

    while (option != 0)
    {
        cout << "1. Load and Play Game" << endl;
        cout << "2. Statistics" << endl;
        cout << "0. Exit" << endl;
        cin >> option;

        if (option == 1)
        {
            Board board = loadAndMakeBoard();

            while (guess != 0 && !isBoardComplete(board))
            {

                cout << endl
                     << endl;
                printBoard(board);

                cout << "Enter row , column, guess: ";
                cin >> row >> column >> guess;

                if (guess == 0)
                {
                    cout << "You quit" << endl;
                    quits++;
                    guess = -1;
                    break;
                }
                else
                {
                    if (isValidGuess(board, row, column, guess))
                    {
                        board.tiles[row][column].data = guess;
                        correctGuesses++;
                        if (isBoardComplete(board))
                        {
                            cout << "You win" << endl;
                            wins++;
                        }
                    }
                    else
                    {
                        cout << "Invalid guess" << endl;
                        incorrectGuesses++;
                    }
                }
            }
        }

        if (option == 2)
        {
            cout << "Wins: " << wins << endl;
            cout << "Quits: " << quits << endl;
            cout << "Correct Guesses: " << correctGuesses << endl;
            cout << "inCorrect Guesses: " << incorrectGuesses << endl;
        }
    }

    return 0;
}

Tile makeTile(int data, bool isEditable)
{
    Tile tile = {data, isEditable};
    return tile;
}

Board loadAndMakeBoard()
{
    ifstream file;
    file.open("gameData.txt");

    Board b;
    b.size = 4;
    int data;

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            file >> data;
            if (data == 0)
                b.tiles[row][column] = makeTile(data, true);
            else
                b.tiles[row][column] = makeTile(data, false);
        }
    }

    file.close();

    return b;
}

void printBoard(Board board)
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (board.tiles[row][column].data == 0)
            {
                cout << "_ ";
            }
            else
            {
                cout << board.tiles[row][column].data << " ";
            }
        }
        cout << endl;
    }
}

bool isUniqueForQuadrant(Board board, int row, int column, int guess)
{
    if (row < 2 && column < 2)
    {
        return !(board.tiles[0][0].data == guess || board.tiles[0][1].data == guess || board.tiles[1][0].data == guess || board.tiles[1][1].data == guess);
    }
    else if (row < 2 && column >= 2)
    {
        return !(board.tiles[0][2].data == guess || board.tiles[0][3].data == guess || board.tiles[1][2].data == guess || board.tiles[1][3].data == guess);
    }
    else if (row >= 2 && column < 2)
    {
        return !(board.tiles[2][0].data == guess || board.tiles[2][1].data == guess || board.tiles[3][0].data == guess || board.tiles[3][1].data == guess);
    }
    else
    {
        return !(board.tiles[2][2].data == guess || board.tiles[2][3].data == guess || board.tiles[3][2].data == guess || board.tiles[3][3].data == guess);
    }
}

bool isValidGuess(Board board, int row, int column, int guess)
{
    if (!board.tiles[row][column].isEditable || guess > 4 || guess < 1)
    {
        return false;
    }

    for (int r = 0; r < 4; r++)
    {
        if (board.tiles[r][column].data == guess)
        {
            return false;
        }
    }

    for (int c = 0; c < 4; c++)
    {
        if (board.tiles[row][c].data == guess)
        {
            return false;
        }
    }

    return isUniqueForQuadrant(board, row, column, guess);
}

bool isBoardComplete(Board board)
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (board.tiles[row][column].data == 0)
            {
                return false;
            }
        }
    }
    return true;
}