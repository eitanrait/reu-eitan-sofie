#include <stdio.h>
#include "chase_static_point.h"

typedef struct {
  int i;
  int j;
  char visible[11];
} point_t;

void synthesizeChasing(int x0, int y0, int x1, int y1) {
	
	// should call findLine() from chase_static_point
	// X can move with a random walk

}

int main() {

	// initial points of Boat X and Y
	// note that Boat Y is chasing X 
	// thus Y.i < X.i because we are using Brenenham's algorithm
	point_t X;
	point_t Y;

	Y.i = 10;
	Y.j = 10;
	X.i = 25;
	X.j = 15;

	synthesizeChasing(Y.i, Y.j, X.i, X.j);	
	return 0;

}

