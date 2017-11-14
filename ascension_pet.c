#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_LEGIOS 6
#define NUM_ATTEMPTS 100000
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

int roll_pet(int *legio_kc){
	int drop_rate = 1000;
	int thresholds = *legio_kc / 1200;
	if (thresholds>9)
		thresholds = 9;
	drop_rate /= (1 + thresholds);
	return (rand() % drop_rate) == 0;  // Has a 1/1000 chance of returning 1, with a threshold of 1200
}


int rand_signet(){
	return rand() % NUM_LEGIOS;
}


void print_array(int* array, size_t size){
	for(int i = 0; i < size; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");
}


void reset(int **kc, int **signet_counts, int **legio_kc){
	free(*kc);
	free(*legio_kc);
	free(*signet_counts);
	*signet_counts = calloc(NUM_LEGIOS, sizeof(int));
	*kc = calloc(1, sizeof(int));
	*legio_kc = calloc(1, sizeof(int));
}

void get_all_pets(int *kc, int *pet_counts, int *legio_kc){
	// Set the required pets to one
	int required_pets = 1;
	while (1){
		// Kill an ascension creature, and roll for a keystone
		*kc += 1;
		if (roll_keystone()){
			// Pick a random legio
			int legio_index = rand_signet();
			*legio_kc += 1;

			// Kill a Legio and see if we get a pet
			if (roll_pet(legio_kc)){
				pet_counts[legio_index] += 1;
				
				// Check if we have enough pets
				if (min(pet_counts, NUM_LEGIOS) >= required_pets){
					#ifdef DEBUG
						printf("Done at %d as we got a keystone_index = %d\n", *kc, legio_index);
						printf("Signet counts: ");
						print_array(pet_counts, NUM_LEGIOS);
					#endif
					return;
				}
			}
		}
	}
}


int main(){

	int *pet_counts = calloc(NUM_LEGIOS, sizeof(int));
	int *kc = calloc(1, sizeof(int));
	int *legio_kc = calloc(1, sizeof(int));

	for (int i = 0; i < NUM_ATTEMPTS; ++i){
		// Simulate killing ascension creatures until we get the desired amount of crossbows
		get_all_pets(kc, pet_counts, legio_kc);
		// Print the kc
		printf("%d\n",*kc);
		// Reset the kc and amount of signets for the next attempt.
		reset(&kc, &pet_counts, &legio_kc);
	}

	free(pet_counts);
	free(kc);
	free(legio_kc);
}