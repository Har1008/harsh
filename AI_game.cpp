#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 3
#define PLAYER1 'X'
#define PLAYER2 'O'
#define EMPTY ' '

class GameState {
public:
    char board[SIZE][SIZE];

    GameState() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = EMPTY;
            }
        }
    }

    void displayBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                std::cout << " " << board[i][j] << " ";
                if (j < SIZE - 1) std::cout << "|";
            }
            std::cout << "\n";
            if (i < SIZE - 1) std::cout << "---|---|---\n";
        }
    }

    bool isBoardFull() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    return false;
                }
            }
        }
        return true;
    }

    bool checkWin(char player) {
        for (int i = 0; i < SIZE; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
                return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;
        return false;
    }

    void playerMove(char player) {
        int row, col;
        do {
            std::cout << "Player " << player << ", enter your move (row and column): ";
            std::cin >> row >> col;
        } while (row < 1 || row > SIZE || col < 1 || col > SIZE || board[row - 1][col - 1] != EMPTY);
        board[row - 1][col - 1] = player;
    }

    void aiMove(char player) {
        int row, col;
        do {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (board[row][col] != EMPTY);
        board[row][col] = player;
    }

    void gameLoop() {
        char currentPlayer = PLAYER1;
        while (true) {
            displayBoard();
            if (currentPlayer == PLAYER1) {
                playerMove(currentPlayer);
            } else {
                aiMove(currentPlayer);
            }
            if (checkWin(currentPlayer)) {
                displayBoard();
                std::cout << "Player " << currentPlayer << " wins!\n";
                break;
            }
            if (isBoardFull()) {
                displayBoard();
                std::cout << "The game is a draw!\n";
                break;
            }
            currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
        }
    }
};

int main() {
    srand(time(NULL));
    GameState state;
    state.gameLoop();
    return 0;
}
