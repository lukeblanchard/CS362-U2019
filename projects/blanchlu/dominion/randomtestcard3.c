#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int checkTribute(int currentPlayer, int nextPlayer, struct gameState *post)
{
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    int r, i;
    int tributeRevealedCards[2] = {-1, -1};

    r = Tribute(currentPlayer, nextPlayer, post);

    if ((pre.discardCount[nextPlayer] + pre.deckCount[nextPlayer]) <= 1)
    {
        if (pre.deckCount[nextPlayer] > 0)
        {
            tributeRevealedCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
            pre.deckCount[nextPlayer]--;
        }
        else if (pre.discardCount[nextPlayer] > 0)
        {
            tributeRevealedCards[0] = pre.discard[nextPlayer][pre.discardCount[nextPlayer] - 1];
            pre.discardCount[nextPlayer]--;
        }
    }

    else
    {
        if (pre.deckCount[nextPlayer] == 0)
        {
            for (i = 0; i < pre.discardCount[nextPlayer]; i++)
            {
                pre.deck[nextPlayer][i] = pre.discard[nextPlayer][i]; //Move to deck
                pre.deckCount[nextPlayer]++;
                pre.discard[nextPlayer][i] = -1;
                pre.discardCount[nextPlayer]--;
            }

            shuffle(nextPlayer, &pre); //Shuffle the deck
        }
        tributeRevealedCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
        pre.deck[nextPlayer][pre.deckCount[nextPlayer]--] = -1;
        pre.deckCount[nextPlayer]--;
        tributeRevealedCards[1] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
        pre.deck[nextPlayer][pre.deckCount[nextPlayer]--] = -1;
        pre.deckCount[nextPlayer]--;
    }

    if (tributeRevealedCards[0] == tributeRevealedCards[1])
    { //If we have a duplicate card, just drop one
        pre.playedCards[pre.playedCardCount] = tributeRevealedCards[1];
        pre.playedCardCount++;
        tributeRevealedCards[1] = -1;
    }

    for (i = 0; i < 2; i++)
    {
        if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold)
        { //Treasure cards
            pre.coins += 2;
        }

        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall)
        { //Victory Card Found
            drawCard(currentPlayer, &pre);
            drawCard(currentPlayer, &pre);
        }
        else if (tributeRevealedCards[i] != -1)
        { //Action Card
            pre.numActions = pre.numActions + 2;
        }
    }

    if (r != 0 || memcmp(&pre, post, sizeof(struct gameState)) != 0)
    {
        return 1;
    }

    return 0;
}

int main()
{
    int i, j, n, p, numPlayers, nextPlayer, failFlag;
    int denominations = 25;
    struct gameState G;

    printf("Testing Tribute.\n");
    printf("***************\n");

    printf("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char *)&G)[i] = floor(Random() * 256);
        }
        numPlayers = floor(Random() * (MAX_PLAYERS - 1)) + 1;
        G.numPlayers = numPlayers;
        G.numActions = 1;
        G.playedCardCount = floor(Random() * MAX_DECK);
        p = floor(Random() * numPlayers);
        nextPlayer = p + 1;
        if (nextPlayer > (G.numPlayers - 1))
        {
            nextPlayer = 0;
        }
        for (i = 0; i < G.playedCardCount; i++)
        {
            G.playedCards[i] = floor(Random() * denominations);
        }

        // set up piles and hand for each other player
        for (i = 0; i < numPlayers; i++)
        {
            G.handCount[i] = floor(Random() * MAX_HAND);
            G.deckCount[i] = floor(Random() * MAX_DECK);
            G.discardCount[i] = MAX_DECK - G.deckCount[i];
            for (j = 0; j < G.handCount[i]; j++)
            {
                G.hand[i][j] = floor(Random() * denominations);
            }
            for (j = 0; j < G.discardCount[i]; j++)
            {
                G.discard[i][j] = floor(Random() * denominations);
            }
            for (j = 0; j < G.deckCount[i]; j++)
            {
                G.deck[i][j] = floor(Random() * denominations);
            }
        }
        G.coins = floor(Random() * 10);
        G.whoseTurn = p;

        if (checkTribute(p, nextPlayer, &G) == 1)
        {
            failFlag = 1;
        }
    }

    printf("ALL TESTS RUN\n");
    if (failFlag)
    {
      printf("TESTS FAILED\n\n");
    }

    return 0;
}
