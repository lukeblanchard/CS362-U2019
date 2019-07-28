/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * unittest3.c
 * Testing the refactored ambassador case function
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
    
    //Manually set cards in players hand
    int i = 0;
    for(i = 0; i < baseGame.handCount[checkPlayer]; i++){
        baseGame.hand[checkPlayer][i] = estate;
    }
    
    // Reset last two card to some other card to count number of allowable cards
    baseGame.hand[checkPlayer][baseGame.handCount[checkPlayer] - 1] = embargo;
    baseGame.hand[checkPlayer][baseGame.handCount[checkPlayer] - 2] = embargo;
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    printf("TESTING AMBASSADOR CASE\n");
    
    printf("\nTesting invalid choice2 input of -1 by checking function return value\n");
    choice2 = -1;
    nb_assert(ambassadorCase(choice1, choice2, &testGame, handPos, checkPlayer), -1);
    
    printf("\nTesting invalid choice2 input of 3 by checking function return value\n");
    choice2 = 3;
    nb_assert(ambassadorCase(choice1, choice2, &testGame, handPos, checkPlayer), -1);
    
    printf("\nTesting invalid choice1 input equal to handPosition of ambassador card by checking function return value\n");
    choice2 = 0;
    choice1 = handPos;
    nb_assert(ambassadorCase(choice1, choice2, &testGame, handPos, checkPlayer), -1);
    
    printf("\nTesting invalid choice2 input of greater than count of choice1 cards by checking function return value\n");
    choice2 = 2;
    choice1 = baseGame.handCount[checkPlayer] -1;
    nb_assert(ambassadorCase(choice1, choice2, &testGame, handPos, checkPlayer), -1);
    
    printf("\nTesting valid choice2 input of less than count of choice1 cards by checking function return value\n");
    choice2 = 1;
    choice1 = baseGame.handCount[checkPlayer] -1;
    nb_assert(ambassadorCase(choice1, choice2, &testGame, handPos, checkPlayer), 0);
    
    printf("\nCheck requested number of cards were sent back to supply by checking supply count of choice1 card\n");
    nb_assert(supplyCount(choice1, &testGame), supplyCount(choice1, &baseGame) + choice2);
    
    printf("\nTesting that choice1 was added to next player by checking if total count of choice1 is greater in testGame for other player\n");
    int nextPlayerChoice1Count_Base = 0;
    
    for(i = 0; i < baseGame.deckCount[checkPlayer + 1]; i++){
        if(baseGame.deck[checkPlayer + 1][i] == choice1){
            nextPlayerChoice1Count_Base++;
        }
    }
    
    for(i = 0; i < baseGame.discardCount[checkPlayer + 1]; i++){
        if(baseGame.discard[checkPlayer + 1][i] == choice1){
            nextPlayerChoice1Count_Base++;
        }
    }
    
    for(i = 0; i < baseGame.handCount[checkPlayer + 1]; i++){
        if(baseGame.hand[checkPlayer + 1][i] == choice1){
            nextPlayerChoice1Count_Base++;
        }
    }
    
    int nextPlayerChoice1Count_Test = 0;
    
    for(i = 0; i < testGame.deckCount[checkPlayer + 1]; i++){
        if(testGame.deck[checkPlayer + 1][i] == choice1){
            nextPlayerChoice1Count_Test++;
        }
    }
    
    for(i = 0; i < testGame.discardCount[checkPlayer + 1]; i++){
        if(testGame.discard[checkPlayer + 1][i] == choice1){
            nextPlayerChoice1Count_Test++;
        }
    }
    
    for(i = 0; i < testGame.handCount[checkPlayer + 1]; i++){
        if(testGame.hand[checkPlayer + 1][i] == choice1){
            nextPlayerChoice1Count_Test++;
        }
    }
    
    nb_assert(nextPlayerChoice1Count_Test, nextPlayerChoice1Count_Base + 1);
    
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