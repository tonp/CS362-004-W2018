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
 * Returns 1 if true
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


/* Name : testSmithy()
 * Param : struct gameState testState, state, int player, int kingdom[]
 * This function tests the smithy card effect
 */
void testSmithy(struct gameState* testState, struct gameState* state, int player, int kingdom[]){

	int a;

	// Print Current player state
	printf("Player Current Hand Count : %d\n", testState->handCount[player]); 
	printf("Player Current Deck Count : %d\n", testState->deckCount[player]); 
	printf("Expected Hand Count after smithy effect: %d\n", testState->handCount[player]+3); 
	printf("Expected Deck Count After Smithy Effect: %d\n", testState->deckCount[player]-3); 

	printf("\nRunning smithy card effect\n\n"); 
	cardEffect(smithy, 0,0,0,testState,0,0);
  
	printf("\nReturned Hand Count After smithy effect: %d\n", testState->handCount[player]); 
	if(assert(testState->handCount[player], state->handCount[player]+3)){numOfTests++;}

	printf("Returned Deck Count After smithy effect: %d\n", testState->deckCount[player]); 
	if(assert(testState->deckCount[player], state->deckCount[player]-3)){numOfTests++;}


	// Test Victory piles
	printf("Testing Victory : Estate has not changed\n"); 
	if(assert(testState->supplyCount[estate], state->supplyCount[estate])){numOfTests++;}

	printf("Testing Victory : Duchy has not changed\n"); 
	if(assert(testState->supplyCount[duchy], state->supplyCount[duchy])){numOfTests++;}


	printf("Testing Victory : Province has not changed\n"); 
	if(assert(testState->supplyCount[province], state->supplyCount[province])){numOfTests++;}

	// Test Kingdom Pile
	printf("Testing Kingdom Pile has not changed\n"); 
	int i =0;
	for (a =0; a <10; a++){
		if (testState->supplyCount[kingdom[a]] == state->supplyCount[kingdom[a]]){
			i++; 
		}
	}
	if (assert(i, 10)){numOfTests++;}

	// Test Treasure Pile
	printf("Testing Copper Supply Has No Change\n"); 
	if(assert(testState->supplyCount[copper], state->supplyCount[copper])){numOfTests++;}
	printf("Testing Silver Supply Has No Change\n"); 	
	if(assert(testState->supplyCount[silver], state->supplyCount[silver])){numOfTests++;}
	printf("Testing Gold Supply Has No Change\n"); 	
	if(assert(testState->supplyCount[gold], state->supplyCount[gold])){numOfTests++;}

	// Test State for Other Player
	printf("-- Test State Change For Other Player --\n\n"); 
	printf("Testing No Change for Other Player Hand Count\n"); 
	if(assert(testState->handCount[player+1], state->handCount[player+1])){numOfTests++;} 

	printf("Testing No Change for Other Player Deck Count\n");
	if(assert(testState->deckCount[player+1], state->deckCount[player+1])){numOfTests++;}
 

	

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

	// Make gameState + kingdom
	struct gameState state, testState; 	
	int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

	// Initit game 
	initializeGame(numPlayers, kingdom, seed, &state); 

	printf("--- Starting Card Test 1: Smithy ---\n\n\n"); 

	// Copy game state to test case 
	memcpy(&testState, &state, sizeof(struct gameState)); 


	// Call test function
	testSmithy(&testState, &state, player, kingdom);

	printf("----- Total -----\n"); 
	printf("Total Test Case : 11\n"); 
	printf("Total Test Case Passed : %d\n\n", numOfTests); 
	printf("----- Card Test 1 : Smithy Completed ----\n"); 

	return 0; 
}


