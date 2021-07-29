// pseudocodes
// 

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "diver.h"

// not used right now
/*
// random walk
#define ideal .125	// 12%
#define step1 .25	// 12%
#define step2 .375	// 12%
#define step3 .50	// 12%
#define step4 .625	// 12%
#define step5 .75	// 12%
#define step6 .875 	// 12%
#define step7 1.0	// 12%
*/

// prefer steps 1, 2, 6, and 7 away
#define ideal .05	// 5%
#define step1 .25	// 20%
#define step2 .45	// 20%
#define step3 .50	// 5%
#define step4 .55	// 5%
#define step5 .60	// 5%
#define step6 .80 	// 20%
#define step7 1.0	// 20%

struct Point points[SIZE];
int steps[9] = {0};
//int possible_ks[10] = {9, 10, 11, 12, 13, 14, 16, 18, 20, 22};
int possible_ks[10] = {50, 55, 60, 65, 70, 75, 80, 85, 90, 100};
int possible_xs[7] = {0, 1, 2, 6, 7, 8, 0};

typedef struct {
	int offset[2];	
} OFFSET_t;

OFFSET_t directions[9] = {
	{{0, 1}},	// N
	{{1, 1}}, 	// NE
	{{1, 0}},	// E
	{{1, -1}},	// SE
	{{0, -1}},	// S
	{{-1, -1}},	// SW
	{{-1, 0}},	// W
	{{-1, 1}},	// NW
	{{0, 0}}	// STAY

};

int idealDirection(int x, int y, struct Point idealV) {
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
		printf(" -- stay --\n");
		return 8;
	}
}

// loop through defined probabilities 
int checkProbability (int idealDirection, float probability) {

	printf("\ncheckProbability()\n");
	printf("idealDirection: %d   probability: %f\n", idealDirection, probability);
	if (probability < ideal) {
		printf("return: %d\n\n", idealDirection);
		steps[0]++;
		return idealDirection;
	} else if (probability < step1) {
		printf("return: %d\n\n", (idealDirection + 1) % 8);
		steps[1]++;
		return (idealDirection + 1) % 8;
	} else if (probability < step2) {
		printf("return: %d\n\n", (idealDirection + 2) % 8);
		steps[2]++;
		return (idealDirection + 2) % 8;
	} else if (probability < step3) {
		printf("return: %d\n\n", (idealDirection + 3) % 8);
		steps[3]++;
		return (idealDirection + 3) % 8;
	} else if (probability < step4) {
		printf("return: %d\n\n", (idealDirection + 4) % 8);
		steps[4]++;
		return (idealDirection + 4) % 8;
	} else if (probability < step5) {
		printf("return: %d\n\n", (idealDirection + 5) % 8);
		steps[5]++;
		return (idealDirection + 5) % 8;
	} else if (probability < step6) {
		printf("return: %d\n\n", (idealDirection + 6) % 8);
		steps[6]++;
		return (idealDirection + 6) % 8;
	} else if (probability < step7) {
		printf("return: %d\n\n", (idealDirection + 7) % 8);
		steps[7]++;
		return (idealDirection + 7) % 8;
	}

	printf("probability did not fall into any category\n\n");
	steps[8]++;
	return 8;

}

int isVBehind(struct Point * u, struct Point * v, double last_i, double last_j) {

    // A is new U position
    // find another point (B) on the perpendicular
    struct Point * nextPoint = findPerpendicularPoint(u ,v ,last_i, last_j);
  
    struct Point B;
    B.i = nextPoint->i;
    B.j = nextPoint->j;
  
  	struct Point lastU;
  	lastU.i = last_i;
  	lastU.j = last_j;
  
  	// compare with pos of Y for direction of Y in respect to the perp line
  	int directionV;
  	int directionLastU;
	  
	// if no change in X pos, return 2
	if (u->i == B.i && u->j == B.j) {
	  // this checks for no change in movement but for now it's ok
	  return 2;
	}
	  
	directionV = directionOfPoint(*u, B, *v);
	directionLastU = directionOfPoint(*u, B, lastU);
	  
	//printf("X: (%d, %d)  B: (%d, %d)  directionY: %d  directionLastX: %d\n", X.i, X.j, B.i, B.j, directionY, directionLastX);
	  
	if (directionLastU == directionV) {
	  return 1;	// return 1 when U is behind B
	}
	  
	return 0;
	  
}

void follow(struct Params * params, struct Point * u, struct Point * v) {
  
 	int t = 0;
 	
 	double random = 0;
 	int x = 0;
	int behind = 0; // 0 - not behind, 1 - behind                                                                                
	double last_i, last_j;

	double prob = (rand() % 100) *.01;
	int k = possible_ks[(int)prob]; //possible_ks[(int)prob] 12
	int count = k;

	int idealDirectionIndex = 0;
  	int offsetIndex = 0;

  	double take_bresenham_prob = (use_chasing_prob) ? params->chasing_prob : 1.0;

  	while (1) {    
    


    	// check which region boat Y is in
    	v->region = inPolarRegion(v->i, v->j, u->i, u->j);
		printf("behind: %d  region: %c\n",behind, v->region);
    
    	findPath(points, v->i, v->j, u->i, u->j);
    	idealDirectionIndex = idealDirection(v->i, v->j, points[1]);
    	printf("idealDirectionIndex: %d\n", idealDirectionIndex);

    	// if count is less than k, continue in the same direction with some randomness
    	printf(">>> count, k  %d, %d\n", count, k);
    	if (count < k) {
    		// take a step with chasing probability
    		prob = (rand() % 100) *.01;
    		if (prob > take_bresenham_prob) {
				// 50% chance to take bresenham's line
				random++;
				prob = (rand() % 100) *.01;
	    		offsetIndex = checkProbability(idealDirectionIndex, prob);	
			}
			count++;

    	} else {
    		// change directions every k moves
    		printf("-------\ncount: %d\n", count);
    		count = 0;
    		prob = (rand() % 10);
    		printf("prob for k: %f\n", prob);
    		k = possible_ks[(int)prob];

    		// choose an x that does a move 1, 2, 6, or 7 steps away from the ideal
    		prob = (rand() % 7);	// change to length of possible_xs
    		x = possible_xs[(int)prob];
    		printf("x: %d\n", x);
    		offsetIndex = (idealDirectionIndex + x) % 8;	// always mod 8
    		//prob = (rand() % 100) *.01;
    		//offsetIndex = checkProbability(idealDirectionIndex, prob);
    	}
    	
    	printf("offsetIndex: %d\n", offsetIndex);
    	// move boat V by the offset specified in directions struct
    	v->i += directions[offsetIndex].offset[0];
    	v->j += directions[offsetIndex].offset[1];
    	printf("new point v: (%d, %d)\n", v->i, v->j);

    	// store last U position
    	last_i = u->i;
		last_j = u->j;

    	// move boat U by what is in command line
    	prob = (rand() % 100) *.01;
    	updateU(u, params->u_activity, t, prob);
    	
    	printf("%d, %d  %d, %d  %d\n", v->i, v->j, u->i, u->j, t);
		fprintf(params->fpt, "%d, %d, %d, %d\n", u->i, u->j,  v->i, v->j);	// print to csv file
    
    	if (t >= params->maxsteps || (v->i == u->i && v->j == u->j)) {
      		printf("\n-------\nbreak\n");
			// calculate for debugging
			double total = 0;
			for (int k = 0; k < 9; k++) {
				total += steps[k];
			}

			printf("steps taken randomly: %.0f  %f\n", random, random/t);
			printf("ideal   %d\t%.3f\n", steps[0], steps[0]/total);
			printf("1 step  %d\t%.3f\n", steps[1], steps[1]/total);
			printf("2 steps %d\t%.3f\n", steps[2], steps[2]/total);
			printf("3 steps %d\t%.3f\n", steps[3], steps[3]/total);
			printf("4 steps %d\t%.3f\n", steps[4], steps[4]/total);
			printf("5 steps %d\t%.3f\n", steps[5], steps[5]/total);
			printf("6 steps %d\t%.3f\n", steps[6], steps[6]/total);
			printf("7 steps %d\t%.3f\n", steps[7], steps[7]/total);
			printf("  --    %d\t%.3f\n", steps[8], steps[8]/total);

			printf("\nfollowing probability: %.2f\n", take_bresenham_prob);

      		break;
    	}

    	// check where Y is     	
		printf("last_i, last_j (%f, %f)\n", last_i, last_j);
    	behind = isVBehind(u, v, last_i, last_j);
    
    	t++;
    
  }
  
}

struct Point * findPerpendicularPoint(struct Point * u, struct Point * v,double last_i, double last_j) {

	struct Point B;
	struct Point * B_ptr = &B;
	int curr_i = u->i;
	int curr_j = u->j;
	double slope, perp_slope;

	if ((last_i - curr_i != 0) && (last_j - curr_j != 0)) {
		//printf("last: (%f, %f) curr: (%d, %d)\n", last_i, last_j, curr_i, curr_j);
		slope = (curr_j - last_j) / (curr_i - last_i);
		perp_slope = -(1 / slope);
		//printf("slope: %f, perp_slope: %f\n", slope, perp_slope);

		B.i = u->i + 1;
		B.j = perp_slope * (B.i - u->i) + u->j;

	} else if ((last_j - curr_j == 0) && (last_i - curr_i == 0)) {
		// no change in point

		// what to do when X does not move? 
		// let Y keep the same trajectory it did last
		// need to remember the last move Y did
		// or make Y stop moving

		B.i = u->i;
		B.j = u->j;
	
	} else if ((last_j - curr_j == 0)) {
		// no change in y direction
		// slope = 0
		// perpendicular slope is infinity

		B.i = u->i;		// x coordinate stays the same
		B.j = u->j + 1;	// y coordinate increments
	
	} else if ((last_i - curr_i == 0)) {
		// no change in x direction
		// slope = inf
		// perpendicular slope = 0

		B.i = u->i + 1;
		B.j = u->j;

	}
	
	return B_ptr;

}

// A is new X position
// B is another point on the perpendicular
// P is position of boat Y 
int directionOfPoint(struct Point A, struct Point B, struct Point P) {
    // subtracting co-ordinates of point A from
    // B and P, to make A as origin
    B.i -= A.i;
    B.j -= A.j;
    P.i -= A.i;
    P.j -= A.j;
 
    // Determining cross Product
    int cross_product = B.i * P.j - B.j * P.i;
 
    // return RIGHT if cross product is positive
    if (cross_product > 0)
        return RIGHT;
 
    // return LEFT if cross product is negative
    if (cross_product < 0)
        return LEFT;
 
    // return ZERO if cross product is zero.
    return ZERO;
}