#include "dominion.h"
#include "dominion_helpers.h" 
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 


// Init global variable
int correctDeckCount = 0;
int numOfTests = 0; 
int numOfCorrectCopper = 0; 
int numOfCorrectSilver = 0; 
int numOfCorrectGold = 0;

 
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
		printf("TEST FAILED\n\n"); 
		return 0; 
	}
}


/* Name : testAdventurer()
 * Param : struct gameState testState, state, int player, int kingdom[]
 * This function tests the adventurere card effect
 */
void randomUpdateCoins(struct gameState* testState, int player, int kingdom[]){

	int numCopper,numSilver,numGold = 0;	
	int sets = 0; 
	testState->coins = 0; 

	// Set random handcount
	testState->handCount[player] = 1+(rand()%MAX_HAND); 
	int b; 
	for (b =0; b < testState->handCount[player]; b++){
		testState->hand[player][b] = 7+(rand() %26); 
	}

	// Set random number of copper in hand 
	numCopper = 1+(rand()% testState->handCount[player]); 

	// Set random number of coins
	int a = 0; 
	while(a != numCopper){
		
		// Generate number of copper coins
		testState->hand[player][a] = copper; 
		a++;	
	}

	// Generate random bonus
	int randomBonus = 1+(rand() % 100); 
 
	// Call update coins
	updateCoins(player,testState, randomBonus); 

	// Check correct
	if(assert(numCopper+randomBonus, testState->coins)){
		sets++; 
		numOfCorrectCopper++; 
	}

	/////////////////////////////////////////////////////////////////
	testState->coins = 0; 

	// Set random handcount
	testState->handCount[player] = 1+(rand()%MAX_HAND); 
 
	for (b =0; b < testState->handCount[player]; b++){
		testState->hand[player][b] = 7+(rand() %26); 
	}

	// Set random number of silver in hand 
	numSilver = 1+(rand()% testState->handCount[player]); 

	// Set random number of coins
	a = 0; 
	while(a != numSilver){
		
		// Generate number of copper coins
		testState->hand[player][a] = silver; 
		a++;	
	}

	// Generate random bonus
	randomBonus = 1+(rand() % 100); 
 
	// Call update coins
	updateCoins(player,testState, randomBonus); 

	numSilver = numSilver*2;
	// Check correct
	if(assert(numSilver+randomBonus, testState->coins)){
		sets++; 
		numOfCorrectSilver++;
	}

	/////////////////////////////////////////////////////////////////
	testState->coins = 0; 

	// Set random handcount
	testState->handCount[player] = 1+(rand()%MAX_HAND); 
 
	for (b =0; b < testState->handCount[player]; b++){
		testState->hand[player][b] = 7+(rand() %26); 
	}

	// Set random number of Gold in hand 
	numGold = 1+(rand()% testState->handCount[player]); 

	// Set random number of coins
	a = 0; 
	while(a != numGold){
		
		// Generate number of copper coins
		testState->hand[player][a] = gold; 
		a++;	
	}

	// Generate random bonus
	randomBonus = 1+(rand() % 100); 
 
	// Call update coins
	updateCoins(player,testState, randomBonus); 

	// Check correct
	if(assert(numGold*3+randomBonus, testState->coins)){
		sets++; 
		numOfCorrectGold++;
	}

	// Increment numOfTests if all three sets are correct
	if(assert(sets,3)){numOfTests++;}


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

	printf("--- Starting Random Card Test 1 : Adventurer ---\n\n"); 

	// Call test function
	int a; 
	for (a=0; a < 500000; a++){

		// Init gameSate
		struct gameState state;	
		int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

		// Initit game 
		initializeGame(numPlayers, kingdom, seed, &state);  

		// Call test function 
		randomUpdateCoins(&state, player, kingdom);  
	}

	printf("----- Total -----\n"); 
	printf("Correct Copper Counted : %d\n", numOfCorrectCopper); 
	printf("Correct Silver Counted : %d\n", numOfCorrectSilver); 
	printf("Correct Gold Counted : %d\n", numOfCorrectGold);
	printf("Number of Tests : 500000\n"); 
	printf("Number of Tests Passed : %d\n", numOfTests);  
	printf("----- Random Card Test 1 : UpdateCoins() Completed----\n"); 





	return 0; 
}


