/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * unittest5.c
 * Testing the refactored mine case function
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
    int choice1 = 1,
        handPos = 0;
    
    
    initializeGame(numPlayers, kingdomSupply, randSeed, &baseGame);
    
    baseGame.hand[checkPlayer][choice1] = duchy;
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    printf("\nTESTING MINE CASE\n");
    
    printf("\nTesting invalid choice1 card less than copper\n");
    nb_assert(mineCase(choice1, gold, &testGame, handPos, checkPlayer), -1);
    
    baseGame.hand[checkPlayer][choice1] = minion;
    printf("\nTesting invalid choice1 card greater than gold \n");
    nb_assert(mineCase(choice1, gold, &testGame, handPos, checkPlayer), -1);
    
    baseGame.hand[checkPlayer][choice1] = copper;
    printf("\nTesting valid choice1 card but more than 3 coins less than gold \n");
    nb_assert(mineCase(choice1, gold, &testGame, handPos, checkPlayer), -1);
    
    baseGame.hand[checkPlayer][choice1] = -1;
    printf("\nTesting invalid choice1 card, less than curse \n");
    nb_assert(mineCase(choice1, gold, &testGame, handPos, checkPlayer), -1);
    
    baseGame.hand[checkPlayer][choice1] = 30;
    printf("\nTesting invalid choice1 card, greater than treasure_map \n");
    nb_assert(mineCase(choice1, gold, &testGame, handPos, checkPlayer), -1);
    
    baseGame.hand[checkPlayer][choice1] = copper;
    printf("\nTesting valid copper for silver trade return result");
    nb_assert(mineCase(choice1, silver, &testGame, handPos, checkPlayer), 0);
    
    printf("\nTesting gainCard sent to hand\n");
    nb_assert(testGame.hand[checkPlayer][testGame.handCount[checkPlayer] -1], silver);
    
    printf("\nTesting mine card was discarded at end of function\n");
    nb_assert(testGame.discard[checkPlayer][testGame.discardCount[checkPlayer] -2], baseGame.hand[checkPlayer][handPos]);
    
    printf("\nTesting treasure card choice1 was discarded at end of function\n");
    nb_assert(testGame.discard[checkPlayer][testGame.discardCount[checkPlayer] -1], baseGame.hand[checkPlayer][choice1]);
    
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

