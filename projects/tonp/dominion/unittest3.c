#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 



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


/* Name : main()
 * Param : ----
 * Descript : Testing isGameOver()
 */
int main(){
	
	// Init variables
	int a; 
	int result;
	int numPlayers = 2; 
	int seed = 6666; 

	// Init srand 
	srand(time(NULL)); 

	// Init Struct + kingdom
	struct gameState state, testState; 	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

	// Initit game 
	initializeGame(numPlayers, k, seed, &state); 

	printf("--- Starting Unit Test 3 ---\n\n\n"); 

	// Copy game state to test case 
	memcpy(&testState, &state, sizeof(struct gameState)); 

	// Test function
	for (a = 0; a < 3; a++){
		printf("----- Test Case %d -----\n\n",a+1);

		// Test if game is ongoing 
		printf("Province Count = %d\n", testState.supplyCount[province]); 
		printf("First 3 Supply Count\n"); 
		int i; 
		for (i = 0; i < 3; i++){
			printf("Supply %d: %d\n", i, testState.supplyCount[i]); 
		}

		printf("Calling isGameOver()\n"); 
		result = isGameOver(&testState); 
		if (result ==0){
			printf("Game is ongoing\n"); 
		}
		else{
			printf("Game is over\n"); 
		}
		numOfTests += assert(result, 0); 
			
		// Reset the state
		memcpy(&testState, &state, sizeof(struct gameState)); 	
	

		printf("Province Count = %d\n", testState.supplyCount[province]);
		printf("Setting Province Count to 0\n"); 
		
		// Set the province count to 0 
		testState.supplyCount[province] = 0; 
		printf("Current Province Count = %d\n", testState.supplyCount[province]); 
		
		// Call isGameOver(); 
		printf("Calling isGameOver()\n"); 
		result = isGameOver(&testState);
		if (result ==1){
			printf("Game is over\n");
		}
		else{
			printf("Game is not over\n"); 
		} 
		numOfTests += assert(result, 1);  

		// Reset the state
		memcpy(&testState, &state, sizeof(struct gameState)); 
		
		// Print the current suppy pile
		printf("First 3 Supply Count\n");  
		for (i = 0; i < 3; i++){
			printf("Supply %d: %d\n", i, testState.supplyCount[i]); 
		}

		printf("Setting first three supply pile to 0\n"); 
		testState.supplyCount[0] = 0;
		testState.supplyCount[1] = 0; 
		testState.supplyCount[2] = 0;  
		
		for (i = 0; i < 3; i++){
			printf("Supply %d: %d\n", i, testState.supplyCount[i]); 
		}

		printf("Calling isGameOver()\n"); 
		result = isGameOver(&testState);
		if (result ==1){
			printf("Game is over\n");
		}
		else{
			printf("Game is not over\n"); 
		} 
		numOfTests += assert(result, 1);  
		
		// Reset the state
		memcpy(&testState, &state, sizeof(struct gameState)); 
	

	}

	
	printf("----- Total -----\n"); 
	printf("Total Test Case : 9\n"); 
	printf("Total Test Case Passed : %d\n\n", numOfTests); 
	printf("----- Unit Test 3 Completed ----\n"); 





	return 0; 
}


