#include <Sefn/InputUtils.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

class TicTacToe {
    int gridSize = 3;
    std::vector<std::vector<char>> board;
    int viableLines;
    std::vector<char> rowStates, colStates, diagStates;
    bool isXTurn = true;

    // anti-diag (down-left), col (down), main-diag (down-right), row (right)
    int dr[4]{1, 1, 1, 0};
    int dc[4]{-1, 0, 1, 1};

    struct Point {
        int row;
        int col;
        Point& operator--() {
            --row;
            --col;
            return *this;
        }
        friend std::istream& operator>>(std::istream& is, Point& p) {
            is >> p.row >> p.col;
            return is;
        }
    };

    bool isValid(int r, int c) { return r >= 0 && r < gridSize && c >= 0 && c < gridSize; }

    void displayBoard() {
        std::ofstream outFile("board.txt");
        outFile << "\n<============================>\n";
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                outFile << board[i][j] << " ";
            }
            outFile << "\n";
        }
        outFile << "<============================>\n";
        outFile.close();
    }

    Point getPlayerInput() {
        Point point{-1, -1};
        std::string prompt = "Player ";
        if (isXTurn)
            prompt += "x";
        else
            prompt += "o";
        prompt += " turn. Enter empty location (r, c): ";

        point = Sefn::readValidatedInput<Point>(
            prompt, 0,
            [this](Point p) {
                auto [r, c] = --p;  // Decomposes to row, col
                if (!isValid(r, c)) {
                    std::cout << "\tWrong location, indices must be between 1 and " << gridSize
                              << ". Try again\n";
                    return false;
                }

                if (board[r][c] != '.') {
                    std::cout << "\tThis location is not empty. Try again\n";
                    return false;
                }

                return true;
            },
            "", "Invalid format. Please enter two numbers (e.g., 1 2).\n");
        return --point;
    }

    void updateGameState(int r, int c) {
        char cur = board[r][c];

        // Update Column Status
        if (colStates[c] == '.') {
            colStates[c] = cur;
        } else if (colStates[c] != cur && colStates[c] != '#') {
            viableLines--;
            colStates[c] = '#';
        }

        // Update Row Status
        if (rowStates[r] == '.') {
            rowStates[r] = cur;
        } else if (rowStates[r] != cur && rowStates[r] != '#') {
            viableLines--;
            rowStates[r] = '#';
        }

        // Update Main Diagonal Status
        if (r == c) {
            if (diagStates[0] == '.') {
                diagStates[0] = cur;
            } else if (diagStates[0] != cur && diagStates[0] != '#') {
                viableLines--;
                diagStates[0] = '#';
            }
        }

        // Update Anti-Diagonal Status
        if (r + c == gridSize - 1) {
            if (diagStates[1] == '.') {
                diagStates[1] = cur;
            } else if (diagStates[1] != cur && diagStates[1] != '#') {
                viableLines--;
                diagStates[1] = '#';
            }
        }
    }

    bool checkLine(int r, int c, int direction) {
        char cur = board[r][c];
        for (int i = 1; i < gridSize; ++i) {
            r += dr[direction];
            c += dc[direction];
            if (board[r][c] != cur) {
                return false;
            }
        }
        return true;
    }

    bool checkWin(int r, int c) {
        // Check row (dir 3), col (dir 1), main diag (dir 2), anti diag (dir 0)
        return (rowStates[r] != '#' && checkLine(r, 0, 3)) ||
               (colStates[c] != '#' && checkLine(0, c, 1)) ||
               (diagStates[0] != '#' && r == c && checkLine(0, 0, 2)) ||
               (diagStates[1] != '#' && r + c == gridSize - 1 && checkLine(0, gridSize - 1, 0));
    }

    /**
     * 0 -> normal
     * 1 -> win!
     * 2 -> tie!
     */
    int playTurn() {
        auto [r, c] = getPlayerInput();

        if (isXTurn)
            board[r][c] = 'x';
        else
            board[r][c] = 'o';

        displayBoard();
        updateGameState(r, c);

        if (checkWin(r, c)) {
            return 1;
        } else if (viableLines == 0) {
            return 2;
        }
        isXTurn = !isXTurn;
        return 0;
    }

   public:
    TicTacToe(int size = 3) {
        std::cout << "\n*********Welcome*********\n\n";
        assert(size >= 3 && size < 10);
        gridSize = size;
        viableLines = 2 * gridSize + 2;
        board = std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize, '.'));
        rowStates = colStates = std::vector<char>(gridSize, '.');
        diagStates = std::vector<char>(2, '.');
    }

    void runGame() {
        displayBoard();
        int state = 0;
        while (state == 0) {
            state = playTurn();
        }
        if (state == 1) {
            std::cout << "\n\tPlayer ";
            if (isXTurn)
                std::cout << "x";
            else
                std::cout << "o";
            std::cout << " won!\n";
        } else if (state == 2) {
            std::cout << "\n\tTie!\n";
        }
        std::cout << "\n***********Bye***********\n";
    }
};

int main() {
    int size;
    size = Sefn::readValidatedInput<int>(
        "choose a number(3 - 9) to play with: ", 0, [](int val) { return val >= 3 && val <= 9; },
        "n must be between 3 and 9. Try again!\n");
    TicTacToe game(size);
    game.runGame();
    return 0;
}