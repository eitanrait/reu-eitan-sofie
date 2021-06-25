// watchRandomWalk.c
// 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "randomwalk.h"
#include "classification.h"

#define SIZE 16
#define STEPS 200

typedef struct {
  int i;
  int j;
  char region;
} point_t;

point_t points[SIZE];
point_t u;	// static boat or can also do random walk (watching v do walk)
point_t v;	// boat that is doing random walk

void updateU(char s, int t) {

	if (s == 'u') {		// straight up

		// slow down the movement of X by changing pos every other time unit 
		if (t%2 == 1) {		// every other step
			u.j = u.j + 1;	// move up
		}

		/*
		if (X.i == X.j) {	// if the current point is on the diagonal
			// start moving diagonally to side
			X.i++;
		}
		*/

	} else if (s == 'd') {	// diagonally initially

		if (t%2 == 1) {
			u.i = u.i + 1;
			u.j = u.j + 1;
		}

		/*
		if (X.i == X.j) {	// if the current point is on the diagonal
			// start moving diagonally up
			X.i++;
		}
		*/

	} else if (s == 'v') {	// straight down

		if (t%2 == 1) {
			u.j = u.j - 1;
		}

	} else if (s == 'r') {	// random walk

		int* coordPtr;



	} else if (s == 's') {	// static

		// boat U does not change position

	}

}

void simulate(char U_movement) {

	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/watch_random_walk_static.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}

	float prob = (rand() % 100) *.01;

  	int* coordPtr;
  	int t = 0;

  	while (t < STEPS) {

  		// get new current location of V
		coordPtr = randomPoint(v.i, v.j, prob);
		v.i = *coordPtr;
		v.j = *(coordPtr + 1);

		updateU(U_movement, t);

		fprintf(fpt, "%d, %d, %d, %d\n", u.i, u.j, v.i, v.j);	// print to csv file

		prob = (rand() % 100) *.01;
		t++;

  	}

}

void initPoint() {
  v.i = 300;
  v.j = 200;
  u.i = 1000;
  u.j = 500;
}

int main() {

	// seed time
	srand(0);

  	// have V go in random walk and U can be:
	// 's' - static, 'r' - random walk
	initPoint();
  	simulate('s');
  	
	return 0;

}

// to compile
// gcc -Wall watchRandomWalk.c randomwalk.c classification.c -lm -o watch