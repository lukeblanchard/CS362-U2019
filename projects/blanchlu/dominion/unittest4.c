#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "tribute"

void myAssert(int bool) {
	if(bool == 1) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
	}
}

int main() {
    int i, error; 
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, testEstateCount = 0, estateCount = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0, nextPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 --------------
	printf("TEST 1:\n");
    printf("Conditions:\n"); 
    printf("* other player deck count = 2\n");
    printf("* deck = one action card + one treasure card\n");
    printf("Expected: current player gets +2 action and +2 coins\n");
    
	memcpy(&testG, &G, sizeof(struct gameState));

    // set up next player 
    testG.deckCount[nextPlayer] = 2;
    testG.deck[nextPlayer][0] = copper;
    testG.deck[nextPlayer][1] = council_room;

	cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
    myAssert(G.numActions + 2 == testG.numActions && G.coins + 2 == testG.coins);

	// ----------- TEST 2 --------------
	printf("\nTEST 2:\n");
    printf("Conditions:\n"); 
    printf("* other player deck count = 6\n");
    printf("* deck = all same treasure\n");
    printf("Expected: current player gets +2 coins because of duplicate\n");

	memcpy(&testG, &G, sizeof(struct gameState));

    // set up next player 
    testG.deckCount[nextPlayer] = 6;
    testG.deck[nextPlayer][0] = copper;
    testG.deck[nextPlayer][1] = copper;
    testG.deck[nextPlayer][2] = copper;
    testG.deck[nextPlayer][3] = copper;
    testG.deck[nextPlayer][4] = copper;
    testG.deck[nextPlayer][5] = copper;

	cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
    myAssert(G.coins + 2 == testG.coins);

	// ----------- TEST 2 --------------
	printf("\nTEST 3:\n");
    printf("Conditions:\n"); 
    printf("* other player deck count = 6\n");
    printf("* deck = all different victory\n");
    printf("Expected: current player draws 4 cards\n");
    
	memcpy(&testG, &G, sizeof(struct gameState));

    // set up next player 
    testG.deckCount[nextPlayer] = 5;
    testG.deck[nextPlayer][0] = estate;
    testG.deck[nextPlayer][1] = duchy;
    testG.deck[nextPlayer][2] = province;
    testG.deck[nextPlayer][3] = gardens;
    testG.deck[nextPlayer][4] = great_hall;

	cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
    myAssert(G.handCount[thisPlayer] + 4 == testG.handCount[thisPlayer]);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
