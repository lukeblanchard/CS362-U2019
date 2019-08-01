#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

struct testResults
{
  int supplyCount;
  int coins;
  int state;
};

int checkBaron(int currentPlayer, int choice1, struct gameState *post, struct testResults *results, int handPos)
{
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));
  int r;

  r = baronCase(choice1, post, handPos, currentPlayer);

  if (choice1 > 0)
  {
    int pos = 0;                //Iterator for hand!
    int card_not_discarded = 1; //Flag for discard set!
    while (card_not_discarded)
    {
      if (pre.hand[currentPlayer][pos] == estate)
      {                 //Found an estate card!
        pre.coins += 4; //Add 4 coins to the amount of coins
        pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = pre.hand[currentPlayer][pos];
        pre.discardCount[currentPlayer]++;
        for (; pos < pre.handCount[currentPlayer]; pos++)
        {
          pre.hand[currentPlayer][pos] = pre.hand[currentPlayer][pos + 1];
        }
        pre.hand[currentPlayer][pre.handCount[currentPlayer]] = -1;
        pre.handCount[currentPlayer]--;
        card_not_discarded = 0; //Exit the loop
      }
      else if (pos > pre.handCount[currentPlayer])
      {
        if (supplyCount(estate, &pre) > 0)
        {
          gainCard(estate, &pre, 0, currentPlayer);
          pre.supplyCount[estate]--; //Decrement estates
          if (supplyCount(estate, &pre) == 0)
          {
            isGameOver(&pre);
          }
        }
        card_not_discarded = 0; //Exit the loop
      }

      else
      {
        pos++; //Next card
      }
    }
  }
  else
  {
    if (supplyCount(estate, &pre) > 0)
    {
      gainCard(estate, &pre, 0, currentPlayer); //Gain an estate
      pre.supplyCount[estate]--;                //Decrement Estates
      if (supplyCount(estate, &pre) == 0)
      {
        isGameOver(&pre);
      }
    }
  }

  if (memcmp(&pre, post, sizeof(struct gameState)) != 0)
  {
    results->state = 0;
  }

  if (pre.coins != post->coins)
  {
    results->coins = 0;
  }

  if (pre.supplyCount[estate] != post->supplyCount[estate])
  {
    results->supplyCount = 0;
  }

  return 0;
}

int main()
{
  int i, n, p, choice1, handPos;
  int denominations = 25;
  struct gameState G;
  struct testResults results;

  results.supplyCount = 1;
  results.coins = 1;
  results.state = 1;

  printf("Testing Baron.\n");
  printf("**************\n");

  printf("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++)
  {
    for (i = 0; i < sizeof(struct gameState); i++)
    {
      ((char *)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.handCount[p] = floor(Random() * MAX_HAND);
    handPos = floor(Random() * G.handCount[p]);
    G.discardCount[p] = floor(Random() * MAX_HAND);
    G.deckCount[p] = floor(Random() * MAX_HAND);
    G.coins = floor(Random() * 10);
    G.playedCardCount = floor(Random() * 10);
    choice1 = floor(Random() * 2);
    for (i = 0; i < G.handCount[p]; i++)
    {
      if (i == handPos)
      {
        G.hand[p][i] = baron;
      }
      else
      {
        G.hand[p][i] = floor(Random() * denominations);
      }
    }
    for (i = 0; i < G.discardCount[p]; i++)
    {
      G.discard[p][i] = floor(Random() * denominations);
    }
    for (i = 0; i < G.deckCount[p]; i++)
    {
      G.deck[p][i] = floor(Random() * denominations);
    }
    for (i = 0; i < denominations; i++)
    {
      G.supplyCount[i] = floor(Random() * 10);
    }
    checkBaron(p, choice1, &G, &results, handPos);
  }

  printf("ALL TESTS RUN\n");
  if (!results.state)
  {
    printf("Pre and Post state do not match\n");
  }
  if (!results.coins)
  {
    printf("Pre and Post coin counts do not match\n");
  }
  if (!results.supplyCount)
  {
    printf("Pre and Post estate supply count do not match\n");
  }
  return 0;
}
