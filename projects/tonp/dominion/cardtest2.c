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


/* Name : testAdventurer()
 * Param : struct gameState testState, state, int player, int kingdom[]
 * This function tests the adventurere card effect
 */
void testAdventurer(struct gameState* testState, struct gameState* state, int player, int kingdom[]){

	// Init variables
	int a,randomCoin1,randomCoin2, currentCopper, currentSilver, currentGold,
	gainCopper,gainSilver,gainGold; 
	currentCopper = 0;
	currentSilver =0;
	currentGold = 0;

	// Set random coin value
	randomCoin1 = (rand() %(6 + 1 - 4)) + 4;  
	randomCoin2 =(rand() %(6 + 1 - 4)) + 4;  

	printf("Setting deck to have two random tresure cards\n"); 
	testState->deck[player][0] = randomCoin1; 
	testState->deck[player][1] = randomCoin2; 

	// Add up current treasure in hand
	for (a = 0; a < 5; a++){
		if (testState->hand[player][a] == copper){ currentCopper++; }
		if (testState->hand[player][a] == silver){ currentSilver++;}
		if (testState->hand[player][a] == gold){ currentGold++; }
	}


	printf("Player Current Copper Count in hand : %d\n", currentCopper); 
	printf("Player Current Silver Count in hand : %d\n", currentSilver); 
	printf("Player Current Gold Count in hand : %d\n", currentGold);  
	printf("Player Current Hand Count: %d\n", testState->handCount[player]); 

	
	printf("\nRunning Adventurere card effect\n\n"); 
	cardEffect(adventurer, 0,0,0,testState,0,0);  

	// count amount of treasures after
	int afterCopper = 0; 
	int afterSilver = 0; 
	int afterGold = 0; 
	for (a = 0; a < testState->handCount[player]; a++){
		if (testState->hand[player][a] == copper){ afterCopper++; }
		if (testState->hand[player][a] == silver){ afterSilver++;}
		if (testState->hand[player][a] == gold){ afterGold++; }
	}
 
	printf("Player Copper Count After : %d\n", afterCopper); 
	printf("Player Silver Count After : %d\n", afterSilver); 
	printf("Player Gold Count After : %d\n", afterGold); 
	printf("Player Hand Count After : %d\n", testState->handCount[player]); 

	// Count how many treasures obtained
	gainCopper = afterCopper-currentCopper; 
	printf("\nPlayer Gained %d Copper Card\n", gainCopper);

	gainSilver = afterSilver-currentSilver;
	printf("Player Gained %d Silver Card\n", gainSilver); 

	gainGold = afterGold-currentGold; 
	printf("Player Gained %d Gold Card\n", gainGold); 
 
	printf("\nTesting if player hand count has 2 more treasure cards\n"); 
	if(assert(testState->handCount[player], state->handCount[player]+2)){numOfTests++;}
 
	// Calculat total
	int totalC,totalS, totalG; 
	totalC=0; 
	totalS=0; 
	totalG=0; 
	for (a = 0; a < testState->handCount[player]; a++){
		if (testState->hand[player][a] == copper){ totalC++; }
		if (testState->hand[player][a] == silver){ totalS++;}
		if (testState->hand[player][a] == gold){ totalG++; }
	}

	printf("Testing total treasure\n");
	int y=0;
	for(a=0; a<5; a++){
		if (state->hand[player][a] == copper){y+=1;}
		if (state->hand[player][a] == silver){y+=2;}
		if (state->hand[player][a] == gold){y+=3;}
	}
	if(assert(totalS*2+totalG*3+totalC*1, y+gainCopper*1+gainGold*3+gainSilver*2)){numOfTests++;}
 
	// Testing Vitory pile
	printf("Testing Victory : Estate has not changed\n"); 
	if(assert(testState->supplyCount[estate], state->supplyCount[estate])){numOfTests++;}

	printf("Testing Victory : Duchy has not changed\n"); 
	if(assert(testState->supplyCount[duchy], state->supplyCount[duchy])){numOfTests++;}


	printf("Testing Victory : Province has not changed\n"); 
	if(assert(testState->supplyCount[province], state->supplyCount[province])){numOfTests++;}

	// Testing Kingdom pile
	printf("Testing Kingdom Pile has not changed\n"); 
	int i =0;
	for (a =0; a <10; a++){
		if (testState->supplyCount[kingdom[a]] == state->supplyCount[kingdom[a]]){
			i++; 
		}
	}
	if (assert(i, 10)){numOfTests++;}

	// Testing treasure pile
	printf("Testing Copper Supply Has No Change\n"); 
	if(assert(testState->supplyCount[copper], state->supplyCount[copper])){numOfTests++;}
	printf("Testing Silver Supply Has No Change\n"); 	
	if(assert(testState->supplyCount[silver], state->supplyCount[silver])){numOfTests++;}
	printf("Testing Gold Supply Has No Change\n"); 	
	if(assert(testState->supplyCount[gold], state->supplyCount[gold])){numOfTests++;}


	// Testing other player
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

	// Init gameSate
	struct gameState state, testState; 	
	int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
			sea_hag, tribute, smithy};

	// Initit game 
	initializeGame(numPlayers, kingdom, seed, &state); 

	printf("--- Starting Card Test 2: Adventurer ---\n\n\n"); 

	// Copy game state to test case 
	memcpy(&testState, &state, sizeof(struct gameState)); 


	// Call test function
	testAdventurer(&testState, &state, player, kingdom);

	printf("----- Total -----\n"); 
	printf("Total Test Case : 11\n"); 
	printf("Total Test Case Passed : %d\n\n", numOfTests); 
	printf("----- Card Test 2 : Adventurer Completed ----\n"); 





	return 0; 
}


