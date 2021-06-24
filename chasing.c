// to compile
// gcc -Wall chasing.c classification.c randomwalk.c -o chase

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "driver.h"

point_t points[DEFAULT_SIZE];


// inputs: int Y_x, int Y_y, int X_x, int X_y
// using global variables point_t X and Y for inputs atm 
// X does random walk
void chasingRandom() {
	
	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/chasing_random_walk.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}
	fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");

	// calls findPath() which modifies points to get a new line 
	// X can move with a random walk
  	float prob = (rand() % 100) *.01;

  	int* coordPtr;
  	int t = 0;	// for testing
  	printf("chasing 'skewed' random\n");
  	printf("Y              X\n");
	while (1) {

		// get current location of X
		coordPtr = randomPoint(X.i, X.j, prob);
		X.i = *coordPtr;
		X.j = *(coordPtr + 1);

		// get new line
		findPathE(Y.i, Y.j, X.i, X.j);

		// could check if first invisible
		Y.i = points[1].i;
		Y.j = points[1].j;

		// check the zones 
		// maybe need to change this concept
		// A is pretty much just X since Y is trying to get to X
		Y.region = inRegion(Y.i, Y.j);
		X.region = inRegion(X.i, X.j);
		
		printf("%c: %d, %d  %c: %d, %d\n", Y.region, Y.i, Y.j, X.region, X.i, X.j);
		fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file
		prob = (rand() % 100) *.01;
		t++;

		// check for breaking 
		if (Y.i == X.i && Y.j == X.j) {
			break;
		}

		//sleep(1); 	// sleep for 1 second "time driven simulation"

	}

}

// chasing while X goes diagonally up
// csv file output
void chasingDiagonal() {
	
	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/chasing_diagonal.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}

	fprintf(fpt, "X.i, X.j, Y.i, Y.j, slope\n");

	printf("chase diagonal\n");
  	printf("Y      X\n");
  	printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);	// initial point
  	int t = 0;

	while (1) {

		// get current location of X
		updateX('d', t);
		
		// not worrying about speed
		//X.i += 1;
		//X.j += 1;

		// get new line
		// get new line every other time
/*
		if (t%2 == 1) {
			findPathE(Y.i, Y.j, X.i, X.j);
		}
		*/
		findPathE(Y.i, Y.j, X.i, X.j);

		// could check if first invisible
		Y.i = points[1].i;
		Y.j = points[1].j;

		// check the zones 
		// maybe need to change this concept
		// A is pretty much just X since Y is trying to get to X
		Y.region = inRegion(Y.i, Y.j);
		X.region = inRegion(X.i, X.j);
		
		printf("%d, %d   %d, %d  %d\n", Y.i, Y.j, X.i, X.j, t);
		fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file

		// check for breaking 
		if ((Y.i == X.i && Y.j == X.j) || t > 1000) {
			break;
		}

		//sleep(1); 	// sleep for 1 second "time driven simulation"
		t++;

	}

}

void chasingStraightUp() {

	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/chasing_straight_up.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}

	fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");

	printf("chase straight up\n");
  	printf("Y      X\n");
  	printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);	// initial point
  	int t = 0;

	while (1) {

		// get current location of X
		updateX('u', t);

		// not worrying about speed
		//X.j += 1;

		if ((Y.i+1 == X.i) && (Y.j + 1 == X.j)) {
			printf("directly diagonal\n");
			// should stop the program?
		} 

		// get new line every other time
		//if (t%2 == 1) {
			findPathE(Y.i, Y.j, X.i, X.j);
		//}
		//findPathE(Y.i, Y.j, X.i, X.j);

		// could check if first invisible
		Y.i = points[1].i;
		Y.j = points[1].j;

		// check the zones 
		// maybe need to change this concept
		// A is pretty much just X since Y is trying to get to X
		Y.region = inRegion(Y.i, Y.j);
		X.region = inRegion(X.i, X.j);
		
		printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);
		fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file

		// check for breaking 
		if ((Y.i == X.i && Y.j == X.j) || t > 1500) {	// no cut off for time
			break;
		}

		//sleep(1); 	// sleep for 1 second "time driven simulation?"
		t++;

	}

}

void chasingStraightDown() {

	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/chasing_straight_down.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}
	fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");

	printf("chase straight down\n");
  	printf("Y      X\n");
  	printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);	// initial point
  	int t = 0;

	while (1) {

		// get current location of X
		updateX('v', t);

		// not worrying about speed
		//X.j -= 1;

		if (((Y.i+1 == X.i) && (Y.j + 1 == X.j)) || t > 1500) {
			printf("directly diagonal\n");
			// should stop the program?
		} 

		// get new line
		// get new line every other time
		//if (t%2 == 1) {
			findPathE(Y.i, Y.j, X.i, X.j);
		//}
		//findPathE(Y.i, Y.j, X.i, X.j);

		// could check if first invisible
		Y.i = points[1].i;
		Y.j = points[1].j;

		// check the zones 
		// maybe need to change this concept
		// A is pretty much just X since Y is trying to get to X
		Y.region = inRegion(Y.i, Y.j);
		X.region = inRegion(X.i, X.j);
		
		printf("%d, %d   %d, %d  %d\n", Y.i, Y.j, X.i, X.j, t);
		fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file

		// check for breaking 
		if ((Y.i == X.i && Y.j == X.j) || t > 1500) {	// no cut off for time
			break;
		}

		//sleep(1); 	// sleep for 1 second "time driven simulation?"
		t++;

	}

}

int main() {

	// seed time
	srand(0);

	//initPoint();
	//chasingRandom();
	initPoint();
	chasingDiagonal();
	initPoint();
	chasingStraightUp();	
	initPoint();
	chasingStraightDown();

	return 0;

}

