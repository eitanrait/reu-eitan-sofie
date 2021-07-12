#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "diver.h"

struct Point points[SIZE];
int ratios[9] = {0};

int* moveWithProbability(int x, int y, struct Point idealV, float bresenhamP, float * prob) {
	int coord[2];
	int * coord_ptr = coord;
	printf("random number is %.2f\n",*prob);
	float p = (1.0 - bresenhamP) / 8.0;
	//printf("split p: %.2f total p: %.2f\n",p,p*8.0);
	// when ideal is to NE
	if ((x + 1 == idealV.i) && (y + 1 == idealV.j)) {	
			printf("Ideal is Northeast\n");
		if(*prob <= bresenhamP + p) { // E
			printf("East\n");
			x += 1;
			ratios[0]++;
		} else if (*prob <= bresenhamP + (2.0 * p)) { // SE
			printf("Southeast\n");
			x += 1;
			y -= 1;
			ratios[1]++;
		} else if (*prob <= bresenhamP + (3.0 * p)) { // S
			printf("South\n");
			y -= 1;
			ratios[2]++;
		} else if (*prob <= bresenhamP + (4.0 * p)) { // SW
			printf("Southwest\n");
			x -= 1;
			y -= 1;
			ratios[3]++;
		} else if (*prob <= bresenhamP + (5.0 * p)) { // W
			printf("West\n");
			x -= 1;
			ratios[4]++;
		} else if (*prob <= bresenhamP + (6.0 * p)) { // NW
			printf("Northwest\n");
			x -= 1;
			y += 1;
			ratios[5]++;
		} else if (*prob <= bresenhamP + (7.0 * p)) { // N
			printf("North\n");
			y += 1;
			ratios[6]++;
		} else {
			ratios[8]++;
		}
	}

	// when ideal is directly E:
	else if ((x + 1 == idealV.i) && (y == idealV.j)) {
			printf("Ideal is East\n");
		if(*prob <= bresenhamP + p) { // NE
			printf("Northeast\n");
			x += 1;
			y += 1;
			ratios[7]++;
		} else if (*prob <= bresenhamP + (2.0 * p)) { // N
			printf("North\n");
			y += 1;
			ratios[6]++;
		} else if (*prob <= bresenhamP + (3.0 * p)) { // NW
			printf("Northwest\n");
			x -= 1;
			y += 1;
			ratios[5]++;
		} else if (*prob <= bresenhamP + (4.0 * p)) { // W
			printf("West\n");
			x -= 1;
			ratios[4]++;
		} else if (*prob <= bresenhamP + (5.0 * p)) { // SW
			printf("Southwest\n");
			x -= 1;
			y -= 1;
			ratios[3]++;
		} else if (*prob <= bresenhamP + (6.0 * p)) { // S
			printf("South\n");
			y -= 1;
			ratios[2]++;
		} else if (*prob <= bresenhamP + (7.0 * p)) { // SE
			printf("Southeast\n");			
			x += 1;
			y -= 1;
			ratios[1]++;
		} else {
			ratios[8]++;
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
		printf("time %d\n",t);
		// get new line
		findPathSofie(points, v->i, v->j, u->i, u->j);

		// add probability to if boat V will take bresenham's move
		if (prob <= take_bresenham_prob) {
			// 50% chance to take bresenham's line
			v->i = points[1].i;
			v->j = points[1].j;
		} else {
			// definitely check this, it does not seem right
			idealV.i = points[1].i;
			idealV.j = points[1].j;
			printf("idealV.i: %d  idealV.j: %d\n",idealV.i,idealV.j);
			coordPtr = moveWithProbability(v->i,v->j,idealV,take_bresenham_prob,&prob);
			v->i = *coordPtr;
			v->j = *(coordPtr+1);
		} 	
		
		printf("Move Direction Count:\n\tE: %d\n\tSE: %d\n\tS: %d\n\tSW: %d\n\tW: %d\n\tNW: %d\n\tN: %d\n\tNE: %d\n\tSTAY: %d\n",ratios[0],ratios[1],ratios[2],ratios[3],ratios[4],ratios[5],ratios[6],ratios[7],ratios[8]);
		
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
		prob = (rand() % 100) * .01;
		printf("random number changed to %.2f\n",prob);
		
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

		t++;
	}
}