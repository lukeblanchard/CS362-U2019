#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "minion"

void myAssert(int bool) {
	if(bool == 1) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
	}
}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m, match;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +1 buys --------------
	printf("TEST 1: +1 Action\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	myAssert(testG.numActions == G.numActions + 1);

	// ----------- TEST 2: choice1 = 1 = +2 coins --------------
	printf("\nTEST 2: choice1 = 1 = +2 coins\n");

	choice1 = 1;
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	myAssert(testG.coins == G.coins + 2);

	// ----------- TEST 3: choice2 = 1 = redraw cards --------------
	printf("\nTEST 3: choice2 = 1 = draw new cards\n");

    printf("*Draw new cards = old cards in playedCards, not trashed ");
	choice1 = 0;
	choice2 = 1;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
     
    // check to see playedCards == previous hand
    match = 1; 
    i = G.handCount[thisPlayer] - 1;
    j = 1; 
    // first card will match, then discard function moves last card to handPos, reduces handCount by one, so arrays should be in reverse order respective to each other
    if(G.hand[thisPlayer][0] != testG.playedCards[0]) 
    {
        match = 0;
    }
    while(i > 0)
	{
	    if(G.hand[thisPlayer][i] != testG.playedCards[j]) {
            match = 0;
            i = 0;
        }
        i--;
        j++;
	}
	myAssert(match == 1);
    
    printf("*New hand count is 4 ");
    myAssert(testG.handCount[thisPlayer] == 4);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
