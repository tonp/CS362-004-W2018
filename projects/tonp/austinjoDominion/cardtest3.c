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


/* Name : testVillage()
 * Param : struct gameState testState, state, int player, int kingdom[]
 * This function tests the village card effect
 */
void testVillage(struct gameState* testState, struct gameState* state, int player, int kingdom[]){

	// Init variables
	int a; 
	int currentHand = testState->handCount[player]; 
	int numAction = testState->numActions; 
	int currentDeck = testState->deckCount[player]; 

	printf("Player current hand count : %d\n", currentHand); 
	printf("Player current number of actions count : %d\n", numAction); 
	printf("Player current deck count : %d\n", currentDeck); 

	printf("\nRunning village card effect\n\n");
	cardEffect(village,0,0,0,testState,0,0);  

	printf("Player hand count after : %d\n", testState->handCount[player]); 
	printf("Player number of actions after : %d\n", testState->numActions);
	printf("Player deck count after : %d\n", testState->deckCount[player]); 

	printf("\nTesting if player has same number of cards in hand\n");
	if(assert(testState->handCount[player], state->handCount[player])){numOfTests++;}
	
	printf("Testing if player has gained 2 more actions\n"); 
	if(assert(testState->numActions, state->numActions+2)){numOfTests++;}
	
	printf("Testing if player deck count has 1 less\n"); 
	if(assert(testState->deckCount[player], state->deckCount[player]-1)){numOfTests++;}
	

	// Testing Victory pile
	printf("Testing Victory : Estate has not changed\n"); 
	if(assert(testState->supplyCount[estate], state->supplyCount[estate])){numOfTests++;}

	printf("Testing Victory : Duchy has not changed\n"); 
	if(assert(testState->supplyCount[duchy], state->supplyCount[duchy])){numOfTests++;}


	printf("Testing Victory : Province has not changed\n"); 
	if(assert(testState->supplyCount[province], state->supplyCount[province])){numOfTests++;}

	printf("Testing Kingdom Pile has not changed\n"); 
	int i =0;
	for (a =0; a <10; a++){
		if (testState->supplyCount[kingdom[a]] == state->supplyCount[kingdom[a]]){
			i++; 
		}
	}
	if (assert(i, 10)){numOfTests++;}

	// Testing Treasure Piles
	printf("Testing Copper Supply Has No Change\n"); 
	if(assert(testState->supplyCount[copper], state->supplyCount[copper])){numOfTests++;}
	printf("Testing Silver Supply Has No Change\n"); 	
	if(assert(testState->supplyCount[silver], state->supplyCount[silver])){numOfTests++;}
	printf("Testing Gold Supply Has No Change\n"); 	
	if(assert(testState->supplyCount[gold], state->supplyCount[gold])){numOfTests++;}

	// Testing state of other player
	printf("-- Test State Change For Other Player --\n\n"); 
	printf("Testing No Change for Other Player Hand Count\n"); 
	if(assert(testState->handCount[player+1], state->handCount[player+1])){numOfTests++;} 

	printf("Testing No Change for Other Player Deck Count\n");
	if(assert(testState->deckCount[player+1], state->deckCount[player+1])){numOfTests++;}
 


	

}

/* Name : main()
 * Descript : Calls the testVillage()
 */
int main(){

	// Init variables
	int player =0; 
	int numPlayers = 2; 
	int seed = 6666; 

	// Init srand 
	srand(time(NULL)); 

	// Innit struct + kingdom
	struct gameState state, testState; 	
	int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

	// Initit game 
	initializeGame(numPlayers, kingdom, seed, &state); 

	printf("--- Starting Card Test 3: Village ---\n\n\n"); 

	// Copy game state to test case 
	memcpy(&testState, &state, sizeof(struct gameState)); 


	// Call test function
	testVillage(&testState, &state, player, kingdom);

	printf("----- Total -----\n"); 
	printf("Total Test Case : 12\n"); 
	printf("Total Test Case Passed : %d\n\n", numOfTests); 
	printf("----- Card Test 3 : Village Completed ----\n"); 

	return 0; 
}


