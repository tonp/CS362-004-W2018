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
int numOfCorrectCards = 0;  
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


/* Name : testAdventurer()
 * Param : struct gameState testState, state, int player, int kingdom[]
 * This function tests the adventurere card effect
 */
void randomAdventurer(struct gameState* testState, int player, int kingdom[]){

	// Init variables
	int a,randomCoin1,randomCoin2, currentCopper, currentSilver, currentGold,
	expectedCopper,expectedSilver,expectedGold, resultGold,resultSilver,resultCopper;
	expectedCopper = 0; 
	expectedSilver = 0; 
	expectedGold = 0; 
	currentCopper = 0;
	currentSilver =0;
	currentGold = 0;
	resultCopper = 0; 
	resultSilver = 0; 
	resultGold = 0;

	// Set deckcount
	int deckCount = testState->deckCount[player]; 
 
	// Set random coin value 
	randomCoin1 = (rand() %(6 + 1 - 4)) + 4;  
	randomCoin2 =(rand() %(6 + 1 - 4)) + 4;  

	// Set Deck to have two random treasure cards 
	testState->deck[player][0] = randomCoin1; 
	testState->deck[player][1] = randomCoin2; 

	// Add up current treasure in hand
	for (a = 0; a < 5; a++){
		if (testState->hand[player][a] == copper){ currentCopper++; }
		if (testState->hand[player][a] == silver){ currentSilver++;}
		if (testState->hand[player][a] == gold){ currentGold++; }
	}
	
	// Set expected Coins	
	if (randomCoin1 == copper){
		expectedCopper = 1; 
	}
	else if(randomCoin1 == silver){
		expectedSilver = 1; 
	}
	else if (randomCoin1 == gold){
		expectedGold = 1; 
	}

	if (randomCoin2 == copper){
		expectedCopper += 1; 
	}
	else if(randomCoin2 == silver){
		expectedSilver += 1; 
	}
	else if (randomCoin2 == gold){
		expectedGold += 1; 
	}

	// Add up all expected coins. 
	expectedCopper = expectedCopper + currentCopper; 
	expectedGold = expectedGold + currentGold; 
	expectedSilver = expectedSilver + currentSilver; 

	// Call cardEffect 
	cardEffect(adventurer, 0,0,0,testState,0,0);  

	 
	// Add up current treasure in handi

	for (a = 0; a < testState->handCount[player]; a++){
		if (testState->hand[player][a] == copper){ resultCopper++; }
		if (testState->hand[player][a] == silver){ resultSilver++;}
		if (testState->hand[player][a] == gold){ resultGold++; }
	}

	int t = 0; 
	if (resultCopper == expectedCopper){
		numOfCorrectCopper++; 
		t++; }
	if(resultSilver == expectedSilver){
		numOfCorrectSilver++; 
		t++; }
	if(resultGold == expectedGold){
		numOfCorrectGold++; 
		t++; 
	}

	// If all three coins are counted correctly
	if (t == 3){
		numOfTests++; 
	}
 
	// If draw correct number of cards
	if(testState->handCount[player] == 6){
		numOfCorrectCards++; 
	}

	// If Deck count is less 
	if (testState->deckCount[player] == deckCount-2){
		correctDeckCount++; 
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
		randomAdventurer(&state, player, kingdom); 
	}

	printf("----- Total -----\n"); 
	printf("Correct Copper Drawn : %d\n", numOfCorrectCopper); 
	printf("Correct Silver Drawn : %d\n", numOfCorrectSilver); 
	printf("Correct Gold Drawn : %d\n", numOfCorrectGold);
	printf("Correct Card Drawn: %d\n", numOfCorrectCards);  
	printf("Correct Deck Count : %d\n", correctDeckCount); 
	printf("Number of Tests : 500000\n"); 
	printf("Number of Tests Passed : %d\n", numOfTests);  
	printf("----- Random Card Test 1 : Adventurer Completed ----\n"); 





	return 0; 
}


