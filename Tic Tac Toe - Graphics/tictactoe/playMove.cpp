//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//
// resolved_issue: able to compile using make and run .exe , BUT, exerciser/submit giving weird output 
// resolved_MAJOR ISSUE: must retun IF move invalid -- coz turn is still changing if invalid key is pressed!!!
// issue : starting with O

#include "tictactoe.h"
#include "gameState.h"
#include <iostream>
using namespace std;

void playMove(gameState& game_state) {

    // don't proceed if gameOver is true
    if (game_state.get_gameOver() == true)
        return;

    // checking if move is valid - return if move is invalid
    int playRow = game_state.get_clickedRow();
    int playColumn = game_state.get_clickedColumn();

    if (game_state.get_gameBoard(playRow, playColumn) == Empty
            && playRow < 3 && playRow >= 0 && playColumn < 3 && playColumn >= 0) {
        game_state.set_moveValid(true);
    } else {
        game_state.set_moveValid(false);
        return;
    }

    // setting turn
    int turn = 0;
    if (game_state.get_turn() == false) {//first player has to be X
        game_state.set_turn(true);
        turn = O;
    } else {
        game_state.set_turn(false);
        turn = X;
    }

    // at this point, turn is valid, place the turn    
    if (game_state.get_moveValid() == true)
        game_state.set_gameBoard(playRow, playColumn, turn);

    // checking for game over
    // checking rows and columns
    for (int i = 0; i < 3 && game_state.get_gameOver() == false; i++) {//NOTE: i, and j are just counters used to run through the 3x3 array

        int rowChecker = 0;
        int colChecker = 0;

        for (int j = 0; j < 3 && game_state.get_gameOver() == false; j++) {
            if (game_state.get_gameBoard(i, j) == turn)
                rowChecker += turn;
        }

        for (int j = 0; j < 3 && game_state.get_gameOver() == false; j++) {
            if (game_state.get_gameBoard(j, i) == turn)
                colChecker += turn;
        }

        if (rowChecker == 3 * turn) {
            game_state.set_gameOver(true);
            game_state.set_winCode(i + 1);
        }

        if (colChecker == 3 * turn) {
            game_state.set_gameOver(true);
            game_state.set_winCode(i + 4);
        }
    }

    // checking diagnals
    if (game_state.get_gameBoard(0, 0) == turn && game_state.get_gameBoard(1, 1) == turn
            && game_state.get_gameBoard(2, 2) == turn) {
        game_state.set_gameOver(true);
        game_state.set_winCode(7);
    }

    if (game_state.get_gameBoard(0, 2) == turn && game_state.get_gameBoard(1, 1) == turn
            && game_state.get_gameBoard(2, 0) == turn) {
        game_state.set_gameOver(true);
        game_state.set_winCode(8);
    }

    // since all cases tested and no winner, it could be a draw
    // checking if draw
    int emptyCounter = 0;

    for (int i = 0; i < 3; i++) { //NOTE: i, and j are just counters used to run through the 3x3 array
        for (int j = 0; j < 3; j++) {
            if (game_state.get_gameBoard(i, j) == Empty) // The moment it hits an empty, it means game is not over 
                emptyCounter++;
        }
    }

    if (emptyCounter == 0 && game_state.get_gameOver() == false) {// game_state.get_gameBoard(i,j) is full, no winner - DRAW
        game_state.set_gameOver(true);
        game_state.set_winCode(0);
    }
}
