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

// returns the sign of a - b
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
void findPath(int x1, int y1, int x2, int y2) {
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

void followRandomWalk() {

	printf("follow random walk\n");


}

void followDiagonal() {

	printf("follow diagonal path\n");

}


int main() {

	// seed time
	srand(0);

	initPoint();
	followRandomWalk();
	followDiagonal();

	return 0;

}

// to compile
// gcc -Wall following.c classification.c randomwalk.c -o follow
