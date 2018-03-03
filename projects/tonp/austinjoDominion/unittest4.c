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
 */int assert(int a, int b){
	if (a == b){
		printf("TEST PASSED\n\n"); 
		return 1; 
	}
	else{
		printf("TEST FAILED\n\n"); 
		return 0; 
	}
}

/* Name : main()
 * Param : ----
 * Descript : Testing numHandsCount()
 */
int main(){

	// Init variables
	int a,player,randomCount, result; 
	int numPlayers = 2; 
	int seed = 6666; 

	// Init srand 
	srand(time(NULL)); 

	// Init game struct
	struct gameState state, testState; 	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

	// Initit game 
	initializeGame(numPlayers, k, seed, &state); 

	printf("--- Starting Unit Test 4 ---\n\n\n"); 

	// Copy game state to test case 
	memcpy(&testState, &state, sizeof(struct gameState)); 

	
	// Set random current player 
	for (a = 0; a < 3; a++){
		
		printf("----- Test Case %d -----\n\n", a+1); 


		// Set random player
		player= rand() % 2; 
		testState.whoseTurn = player; 
		
		// Set random count
		randomCount = 1+(rand() % MAX_HAND); 
		testState.handCount[player] = randomCount;
		
		printf("Current Player : %d\n", player); 
		printf("Expected handcount : %d\n", randomCount); 
		printf("Running numHandsCards for Player %d\n", player); 
	
		// Run hand count  
		result = numHandCards(&testState); 
		printf("Returned handcount : %d\n",result); 
		
		// assert 
		if(assert(result, randomCount)){
			numOfTests++;
		}  
	
		// Reset state
	memcpy(&testState, &state, sizeof(struct gameState)); 
	}
	printf("----- Total -----\n"); 
	printf("Total Test Case : 3\n"); 
	printf("Total Test Case Passed : %d\n\n", numOfTests); 
	printf("----- Unit Test 4 Completed ----\n"); 

	return 0; 
}


