#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "mine"

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
    printf("Conditions:\n"); 
    printf("* choice1 = non-treasure card\n");
    printf("Expected: function returns -1\n");
    
	memcpy(&testG, &G, sizeof(struct gameState));

    choice1 = 1; 
    testG.hand[thisPlayer][1] = smithy;
    
	error = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    myAssert(error == -1);

	// ----------- TEST 2 --------------
	printf("\nTEST 2:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = copper\n");
    printf("* choice2 = gold\n");
    printf("Expected: function returns -1, gold is more than copper value + 3\n");

	memcpy(&testG, &G, sizeof(struct gameState));

    choice1 = 1; 
    choice2 = gold;
    testG.hand[thisPlayer][1] = copper;

	error = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);

    myAssert(error == -1);

	// ----------- TEST 3 --------------
	printf("\nTEST 3:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = gold\n");
    printf("* choice2 = copper\n");
    printf("Expected: thisPlayer adds copper to hand\n");

	memcpy(&testG, &G, sizeof(struct gameState));

    choice1 = 1; 
    choice2 = copper;
    testG.hand[thisPlayer][1] = gold;

	cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    myAssert(testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] == choice2);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
