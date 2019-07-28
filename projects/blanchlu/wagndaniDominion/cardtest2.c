/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * cardtest2.c
 * Testing the shuffle function
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
        
    baseGame.deckCount[checkPlayer] = 10;
    int i = 0;
    for(i = 0; i < 10; i++){
            baseGame.deck[checkPlayer][i] = i;
    }
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    
    
    
    
    printf("\nTESTING SHUFFLE FUNCTION\n");
    
    printf("\nTesting when deck count is empty, should return negative 1\n");
    baseGame.deckCount[checkPlayer] = 0;
    nb_assert(shuffle(checkPlayer, &baseGame), -1);
    
    printf("\nTesting number of card in different positions\n");
    int diffcards = 0;
    int allValidCards = 1;
    int cardCount[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int validCounts = 1;
    
    baseGame.deckCount[checkPlayer] = 10;
    
    shuffle(checkPlayer, &testGame);
    for(i = 0; i < baseGame.deckCount[checkPlayer]; i++){
        if(baseGame.deck[checkPlayer][i] != testGame.deck[checkPlayer][i]){
            diffcards++;
        }
        if(testGame.deck[checkPlayer][i] < 0 || testGame.deck[checkPlayer][i] > 9){
            allValidCards = 0;
        }
        cardCount[testGame.deck[checkPlayer][i]]++;
        printf("in Position %d: Base %d, test %d\n", i, baseGame.deck[checkPlayer][i], testGame.deck[checkPlayer][i]);
    }
    
    for(i = 0; i < 10; i++){
        if(cardCount[i] != 1){
            validCounts = 0;
        }
    }
    
    nb_assert_test_GTE(diffcards, 3);
    printf("\nChecking all shuffled cards are same cards as input, using 1 as true, 0 as false\n");
    nb_assert(allValidCards, 1);
    
    printf("\nChecking all shuffled cards are only used 1, using 1 as true, 0 as false\n");
    nb_assert(validCounts, 1);

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

