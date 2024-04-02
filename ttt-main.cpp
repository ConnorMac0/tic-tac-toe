#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

void makeBoard(char board[3][3]) {
    cout << "--------------\n";
    for (int i = 0; i < 3; i++){
        cout << "| ";
        for (int j = 0; j < 3; j++){
            cout << board[i][j] << " | ";
        }
        cout << "\n--------------\n";
    }
}

bool checkWin(char board[3][3], char player){
    for (int i = 0; i < 3; i++){
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;
    if (board[2][0] == player && board[1][1] == player && board[0][2] == player)
            return true;
    return false;
}

int main() {
    char board[3][3] = { {' ',' ',' '}, 
                         {' ',' ',' '}, 
                         {' ',' ',' '} };
    char player = 'X';
    int row, col;

    cout << "Tic-Tac-Toe!!\n";
    for (int i = 0; i < 9; i++){

        makeBoard(board);

        while (true){
            cout << "Player " << player;
            cout << ", enter row (0-2) and col (0-2): ";
            cin >> row >> col;

            if (board[row][col] != ' ' || row > 2 || row < 0 || col > 2 || col < 0)
                cout << "Invalid move, please try again. \n";
            else
                break;
        }
        board[row][col] = player;

        if(checkWin(board, player)){
            makeBoard(board);
            cout << "####################\n";
            cout << "##                ##\n";
            cout << "## Player " << player << " Wins! ##\n";
            cout << "##                ##\n";
            cout << "####################\n";
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    if (!checkWin(board, 'X') && !checkWin(board, 'O')){
        makeBoard(board);
        cout << "####################\n";
        cout << "##                ##\n";
        cout << "##     Draw!      ##\n";
        cout << "##                ##\n";
        cout << "####################\n";
    }

    return 0;
}