#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "diver.h"

struct Point points[SIZE];

int* moveWithProbability(int x, int y, struct Point idealV, float bresenhamP) {
	// when ideal is to NE
	int coord[2];
	int * coord_ptr = coord;
	float p = (1.0 - bresenhamP) / 9.0;
	printf("p: %f p x 9: %f\n",p,p*9.0);
	
	if ((x + 1 == idealV.i) && (y + 1 == idealV.j)) {	

		if(p <= bresenhamP + p) { // E
			x += 1;
		} else if (p <= bresenhamP + (2.0 * p)) { // SE
			x += 1;
			y -= 1;
		} else if (p <= bresenhamP + (3.0 * p)) { // S
			y -= 1;
		} else if (p <= bresenhamP + (4.0 * p)) { // SW
			x -= 1;
			y -= 1;
		} else if (p <= bresenhamP + (5.0 * p)) { // W
			x -= 1;
		} else if (p <= bresenhamP + (6.0 * p)) { // NW
			x -= 1;
			y += 1;
		} else if (p <= bresenhamP + (7.0 * p)) { // N
			y += 1;
		}
	}

	// when ideal is directly E:
	if ((x + 1 == idealV.i) && (y == idealV.j)) {

		if(p <= bresenhamP + p) { // NE
			x += 1;
			y += 1;
		} else if (p <= bresenhamP + (2.0 * p)) { // N
			y += 1;
		} else if (p <= bresenhamP + (3.0 * p)) { // NW
			x -= 1;
			y += 1;
		} else if (p <= bresenhamP + (4.0 * p)) { // W
			x -= 1;
		} else if (p <= bresenhamP + (5.0 * p)) { // SW
			x -= 1;
			y -= 1;
		} else if (p <= bresenhamP + (6.0 * p)) { // S
			y -= 1;
		} else if (p <= bresenhamP + (7.0 * p)) { // SE
			x += 1;
			y -= 1;
		}
	} 
	coord[0] = x;
	coord[1] = y;
	return coord_ptr;
}

void chase(struct Params * params, struct Point * u, struct Point * v) {
	
	int t = 0;
  	float prob = (rand() % 100) *.01;
  	struct Point idealV;
  	int * coordPtr;
  	float take_bresenham_prob = (use_chasing_prob) ? params->chasing_prob : 1.0;
	
	while (1) {

		// get new line
		findPathSofie(points, v->i, v->j, u->i, u->j);

		// add probability to if boat V will take bresenham's move
		if (prob < take_bresenham_prob) {
			// 50% chance to take bresenham's line
			v->i = points[1].i;
			v->j = points[1].j;
		} else {
			printf("not taking brezzies\n");
			idealV.i = points[1].i;
			idealV.j = points[1].j;
			coordPtr = moveWithProbability(v->i,v->j,idealV,take_bresenham_prob);
			v->i = *coordPtr;
			v->j = *(coordPtr+1);
		} 	
		
		/*
		else {
			// 50% chance to take random walk
			// with all 8 directions, stay, and inv having 10% chance each
			coordPtr = randomPoint(v->i, v->j, prob);
			v->i = *coordPtr;
			v->j = *(coordPtr + 1);
		}
		*/
		// take bresenham every time
		//v->i = points[1].i;
		//v->j = points[1].j;
		
		// new prob?
		prob = (rand() & 100) * .01;
		
		updateU(u, params->u_activity, t, prob);
		
		// check the zones 
		v->region = inPolarRegion(v->i, v->j, u->i, u->j);
		
		printf("V: %d, %d, %c U: %d, %d, t: %d\n\n", v->i, v->j, v->region, u->i, u->j, t);
		fprintf(params->fpt, "%d, %d, %d, %d\n", u->i, u->j, v->i, v->j);

		// check for breaking 
		if (t > params->maxsteps || (v->i == u->i && v->j == u->j)) {
			printf("break   chasing prob: %.2f\n", take_bresenham_prob);
			break;
		}
		
		prob = (rand() & 100) * .01;
		t++;
	}
}