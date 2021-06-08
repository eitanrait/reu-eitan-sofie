#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include "chase_static_point.h"	// moved findLine() to this file
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

// use the Bresenham algorithm for drawing a line
// to find the fastest pasth from pixel a to b 
// assuming x0 < x1
void findPath(int x0, int y0, int x1, int y1) { 
    int A, B, g, x, y, t;

    t = 0;
 	B = x0 - x1;
	A = y1 - y0;
 
	x = x0;
	y = y0;
 
	g = 2 * A + B;	// initial biased error
	int diag_inc = 2 * (A + B);
	int right_inc = 2 * A; 
 
	while (x <= x1 && t < SIZE) {
		points[t].i = x;
		points[t].j = y;

		if(g >= 0) {

			// go in y direction
			y = y + 1;
			g = g + diag_inc;

		} else {	// if error is negative

			// go in x direction
			g = g + right_inc;

		}
		x = x + 1;	// increment in x direction
		t = t + 1;	// increment array index

	}


}

// inputs: int Y_x, int Y_y, int X_x, int X_y
// using global variables point_t X and Y for inputs atm 
void synthesizeChasing() {
	
	// calls findPath() which modifies points to get a new line 
	// X can move with a random walk
	srand(time(0));
  	float prob = (rand() % 100) *.01;

  	//int X_coord[2];
  	int* coordPtr;
  	int t = 0;	// for testing
  	printf("Y       X\n");
	while (Y.i < X.i && t < SIZE) {

		// get current location of X
		coordPtr = randomPoint(X.i, X.j, prob);
		X.i = *coordPtr;
		X.j = *(coordPtr + 1);

		// get new line
		findPath(Y.i, Y.j, X.i, X.j);
		// could check if first invisible
		Y.i = points[1].i;
		Y.j = points[1].j;
		printf("%d, %d  %d, %d\n", Y.i, Y.j, X.i, X.j);

		// check the zones 

		
		prob = (rand() % 100) *.01;
		t++;


	}

}

int main() {

	// initial points of Boat X and Y
	// note that Boat Y is chasing X 
	// thus Y.i < X.i because we are using Brenenham's algorithm

	// Y is in B and X is in A
	Y.i = 1600;
	Y.j = 2500;
	X.i = 2047;
	X.j = 2047;

	// seed time
	srand(time(0));

	synthesizeChasing(Y.i, Y.j, X.i, X.j);	
	return 0;

}

