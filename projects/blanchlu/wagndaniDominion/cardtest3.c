/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * cardtest3.c
 * Testing the endTurn function
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
void nb_assert_test_GTE(int, int);

int main(){
    
    // Variables to initialize game --START
    int checkPlayer = 0;
    
    struct gameState baseGame, testGame, checkDiscard;
        

    baseGame.whoseTurn = 0;
    baseGame.numPlayers = 2;
    baseGame.handCount[checkPlayer] = 5;
    baseGame.deckCount[checkPlayer + 1] = 5;
    baseGame.discardCount[checkPlayer] = 0;
    checkDiscard.discardCount[checkPlayer] = 5;
    
    int i = 0;
    for(i = 0; i < 5; i++){
        baseGame.hand[checkPlayer][i] = i;
        checkDiscard.discard[checkPlayer][i] = i;
    }
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    printf("\nTESTING ENDTURN FUNCTION\n");
    
    printf("Testing when current player is player position 0\n");
    endTurn(&baseGame);
    printf("Checking discard pile count of player position 0\n");
    nb_assert(baseGame.discardCount[checkPlayer], 5);
    
    printf("Checking hand count of player position 0\n");
    nb_assert(baseGame.handCount[checkPlayer], 0);
    
    printf("Checking if discard pile matches original hand\n");
    int matchCardBool = 1;
    for(i = 0; i < 5; i++){
        if(baseGame.discard[checkPlayer][i] != checkDiscard.discard[checkPlayer][i]){
            matchCardBool = 0;
        }
    }
    nb_assert(matchCardBool, 1);
    
    printf("Checking hand count of player position 1\n");
    nb_assert(baseGame.handCount[checkPlayer + 1], 5);
    
    printf("Checking whoseTurn\n");
    nb_assert(baseGame.whoseTurn, 1);
    
    printf("\nChecking when current player is last person in player count, function should change whoseTurn to 0\n");
    endTurn(&baseGame);
    printf("Checking whoseTurn\n");
    nb_assert(baseGame.whoseTurn, 0);

    
    

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

void nb_assert_test_GTE(int test, int base){
    
       printf("Expected at least %d, result was %d\n", base, test);
    if(base <= test){
        printf("TEST PASSED\n");
    }
    
    else{
        printf("TEST FAILED\n");
    }
    
    return;
}

