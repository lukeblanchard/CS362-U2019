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
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 --------------
	printf("TEST 1:\n");
    printf("Expected: +1 buys\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	myAssert(testG.numBuys == G.numBuys + 1);

	// ----------- TEST 2 --------------
	printf("\nTEST 2:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = 1\n");
    printf("* player has estate\n"); 
    printf("Expected: coins increase by +4\n");

	choice1 = 1;
    G.hand[thisPlayer][0] = estate;
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
    myAssert(testG.coins == G.coins + 4);

	// ----------- TEST 3 --------------
	printf("\nTEST 3:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = 1\n");
    printf("* player has estate\n"); 
    printf("Expected: estate in discard pile\n");
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

	// ----------- TEST 4 --------------
	printf("\nTEST 4:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = 1\n");
    printf("* player has no estate\n"); 
    printf("Expected: estate card decrements from supply by one\n");
    myAssert(G.supplyCount[estate] == testG.supplyCount[estate] + 1);

	// ----------- TEST 5 --------------
	printf("\nTEST 5:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = 0\n");
    printf("Expected: player gains estate\n");

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

	// ----------- TEST 6 --------------
	printf("\nTEST 6:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = 0\n");
    printf("Expected: state card decrements from supply by one ");
    myAssert(G.supplyCount[estate] == testG.supplyCount[estate] + 1);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
