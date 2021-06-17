#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265

// input of i,j coordinate
// determine in which region
// output a,b,c,d accordingly
char inRegion(int i, int j) {

	// region A: (1792, 1792) -> (1792, 2304)
	//           (1792, 2304) -> (2304, 2304)
	// region B: (1536, 1536) -> (2560, 1536)
	//           (1536, 2560) -> (2560, 2560)
	// region C: (1024, 1024) -> (3072, 1024)
	//           (1024, 3072) -> (3072, 3072)
	// region d: (0, 0)       -> (4096, 0)
	//           (0, 4096)    -> (4096, 4096)
	
	if (i >= 1792 && i <= 2304 && j >= 1792 && j <= 2304) {
		return 'a';
	} else if (i >= 1536 && i <= 2560 && j >= 1536 && j <= 2560) {
		return 'b';
	} else if (i >= 1024 && i <= 3072 && j >= 1024 && j <= 3072) {
		return 'c';
	} else if (i >= 0 && i <= 4096 && j >= 0 && j <= 4096) {
		return 'd';
	}

	return 'i';	// invisible
}


// input is (x,y) cartesian coordinate
// using conversion between cartesion and polar, find the point in polar
// then classfy using radius comparison  
char inPolarRegion(double vx, double vy, int ux, int uy) {

	// assume the center of the circle is (ux, uy)
	vx -= ux;
	vy -= uy;

	// convert between cartesian and polar
	// r = sqrt (x^2 + y^2)
	double x2 = vx * vx;
	double y2 = vy * vy;
	double r = sqrt(x2 + y2);

	// tha angle is not in the correct direction
	// when x is negative, theta should be negative of original
	double val = 180.0 / PI;
	double theta = atan(vy / vx) * val;	// to get theta in degreees

	if (vx < 0) {
		theta = 180 + theta;
	}

	printf("radius: %f  theta: %f \n", r, theta);

	if (r <= 256) {		// 512/2
		return 'a';
	} else if (r <= 512) {		// 1024/2
		return 'b';
	} else if (r <= 1536) {		// 3072/2
		return 'c';
	} else if (r <= 2048) {		// 4096/2
		return 'd';
	}

	return 'i';
}

/*
int main() {

	int centerx = 2047;
	int centery = 2047;

	int x0 = 1700;
	int y0 = 2400;
	char p = inPolarRegion(x0, y0, centerx, centery);
	printf("(%d, %d) (%d, %d) %c\n", centerx, centery, x0, y0, p);

	centerx = 1600;
	centery = 2500;
	p = inPolarRegion(x0, y0, centerx, centery);

	printf("(%d, %d) (%d, %d) %c\n", centerx, centery, x0, y0, p);
	return 0;
}
*/

// to compile
// gcc classification.c -lm -o classification