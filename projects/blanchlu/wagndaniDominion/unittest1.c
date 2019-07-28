/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * unittest1.c
 * Testing the refactored baron case function
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
        handPos = 0;
    
    
    initializeGame(numPlayers, kingdomSupply, randSeed, &baseGame);
    
    baseGame.hand[checkPlayer][baseGame.handCount[checkPlayer] -1] = estate;
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    // Baron Case: 
    printf("TESTING BARON CASE\n");

    printf("\nTesting With Estate Card in Hand\n");
    choice1 = 1;
    printf("Testing coin return with choice1 variable set to %d.\n", choice1);
    baronCase(choice1, &testGame, handPos, checkPlayer);
    nb_assert(testGame.coins, baseGame.coins + 4);
    //Assuming discardCard function does its job, did we make the correct inputs?
    printf("Testing # of discarded cards in players discard pile\n");
    nb_assert(testGame.discardCount[checkPlayer], baseGame.discardCount[checkPlayer] + 2);
    printf("Testing # of cards in players hand\n");
    nb_assert(testGame.handCount[checkPlayer], baseGame.handCount[checkPlayer] - 2);
    printf("Testing if estate card is second to last in discard pile\n");
    nb_assert(testGame.discard[checkPlayer][testGame.discardCount[checkPlayer] -2], estate);

    choice1 = 0;
    // Reset test case to base case for new test
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    printf("Testing coin return with choice1 variable set to %d.\n", choice1);
    baronCase(choice1, &testGame, handPos, checkPlayer);
    nb_assert(testGame.coins, baseGame.coins);
    printf("Testing # of discarded cards in players discard pile\n");
    nb_assert(testGame.discardCount[checkPlayer], baseGame.discardCount[checkPlayer] + 2);
    printf("Testing # of cards in players hand\n");
    nb_assert(testGame.handCount[checkPlayer], baseGame.handCount[checkPlayer] - 1);
    printf("Testing if card in handPos is last card in (top of) discard pile\n");
    nb_assert(testGame.discard[checkPlayer][testGame.discardCount[checkPlayer] -1], baseGame.hand[checkPlayer][0]);
    
    /* END OF TESTS WHERE PLAYER HOLDS AN ESTATE CARD */
    
    /* REPLACE ANY ESTATE CARDS IN HAND WITH SOME OTHER CARD*/
    int p;
    for(p = 0; p < testGame.handCount[checkPlayer]; p++){
        if (baseGame.hand[checkPlayer][p] == estate){
            baseGame.hand[checkPlayer][p] = mine;
        }
    }
    
    /* TESTS WHERE PLAYER DOES NOT HAVE ESTATE CARD IN HAND*/

    printf("\nTesting No Estate Card in Hand\n");
    choice1 = 1;
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    printf("Testing coin return with choice1 variable set to %d.\n", choice1);
    baronCase(choice1, &testGame, handPos, checkPlayer);
    nb_assert(testGame.coins, baseGame.coins);
    //Assuming discardCard function does its job, did we make the correct inputs?
    printf("Testing # of discarded cards in players discard pile\n");
    nb_assert(testGame.discardCount[checkPlayer], baseGame.discardCount[checkPlayer] + 2);
    printf("Testing if baron card is  last in discard pile\n");
    nb_assert(testGame.discard[checkPlayer][testGame.discardCount[checkPlayer] -1], baseGame.hand[checkPlayer][handPos]);
    printf("Testing if hand count was decremented by 1 in players hand.\n");
    nb_assert(testGame.handCount[checkPlayer], baseGame.handCount[checkPlayer] - 1);


    choice1 = 0;
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    printf("Testing coin return with choice1 variable set to %d.\n", choice1);
    baronCase(choice1, &testGame, handPos, checkPlayer);
    nb_assert(testGame.coins, baseGame.coins);
    printf("Testing # of discarded cards in players discard pile\n");
    nb_assert(testGame.discardCount[checkPlayer], baseGame.discardCount[checkPlayer] + 2);
    printf("Testing # of cards in players hand\n");
    nb_assert(testGame.handCount[checkPlayer], baseGame.handCount[checkPlayer] - 1);
    printf("Testing if card in handPos is last card in (top of) discard pile\n");
    nb_assert(testGame.discard[checkPlayer][testGame.discardCount[checkPlayer] -1], baseGame.hand[checkPlayer][0]);


    
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