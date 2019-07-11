#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i, card;
    for(i = 5; i > 0; i--){
        card = floor(Random() * i);
        printf("Random: %f\n", Random());
        printf("%d\n", card);
    }
    return 0;
}
