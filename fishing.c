// synthesize fishing movement 
// seemingly random walk in one region
// later we will use fishing movement to detect fishing
// boat U fishing and V follows
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "randomwalk.h"
#include "classification.h"

#define SIZE 16

typedef struct {
  int i;
  int j;
  char region;
} point_t;

point_t points[SIZE];
point_t u;

void fishing() {

	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/fishing_sim.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}
	fprintf(fpt, "U.i, U.j\n");

	float prob = (rand() % 100) *.01;
	int t = 0;
	// U is boat that does fishing
	while(1) {
		
		// change between random walk in a one place 
		// move to next fishing spot
		// look up fishing patterns

		printf("%d, %d  %d\n", u.i, u.j, t);
		fprintf(fpt, "%d, %d\n", u.i, u.j);	// print to csv file

  		if (t > 600) {
  			break;
  		}

  		prob = (rand() % 100) *.01;
  		t++;
	}

}

// used in following.c and chasing.c to simulate next movement of a fishing boat
int* fishingPoint(int x, int y, float prob, int t) {

}

int main() {

	fishing();
	return 0;
}

// to compile
// gcc -Wall fishing.c randomwalk.c classification.c -lm -o fish
