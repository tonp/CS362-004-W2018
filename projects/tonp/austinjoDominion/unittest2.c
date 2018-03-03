#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 


// Init global variable
int numOfTests = 0; 

/* Name : assert()
 * Param : int a, int b
 * Description : This function compares two int param. 
 * Returns 1 if true, print test passed
 * Returns 0 if false
 */
int assert(int a, int b){
	if (a == b){
		printf("TEST PASSED\n\n"); 
		return 1; 
	}
	else{
		printf("TEST FAILED\n\n"); 
		return 0; 
	}
}


/* Name : testFunct()
 * Param : int deckNum, card, struct gameState, testState
 * Description : This function tests the fullDeckCount() from dominion.c
 */
void testFunct(int deckNum, int card, struct gameState *testState){
	
	
	// Variable declaration
	int a,i, randomNum; 
	int thisPlayer = 0; 

	// Set deck and hand count to be 0; 
	for (a=0; a < 5; a++){
		testState->deckCount[thisPlayer]--; 
		testState->handCount[thisPlayer]--; 
	}

	// Set the discard deck to have five cardsd that are copper for testing
	for (a = 0; a < deckNum; a++){
		testState->discard[thisPlayer][a]= copper; 
		testState->discardCount[thisPlayer]++; 

		testState->hand[thisPlayer][a]= copper; 
		testState->handCount[thisPlayer]++; 

		testState->deck[thisPlayer][a]= copper; 
		testState->deckCount[thisPlayer]++; 
	}

 

	// Print amount of cards in each deck; 
	printf("Deck Count: %d\nDiscard Count: %d\nHand Count: %d\n", 
		testState->deckCount[thisPlayer], testState->discardCount[thisPlayer], testState->handCount[thisPlayer]);

	// Set randomNum for the selected card
	randomNum =1+(rand() % MAX_DECK);

	while (randomNum > deckNum){
		randomNum = 1+(rand() %MAX_DECK); 
	}


	// Set randomNum amount of randomCard into deck and hand
	for (a = 0; a < randomNum; a++){
		testState->deck[thisPlayer][a] = card;
	
		testState->hand[thisPlayer][a] = card;

		testState->discard[thisPlayer][a] = card;

	}

	printf("Expected total of card number %d in deck + discard + hand: %d\n", card, randomNum *3); 
	printf("Running fullDeckCount()\n"); 
	i = fullDeckCount(thisPlayer, card, testState); 
	printf("Actual total of card number %d in deck + discard + hand: %d\n", card, i); 
		
	// Assert the two numbers 
	if(assert(randomNum*3, i)){
		numOfTests++; 
	}
	 


}


/* Name : main()
 * Param : -----
 * Description : Control flow of the test
 */
int main(){

	// Init variables
	int a; 
	int randomCard; 
	int randomNum;   
	int numPlayers = 2; 
	int seed = 6666; 

	// Init srand 
	srand(time(NULL)); 

	// Make gameStates + kingdom cards
	struct gameState state, testState; 	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

	// Initit game 
	initializeGame(numPlayers, k, seed, &state); 

	printf("--- Starting Unit Test 2 ---\n\n\n"); 

	// Copy game state to test case 
	memcpy(&testState, &state, sizeof(struct gameState)); 

	// counts up total number of cards for a selected card in all deck 
	for (a = 0; a < 3; a++){
		printf("----- Test Case %d -----\n\n",a+1);
		randomCard = 1+(rand() %10); // Generate a random card from kingdom deck 
		randomNum = 1+(rand() %MAX_DECK); 
		testFunct(randomNum,k[randomCard], &testState); 
		// Reset state
		memcpy(&testState, &state, sizeof(struct gameState)); 
	}

	
	printf("----- Total -----\n"); 
	printf("Total Test Case : 3\n"); 
	printf("Total Test Case Passed : %d\n\n", numOfTests); 
	printf("----- Unit Test 2 Completed ----\n"); 

	return 0; 
}


