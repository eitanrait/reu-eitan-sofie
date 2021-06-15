// start writing following algo here

// what does it mean to be behind X?
// Boat Y is behind X when Y is behind X for a certain amount of time
// Y could just be driving by X for a bit (that is not following)
// need to check for the amount of time

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "randomwalk.h"
#include "classification.h"

#define SIZE 100

typedef struct {
  int i;
  int j;
  char region;
} point_t;

point_t points[SIZE];
point_t X;
point_t Y;

// initial points of Boat X and Y
// note that Boat Y is following X 
// thus Y.i < X.i because we are using Brenenham's algorithm assumption
void initPoint() {
	Y.i = 0;
	Y.j = 0;
	X.i = 400;
	X.j = 300;
}

int main() {

	// seed time
	srand(0);

	initPoint();
	// follow a random walk 
	// follow a straight up walk
	// follow a diagonal

	return 0;

}

// to compile
// gcc -Wall following.c classification.c randomwalk.c -o follow
