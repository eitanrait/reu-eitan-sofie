#include <stdio.h>
<<<<<<< HEAD
#include <stdlib.h>
#include <time.h>
#include "classification.h"

#define FALSE 0
#define TRUE 1
#define N .33
#define NE .67
#define E 1
#define SE 0
#define S 0
#define SW 0
#define W 0
#define NW 0
#define STAY 0
#define GONE 0
=======
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
//#include <windows.h>
#include "randomwalk.h"
#include "classification.h"

#define SIZE 100
>>>>>>> 25721a5969d6c08dc9c603a98a6c8b7364f60292

typedef struct {
  int i;
  int j;
  char region;
} point_t;

<<<<<<< HEAD
void findPath(point_t * point0, point_t * point1) { 

   int B = point0->i - point1->i;
   int A = point1->j - point0->j;
   int g = 2 * A + B;	// initial biased error
   int diag_inc = 2 * (A + B);
   int right_inc = 2 * A; 
   
   if(g >= 0) {
     // go in y direction
     point0->j++;
     g += diag_inc;
   } else {	// if error is negative
     // go in x direction
     g += right_inc;
   }
   point0->i += 1;	// increment in x direction
   
}

void randomwalk(point_t * point, float prob) {
  if (prob >= 0 && prob < N)
    point->j++;
  else if (prob < NE) {
    point->i++;
    point->j++;
  }
  else if (prob < E)
    point->i++;
  else if ( prob < SE) {
    point->i++;
    point->j--;
  }
  else if (prob < S)
    point->j--;
  else if (prob < SW) {
    point->i--;
    point->j--;
  }
  else if(prob < W)
    point->i--;
  else if (prob < NW) {
    point->i--;
    point->j++;
  }
  else {}
=======
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
// X does random walk
void synthesizeChasingRandom() {
	
	// csv file init
	FILE *fpt;
	fpt = fopen("chasing_random_walk.csv", "w+");
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
  	printf("Y              X\n");
	while (1) {

		// get current location of X
		coordPtr = randomPoint(X.i, X.j, prob);
		X.i = *coordPtr;
		X.j = *(coordPtr + 1);

		// get new line
		findPath(Y.i, Y.j, X.i, X.j);

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

		sleep(1); 	// sleep for 1 second "time driven simulation"

	}

}

// chasing while X goes diagonally up
// csv file output
void synthesizeChasingDiagonal() {
	
	// csv file init
	FILE *fpt;
	fpt = fopen("chasing_diagonal1.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}
	fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");

  	printf("Y              X\n");
  	int t = 0;
	while (1) {

		// get current location of X
		X.i = X.i + 1;
		X.j = X.j + 1;

		// get new line
		findPath(Y.i, Y.j, X.i, X.j);

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

		// check for breaking 
		if ((Y.i == X.i && Y.j == X.j) || t > 50) {
			break;
		}

		sleep(1); 	// sleep for 1 second "time driven simulation"
		t++;

	}

}

void synthesizeChasingStraightUp() {

	// csv file init
	FILE *fpt;
	fpt = fopen("chasing_straight_up.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}
	fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");

  	printf("Y              X\n");
  	int t = 0;
	while (1) {

		// get current location of X
		X.j = X.j + 1;

		// get new line
		findPath(Y.i, Y.j, X.i, X.j);

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

		// check for breaking 
		if ((Y.i == X.i && Y.j == X.j) || t > 60) {
			break;
		}

		sleep(1); 	// sleep for 1 second "time driven simulation"
		t++;

	}

>>>>>>> 25721a5969d6c08dc9c603a98a6c8b7364f60292
}


int main() {

	// initial points of Boat X and Y
	// note that Boat Y is chasing X 
	// thus Y.i < X.i because we are using Brenenham's algorithm
<<<<<<< HEAD
	point_t X;
	point_t Y;
	float prob;
	int halt = FALSE;
=======
>>>>>>> 25721a5969d6c08dc9c603a98a6c8b7364f60292

	Y.i = 10;
	Y.j = 10;
	X.i = 44;
	X.j = 33;
<<<<<<< HEAD
	
	srand(time(0));
	prob = (rand() % 100)*.01;

	printf("Y.i:%d, Y.j%d, X.i:%d, X.j:%d\n", Y.i, Y.j, X.i, X.j);

	while(halt == FALSE) {	  
	  findPath(&Y, &X);  
	  randomwalk(&X, prob);
	  prob = (rand() % 100)*.01;
	  printf("Y.i:%d, Y.j%d, X.i:%d, X.j:%d\n", Y.i, Y.j, X.i, X.j);
	  if (Y.i >= X.i || Y.j >= X.j)
	    halt = TRUE;
	}
	
=======

	// seed time
	srand(0);

	//synthesizeChasingRandom();
	//synthesizeChasingDiagonal();
	synthesizeChasingStraightUp();	
>>>>>>> 25721a5969d6c08dc9c603a98a6c8b7364f60292
	return 0;

}

