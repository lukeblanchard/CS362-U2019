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
    int i, j, match;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 4;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 --------------
	printf("TEST 1:\n");
    printf("Expected: +1 actions\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	myAssert(testG.numActions == G.numActions + 1);

	// ----------- TEST 2 --------------
	printf("\nTEST 2:\n");
    printf("Conditions:\n"); 
    printf("* choice1 = 1\n");
    printf("Expected: coins increase by +2\n");

	choice1 = 1;
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	myAssert(testG.coins == G.coins + 2);

	// ----------- TEST 3 --------------
	printf("\nTEST 3:\n");
    printf("Conditions:\n"); 
    printf("* choice2 = 1\n");
    printf("Expected: player discards hand, those cards go to playedCards pile\n");
    
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
    
	// ----------- TEST 4 --------------
	printf("\nTEST 4:\n");
    printf("Conditions:\n"); 
    printf("* choice2 = 1\n");
    printf("Expected: player discards hand, new hand count is 4\n");
    myAssert(testG.handCount[thisPlayer] == 4);

	// ----------- TEST 5 --------------
	printf("\nTEST 5:\n");
    printf("Conditions:\n"); 
    printf("* choice2 = 1\n");
    printf("Expected: other player discards hand, new hand count is 4\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    // initialize other player's hand
    for(i = 0; i < 5; i++){
        testG.hand[thisPlayer + 1][i] = i;
    }

    testG.handCount[thisPlayer + 1] = 5;
    
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
    myAssert(testG.handCount[thisPlayer + 1] == 4);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    
	return 0;
}
