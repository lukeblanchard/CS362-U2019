#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

struct testResults {
    int coins;
    int handCount;
    int actions;
    int state;
};

int checkMinion(int currentPlayer, int choice1, int choice2, struct gameState *post, int handPos, struct testResults *results)
{
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));
  int r;

  r = Minion(currentPlayer, choice1, choice2, post, handPos);

  //+1 action
  int i;
  int j;
  pre.numActions++;

  //discard card from hand
  discardCard(handPos, currentPlayer, &pre, 0);

  if (choice1) //+2 coins
  {
    pre.coins = pre.coins + 2;
  }

  else if (choice2) //discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
  {
    //discard hand
    while (numHandCards(&pre) > 0)
    {
      discardCard(handPos, currentPlayer, &pre, 0);
    }

    //draw 4
    for (i = 0; i < 4; i++)
    {
      drawCard(currentPlayer, &pre);
    }

    //other players discard hand and redraw if hand size > 4
    for (i = 0; i < pre.numPlayers; i++)
    {
      if (i != currentPlayer)
      {
        if (pre.handCount[i] > 4)
        {
          //discard hand
          while (pre.handCount[i] > 0)
          {

            discardCard(handPos, i, &pre, 0);
          }

          //draw 4
          for (j = 0; j < 4; j++)
          {
            drawCard(i, &pre);
          }
        }
      }
    }
  }

  if (memcmp(&pre, post, sizeof(struct gameState)) != 0)
  {
    results->state = 0;
  }

  if (pre.coins != post->coins) {
    results->coins = 0;
  }

  if (pre.numActions != post->numActions) {
    results->actions = 0;
  }

  if (pre.handCount[currentPlayer] != post->handCount[currentPlayer]) {
    results->handCount = 0;
  }

  return 0;
}

int main()
{
  int i, j, n, p, choice1, choice2, handPos, numPlayers;
  int denominations = 25;
  struct gameState G;
  struct testResults results;

  results.handCount = 1;
  results.coins = 1;
  results.actions = 1;
  results.state = 1;

  printf("Testing Minion.\n");
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

    for (i = 0; i < G.playedCardCount; i++)
    {
      G.playedCards[i] = floor(Random() * denominations);
    }

    // set up piles and hand for each other player
    for (i = 0; i < numPlayers; i++)
    {
      G.handCount[i] = floor(Random() * MAX_HAND);
      G.discardCount[i] = floor(Random() * MAX_HAND);
      G.deckCount[i] = floor(Random() * MAX_HAND);
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
    choice1 = floor(Random() * 2);
    choice2 = floor(Random() * 2);

    handPos = floor(Random() * G.handCount[p]);
    G.hand[p][handPos] = minion;

    checkMinion(p, choice1, choice2, &G, handPos, &results);
  }

  printf("ALL TESTS RUN\n");
  if(!results.state)
  {
    printf("Pre and Post state do not match\n");
  }
  if(!results.coins)
  {
    printf("Pre and Post coin counts do not match\n");
  }
  if(!results.actions)
  {
    printf("Pre and Post actions do not match\n");
  }
  if(!results.handCount) 
  {
    printf("Pre and Post handCount do not match\n");
  }
  return 0;
}
