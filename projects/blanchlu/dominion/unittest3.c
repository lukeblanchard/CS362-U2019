#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "ambassador"

void myAssert(int bool) {
	if(bool == 1) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
	}
}

int main() {
    int error; 
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, testEstateCount = 0, estateCount = 0;
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
    printf("Conditions:\n"); 
    printf("* choice2 = 3\n");
    printf("Expected: return error, player cannot choose more than 2 for discard\n");

	// copy the game state to a test case
    choice2 = 3;
	memcpy(&testG, &G, sizeof(struct gameState));
	error = cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, &bonus);
	myAssert(error == -1);

	// ----------- TEST 2 --------------
	printf("\nTEST 2:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = 1 (estate)\n");
    printf("* choice2 = 2\n");
    printf("* player has 2 estates in hand\n");
    printf("Expected: discard count for other player increases by 2\n");

    choice1 = 1;
    choice2 = 2;
	memcpy(&testG, &G, sizeof(struct gameState));

    // add estates to thisPlayer hand
    testG.hand[thisPlayer][1] = estate;
    testG.hand[thisPlayer][2] = estate;
    testG.hand[thisPlayer][3] = estate;
	cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, &bonus);
    myAssert(testG.discardCount[thisPlayer + 1] == G.discardCount[thisPlayer + 1] + 2);

	// ----------- TEST 2 --------------
	printf("\nTEST 3:\n");
    printf("* choice1 = 1 (estate)\n");
    printf("* choice2 = 2\n");
    printf("* player has 2 estates in hand\n");
    printf("Expected: estate count for current player decreases by 2\n");
    
    for(i = 0; i < testG.handCount[thisPlayer]; i++) {
        if(testG.hand[thisPlayer][i] == estate) {
            testEstateCount++;     
        }
    }

    for(i = 0; i < G.handCount[thisPlayer]; i++) {
        if(G.hand[thisPlayer][i] == estate) {
            estateCount++;     
        }
    }
    myAssert(testEstateCount == estateCount - 2);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
