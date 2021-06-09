#include <stdio.h>
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

typedef struct {
  int i;
  int j;
  char region;
} point_t;

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
}

int main() {

	// initial points of Boat X and Y
	// note that Boat Y is chasing X 
	// thus Y.i < X.i because we are using Brenenham's algorithm
	point_t X;
	point_t Y;
	float prob;
	int halt = FALSE;

	Y.i = 10;
	Y.j = 10;
	X.i = 44;
	X.j = 33;
	
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
	
	return 0;

}

