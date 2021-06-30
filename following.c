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

#define SIZE 16

typedef struct {
  int i;
  int j;
  char region;
} point_t;

point_t points[SIZE];
point_t X;
point_t Y;

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


// use the Bresenham algorithm for drawing a line
// to find the fastest pasth from pixel a to b 
// assuming x0 < x1
void findPathSofie(int x0, int y0, int x1, int y1) { 
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


point_t* findPerpendicularPoint(double last_i, double last_j) {

	point_t B;
	point_t* B_ptr = &B;
	int curr_i = X.i;
	int curr_j = X.j;
	double slope, perp_slope;

	if ((last_i - curr_i != 0) && (last_j - curr_j != 0)) {
		//printf("last: (%f, %f) curr: (%d, %d)\n", last_i, last_j, curr_i, curr_j);
		slope = (curr_j - last_j) / (curr_i - last_i);
		perp_slope = -(1 / slope);
		//printf("slope: %f, perp_slope: %f\n", slope, perp_slope);

		B.i = X.i + 1;
		B.j = perp_slope * (B.i - X.i) + X.j;

	} else if ((last_j - curr_j == 0) && (last_i - curr_i == 0)) {
		// no change in point

		// what to do when X does not move? 
		// let Y keep the same trajectory it did last
		// need to remember the last move Y did
		// or make Y stop moving

		B.i = X.i;
		B.j = X.j;
	
	} else if ((last_j - curr_j == 0)) {
		// no change in y direction
		// slope = 0
		// perpendicular slope is infinity

		B.i = X.i;		// x coordinate stays the same
		B.j = X.j + 1;	// y coordinate increments
	
	} else if ((last_i - curr_i == 0)) {
		// no change in x direction
		// slope = inf
		// perpendicular slope = 0

		B.i = X.i + 1;
		B.j = X.j;

	}
	
	return B_ptr;

}

// constant integers for directions
const int RIGHT = 1, LEFT = -1, ZERO = 0;
 
// A is new X position
// B is another point on the perpendicular
// P is position of boat Y 
int directionOfPoint(point_t A, point_t B, point_t P) {
    // subtracting co-ordinates of point A from
    // B and P, to make A as origin
    B.i -= A.i;
    B.j -= A.j;
    P.i -= A.i;
    P.j -= A.j;
 
    // Determining cross Product
    int cross_product = B.i * P.j - B.j * P.i;
 
    // return RIGHT if cross product is positive
    if (cross_product > 0)
        return RIGHT;
 
    // return LEFT if cross product is negative
    if (cross_product < 0)
        return LEFT;
 
    // return ZERO if cross product is zero.
    return ZERO;
}

int YIsBehind(double last_i, double last_j) {

	// A is new X position
	// find another point (B) on the perpendicular
	point_t* nextPoint = findPerpendicularPoint(last_i, last_j);

	point_t B;
	B.i = nextPoint->i;
	B.j = nextPoint->j;

	point_t lastX;
	lastX.i = last_i;
	lastX.j = last_j;

	// compare with pos of Y for direction of Y in respect to the perp line
	int directionY;
	int directionLastX;

	// if no change in X pos, return 2
	if (X.i == B.i && X.j == B.j) {
		return 2;
	}

	directionY = directionOfPoint(X, B, Y);
	directionLastX = directionOfPoint(X, B, lastX);

	//printf("X: (%d, %d)  B: (%d, %d)  directionY: %d  directionLastX: %d\n", X.i, X.j, B.i, B.j, directionY, directionLastX);

	if (directionLastX == directionY) {
		return 1;
	}

	return 0;

}

void updateX(char s, int t, int prob) {
  int * coordPtr;
  printf("\n%c %d\n",s,t);
  if(t%2 == 0) {
    if(s == 'r') {	// random walk
      coordPtr = randomPoint(X.i, X.j, prob);
      X.i = *coordPtr;
      X.j = *(coordPtr + 1);
    } else if (s == 'u') {    // straight up
      X.j += 1;  // move up
    } else if (s == 'd') { // diagonally initially
      X.i += 1;
      X.j += 1;
    } else if (s == 'v') {  // straight down
      X.j -= 1;
    }
  } 
  //... (can add different movement patterns)
}


void followRandomWalk() {

	printf("follow random walk\n");

	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/follow_random.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}

	fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");

  	printf("Y      X\n");
  	printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);	// initial point
  	int t = 0;
  	int behind = 0;	// 0 - not behind, 1 - behind
  	double last_i, last_j;
  	
  	int* coordPtr;
  	float prob = (rand() % 100) *.01;
  	int noMovement = 2;

  	while (1) {

  		// remember last X position
  		last_i = X.i;
  		last_j = X.j;

  		// update X position
  		coordPtr = randomPoint(X.i, X.j, prob);
		X.i = *coordPtr;
		X.j = *(coordPtr + 1);

  		// check where Y is 
  		behind = YIsBehind(last_i, last_j);

  		// store Y position
  		// check which region boat Y is in
  		Y.region = inPolarRegion(Y.i, Y.j, X.i, X.j);

  		// if boat Y in region A, chase 
  		// if boat Y in region B, chase with stealth
  		// if boat Y in outer regions and behind, disguised walk towards boat X/U
  		// else, stay in place

  		// update prob for Y movement
  		prob = (rand() % 100) *.01;

  		if (behind == 1 && (Y.region == 'a')) {
  			// move Y towards X
  			// get new line towards Boat X/U
			findPathSofie(Y.i, Y.j, X.i, X.j);

			Y.i = points[1].i;
			Y.j = points[1].j;
			noMovement = 2;

  		} else if (behind == 1 && (Y.region == 'b')) {
  			// in region B
  			// every couple tics (will swtich more often to move towards) switch from random walk to move towards
  			noMovement = 2;
  			if (t % 3 == 0) {
  				// random walk
  				coordPtr = randomPoint(Y.i, Y.j, prob);
				Y.i = *coordPtr;
				Y.j = *(coordPtr + 1);

  			} else {
  				// walk towards
  				// walks towards X more often
  				findPathSofie(Y.i, Y.j, X.i, X.j);

				Y.i = points[1].i;
				Y.j = points[1].j;

  			}

  		} else if (behind == 1) {
  			// behind and in regions C and D
  			// every couple tics switch from random walk to move towards
  			noMovement = 2;
  			if (t % 3 == 0) {
  				// walk towards
  				findPathSofie(Y.i, Y.j, X.i, X.j);

				Y.i = points[1].i;
				Y.j = points[1].j;

  			} else {
  				// random walk
  				// random walks more often
  				coordPtr = randomPoint(Y.i, Y.j, prob);
				Y.i = *coordPtr;
				Y.j = *(coordPtr + 1);

  			}

  		} else if (behind == 2) {
  			// no change in X
  			// but Y should continue on its path from last time
  			// which is saved in the points array 
  			
  			if (t == 0) {
  				Y.i = points[1].i;
				Y.j = points[1].j;
  			} else {
  				Y.i = points[noMovement].i;
				Y.j = points[noMovement].j;
			}	
			noMovement++;

  		} else {
  			// stay in place when Y is on the wrong side of the perpendicular line 
  			noMovement = 2;

  		}

  		printf("%d, %d  %d, %d  %d  %c\n", Y.i, Y.j, X.i, X.j, t, Y.region);
		fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file

  		if ((Y.i == X.i && Y.j == X.j)) {	//t > 12000 || 
  			break;
  		}

  		prob = (rand() % 100) *.01;
  		t++;

  	}

}


void followDiagonalPath(char x_activity) {

	printf("follow diagonal path\n");

	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/follow_diagonal.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}

	//fprintf(fpt, "X.i, X.j, Y.i, Y.j, region, t\n");

  	printf("Y      X\n");
  	printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);	// initial point
  	int t = 0;
  	int behind = 0;	// 0 - not behind, 1 - behind
  	double last_i, last_j;
  	
  	int* coordPtr;
  	float prob = (rand() % 100) *.01;
  	findPathSofie(Y.i, Y.j, X.i, X.j);
  	int noMovement = 2;

  	while (1) {

  		// remember last X position
  		last_i = X.i;
  		last_j = X.j;

  		// update X position every two steps (U)
  		/*
     	if (t % 2 == 0) {
  			X.i += 1;
			X.j += 1;
  		}
      	*/
        updateX(x_activity, t, prob);

  		// check where Y is 
  		behind = YIsBehind(last_i, last_j);

  		// store Y position
  		// check which region boat Y is in
  		Y.region = inPolarRegion(Y.i, Y.j, X.i, X.j);

  		// if boat Y in region A, chase 
  		// if boat Y in region B, chase with stealth
  		// if boat Y in outer regions and behind, disguised walk towards boat X/U
  		// else, stay in place

  		// update prob for Y movement
  		prob = (rand() % 100) *.01;
  		printf("behind: %d, region: %c\n", behind, Y.region);

  		if (behind == 1 && (Y.region == 'a')) {
  			// move Y towards X
  			// get new line towards Boat X/U
  			 noMovement = 2;
			   findPathSofie(Y.i, Y.j, X.i, X.j);

			   Y.i = points[1].i;
			   Y.j = points[1].j;

  		} else if (behind == 1 && (Y.region == 'b')) {
  			// in region B
  			// every couple tics (will swtich more often to move towards) switch from random walk to move towards
  			noMovement = 2;
  			if (t % 3 == 0) {
  				// random walk
  				coordPtr = randomPoint(Y.i, Y.j, prob);
				  Y.i = *coordPtr;
				  Y.j = *(coordPtr + 1);

  			} else {
  				// walk towards
  				// walks towards X more often
  				findPathSofie(Y.i, Y.j, X.i, X.j);

				Y.i = points[1].i;
				Y.j = points[1].j;

  			}

  		} else if (behind == 1) {
  			// behind and in regions C and D
  			// every couple tics switch from random walk to move towards
  			noMovement = 2;
  			if (t % 6 == 0 || t % 6 == 1 || t % 6 == 2) {
  				// walk towards
  				printf("finding path\n");
  				findPathSofie(Y.i, Y.j, X.i, X.j);

				  Y.i = points[1].i;
				  Y.j = points[1].j;

  			} else {
  				// random walk
  				// random walks more often
  				printf("random\n");
  				coordPtr = randomPoint(Y.i, Y.j, prob);
				  Y.i = *coordPtr;
				  Y.j = *(coordPtr + 1);

  			}

  		} else if (behind == 2) {
  			// no change in X
  			// but Y should continue on its path from last time
  			// which is saved in the points array   			
  			if (t == 0) {
  				Y.i = points[1].i;
				Y.j = points[1].j;
  			} else {
  				Y.i = points[noMovement].i;
				Y.j = points[noMovement].j;
			}	
			noMovement++;

  		} else {
  			// stay in place
  			noMovement = 2;
  		}

  		printf("%d, %d  %d, %d  %d\n", Y.i, Y.j, X.i, X.j, t);
		  fprintf(fpt, "%d, %d, %d, %d, %c, %d\n", X.i, X.j, Y.i, Y.j, Y.region, t);	// print to csv file

  		if (t > 6000 || (Y.i == X.i && Y.j == X.j)) {
  			printf("break\n");
  			break;
  		}

  		t++;

  	}

}

void followVerticalPath(char x_activity) {

	printf("follow vertical walk\n");

	// csv file init
	FILE *fpt;
	fpt = fopen("csv_files/follow_vertical1.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}

	fprintf(fpt, "X.i, X.j, Y.i, Y.j, region, t\n");

  	printf("Y      X\n");
  	printf("%d, %d   %d, %d\n", Y.i, Y.j, X.i, X.j);	// initial point
  	int t = 0;
  	int behind = 0;	// 0 - not behind, 1 - behind
  	double last_i, last_j;
  	
  	int* coordPtr;
  	float prob = (rand() % 100) *.01;
  	findPath(Y.i, Y.j, X.i, X.j);
  	int noMovement = 2;

  	while (1) {

  		// remember last X position
  		last_i = X.i;
  		last_j = X.j;

  		// update X position every two steps 
  		/*
  		if (t % 2 == 0) {
			X.j += 1;
  		}
  		*/
  		updateX(x_activity, t, prob);

  		// check where Y is 
  		behind = YIsBehind(last_i, last_j);

  		// store Y position
  		// check which region boat Y is in
  		Y.region = inPolarRegion(Y.i, Y.j, X.i, X.j);

  		// if boat Y in region A, chase 
  		// if boat Y in region B, chase with stealth
  		// if boat Y in outer regions and behind, disguised walk towards boat X/U
  		// else, stay in place

  		// update prob for Y movement
  		prob = (rand() % 100) *.01;
  		printf("behind: %d, noMovement: %d, region: %c\n", behind, noMovement, Y.region);

  		if (behind == 1 && (Y.region == 'a')) {
  			// move Y towards X
  			// get new line towards Boat X/U
  			noMovement = 2;
			findPath(Y.i, Y.j, X.i, X.j);

			Y.i = points[1].i;
			Y.j = points[1].j;

  		} else if (behind == 1 && (Y.region == 'b')) {
  			// in region B
  			// every couple tics (will swtich more often to move towards) switch from random walk to move towards
  			noMovement = 2;
  			if (t % 3 == 0) {
  				// random walk
  				coordPtr = randomPoint(Y.i, Y.j, prob);
				Y.i = *coordPtr;
				Y.j = *(coordPtr + 1);

  			} else {
  				// walk towards
  				// walks towards X more often
  				findPath(Y.i, Y.j, X.i, X.j);

				Y.i = points[1].i;
				Y.j = points[1].j;

  			}

  		} else if (behind == 1) {
  			// behind and in regions C and D
  			// every couple tics switch from random walk to move towards
  			noMovement = 2;
  			if (t % 6 == 0 || t % 6 == 1 || t % 6 == 2) {
  				// walk towards
  				printf("finding path\n");
  				findPath(Y.i, Y.j, X.i, X.j);

				Y.i = points[1].i;
				Y.j = points[1].j;

  			} else {
  				// random walk
  				// random walks more often
  				printf("random\n");
  				coordPtr = randomPoint(Y.i, Y.j, prob);
				  Y.i = *coordPtr;
				  Y.j = *(coordPtr + 1);

  			}

  		} else if (behind == 2) {
  			// no change in X
  			// but Y should continue on its path from last time
  			// which is saved in the points array 
  			if (t == 1) {
  				Y.i = points[1].i;
				Y.j = points[1].j;
  			} else {
  				Y.i = points[noMovement].i;
				Y.j = points[noMovement].j;
			}
			noMovement++;	

  		} else {
  			// stay in place
  			noMovement = 2;

  		}

  		printf("%d, %d  %d, %d  %d\n", Y.i, Y.j, X.i, X.j, t);
		fprintf(fpt, "%d, %d, %d, %d, %c, %d\n", X.i, X.j, Y.i, Y.j, Y.region, t);	// print to csv file

  		if (t > 6000 || (Y.i == X.i && Y.j == X.j)) {	//t > 6000 || 
  			printf("break\n");
  			break;
  		}

  		t++;

  	}

}

// initial points of Boat X and Y
// note that Boat Y is following X 
// thus Y.i < X.i because we are using Brenenham's algorithm assumption
void initPoint() {
	Y.i = 0;	// boat V
	Y.j = 700;
	X.i = 800;	// boat U
	X.j = 800;
}

int main() {

	// seed time
	srand(0);

	//initPoint();
	//followRandomWalk();
	//initPoint();
	//followDiagonalPath('u');	// d means boat U/X will go diagonally 
	initPoint();
	followVerticalPath('v');

	return 0;

}

// to compile
// gcc -Wall following.c classification.c randomwalk.c -lm -o follow
