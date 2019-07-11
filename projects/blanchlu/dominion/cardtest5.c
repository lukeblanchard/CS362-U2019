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
    int count, deckCounter, currentPlayer, drawnCard, cardInHand;
	int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

	// test supply count based on number of players

	printf("----------------- Testing Function: drawCard() ----------------\n");
	printf("TEST 1:\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayers, k, seed, &G); // initialize a new game
    currentPlayer = G.whoseTurn; 
     
	deckCounter = G.deckCount[currentPlayer];//Create holder for the deck count
    drawnCard = G.deck[currentPlayer][deckCounter - 1];
    
    drawCard(currentPlayer, &G);
	count = G.handCount[currentPlayer];//Get current hand count for player
    cardInHand = G.hand[currentPlayer][count - 1];
    printf("Card at top of deck transfers to hand\n"); 
    myAssert(cardInHand == drawnCard);

    return 0;
}
