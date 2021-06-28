#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "driver.h"

struct Point points[SIZE];

void chase(struct Params * params, struct Point * u, struct Point * v) {
	
	int t = 0;
  	float prob = (rand() % 100) *.01;
	
	while (1) {
		updateU(u, params->u_activity, t, prob);

		// get new line
		findPath(points, v->i, v->j, u->i, u->j);

		v->i = points[1].i;
		v->j = points[1].j;

		// check the zones 
		v->region = inPolarRegion(v->i, v->j, u->i, u->j);
		
		printf("V: %d, %d, %c U: %d, %d, t: %d\n\n", v->i, v->j, v->region, u->i, u->j, t);
		fprintf(params->fpt, "%d, %d, %d, %d\n", u->i, u->j, v->i, v->j);

		// check for breaking 
		if (t > params->maxsteps || (v->i == u->i && v->j == u->j)) {
			printf("break\n");
			break;
		}
		
		prob = (rand() & 100) * .01;
		t++;
	}
}