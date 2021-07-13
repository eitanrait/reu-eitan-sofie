#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "diver.h"
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
void findPath(struct Point * points, int x1, int y1, int x2, int y2) {
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

	for (int i=0;i<SIZE;i++) {
		
		if ( E < 0 ) {
    		if ( interchange == 1 ) {
				y += s2;
	  		} else {
			x += s1;
	  	}
	  	
	  	E += A;
	  	
	} else {
	
	  y += s2;
	  x += s1;
	  E += B;
	
	}

	t++;
	points[t].i = x;
	points[t].j = y;
	
  }
}


// use the Bresenham algorithm for drawing a line
// to find the fastest pasth from pixel a to b 
// assuming x0 < x1
void findPathSofie(struct Point * points, int x0, int y0, int x1, int y1) {

    int A, B, g, t;
    double x, y;
    t = 0;
 	B = x0 - x1;
	A = y1 - y0;
 
	x = x0;
	y = y0;
 
	g = 2 * A + B;	// initial biased error
	int diag_inc = 2 * (A + B);
	int right_inc = 2 * A; 
 
 	printf("\nfinding path -\n");
 	printf("between: (%.0f, %.0f) (%d, %d)\n", x, y, x1, y1);
 	// print slope
 	printf("slope: %f\n", (y1-y)/(x1-x));
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
		printf("t: %d x: %.0f\n", t, x);
		x = x + 1;	// increment in x direction
		t = t + 1;	// increment array index

	}

	if(is_verbose)
		printf("points[0]:%d,%d points[1]:%d,%d points[2]:%d,%d points[3]:%d,%d\n", points[0].i, points[0].j, points[1].i, points[1].j, points[2].i, points[2].j,points[3].i, points[3].j);
 
}

// got from 
// https://www.programmersought.com/article/58075286669/
// to check if any difference when we take into account the magintude slopes
void MyLine(struct Point * points, int xs, int ys, int xe, int ye)
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
