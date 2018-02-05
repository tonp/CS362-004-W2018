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
 * This function tests the councilroom card effect
 */
void testCouncilRoom(struct gameState* testState, struct gameState* state, int player, int kingdom[]){

	// Init variables
	int a; 
	int otherPlayer = 1; 
	int currentHand = testState->handCount[player]; 
	int numBuy = testState->numBuys;  
	int currentDeck = testState->deckCount[player]; 
	int otherPlayerCurrentHand = testState->handCount[otherPlayer];
	int otherPlayerCurrentDeck = testState->deckCount[otherPlayer];  

	printf("Player current hand count : %d\n", currentHand); 
	printf("Player current number of buys : %d\n", numBuy); 
	printf("Player current deck count : %d\n", currentDeck); 

	printf("\nOther Player current hand count : %d\n", otherPlayerCurrentHand); 
	printf("Other Player current deck count : %d\n", otherPlayerCurrentDeck); 

	printf("\nRunning council room card effect\n\n");
	cardEffect(council_room,0,0,0,testState,0,0);  

	printf("Player hand count after : %d\n", testState->handCount[player]); 
	printf("Player number of buys after : %d\n", testState->numBuys);
	printf("Player deck count after : %d\n", testState->deckCount[player]); 

	printf("\nOther Player hand count after : %d\n", testState->handCount[otherPlayer]); 
	printf("Other Player deck count after : %d\n", testState->deckCount[otherPlayer]); 


	printf("\nTesting if player hand count contains 4 more cards\n");
	if(assert(testState->handCount[player], state->handCount[player]+3)){numOfTests++;}
	
	printf("Testing if player has gained 1 more buys\n"); 
	if(assert(testState->numBuys, state->numBuys+1)){numOfTests++;}
	
	printf("Testing if player deck count has 4 less cards\n"); 
	if(assert(testState->deckCount[player], state->deckCount[player]-4)){numOfTests++;}

	printf("Testing if other player hand count has 1 more cards\n"); 
	if(assert(testState->handCount[otherPlayer], state->handCount[otherPlayer]+1)){numOfTests++;}

	printf("Testing if other player deck count has 1 less cards\n"); 
	if(assert(testState->deckCount[otherPlayer], state->deckCount[otherPlayer]-1)){numOfTests++;}


	// Testing Vitory Pile	
	printf("Testing Victory : Estate has not changed\n"); 
	if(assert(testState->supplyCount[estate], state->supplyCount[estate])){numOfTests++;}

	printf("Testing Victory : Duchy has not changed\n"); 
	if(assert(testState->supplyCount[duchy], state->supplyCount[duchy])){numOfTests++;}

	printf("Testing Victory : Province has not changed\n"); 
	if(assert(testState->supplyCount[province], state->supplyCount[province])){numOfTests++;}

	// Testing kingdom pile
	printf("Testing Kingdom Pile has not changed\n"); 
	int i =0;
	for (a =0; a <10; a++){
		if (testState->supplyCount[kingdom[a]] == state->supplyCount[kingdom[a]]){
			i++; 
		}
	}
	if (assert(i, 10)){numOfTests++;}

	// Testing Treasure Pile
	printf("Testing Copper Supply Has No Change\n"); 
	if(assert(testState->supplyCount[copper], state->supplyCount[copper])){numOfTests++;}
	printf("Testing Silver Supply Has No Change\n"); 	
	if(assert(testState->supplyCount[silver], state->supplyCount[silver])){numOfTests++;}
	printf("Testing Gold Supply Has No Change\n"); 	
	if(assert(testState->supplyCount[gold], state->supplyCount[gold])){numOfTests++;}


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

	// Init struct + kingdom
	struct gameState state, testState; 	
	int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

	// Initit game 
	initializeGame(numPlayers, kingdom, seed, &state); 

	printf("--- Starting Card Test 3: Council Room ---\n\n\n"); 

	// Copy game state to test case 
	memcpy(&testState, &state, sizeof(struct gameState)); 


	// Call test function
	testCouncilRoom(&testState, &state, player, kingdom);

	printf("----- Total -----\n"); 
	printf("Total Test Case : 12\n"); 
	printf("Total Test Case Passed : %d\n\n", numOfTests); 
	printf("----- Card Test 4 : Council Room Completed ----\n"); 
	return 0; 
}


