#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "baron"

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

    int i, j, m;
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
	printf("TEST 1: +1 buys\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	myAssert(testG.numBuys == G.numBuys + 1);

	// ----------- TEST 2: choice1 = 1 = discard estate --------------
	printf("\nTEST 2: choice1 = 1 = discard estate\n");

	choice1 = 1;
    G.hand[thisPlayer][0] = estate;
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("*Discarding estate = coins +4 ");
    myAssert(testG.coins == G.coins + 4);
    printf("*Discarding estate = estate in discard pile ");
    myAssert(testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1] == estate);
    
    // remove any estates from hand
    for(i = 0; i < G.handCount[thisPlayer]; i++) {
        if(G.hand[thisPlayer][i] == estate) {
            G.hand[thisPlayer][i] = duchy;     
        }
    }
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("*User has no estate = estate card decrements from supply by one ");
    myAssert(G.supplyCount[estate] == testG.supplyCount[estate] + 1);

	// ----------- TEST 3: choice1 = 0 = gain estate --------------
	printf("\nTEST 3: choice1 = 0 = gain estate\n");

    // remove any estates from hand
    for(i = 0; i < G.handCount[thisPlayer]; i++) {
        if(G.hand[thisPlayer][i] == estate) {
            G.hand[thisPlayer][i] = duchy;     
        }
    }
    
    choice1 = 0;
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("*User chooses to gain estate card = state card decrements from supply by one ");
    myAssert(G.supplyCount[estate] == testG.supplyCount[estate] + 1);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
