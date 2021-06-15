// to compile
// gcc -Wall chasing.c classification.c randomwalk.c -o chase

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

void updateX(char s, int t) {

	if (s == 'u') {		// straight up

		// slow down the movement of X by changing pos every other time unit 
		if (t%2 == 1) {		// every other step
			X.j = X.j + 1;	// move up
		}

		/*
		if (X.i == X.j) {	// if the current point is on the diagonal
			// start moving diagonally to side
			X.i++;
		}
		*/

	} else if (s == 'd') {	// diagonally initially

		if (t%2 == 1) {
			X.i = X.i + 1;
			X.j = X.j + 1;
		}

		/*
		if (X.i == X.j) {	// if the current point is on the diagonal
			// start moving diagonally up
			X.i++;
		}
		*/

	} else if (s == 'v') {	// straight down

		if (t%2 == 1) {
			X.j = X.j - 1;
		}

	}

}

// got from 
// https://www.programmersought.com/article/58075286669/
// to check if any difference when we take into account the magintude slopes
void MyLine(int xs, int ys, int xe, int ye)
{

    int x = xs;
	int y = ys;
	int dx = abs(xe - xs);
	int dy = abs(ye - ys);
	int s1 = xe > xs ? 1 : -1;
	int s2 = ye > ys ? 1 : -1;
	int t = 0;
 
	 bool interchange = false; // No interchange by default dx, dy
	 if (dy> dx) // When the slope is greater than 1, dx and dy are swapped
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = true;
	}
 
	int e = 2 * dy - dx;
	for(int i = 0; i <= dx; i++)	// dx
	{
		points[t].i = x;
		points[t].j = y;
		t++;
		if (e >= 0)
		{
			 if (!interchange) // When the slope is <1, select the upper and lower pixels
				y += s2;
			 else // When the slope> 1, select the left and right pixels
				x += s1;
			e -= 2 * dx;
		}
		if (!interchange)
			 x += s1; // When the slope <1, select x as the step size
		else
			 y += s2; // When the slope> 1, select y as the step size
		e += 2 * dy;
	}
}

// copy eitan's bresenham
int Sign(int a, int b) {
  int c;
  c = a-b;

  if(c > 0)
    return 1;
  else if(c < 0)
    return -1;
  else
    return 0;
}

// use the Bresenham algorithm for drawing a line                                                                                                                                                  
// to find the fastest path from pixel a to b                                                                                                                                                     
void findPathE(int x1, int y1, int x2, int y2) {
  int A, B, E, x, y, t, deltX, deltY, s1, s2, temp, interchange;
  t = 0;
  x = x1;
  y = y1;
  deltX = abs(x2-x1);
  deltY = abs(y2-y1);
  s1 = Sign(x2,x1);
  s2 = Sign(y2,y1);
  
  if(deltY > deltX) {
    temp = deltX;
    deltX = deltY;
    deltY = temp;
    interchange = 1;
  }
  else {
    interchange = 0;
  }

  E = 2 * deltY - deltX;
  A = 2 * deltY;
  B = 2 * deltY - 2 * deltX;

  //int diag_inc = 2 * (A + B);                                                                                                                                                                     
  //int right_inc = 2 * A;                                                                                                                                                                          

  points[t].i = x;
  points[t].j = y;

  for (int i=0;i<deltX;i++) {
    if ( E < 0 ) {
      if ( interchange == 1 ) {
        y = y + s2;
      }
      else {
        x = x + s1;
      }
      E = E + A;
    }
    else {
      y = y + s2;
      x = x + s1;
      E = E + B;
    }
    
    t++;
    points[t].i = x;
    points[t].j = y;
  }
}

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

	fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");

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
		//findPath(Y.i, Y.j, X.i, X.j);
		findPathE(Y.i, Y.j, X.i, X.j);

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
		if ((Y.i == X.i && Y.j == X.j)) {
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

		if ((Y.i+1 == X.i) && (Y.j + 1 == X.j)) {
			printf("directly diagonal\n");
			// should stop the program?
		} 

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
		
		printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);
		fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file

		// check for breaking 
		if ((Y.i == X.i && Y.j == X.j)) {	// no cut off for time
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

		if ((Y.i+1 == X.i) && (Y.j + 1 == X.j)) {
			printf("directly diagonal\n");
			// should stop the program?
		} 

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
		
		printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);
		fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file

		// check for breaking 
		if ((Y.i == X.i && Y.j == X.j)) {	// no cut off for time
			break;
		}

		//sleep(1); 	// sleep for 1 second "time driven simulation?"
		t++;

	}

}

// initial points of Boat X and Y
// note that Boat Y is chasing X 
// thus Y.i < X.i because we are using Brenenham's algorithm
void initPoint() {
	Y.i = 0;
	Y.j = 0;
	X.i = 400;
	X.j = 300;
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
	//initPoint();
	//chasingStraightDown();

	return 0;

}

