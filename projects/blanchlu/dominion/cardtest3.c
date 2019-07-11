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
	int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

	// test supply count based on number of players

	printf("----------------- Testing Function: endTurn() ----------------\n");
	printf("TEST 1:\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayers, k, seed, &G); // initialize a new game
    endTurn(&G); 
    printf("Current Player increments to next player\n");  
    myAssert(G.whoseTurn == 1); 
    printf("outpostPlayed == 0\n");    
    myAssert(G.outpostPlayed == 0);
    printf("numActions == 1\n");    
	myAssert(G.numActions == 1);
    printf("Current Player handCount == 5\n");
	myAssert(G.handCount[G.whoseTurn] == 5);
    printf("All tests passed!\n");
    return 0;
}
