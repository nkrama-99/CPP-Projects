//
//  gameState.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.

#include "tictactoe.h"
#include "gameState.h"

/*
    * NOTE:
    * when "get_variable" is called in playMove, the value of the variable is returned
    * when "set_variable" is called in playMove, the value of the variable is changed/set
*/

int gameState::get_clickedColumn() {
    return clickedColumn;
}

int gameState::get_clickedRow() {
    return clickedRow;
}

void gameState::set_clickedColumn(int value) {
    if (value < boardSize && value >= 0)
        clickedColumn = value;
    return;
}

void gameState::set_clickedRow(int value) {
    if (value < boardSize && value >= 0)
        clickedRow = value;
    return;
}

bool gameState::get_moveValid() {
    return moveValid;
}

void gameState::set_moveValid(bool value) {
    moveValid = value;
    return;
}

bool gameState::get_gameOver() {
    return gameOver;
}

void gameState::set_gameOver(bool value) {
    gameOver = value;
    return;
}

int gameState::get_winCode() {
    return winCode;
}

void gameState::set_winCode(int value) {
    winCode = value;
    return;
}

bool gameState::get_turn() {
    return turn;
}

void gameState::set_turn(bool value) {
    turn = value;
    return;
}

int gameState::get_gameBoard(int row, int col) {
    return gameBoard[row][col];
}

void gameState::set_gameBoard(int row, int col, int value) {
    gameBoard[row][col] = value;
    return;
}



