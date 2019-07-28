/*
 * CS362 Software Engineering II
 * Summer 2019
 * 
 * Daniel S Wagner 
 * wagndani@oregonstate.edu
 * 
 * Assignment 3
 * 
 * cardtest1.c
 * Testing the initializeGame function
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
    int randSeed = 1000;
    
    struct gameState baseGame;
        
    int kingdomSupply[10] = {adventurer, council_room, feast, gardens, remodel, 
                                smithy, village, great_hall, steward, adventurer};
    
    int k = 0;
    
    printf("\nTESTING INITIALIZEGAME FUNCTION\n");
    
    printf("\nTesting return value upon Invalid player inputs, greater than MAX_PLAYERS\n");
    nb_assert(initializeGame(MAX_PLAYERS + 1, kingdomSupply, randSeed, &baseGame), -1);
    printf("\nTesting return value upon Invalid player inputs, less than 2\n");
    nb_assert(initializeGame(1, kingdomSupply, randSeed, &baseGame), -1);
    
    printf("\nTesting return value upon duplicate kingdom cards inputs\n");
    nb_assert(initializeGame(1, kingdomSupply, randSeed, &baseGame), -1);
    
    kingdomSupply[9] = embargo;
    
    printf("\nTesting state results when number of players is 2\n");
    initializeGame(2, kingdomSupply, randSeed, &baseGame);
    printf("Checking number of victory cards when number of players is 2\n");
    nb_assert(baseGame.supplyCount[estate] + baseGame.supplyCount[duchy] + baseGame.supplyCount[province], 8 * 3);
    printf("Checking number of curse cards when number of players is 2\n");
    nb_assert(baseGame.supplyCount[curse], 10);
    printf("Checking number of copper cards when number of player is 2\n");
    nb_assert(baseGame.supplyCount[copper], 60 - (7*2));
    
    printf("\nTesting KingdomSupply Counts when number of players is 2\n");
    
    for(k = 0; k < 10; k++){
        if(kingdomSupply[k] == great_hall || kingdomSupply[k] == gardens){
            nb_assert(baseGame.supplyCount[k], 8);
        }
        else{
            nb_assert(baseGame.supplyCount[k], 10);
        }
    }
    
    printf("\nTesting state results when number of players is 5\n");
    initializeGame(5, kingdomSupply, randSeed, &baseGame);
    printf("Checking number of victory cards when number of players is 5\n");
    nb_assert(baseGame.supplyCount[estate] + baseGame.supplyCount[duchy] + baseGame.supplyCount[province], 12 * 3);
    printf("Checking number of curse cards when number of players is 5\n");
    nb_assert(baseGame.supplyCount[curse], 30);
    printf("Checking number of copper cards when number of player is 5\n");
    nb_assert(baseGame.supplyCount[copper], 60 - (7*5));
    
    printf("\nTesting KingdomSupply Counts when number of players is 5\n");
    for(k = 0; k < 10; k++){
        if(kingdomSupply[k] == great_hall || kingdomSupply[k] == gardens){
            nb_assert(baseGame.supplyCount[k], 12);
        }
        else{
            nb_assert(baseGame.supplyCount[k], 10);
        }
    };
    
    printf("\nTesting cards in players initial deck\n");
    printf("Each player should have 3 estate cards\n");
    int player_estates = 0;
    int player_coppers = 0;
    int i = 0;
    int numberPlayers = 5;
    
    for(i = 0; i < numberPlayers; i++){
        if(i != baseGame.whoseTurn){
            for(k = 0; k < baseGame.deckCount[i]; k++){
                if(baseGame.deck[i][k] == estate){
                    player_estates++;
                }
                if(baseGame.deck[i][k] == copper){
                    player_coppers++;
                }
            }
            printf("Testing number of estates in player %d deck\n", i);
            nb_assert(player_estates, 3);
            printf("Testing number of coppers in player %d deck\n", i);
            nb_assert(player_coppers, 7);
        }
    }
    

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

