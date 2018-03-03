#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 


// Count number of tests
int numOfTests = 0; 


/* Name : assert()
 * Param : int a, int b
 * Description : This function compares two int param. 
 * Returns 1 if true, print test passed and numOfTests is incremented
 * Returns 0 if false
 */
int assert(int a, int b){
	if (a == b){
		printf("TEST PASSED\n\n"); 	
		numOfTests++; 
		return 1; 
	}
	else{
		printf("TEST FAILED\n\n"); 
		return 0; 
	}
}

/* Function : main()
 * Param : 
 * Description : This function test the updateCoins()
 * Return : ----- 
 */
int main(){

	// Init variables
	int a,i; 
	int randomBonus;  
	int numPlayers = 2;
	int thisPlayer = 0;  
	int seed = 6666; 

	// Init srand 
	srand(time(NULL)); 

	// Make gameState structs
	struct gameState state, testState; 	

	// Init k for kingdom -- from dominion.c
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

	// Initit game 
	initializeGame(numPlayers, k, seed, &state); 

	printf("--- Starting Unit Test 1 ---\n\n\n"); 

	// Copy game state to test case 
	memcpy(&testState, &state, sizeof(struct gameState)); 

	
	printf("---- Test Case 1 : All Copper Hand ----\n"); 

	// Set all cards in hand to be copper 
	for (a = 0; a < testState.handCount[thisPlayer]; a++){
		testState.hand[thisPlayer][a] = copper;  
	}

		
	printf("Number of Copper Cards In Hand : %d\n", testState.handCount[thisPlayer]); 
	printf("Expected coins: %d\n", 1*testState.handCount[thisPlayer]); 
	printf("Running updateCoins()\n"); 

	// Runn update Coins with 0 bonus
	updateCoins(thisPlayer, &testState, 0); 
	printf("Coins After updateCoins() = %d\n", testState.coins); 

	assert(1*testState.handCount[thisPlayer],testState.coins);

	// Generate Random bonus from 1-10 
	randomBonus = 1 + (rand() % 10); 
	printf("Adding %d Bonus\n", randomBonus); 

	i = testState.coins + randomBonus; 
	printf("Expected Coins After %d Bonus : %d\n",randomBonus, i); 
	
	printf("Running UpdateCoins()\n"); 
	
	// Run update coin agian with added bonus 
	updateCoins(thisPlayer, &testState, randomBonus); 
	
	printf("Total Coins After updateCoins With Bonus : %d\n", testState.coins); 

	assert(i,testState.coins);

	/////////////////////////////////////////////////////////////////////////////////////

	// Copy the state into testState
	memcpy(&testState, &state, sizeof(struct gameState)); 

	
	printf("---- Test Case 2 ----\n"); 

	// Set all cards in hand to be silver
	for (a = 0; a < testState.handCount[thisPlayer]; a++){
		testState.hand[thisPlayer][a] = silver;  
	}
	
	printf("Number of Silver  Cards In Hand : %d\n", testState.handCount[thisPlayer]); 
	printf("Expected coins: %d\n", 2*testState.handCount[thisPlayer]); 
	printf("Running updateCoins()\n"); 

	// Runn update Coins with 0 bonus
	updateCoins(thisPlayer, &testState, 0); 
	printf("Coins After updateCoins() = %d\n", testState.coins); 

	assert(2*testState.handCount[thisPlayer],testState.coins); 

	// Generate Random bonus from 1-10 
	randomBonus =1+(rand() %10); 
	printf("Adding %d Bonus\n", randomBonus); 

	i = testState.coins + randomBonus; 
	printf("Expected Coins After %d Bonus : %d\n",randomBonus, i); 
	
	printf("Running UpdateCoins()\n"); 
	
	// Run update coin agian with added bonus 
	updateCoins(thisPlayer, &testState, randomBonus); 
	
	printf("Total Coins After updateCoins With Bonus : %d\n", testState.coins); 

	assert(i,testState.coins);

	/////////////////////////////////////////////////////////////////////////////////////
	
	// Copy state into testState
	memcpy(&testState, &state, sizeof(struct gameState)); 

	
	printf("---- Test Case 3 ----\n"); 

	// Set all cards in hand to be gold
	for (a = 0; a < testState.handCount[thisPlayer]; a++){
		testState.hand[thisPlayer][a] = gold;  
	}
	
	printf("Number of Gold Cards In Hand : %d\n", testState.handCount[thisPlayer]); 	
	printf("Expected coins: %d\n", 3*testState.handCount[thisPlayer]); 
	printf("Running updateCoins()\n"); 

	// Runn update Coins with 0 bonus
	updateCoins(thisPlayer, &testState, 0); 
	printf("Coins After updateCoins() = %d\n", testState.coins); 

	assert(3*testState.handCount[thisPlayer],testState.coins);

	// Generate Random bonus from 1-10 
	randomBonus = 1+(rand()%10); 
	printf("Adding %d Bonus\n", randomBonus); 

	i = testState.coins + randomBonus; 
	printf("Expected Coins After %d Bonus : %d\n",randomBonus, i); 
	
	printf("Running UpdateCoins()\n"); 
	
	// Run update coin agian with added bonus 
	updateCoins(thisPlayer, &testState, randomBonus); 
	
	printf("Total Coins After updateCoins With Bonus : %d\n", testState.coins); 

	assert(i,testState.coins); 


	///////////////////////////////////////////////////////////////
	

	// Print total num of tests 
	printf("---- Total Tests ----\n"); 
	printf("Total number of test: 6\n"); 
	printf("Total number of passed test: %d\n", numOfTests); 

	printf("--- End of Unit Test 1 ---\n"); 

	return 0; 
}


