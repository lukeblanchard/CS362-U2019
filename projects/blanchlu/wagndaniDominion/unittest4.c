/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * unittest4.c
 * Testing the refactored tribute case function
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
    int nextPlayer = checkPlayer + 1;
    
    
    initializeGame(numPlayers, kingdomSupply, randSeed, &baseGame);
    
    // Manually initialize nextPlayer hand and set last two cards of nextplayers deck to same action card
    printf("Base deck count: %d\n", baseGame.deckCount[nextPlayer]);
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 1] = embargo;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 2] = embargo;
    
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    printf("\nTESTING TRIBUTE CASE\n");
    
    printf("/nTesting two action cards revealed by next player that are identical yields +2 actions\n");
    tributeCase(&testGame, checkPlayer, nextPlayer);
    nb_assert(testGame.numActions, baseGame.numActions +2);
    
    printf("\nTesting two cards were added to nextPlayers DiscardPile\n");
    nb_assert(testGame.discardCount[nextPlayer], baseGame.discardCount[nextPlayer] + 2);
    
    printf("\nTesting two cards were removed from nextPlayers deck\n");
    nb_assert(testGame.deckCount[nextPlayer], baseGame.deckCount[nextPlayer] - 2);

    
    printf("\nTesting when next player only has 1 card available\n");
    
    // Manually initialize nextPlayer hand and set last two cards of nextplayers deck to same action card
    baseGame.deckCount[nextPlayer] = 1;
    
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 1] = embargo;

    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    printf("\nTesting single action cards revealed by next player yields +2 actions\n");
    tributeCase(&testGame, checkPlayer, nextPlayer);
    nb_assert(testGame.numActions, baseGame.numActions +2);
    
    printf("\nTesting single card was added to nextPlayers Discard Pile\n");
    nb_assert(testGame.discardCount[nextPlayer], baseGame.discardCount[nextPlayer] + 1);
    
    printf("\nTesting single card was removed from nextPlayers deck\n");
    nb_assert(testGame.deckCount[nextPlayer], baseGame.deckCount[nextPlayer] - 1);
    
    
    printf("\nTesting when next player only has 1 card in deck but multiple in discard all same cards\n");
    
    // Manually initialize nextPlayer deck and set last card of nextplayers deck to action card
    baseGame.deckCount[nextPlayer] = 1;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 1] = embargo;
    
    baseGame.discardCount[nextPlayer] = 5;
    int i;
    for(i = 0; i < baseGame.discardCount[nextPlayer]; i++){
        baseGame.discard[nextPlayer][i] = embargo;
    }

    memcpy(&testGame, &baseGame, sizeof(struct gameState));
   tributeCase(&testGame, checkPlayer, nextPlayer);
   
   printf("\nTesting single action cards revealed by next player yields +2 actions\n");
    nb_assert(testGame.numActions, baseGame.numActions +2);
    
    printf("\nTesting two cards was added to nextPlayers Discard Pile AFTER discard pile was shuffled back into deck\n");
    nb_assert(testGame.discardCount[nextPlayer], 1);
    
    printf("\nTesting discard pile was added to deck and then single card from deck were discarded\n");
    nb_assert(testGame.deckCount[nextPlayer], baseGame.deckCount[nextPlayer] + baseGame.discardCount[nextPlayer] - 1);
    
    
    printf("\nTesting identical treasure cards revealed by next player only yield +2\n");
    // Manually initialize nextPlayer hand and set last two cards of nextplayers deck to same action card
    baseGame.deckCount[nextPlayer] = 10;
    baseGame.discardCount[nextPlayer] = 0;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 1] = copper;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 2] = copper;
     memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    tributeCase(&testGame, checkPlayer, nextPlayer);
    nb_assert(testGame.coins, baseGame.coins +2);
    
    
    printf("\nTesting different treasure cards revealed by next player yield +4 coins\n");
    // Manually initialize nextPlayer hand and set last two cards of nextplayers deck to same action card
    baseGame.deckCount[nextPlayer] = 10;
    baseGame.discardCount[nextPlayer] = 0;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 1] = copper;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 2] = gold;
    memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    tributeCase(&testGame, checkPlayer, nextPlayer);
    nb_assert(testGame.coins, baseGame.coins +4);
    printf("\nTesting if 'if' statements did not pick up treasure, or victory, defaulted to action by checking numAction variable\n");
    nb_assert(testGame.numActions, baseGame.numActions);
    
    printf("\nTesting different victory cards revealed by next player yield +4 cards\n");
    // Manually initialize nextPlayer hand and set last two cards of nextplayers deck to same action card
    baseGame.deckCount[nextPlayer] = 10;
    baseGame.discardCount[nextPlayer] = 0;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 1] = estate;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 2] = province;
     memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    tributeCase(&testGame, checkPlayer, nextPlayer);
    nb_assert(testGame.deckCount[nextPlayer], baseGame.deckCount[nextPlayer] +4);
    
    printf("\nTesting different action cards revealed by next player yield +4 actions\n");
    // Manually initialize nextPlayer hand and set last two cards of nextplayers deck to same action card
    baseGame.deckCount[nextPlayer] = 10;
    baseGame.discardCount[nextPlayer] = 0;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 1] = smithy;
    baseGame.deck[nextPlayer][baseGame.deckCount[nextPlayer] - 2] = steward;
     memcpy(&testGame, &baseGame, sizeof(struct gameState));
    
    tributeCase(&testGame, checkPlayer, nextPlayer);
    nb_assert(testGame.numActions, baseGame.numActions + 4);
    
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

