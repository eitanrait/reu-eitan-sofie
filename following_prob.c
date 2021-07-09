// start writing foAllowing algo here

// what does it mean to be behind X?
// Boat V is behind U when V is behind U for a certain amount of time
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "diver.h"

struct Point points[SIZE];

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
    return 2;
  }
  
  directionV = directionOfPoint(*u, B, *v);
  directionLastU = directionOfPoint(*u, B, lastU);
  
  //printf("X: (%d, %d)  B: (%d, %d)  directionY: %d  directionLastX: %d\n", X.i, X.j, B.i, B.j, directionY, directionLastX);
  
  if (directionLastU == directionV) {
    return 1;
  }
  
  return 0;
  
}

void follow(struct Params * params, struct Point * u, struct Point * v) {
  
 	int t = 0;
	int behind = 0; // 0 - not behind, 1 - behind                                                                                
	double last_i, last_j;
	int * coordPtr;
	
  	srand(params->randomseed);
	
	float prob = (rand() % 100) *.01;
	findPathSofie(points, v->i, v->j, u->i, u->j);
  	int noMovement = 2;
  
  	fprintf(params->fpt, "%d, %d, %d, %d, %c, %d\n", u->i, u->j,  v->i, v->j, v->region, t); // initial point
  	
  	while (1) {    
    
		// remember last position of boat U
		last_i = u->i;
		last_j = u->j;
		
  		updateU(u, params->u_activity, t, prob);
    
    	// check where Y is 
    	behind = isVBehind(u, v, last_i, last_j);
    	// store Y position
    
    	// check which region boat Y is in
    	v->region = inPolarRegion(v->i, v->j, u->i, u->j);
		printf("behind: %d,  region: %c\n",behind,v->region);
    
    	// if boat V in region A, chase 
    	// if boat V in region B, chase with stealth
    	// if boat V in outer regions and behind, disguised walk towards boat U
    	// else, stay in place
    	// update prob for Y movement
    	prob = (rand() % 100) *.01;
	    if (behind == 1 && (v->region == 'a')) {
	    	noMovement = 2;
    	 	// move Y towards X
     		// get new line towards Boat X/U
			findPathSofie(points, v->i, v->j, u->i, u->j);
     	 	v->i = points[1].i;
     	 	v->j = points[1].j;
    	} else if (behind == 1 && (v->region == 'b')) { // in region B   		
    		noMovement = 2;
			prob = (rand() % 100) *.01;    		
     	 	if (prob < 0.33) {
				// random walk
				printf("randomwalk in region b\n");
				coordPtr = randomPoint(v->i, v->j, prob);
				v->i = *coordPtr;
				v->j = *(coordPtr + 1);
				//findPathSofie(points, v->i, v->j, u->i, u->j);
	  		} else {
  				// walks towards X more often
				printf("calculate new line and follow in region b\n");
				findPathSofie(points, v->i, v->j, u->i, u->j);
				v->i = points[1].i;
				v->j = points[1].j;
			}
   		} else if (behind == 1) { // behind and in regions C and D
      		noMovement = 2;
			prob = (rand() % 100) *.01;    		
      		if (prob < 0.50) { // move forward along bresenham's line
				findPathSofie(points, v->i, v->j, u->i, u->j);	
				v->i = points[1].i;
				v->j = points[1].j;
      		} else { //randomwalk
				coordPtr = randomPoint(v->i, v->j, prob);
				v->i = *coordPtr;
				v->j = *(coordPtr + 1);
				//findPathSofie(points, v->i, v->j, u->i, u->j);					
    		}
    		
    } else if (behind == 2) { // enter this condition if no movement of boat U is detected
      						  // boat V should continue moving along the path determined from 
      						  // the last time findPath() updated the contents of the points array
		if (t == 1) { // if U does not move at 1st tic, update v position to the next coordinate on the line 
      		v->i = points[1].i;
      		v->j = points[1].j;
      	} else { 			  // u does not move, keep updating v position to the following coordinate on the line
      		v->i = points[noMovement].i; 
      		v->j = points[noMovement].j;
      	}
      	noMovement++;
      	
    } else { 		  // stay in place when Y is on the wrong side of the perpendicular line 
      noMovement = 2; // starting index of boat V's position when boat U does not move that tic
    }
    
    printf(" v: %d, %d  u: %d, %d  %d\n", v->i, v->j, u->i, u->j, t);
	fprintf(params->fpt, "%d, %d, %d, %d, %c, %d\n", u->i, u->j,  v->i, v->j, v->region, t);	// print to csv file
    
    if (t > params->maxsteps || (v->i == u->i && v->j == u->j)) {
      printf("break\n");
      break;
    }
    prob = (rand() % 100) *.01;
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