#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "diver.h"

struct Point points[SIZE];
int ratios[9] = {0};

int switchDirection(int x, int y, struct Point idealV) {
	if ((x == idealV.i) && (y+1 == idealV.j)) {
		printf("Ideal: North\n");
		return 0;
	} else if ((x+1 == idealV.i) && (y+1 == idealV.j)) {
		printf("Ideal: Northeast\n");
		return 1;
	} else if ((x+1 == idealV.i) && (y == idealV.j)) {
		printf("Ideal: East\n");
		return 2;
	} else if ((x+1 == idealV.i) && (y-1 == idealV.j)) {
		printf("Ideal: Southeast\n");
		return 3;
	} else if ((x == idealV.i) && (y-1 == idealV.j)) {
		printf("Ideal: South\n");
		return 4;
	} else if ((x-1 == idealV.i) && (y-1 == idealV.j)) {
		printf("Ideal: Southwest\n");
		return 5;
	} else if ((x-1 == idealV.i) && (y == idealV.j)) {
		printf("Ideal: West\n");
		return 6;
	} else if ((x-1 == idealV.i) && (y+1 == idealV.j)) {
		printf("Ideal: Northwest\n");
		return 7;
	}
	else {
		return 0;
	}
}

int* moveWithProbability(int x, int y, struct Point idealV, float bresenhamP, float * prob) {

	int coord[2];
	int * coord_ptr = coord;
	int ideal = 0;
	ideal = switchDirection(x, y, idealV);
	//printf("value of ideal: %d\n",ideal);
	float p = (1.0 - bresenhamP) / 8.0;
	//printf("bresenhamP+(1*p): %f\n",bresenhamP+(1*p));
	printf("random number is %.2f\n",*prob);
	//printf("split probability: %f\n", p);
	/*
	if (*prob <= bresenhamP + (1.0 * p)) { 		  // probability of moving in direction 1 unit away from ideal this one
		switch(ideal) {
			case 0: // Ideal N
				x += 1;
				y += 1;
				ratios[1]++;
				break;
			case 1: // Ideal NE
				x += 1;
				ratios[2]++;
				break;
			case 2: // Ideal E
				x += 1;
				y -= 1;
				ratios[3]++;
				break;
			case 3: // Ideal SE
				y -= 1;
				ratios[4]++;
				break;
			case 4: // Ideal S
				x -= 1;
				y -= 1;
				ratios[5]++;
				break;
			case 5: // Ideal SW
				x -= 1;
				ratios[6]++;
				break;
			case 6: // Ideal W
				x -= 1;
				y += 1;
				ratios[7]++;
				break;
			case 7: // Ideal NW
				y += 1;
				ratios[0]++;
				break;
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (1.5 * p)) { // probability of moving in direction 2 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				x += 1;
				ratios[2]++;
				break;
			case 1: // Ideal NE
				x += 1;
				y -= 1;
				ratios[3]++;
				break;
			case 2: // Ideal E
				y -= 1;
				ratios[4]++;
				break;
			case 3: // Ideal SE
				x -= 1;
				y -= 1;
				ratios[5]++;
				break;
			case 4: // Ideal S
				x -= 1;
				ratios[6]++;
				break;
			case 5: // Ideal SW
				x -= 1;
				y += 1;
				ratios[7]++;
				break;
			case 6: // Ideal W
				y += 1;
				ratios[0]++;
				break;
			case 7: // Ideal NW
				x += 1;
				y += 1;
				ratios[1]++;
				break;
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (2.5 * p)) { // probability of moving in direction 3 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				x += 1;
				y -= 1;
				ratios[3]++;
				break;
			case 1: // Ideal NE
				y -= 1;
				ratios[4]++;
				break;
			case 2: // Ideal E
				x -= 1;
				y -= 1;
				ratios[5]++;
				break;
			case 3: // Ideal SE
				x -= 1;
				ratios[6]++;
				break;
			case 4: // Ideal S
				x -= 1;
				y += 1;
				ratios[7]++;
				break;
			case 5: // Ideal SW
				y += 1;
				ratios[0]++;
				break;
			case 6: // Ideal W
				x += 1;
				y += 1;
				ratios[1]++;
				break;
			case 7: // Ideal NW
				x += 1;
				ratios[2]++;
				break;
			default:
				break;
		}
	} else if (*prob <= bresenhamP + (5.5 * p)) { // probability of moving in direction 4 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				y -= 1;
				ratios[4]++;
				break;
			case 1: // Ideal NE
				x -= 1;
				y -= 1;
				ratios[5]++;
				break;
			case 2: // Ideal E
				x -= 1;
				ratios[6]++;
				break;
			case 3: // Ideal SE
				x -= 1;
				y += 1;
				ratios[7]++;
				break;
			case 4: // Ideal S
				y += 1;
				ratios[0]++;
				break;
			case 5: // Ideal SW
				x += 1;
				y += 1;
				ratios[1]++;
				break;
			case 6: // Ideal W
				x += 1;
				ratios[2]++;
				break;
			case 7: // Ideal NW
				x += 1;
				y -= 1;
				ratios[3]++;
				break;
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (6.5 * p)) { // probability of moving in direction 5 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				x -= 1; 
				y -= 1; 
				ratios[5]++;
				break; // southwest
			case 1: // Ideal NE
				x -= 1; 
				ratios[6]++;
				break; // west
			case 2: // Ideal E
				x -= 1;
				y += 1;
				ratios[7]++;
				break; // northwest
			case 3: // Ideal SE
				y += 1;
				ratios[0]++;
				break; // north
			case 4: // Ideal S
				x += 1;
				y += 1;
				ratios[1]++;
				break; // northeast
			case 5: // Ideal SW
				x += 1;
				ratios[2]++;
				break; // east
			case 6: // Ideal W
				x += 1;
				y -= 1;
				ratios[3]++;
				break; // southeast
			case 7: // Ideal NW
				y -= 1;
				ratios[4]++;
				break; // south
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (7.3 * p)) { // probability of moving in direction 6 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				x -= 1;
				ratios[6]++;
				break; // west
			case 1: // Ideal NE
				x -= 1; 
				y += 1;
				ratios[7]++;
				break; // northwest
			case 2: // Ideal E
				y += 1;
				ratios[0]++;
				break; // north
			case 3: // Ideal SE
				x += 1;
				y += 1;
				ratios[1]++;
				break; // northeast
			case 4: // Ideal S
				x += 1;
				ratios[2]++;
				break; // east
			case 5: // Ideal SW
				x += 1;
				y -= 1;
				ratios[3]++;
				break; // southeast
			case 6: // Ideal W
				y -= 1;
				ratios[4]++;
				break; // south
			case 7: // Ideal NW
				x -= 1;
				y -= 1;
				ratios[5]++;
				break; // southwest
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (7.8 * p)) { // probability of moving in direction 7 unit away from ideal this one
		switch(ideal) {
			case 0: // Ideal N
				x -= 1; 
				y += 1; 
				ratios[7]++;
				break; // northwest
			case 1: // Ideal NE
				y += 1; 
				ratios[0]++;
				break; // north
			case 2: // Ideal E
				x += 1;
				y += 1;
				ratios[1]++;
				break; // northeast
			case 3: // Ideal SE
				x += 1;
				ratios[2]++;
				break; // east
			case 4: // Ideal S
				x += 1;
				y -= 1;
				ratios[3]++;
				break; // southeast
			case 5: // Ideal SW
				y -= 1;
				ratios[4]++;
				break; // south
			case 6: // Ideal W
				x -= 1;
				y -= 1;
				ratios[5]++;
				break; // southwest
			case 7: // Ideal NW
				x -= 1;
				ratios[6]++;
				break; // west
			default:
				ratios[8]++;
				break;
		}
	} else { 									  // probability of not moving in any direction
		ratios[8]++;
	} 
	*/
	if (*prob <= bresenhamP + (1.0 * p)) { 		  // probability of moving in direction 1 unit away from ideal this one
		switch(ideal) {
			case 0: // Ideal N
				x += 1;
				y += 1;
				ratios[1]++;
				break;
			case 1: // Ideal NE
				x += 1;
				ratios[2]++;
				break;
			case 2: // Ideal E
				x += 1;
				y -= 1;
				ratios[3]++;
				break;
			case 3: // Ideal SE
				y -= 1;
				ratios[4]++;
				break;
			case 4: // Ideal S
				x -= 1;
				y -= 1;
				ratios[5]++;
				break;
			case 5: // Ideal SW
				x -= 1;
				ratios[6]++;
				break;
			case 6: // Ideal W
				x -= 1;
				y += 1;
				ratios[7]++;
				break;
			case 7: // Ideal NW
				y += 1;
				ratios[0]++;
				break;
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (2.0 * p)) { // probability of moving in direction 2 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				x += 1;
				ratios[2]++;
				break;
			case 1: // Ideal NE
				x += 1;
				y -= 1;
				ratios[3]++;
				break;
			case 2: // Ideal E
				y -= 1;
				ratios[4]++;
				break;
			case 3: // Ideal SE
				x -= 1;
				y -= 1;
				ratios[5]++;
				break;
			case 4: // Ideal S
				x -= 1;
				ratios[6]++;
				break;
			case 5: // Ideal SW
				x -= 1;
				y += 1;
				ratios[7]++;
				break;
			case 6: // Ideal W
				y += 1;
				ratios[0]++;
				break;
			case 7: // Ideal NW
				x += 1;
				y += 1;
				ratios[1]++;
				break;
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (3.0 * p)) { // probability of moving in direction 3 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				x += 1;
				y -= 1;
				ratios[3]++;
				break;
			case 1: // Ideal NE
				y -= 1;
				ratios[4]++;
				break;
			case 2: // Ideal E
				x -= 1;
				y -= 1;
				ratios[5]++;
				break;
			case 3: // Ideal SE
				x -= 1;
				ratios[6]++;
				break;
			case 4: // Ideal S
				x -= 1;
				y += 1;
				ratios[7]++;
				break;
			case 5: // Ideal SW
				y += 1;
				ratios[0]++;
				break;
			case 6: // Ideal W
				x += 1;
				y += 1;
				ratios[1]++;
				break;
			case 7: // Ideal NW
				x += 1;
				ratios[2]++;
				break;
			default:
				break;
		}
	} else if (*prob <= bresenhamP + (4.0 * p)) { // probability of moving in direction 4 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				y -= 1;
				ratios[4]++;
				break;
			case 1: // Ideal NE
				x -= 1;
				y -= 1;
				ratios[5]++;
				break;
			case 2: // Ideal E
				x -= 1;
				ratios[6]++;
				break;
			case 3: // Ideal SE
				x -= 1;
				y += 1;
				ratios[7]++;
				break;
			case 4: // Ideal S
				y += 1;
				ratios[0]++;
				break;
			case 5: // Ideal SW
				x += 1;
				y += 1;
				ratios[1]++;
				break;
			case 6: // Ideal W
				x += 1;
				ratios[2]++;
				break;
			case 7: // Ideal NW
				x += 1;
				y -= 1;
				ratios[3]++;
				break;
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (5.0 * p)) { // probability of moving in direction 5 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				x -= 1; 
				y -= 1; 
				ratios[5]++;
				break; // southwest
			case 1: // Ideal NE
				x -= 1; 
				ratios[6]++;
				break; // west
			case 2: // Ideal E
				x -= 1;
				y += 1;
				ratios[7]++;
				break; // northwest
			case 3: // Ideal SE
				y += 1;
				ratios[0]++;
				break; // north
			case 4: // Ideal S
				x += 1;
				y += 1;
				ratios[1]++;
				break; // northeast
			case 5: // Ideal SW
				x += 1;
				ratios[2]++;
				break; // east
			case 6: // Ideal W
				x += 1;
				y -= 1;
				ratios[3]++;
				break; // southeast
			case 7: // Ideal NW
				y -= 1;
				ratios[4]++;
				break; // south
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (6.0 * p)) { // probability of moving in direction 6 unit away from ideal
		switch(ideal) {
			case 0: // Ideal N
				x -= 1;
				ratios[6]++;
				break; // west
			case 1: // Ideal NE
				x -= 1; 
				y += 1;
				ratios[7]++;
				break; // northwest
			case 2: // Ideal E
				y += 1;
				ratios[0]++;
				break; // north
			case 3: // Ideal SE
				x += 1;
				y += 1;
				ratios[1]++;
				break; // northeast
			case 4: // Ideal S
				x += 1;
				ratios[2]++;
				break; // east
			case 5: // Ideal SW
				x += 1;
				y -= 1;
				ratios[3]++;
				break; // southeast
			case 6: // Ideal W
				y -= 1;
				ratios[4]++;
				break; // south
			case 7: // Ideal NW
				x -= 1;
				y -= 1;
				ratios[5]++;
				break; // southwest
			default:
				ratios[8]++;
				break;
		}
	} else if (*prob <= bresenhamP + (7.0 * p)) { // probability of moving in direction 7 unit away from ideal this one
		switch(ideal) {
			case 0: // Ideal N
				x -= 1; 
				y += 1; 
				ratios[7]++;
				break; // northwest
			case 1: // Ideal NE
				y += 1; 
				ratios[0]++;
				break; // north
			case 2: // Ideal E
				x += 1;
				y += 1;
				ratios[1]++;
				break; // northeast
			case 3: // Ideal SE
				x += 1;
				ratios[2]++;
				break; // east
			case 4: // Ideal S
				x += 1;
				y -= 1;
				ratios[3]++;
				break; // southeast
			case 5: // Ideal SW
				y -= 1;
				ratios[4]++;
				break; // south
			case 6: // Ideal W
				x -= 1;
				y -= 1;
				ratios[5]++;
				break; // southwest
			case 7: // Ideal NW
				x -= 1;
				ratios[6]++;
				break; // west
			default:
				ratios[8]++;
				break;
		}
	} else { 									  // probability of not moving in any direction
		ratios[8]++;
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
		findPath(points, v->i, v->j, u->i, u->j);
		idealV.i = points[1].i;
		idealV.j = points[1].j;
		printf("idealV.i: %d  idealV.j: %d\n",idealV.i,idealV.j);
		
		// add probability to if boat V will take bresenham's move
		if (prob <= take_bresenham_prob) {
			// 50% chance to take bresenham's line
			ratios[switchDirection(v->i,v->j,idealV)]++;
			v->i = points[1].i;
			v->j = points[1].j;
		} else {
			coordPtr = moveWithProbability(v->i,v->j,idealV,take_bresenham_prob,&prob);
			v->i = *coordPtr;
			v->j = *(coordPtr+1);
		} 	
		
		printf("Move Direction Count:\n\tN: %d\n\tNE: %d\n\tE: %d\n\tSE: %d\n\tS: %d\n\tSW: %d\n\tW: %d\n\tNW: %d\n\tSTAY: %d\n",ratios[0],ratios[1],ratios[2],ratios[3],ratios[4],ratios[5],ratios[6],ratios[7],ratios[8]);
		
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