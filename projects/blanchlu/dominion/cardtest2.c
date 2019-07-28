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
    int i;
    int match = 0;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int testDeck[MAX_DECK];

	printf("----------------- Testing Function: shuffle() ----------------\n");
	printf("TEST 1:\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayers, k, seed, &G); // initialize a new game
    
    // add cards to deck
    for(i = 0; i < 10; i++) {
        gainCard(k[i], &G, 1, G.whoseTurn);
    }

    // save the hand for testing
    memcpy(testDeck, G.deck[G.whoseTurn], sizeof(int)*G.deckCount[G.whoseTurn]);
    // shuffle
    shuffle(G.whoseTurn, &G);

    for(i = 0; i < G.deckCount[G.whoseTurn]; i++) {
        if(G.deck[G.whoseTurn][i] == testDeck[i]){
            match++;
        }
    }
    printf("Shuffle changes order of deck\n");
    myAssert(match != G.deckCount[G.whoseTurn]);
    printf("All tests passed!\n");

    return 0;
}
