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
    int score1, score2;
	int numPlayers = 2;
    int players[MAX_PLAYERS];
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

	// test supply count based on number of players

	printf("----------------- Testing Function: getWinners() ----------------\n");
	printf("TEST 1:\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayers, k, seed, &G); // initialize a new game

    printf("getWinners determines player with higher score\n");
    getWinners(players, &G);   

    score1 = scoreFor(0, &G);
    score2 = scoreFor(1, &G);

    if(score1 > score2) {
        myAssert(players[0] == 1);
    }
    else if(score2 > score1) {
        myAssert(players[1] == 1);
    }
    else {
        myAssert(players[0] == 1 && players[1] == 1);
    }

    return 0;
}
