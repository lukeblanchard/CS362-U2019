#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);
int Baron(int currentPlayer, int choice1, struct gameState *state);
int Minion(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos);
int Ambassador(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos);
int Tribute(int currentPlayer, int nextPlayer, struct gameState *state); 
int Mine(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos);
int trashCard(int currentPlayer, struct gameState* state, int card, int trashFlag);
#endif
