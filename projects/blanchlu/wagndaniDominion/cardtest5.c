/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * cardtest5.c
 * Testing the drawCard function
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
    
    struct gameState baseGame, testGame;
        
    baseGame.handCount[checkPlayer] = 5;
    int i = 0;
    for(i = 0; i < 5; i++){
            baseGame.hand[checkPlayer][i] = estate;
    }
    

    
    
    printf("\nTESTING DRAWCARD FUNCTION\n");
    
    printf("Testing when player only has card in hand.  No cards in deck, or discard, no cards to draw.  Draw Card should return -1\n");
    baseGame.deckCount[checkPlayer] = 0;
    baseGame.discardCount[checkPlayer] = 0;
    nb_assert(drawCard(0, &baseGame), -1);
    
    
    printf("\nTesting single card in discard pile, zero cards in draw pile.\n"
            "Single card in discard is province.  All in hand are estate\n");
    baseGame.discardCount[checkPlayer] = 1;
    baseGame.discard[checkPlayer][baseGame.discardCount[checkPlayer] - 1] = province;
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    drawCard(0, &baseGame);
    
    printf("Discard count should be zero\n");
    nb_assert(baseGame.discardCount[checkPlayer], 0);
    
    printf("Deck count should be zero\n");
    nb_assert(baseGame.deckCount[checkPlayer], 0);
    
    printf("Hand count should be 6\n");
    nb_assert(baseGame.handCount[checkPlayer], 6);
    
    printf("Last card in hand should be province\n");
    nb_assert(baseGame.hand[checkPlayer][baseGame.handCount[checkPlayer] - 1], province);
    
    printf("\nTesting single card in deck pile\n"
    "Single card in deck is province.  All in hand are estate\n");
    baseGame.deckCount[checkPlayer] = 1;
    baseGame.discardCount[checkPlayer] = 0;
    baseGame.deck[checkPlayer][baseGame.deckCount[checkPlayer] - 1] = province;
    
    memcpy(&baseGame, &testGame, sizeof(struct gameState));
    drawCard(0, &baseGame);
    
    printf("Discard count should be zero\n");
    nb_assert(baseGame.discardCount[checkPlayer], 0);
    
    printf("Deck count should be zero\n");
    nb_assert(baseGame.deckCount[checkPlayer], 0);
    
    printf("Hand count should be 6\n");
    nb_assert(baseGame.handCount[checkPlayer], 6);
    
    printf("Last card in hand should be province\n");
    nb_assert(baseGame.hand[checkPlayer][baseGame.handCount[checkPlayer] - 1], province);
    
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

