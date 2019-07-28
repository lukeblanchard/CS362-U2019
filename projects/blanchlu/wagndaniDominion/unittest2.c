/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * unittest2.c
 * Testing the refactored minion case function
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

void nb_assert(int, int);

int main(){
    
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
    
    printf("\nTESTING MINION CASE\n");
    choice1 = 1;
    choice2 = 0;
    minionCase(choice1, choice2, &testGame, handPos, checkPlayer);
    printf("\nTesting action count incrementation\n");
    nb_assert(testGame.numActions, baseGame.numActions +1);
    printf("\nChecking card discarded properly by checking discardCount\n");
    nb_assert(testGame.discardCount[checkPlayer], baseGame.discardCount[checkPlayer] +1);
    
    printf("\nTesting choice1 == %d.  Check coin count.\n", choice1);
    nb_assert(testGame.coins, baseGame.coins +2);
    
    printf("\nTesting choice2 == 1 \n");
    choice1 = 0;
    choice2 = 1;
    printf("Verifying Discard of current player\n");
    // Reset testGame to match baseGame
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    minionCase(choice1, choice2, &testGame, handPos, checkPlayer);
    nb_assert(testGame.discardCount[checkPlayer], baseGame.discardCount[checkPlayer] + baseGame.handCount[checkPlayer]);
    
    printf("\nTesting if other player only has 1 card in hand.  Player shouldn't discard or draw.  HandCount should not change.\n");
    // Reset testGame to match baseGame
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    testGame.handCount[checkPlayer + 1] = 1;
    minionCase(choice1, choice2, &testGame, handPos, checkPlayer);
    nb_assert(testGame.handCount[checkPlayer +1 ], 1);
    
    printf("\nTesting that other player did not discard cards by checking discard pile count\n");
    nb_assert(testGame.discardCount[checkPlayer + 1], 0);
    
    printf("\nTesting if other player 5 card in hand.  Player should discard and draw.  Checking hand count of other player\n");
    // Reset testGame to match baseGame
    int i;
    for(i = 0; i < 5; i++){
        baseGame.hand[checkPlayer +1][i] = estate;
        baseGame.handCount[checkPlayer +1]++;
    }
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    minionCase(choice1, choice2, &testGame, handPos, checkPlayer);
    nb_assert(testGame.handCount[checkPlayer + 1], 4);
    printf("Checking if discardCount of other player is equivalent to having discarded current hand\n");
    nb_assert(testGame.discardCount[checkPlayer +1], baseGame.discardCount[checkPlayer +1] + baseGame.handCount[checkPlayer +1]); 
    
    printf("\nTesting if other player had more than 5 cards in hand.  Player should discard and draw.  Checking hand count of other player\n");

    baseGame.handCount[checkPlayer +1] = 6;
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    minionCase(choice1, choice2, &testGame, handPos, checkPlayer);
    nb_assert(testGame.handCount[checkPlayer + 1], 4);
    printf("Checking if discardCount of other player is equivalent to having discarded current hand\n");
    nb_assert(testGame.discardCount[checkPlayer +1], baseGame.discardCount[checkPlayer +1] + baseGame.handCount[checkPlayer +1]); 
    
    return 0;
}

void nb_assert(int test, int base){
    
       printf("Expected %d, result was %d\n", base, test);
    if(base == test){
        printf("TEST PASSED\n");
    }
    
    else{
        printf("TEST FAILED\n");
    }
    
    return;
    
}