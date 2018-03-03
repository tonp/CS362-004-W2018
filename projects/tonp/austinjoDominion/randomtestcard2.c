#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 


// Init global variable
int numOfCorrectCardsHand = 0;
int numCorrectDeckCount = 0;
int numOfTests = 0; 
 
/* Name : assert()
 * Param : int a, int b
 * Description : This function compares two int param. 
 * Returns 1 if true
 * Returns 0 if false
 */
int assert(int a, int b){
	if (a == b){
	//	printf("TEST PASSED\n\n"); 
		return 1; 
	}
	else{
//		printf("TEST FAILED\n\n"); 
		return 0; 
	}
}


/* Name : randomSmithyEffect
 * Param : struct gameState testState, state, int player, int kingdom[]
 * This function tests the smithy card effect
 */
void randomSmithyEffect(struct gameState* testState, int player, int kingdom[]){

	int sets = 0; 
	int handCount, deckCount;

	// Set random deck count
	testState->deckCount[player] = 1+(rand()%MAX_DECK); 
	deckCount = testState->deckCount[player]; 

	// Init the deck with random kingdom cards
	int a; 
	for (a = 0; a < deckCount; a++){
		testState->hand[player][a] = 7+((rand()%26)); 
	}

	// Set random hand count 
	testState->handCount[player] = 1+((rand()%MAX_HAND)); 
	handCount = testState->handCount[player]; 

	// Call smithyEffect
	cardEffect(smithy, 0,0,0,testState,0,0); 

	// Check correct
	if(assert(testState->handCount[player], handCount+2)){
		sets++; 
		numOfCorrectCardsHand++;
//		Hand++; 
	}

	// Check if deck count is correct
	if(assert(testState->deckCount[player], deckCount-3)){
		sets++;
		numCorrectDeckCount++;
		 
	}

	// Ad up the sets
	if(assert(sets,2)){
		numOfTests++; 
	}

}


/* Name : main()
 * Descript : Calls the testSmithy()
 */
int main(){
	
	// Init variables
	int player =0; 
	int numPlayers = 2; 
	int seed = 6666; 

	// Init srand 
	srand(time(NULL)); 

	printf("--- Starting Random Card Test 2 : Smithy ---\n\n"); 

	// Call test function
	int a; 
	for (a=0; a < 5; a++){

		// Init gameSate
		struct gameState state;	
		int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

		// Initit game 
		initializeGame(numPlayers, kingdom, seed, &state);  

		// Call test function 
		randomSmithyEffect(&state, player, kingdom);  
	}

	printf("----- Total -----\n");
	printf("Number of Tests : 500000\n"); 
	printf("Number of correct card drawn: %d\n", numOfCorrectCardsHand); 
	printf("Number of correct deck count: %d\n", numCorrectDeckCount); 
	printf("Number of Tests Passed : %d\n", numOfTests);  
	printf("----- Random Card Test 2 : Smithy Effect Completed----\n"); 





	return 0; 
}


