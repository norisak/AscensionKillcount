#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_SIGNETS 6
#define NUM_ATTEMPTS 10000
#define NUM_CROSSBOWS 1
// Uncomment below to show debug print messages
//#define DEBUG 1 


int min(int *array, size_t size){
	int m = array[0];

	for (int i = 1; i < size; ++i){
		if (array[i] < m){
			m = array[i];
		}
	}
	return m;
}


int roll_keystone(){
	// Gets the more significant bits from rand() as they are "more random".
	return ((rand() >> 9) & 0b111111) == 0;;  // Has a 1/64 chance of returning 1
}


int roll_signet(){
	return (rand() % 50) == 0;  // Has a ~1/50 chance of returning 1
}


int rand_signet(){
	return rand() % NUM_SIGNETS;
}


void print_array(int* array, size_t size){
	for(int i = 0; i < size; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");
}


void reset(int **kc, int **signet_counts){
	free(*kc);
	free(*signet_counts);
	*signet_counts = calloc(NUM_SIGNETS, sizeof(int));
	*kc = calloc(1, sizeof(int));
}


void get_ascension_crossbow(int *kc, int *signet_counts){
	// Set the required signets to one more than what we have the least of. 
	// This will allow us to create one more crossbow.
	int required_signets = min(signet_counts, NUM_SIGNETS) + 1;
	while (1){
		// Kill an ascension creature, and roll for a keystone
		*kc += 1;
		if (roll_keystone()){
			// Pick a random signet/keystone
			int signet_index = rand_signet();

			// Kill a Legio and see if we get a signet
			if (roll_signet()){
				signet_counts[signet_index] += 1;
				
				// Check if we have enough signets to make a crossbow
				if (min(signet_counts, NUM_SIGNETS) >= required_signets){
					#ifdef DEBUG
						printf("Done at %d as we got a keystone_index = %d\n", *kc, signet_index);
						printf("Signet counts: ");
						print_array(signet_counts, NUM_SIGNETS);
					#endif
					return;
				}
			}
		}
	}
}


int main(){

	int *signet_counts = calloc(NUM_SIGNETS, sizeof(int));
	int *kc = calloc(1, sizeof(int));

	for (int i = 0; i < NUM_ATTEMPTS; ++i){
		// Simulate killing ascension creatures until we get the desired amount of crossbows
		for (int j = 0; j < NUM_CROSSBOWS; ++j){
			get_ascension_crossbow(kc, signet_counts);
		}
		// Print the kc
		printf("%d\n",*kc);
		// Reset the kc and amount of signets for the next attempt.
		reset(&kc, &signet_counts);
	}

	free(signet_counts);
	free(kc);
}