#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "diver.h"

struct Point points[SIZE];
int steps1[9] = {0};


// use to get a random point based on previous point and probability
// skew to make the trajectory go away from bresenham algo
// want to get rid of invisible state or not have an invisible state at all
int* randomPointAway(struct Point idealV, struct Point* currentV, float prob) {

  int x = currentV->i;
  int y = currentV->j;
  int p[2];
  int* point_ptr = p;

  printf("currentV: (%d, %d)  idealV: (%d, %d)\n", x, y, idealV.i, idealV.j);
  // ideal move is NE
  if (idealV.i == x + 1 && idealV.j == y + 1) {
  	printf("ideal is NE\n");
  	if (prob >= 0 && prob < 0.12) {   // N
    	y++;
    	steps1[0]++;
  	} else if (prob < 0.14) {         // NE
    	x++;
    	y++;
    	steps1[1]++;
  	} else if (prob < 0.18) {         // E
    	x++;
    	steps1[2]++;
  	} else if (prob < 0.30) {        // SE
    	x++;
    	y--;
    	steps1[3]++;
  	} else if (prob < 0.50) {         // S
    	y--;  
    	steps1[4]++;
  	} else if (prob < 0.60) {         // SW
    	x--;
    	y--;
    	steps1[5]++;
  	} else if(prob < 0.80) {          // W
    	x--;
    	steps1[6]++;
  	} else if (prob < 1.0) {         // NW
    	x--;
    	y++;
    	steps1[7]++;
  	}

  } else if (idealV.i == x + 1 && idealV.j == y) {	// ideal move is E
  	printf("ideal is E\n");
  	if (prob >= 0 && prob < 0.12) {   // N
    	y++;
    	steps1[0]++;
  	} else if (prob < 0.16) {         // NE
    	x++;
    	y++;
    	steps1[1]++;
  	} else if (prob < 0.18) {         // E
    	x++;
    	steps1[2]++;
  	} else if ( prob < 0.30) {        // SE
    	x++;
    	y--;
    	steps1[3]++;
  	} else if (prob < 0.50) {         // S
    	y--;  
    	steps1[4]++;
  	} else if (prob < 0.70) {         // SW
    	x--;
    	y--;
    	steps1[5]++;
  	} else if(prob < 0.80) {          // W
    	x--;
    	steps1[6]++;
  	} else if (prob < 1.0) {         // NW
    	x--;
    	y++;
    	steps1[7]++;
  	}

  } else if (idealV.i == x + 1 && idealV.j == y - 1) {	// ideal move is SE
  	printf("ideal is SE\n");
  	if (prob >= 0 && prob < 0.20) {   // N
    	y++;
    	steps1[0]++;
  	} else if (prob < 0.32) {         // NE
    	x++;
    	y++;
    	steps1[1]++;
  	} else if (prob < 0.36) {         // E
    	x++;
    	steps1[2]++;
  	} else if ( prob < 0.38) {        // SE
    	x++;
    	y--;
    	steps1[3]++;
  	} else if (prob < 0.50) {         // S
    	y--;  
    	steps1[4]++;
  	} else if (prob < 0.70) {         // SW
    	x--;
    	y--;
    	steps1[5]++;
  	} else if(prob < 0.90) {          // W
    	x--;
    	steps1[6]++;
  	} else if (prob < 1.0) {         // NW
    	x--;
    	y++;
    	steps1[7]++;
  	}

  } else if (idealV.i == x && idealV.j == y + 1) {	// ideal move is N
  	printf("ideal is E\n");
  	if (prob >= 0 && prob < 0.2) {   // N
    	y++;
    	steps1[0]++;
  	} else if (prob < 0.6) {         // NE
    	x++;
    	y++;
    	steps1[1]++;
  	} else if (prob < 0.18) {         // E
    	x++;
    	steps1[2]++;
  	} else if ( prob < 0.38) {        // SE
    	x++;
    	y--;
    	steps1[3]++;
  	} else if (prob < 0.48) {         // S
    	y--;  
    	steps1[4]++;
  	} else if (prob < 0.68) {         // SW
    	x--;
    	y--;
    	steps1[5]++;
  	} else if(prob < 0.88) {          // W
    	x--;
    	steps1[6]++;
  	} else if (prob < 1.0) {         // NW
    	x--;
    	y++;
    	steps1[7]++;
  	}

  } else {
  	//y++;
  	//x--;
  	//steps1[0]++;
  	steps1[8]++;
  }
 
  p[0] = x;
  p[1] = y;

  return point_ptr;

}



void chase(struct Params * params, struct Point * u, struct Point * v) {
	
	int t = 0;
  	double prob = (rand() % 100) *.01;
  	int * coordPtr;
  	double take_bresenham_prob = (use_chasing_prob) ? params->chasing_prob : 1.0;
  	//fprintf(params->fpt, "ui, uj, vi, vj\n");
  	double random = 0;
  	double bres = 0;
	
	while (1) {

		// get new line
		//findPathSofie(points, v->i, v->j, u->i, u->j);
		findPath(points, v->i, v->j, u->i, u->j);
		printf("prob for taking bres: %f\n", prob);
		// add probability to if boat V will take bresenham's move
		if (prob <= take_bresenham_prob) {
			// 50% chance to take bresenham's line
			printf("\n bresenham \n");
			v->i = points[1].i;
			v->j = points[1].j;
			bres++;
		} else {
			// 50% chance to take random walk
			// with each direction plus stay and inv having 10% chance
			printf("\n random \n");
			prob = (rand() % 100) * .01;	// no invisible state - prob is out of 90
			printf("prob for coordinate point: %f\n", prob);

			// with all 8 directions, stay, and inv having 10% chance each
			// v is current location of v
			// points[1].i and .j is ideal
			//coordPtr = randomPoint(v->i, v->j, prob);
			coordPtr = randomPointAway(points[1], v, prob);
			v->i = *coordPtr;
			v->j = *(coordPtr + 1);
			printf("new point: (%d, %d)\n", v->i, v->j);
			random++;
		}

		// take bresenham every time
		//v->i = points[1].i;
		//v->j = points[1].j;

		// new prob?
		prob = (rand() % 100) * .01;		// no invisible state

		updateU(u, params->u_activity, t, prob);
		
		// check the zones 
		v->region = inPolarRegion(v->i, v->j, u->i, u->j);
		
		printf("V: %d, %d, %c U: %d, %d, t: %d\n\n", v->i, v->j, v->region, u->i, u->j, t);
		fprintf(params->fpt, "%d, %d, %d, %d\n", u->i, u->j, v->i, v->j);

		// check for breaking 
		if (t > params->maxsteps || (v->i == u->i && v->j == u->j)) {
			printf("break   chasing prob: %.2f\n", take_bresenham_prob);
			// print bresenham to random ratio
			printf("bres taken: %.0f\t%f\nrandom taken: %.0f\t%f\n", bres, bres/t, random, random/t);

			// calculate for debugging
			double total = 0;
			for (int k = 0; k < 9; k++) {
				total += steps1[k];
			}

			printf("steps1 taken randomly: %.0f\n", total);
			printf("N  %d\t%.3f\n", steps1[0], steps1[0]/total);
			printf("NE %d\t%.3f\n", steps1[1], steps1[1]/total);
			printf("E  %d\t%.3f\n", steps1[2], steps1[2]/total);
			printf("SE %d\t%.3f\n", steps1[3], steps1[3]/total);
			printf("S  %d\t%.3f\n", steps1[4], steps1[4]/total);
			printf("SW %d\t%.3f\n", steps1[5], steps1[5]/total);
			printf("W  %d\t%.3f\n", steps1[6], steps1[6]/total);
			printf("NW %d\t%.3f\n", steps1[7], steps1[7]/total);
			printf("-- %d\t%.3f\n", steps1[8], steps1[8]/total);
			break;
		}
		
		prob = (rand() % 100) * .01;
		t++;
	}

}