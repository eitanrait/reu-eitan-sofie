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

#define SIZE 5

typedef struct {
  int i;
  int j;
  char region;
} point_t;

point_t points[SIZE];
point_t X;
point_t Y;

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

  points[t].i = x;
  points[t].j = y;

  for (int i=0;i<4;i++) {
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

// finds perpendicular line to Boat X's trajectory
// use to get line from Boat X position
double findPerpendicularSlope(int x_orig, int y_orig, int x_next, int y_next) {

	printf("in findPerpendicularSlope\n");
	double m, m_perp;

	if ((x_next - x_orig) != 0 && (y_next - y_orig) != 0) {
		m = (y_next - y_orig) / (x_next - x_orig);
		m_perp = - (1 / m);
	} else if ((x_next - x_orig) != 0 && (y_next - y_orig) == 0) {
		// slope is horizontal since no change in y
		// perendicular slope is vertical

	} else {
		// slope is vertical since no change in x
		// so perpendicular slope is horizontal (0)
		m_perp = 0;
	}

	return m_perp;
}

int checkBoatY(int x_orig, int y_orig) {

	printf("in checkBoatY\n");

	double slope = findPerpendicularSlope(x_orig, y_orig, X.i, X.j);

	// which side is "behind" Boat X and is Y on that side?
	// To determine which side of the line from A=(x1,y1) to B=(x2,y2) 
	// a point P=(x,y) falls on you need to compute the value:-
	// d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
	// If d<0 then the point lies on one side of the line, and if d>0 then it lies on the other side. 
	// If d=0 then the point lies exactly line.

	int x1 = X.i;
	int y1 = X.j;

	// point B is another point on the perpendicular axis 
	// where it is found by incrementing right 1 and using y - y1 = m(x - x1)
	point_t B;
	B.i = x1 + 1;
	B.j = slope * (B.i - x1) + y1;

	printf("A: (%d, %d)  B: (%d, %d)\n", x1, y1, B.i, B.j);

	double val = ((Y.i - x1) * (B.j - y1)) - ((Y.j - y1) * (B.i - x1));

	printf("val: %f\n", val);

	if (val < 0) {
		return 1;
	} else if (val > 0) {
		return 0;
	} else {
		return 2;	// on the line
	}

}


void followRandomWalk() {

	printf("follow random walk\n");

}

void followDiagonal() {

	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/follow_diagonal.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}

	fprintf(fpt, "X.i, X.j, Y.i, Y.j, slope\n");

	printf("follow diagonal\n");
  	printf("Y      X\n");
  	printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);	// initial point
  	int t = 0;
  	int behind = 0;	// 0 is false, 1 is true
  	int lastx;
  	int lasty;

	while (1) {

		// get current location of X
		lastx = X.i;
		lasty = X.j;
		//updateX('d', t);
		X.i +=1;
		X.j +=1;

		// find the perpendicular line 
		behind = checkBoatY(lastx, lasty);
		printf("behind: %d\n", behind);

		// check where Y is (which side of the perpendicular is behind the boat)
		// if Y is behind the boat X, move towards dividing line
		findPath(Y.i, Y.j, X.i, X.j);	

		// if Y is in front of X, stay in place for now

		// could check if first invisible
		Y.i = points[1].i;
		Y.j = points[1].j;

		// check the zones 
		// maybe need to change this concept
		// A is pretty much just X since Y is trying to get to X
		Y.region = inPolarRegion(Y.i, Y.j);
		X.region = inPolarRegion(X.i, X.j);
		
		printf("%c: %d, %d   %c: %d, %d  %d\n", Y.region, Y.i, Y.j, X.region, X.i, X.j, t);
		fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file

		// check for breaking 
		if ((Y.i == X.i && Y.j == X.j) || t > 1000) {
			break;
		}

		//sleep(1); 	// sleep for 1 second "time driven simulation"
		t++;

	}


}

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
	followRandomWalk();
	initPoint();
	followDiagonal();

	return 0;

}

// to compile
// gcc -Wall following.c classification.c randomwalk.c -lm -o follow
