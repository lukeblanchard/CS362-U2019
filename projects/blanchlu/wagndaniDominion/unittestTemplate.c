/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// STANDARD C LIBRAIRIES
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// SPECIFIC DOMINION HEADER FILES
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void nb_assert();

void main(){
    
    // Variables to initialize game --START
    int numPlayers = 2;
    int randSeed = 1000;
    
    struct gameState baseGame, testGame;
        
    int kingdomSupply[10] = {adventurer, council_room, feast, gardens, remodel, 
                                smithy, village, great_hall, steward, salvager};
    
    // Variable to pass to card functions
    int checkPlayer = 0;
    int choice1 = 0,
        choice2 = 0,
        handPos = 0;
    
    
    initializeGame(numPlayers, kingdomSupply, randSeed, &baseGame);
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    // Baron Case: 
    // int baronCase(int choice1, struct gameState *state, int handPos, int currentPlayer);

    // int minionCase(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

    // int ambassadorCase(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

    // int tributeCase(struct gameState *state, int currentPlayer, int nextPlayer);

    // int mineCase(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);
    
    return;
}

void nb_assert(){
    return;
}