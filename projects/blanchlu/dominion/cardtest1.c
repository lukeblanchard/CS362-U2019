#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void myAssert(int bool) {
	if(bool == 1) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
	}
}

int main() {
    int seed = 1000;
	int maxPlayers = 4;
    int p;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

	// test supply count based on number of players

	printf("----------------- Testing Function: initializeGame() ----------------\n");
	printf("TEST 1:\n");
	for (p = 2; p <= maxPlayers; p++) {
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(p, k, seed, &G); // initialize a new game
		switch(p){
			case 2:
				printf("Number of Players = 2 => supplyCount[curse] = 10\n");
				myAssert(G.supplyCount[curse] == 10);
				break;	
			case 3:
				printf("Number of Players = 3 => supplyCount[curse] = 20\n");
				myAssert(G.supplyCount[curse] == 20);
				break;	
			case 4:
				printf("Number of Players = 4 => supplyCount[curse] = 30\n");
				myAssert(G.supplyCount[curse] == 30);
				break;	
		}
	}
	printf("\nTEST 2:\n");
    printf("Current Player handCount == 5\n");  
    // reset game 
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    // set number of players to 2
    p = 2;
	initializeGame(p, k, seed, &G); // initialize a new game
    myAssert(G.handCount[G.whoseTurn] == 5);

	printf("\nTEST 3:\n");
    printf("Next Player handCount == 0\n");  
    myAssert(G.handCount[G.whoseTurn + 1] == 0);

    printf("All tests passed!\n");

    return 0;
}
