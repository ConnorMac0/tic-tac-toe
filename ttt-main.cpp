#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;
char bot = 'O';
char player = 'X';
int row, col;

void makeBoard(char board[3][3]) {
    cout << "    0   1   2\n";
    cout << "  -------------\n";
    for (int i = 0; i < 3; i++){
        cout << i << " | ";
        for (int j = 0; j < 3; j++){
            cout << board[i][j] << " | ";
        }
        cout << "\n  -------------\n";
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

bool movesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return true;
        }
    }
    return false;
}

int eval(char board[3][3]){
    for (int i = 0; i < 3; i++){
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            if (board[i][0] == bot)
                return 10;
            else   
                return -10;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == bot)
                return 10;
            else   
                return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        if (board[0][0] == bot)
            return 10;
        else
            return -10;
    }
    if (board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
        if (board[2][0] == bot)
            return 10;
        else
            return -10;
    }

    return 0;
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = eval(board);

    if (score == 10)
        return score - depth;
    
    if (score == -10)
        return score + depth;
    
    if (!movesLeft(board))
        return 0;

    if (isMax) {
        int opt = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' '){
                    board[i][j] = bot;

                    opt = max(opt, minimax(board, depth+1, !isMax));

                    board[i][j] = ' ';
                }
                    
            }
        }
        return opt;
    
    } else {
        int opt = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' '){
                    board[i][j] = player;

                    opt = min(opt, minimax(board, depth+1, !isMax));

                    board[i][j] = ' ';
                }
                    
            }
        }
        return opt;
    }
}

void botMove(char board[3][3]){
    int opt = -1000;
    int optRow, optCol;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = bot;

                int val = minimax(board, 0, false);

                board[i][j] = ' ';

                if (val > opt){
                    optRow = i;
                    optCol = j;
                    opt = val;
                }
            }
        }
    }
    board[optRow][optCol] = bot;
}

bool checkState(char board[3][3], bool mode) {
    if (!mode){
        if(checkWin(board, player)){
            makeBoard(board);
            cout << "####################\n";
            cout << "##                ##\n";
            cout << "##    You Win!    ##\n";
            cout << "##                ##\n";
            cout << "####################\n";
            return false;
        }

        if(checkWin(board, bot)){
            makeBoard(board);
            cout << "#####################\n";
            cout << "##                 ##\n";
            cout << "##    You Lose!    ##\n";
            cout << "##                 ##\n";
            cout << "#####################\n";
            return false;
        }
    } else {
        if(checkWin(board, player)){
            makeBoard(board);
            cout << "####################\n";
            cout << "##                ##\n";
            cout << "## Player " << player << " Wins! ##\n";
            cout << "##                ##\n";
            cout << "####################\n";
            return false;
        }
    }

    if (!checkWin(board, 'X') && !checkWin(board, 'O') && !movesLeft(board)){
        makeBoard(board);
        cout << "####################\n";
        cout << "##                ##\n";
        cout << "##     Draw!      ##\n";
        cout << "##                ##\n";
        cout << "####################\n";
        return false;
    }

    return true;
}

void singlePlayer(char board[3][3]) {
    srand(time(0));
    int playerTurn = rand() % 2;

    while(checkState(board, 0)) {
        if (!playerTurn){
            botMove(board);
            playerTurn = !playerTurn;
        } else {
            makeBoard(board);

            while (true){
                cout << "Player " << player;
                cout << ", enter row (0-2) and col (0-2): ";
                if (cin >> row && cin >> col){
                    if (board[row][col] != ' ' || row > 2 || row < 0 || col > 2 || col < 0)
                        cout << "Invalid move, please try again. \n";
                    else
                        break;
                } else{
                    cout << "Invalid move, please try again. \n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            board[row][col] = player;
            playerTurn = !playerTurn;
        }
    }
}

void multiPlayer(char board[3][3]) {

    while(checkState(board, 1)){

        makeBoard(board);

        while (true){
            cout << "Player " << player;
            cout << ", enter row (0-2) and col (0-2): ";
            if (cin >> row && cin >> col){
                if (board[row][col] != ' ' || row > 2 || row < 0 || col > 2 || col < 0)
                    cout << "Invalid move, please try again. \n";
                else
                    break;
            } else {
                cout << "Invalid move, please try again. \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        board[row][col] = player;

        player = (player == 'X') ? 'O' : 'X';
    }
}

int main() {
    int mode;
    char board[3][3] = { {' ',' ',' '}, 
                         {' ',' ',' '}, 
                         {' ',' ',' '} };
    
    while (true) {
        cout << "Welcome!, Would you like to play singleplayer (0) or multiplayer (1): ";
        if (cin >> mode) {
            if (mode != 0 && mode != 1)
                cout << "Please select 0 or 1 to choose your game mode. \n";
            else
                break;
        } else {
            cout << "Please select 0 or 1 to choose your game mode. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (mode)
        multiPlayer(board);
    else
        singlePlayer(board);

    return 0;
}