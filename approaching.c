#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "driver.h"
#define SIZE 150

struct Point points[SIZE];

// call draw line with two points
// find the path from p1 to p2 assuming p1.x < p2.x and slope is 0 < m <= 1
void approach(struct Point * u, struct Point * v) { 
	
	if(is_verbose)
	{
		printf("values of - v %d %d u %d %d\n",  v->i, v->j, u->i, u->j);
		printf("entering findPath\n");
	}
	
	findPathSofie(points, v->i, v->j, u->i, u->j);
	
	for (int k = 0; k < SIZE; k++) {
		printf("%d, %d\n", points[k].i, points[k].j);
    }
}
