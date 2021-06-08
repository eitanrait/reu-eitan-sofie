#include <stdio.h>

#define SIZE 25

typedef struct {
  int i;
  int j;
  char visible[11];
} point_t;

point_t points[SIZE];

// use the Bresenham algorithm for drawing a line
// to find the fastest pasth from pixel a to b 
point_t* findPath(int x0, int y0, int x1, int y1) { 
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

	return points;

}

void findNextPointOnLine(int x0, int y0, int x1, int y1) {
	int A, B, g, x, y, t;

    t = 0;
 	B = x0 - x1;
	A = y1 - y0;
 
	x = x0;
	y = y0;
 
	g = 2 * A + B;	// initial biased error
	int diag_inc = 2 * (A + B);
	int right_inc = 2 * A; 

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


// main to test the function findPath()
int main() {
	// call draw line with two points
	// find the path from p1 to p2 assuming p1.x < p2.x and slope is 0 < m <= 1
	// (10, 10) -> (25, 10)
	findPath(10, 10, 25, 20);
	for (int k = 0; k < SIZE; k++) {
		printf("%d, %d\n", points[k].i, points[k].j);
	}

	return 0;
}

