# Tic Tac Toe

This is a simple implementation of tic tac toe written in C++ that can be played in the terminal. It can be played in 2 different modes, singleplayer where the player is competeing against an AI, and multiplayer where the player can play against a friend on the same terminal.

## How To Install

First you'll want to dowload the `ttt-main.cpp` game cfile and the open the terminal navigate to the folder that contains it

The you want to compile the file using the command `g++ -o tic-tac-toe ttt-main.cpp`

Then just run `./tic-tac-toe` in the terminal and the game will begin playing

Enjoy!

## AI Opponent

In singleplayer mode, the player is competeing against an AI player. The AI player uses the minimax algorithm to decide what the best move is going to be based on the game state and then makes that move. It will either pick the fastest number of moves to ensure its victory, or it will use the most moves it can to delay the player from winning.

