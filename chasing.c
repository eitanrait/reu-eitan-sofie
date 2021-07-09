#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "diver.h"

struct Point points[SIZE];

void chase(struct Params * params, struct Point * u, struct Point * v) {
	
	int t = 0;
  	float prob = (rand() % 100) *.01;
  	int * coordPtr;
  	float take_bresenham_prob = (use_chasing_prob) ? params->chasing_prob : 1.0;
  	//fprintf(params->fpt, "ui, uj, vi, vj\n");
  	srand(time(0));
	
	while (1) {

		// get new line
		findPathSofie(points, v->i, v->j, u->i, u->j);
		printf("prob for taking bres: %f\n", prob);
		// add probability to if boat V will take bresenham's move
		if (prob < take_bresenham_prob) {
			// 50% chance to take bresenham's line
			printf("\n bresenham \n");
			v->i = points[1].i;
			v->j = points[1].j;
		} else {
			// 50% chance to take random walk
			// with each direction plus stay and inv having 10% chance
			printf("\n random \n");
			prob = (rand() & 100) * .01;
			printf("prob for coordinate point: %f\n", prob);
			coordPtr = randomPoint(v->i, v->j, prob);
			v->i = *coordPtr;
			v->j = *(coordPtr + 1);
		}

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

	// print bresenham to random ratio
}