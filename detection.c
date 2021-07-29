// detection code here

// if boat V in region B, 
// is it following bresenham for K iterations?
// if not K iterations, how mucn and what should classify as?
// use a queue to check last 8 locations and check if following bresenham
// if folliwng bresenham for long enough and is in B, then call it chasing
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "diver.h"

#define K 10

struct Point points[SIZE];

// returns a number that represents how far the actual move of V was from the ideal move
// maybe need to change to probabilities (val/100 where val is the return value)
int findRank(struct Point v, struct Point lastV, struct Point idealV) {
	if (lastV.i + 1 == idealV.i && lastV.j + 1 == idealV.j) {

		if ((v.i == lastV.i + 1 && v.j == lastV.j) || (v.i == lastV.i && v.j == lastV.j + 1)) {
		
			// actual position of V is to N or E
			return 1;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i + 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to SE or NW
			return 2;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to W or S
			return 3;

		} else if (v.i == lastV.i - 1 && v.j == lastV.j - 1) {
		
			// actual position of V is to SW
			return 4;

		}
	}

	// when ideal is directly E:
	if (lastV.i + 1 == idealV.i && lastV.j == idealV.j) {

		if ((v.i == lastV.i + 1 && v.j == lastV.j + 1) || (v.i == lastV.i + 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to NE or SE
			return 1;

		} else if ((v.i == lastV.i && v.j == lastV.j + 1) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to N or S
			return 2;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i - 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to NW or SW
			return 3; 

		} else if (v.i == lastV.i - 1 && v.j == lastV.j) {
		
			// actual position of V is to W
			return 4;

		}
	} 

	return 0;
}

// return the amount of steps away from the idea
// return 0 is taken ideal
int idealNotHere = 0;
int getStepsAway(struct Point v, struct Point lastV, struct Point idealV) {
	// ideal is to NE
	if (lastV.i + 1 == idealV.i && lastV.j + 1 == idealV.j) {

		if ((v.i == lastV.i + 1 && v.j == lastV.j) || (v.i == lastV.i && v.j == lastV.j + 1)) {
		
			// actual position of V is to N or E
			return 1;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i + 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to SE or NW
			return 2;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to W or S
			return 3;

		} else if (v.i == lastV.i - 1 && v.j == lastV.j - 1) {
		
			// actual position of V is to SW
			return 4;

		}

		return 0;
	}

	// when ideal is directly E:
	if (lastV.i + 1 == idealV.i && lastV.j == idealV.j) {

		if ((v.i == lastV.i + 1 && v.j == lastV.j + 1) || (v.i == lastV.i + 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to NE or SE
			return 1;

		} else if ((v.i == lastV.i && v.j == lastV.j + 1) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to N or S
			return 2;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i - 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to NW or SW
			return 3; 

		} else if (v.i == lastV.i - 1 && v.j == lastV.j) {
		
			// actual position of V is to W
			return 4;

		}

		// actual position is also E
		return 0;
	} 

	// when ideal is directly N:
	if (lastV.i == idealV.i && lastV.j + 1 == idealV.j) {

		if ((v.i == lastV.i + 1 && v.j == lastV.j + 1) || (v.i == lastV.i - 1 && v.j == lastV.j + 1)) {
		
			// actual position of V is to NE or NW
			return 1;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j) || (v.i == lastV.i + 1 && v.j == lastV.j)) {
		
			// actual position of V is to W or E
			return 2;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j - 1) || (v.i == lastV.i + 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to SW or SE
			return 3; 

		} else if (v.i == lastV.i && v.j == lastV.j - 1) {
		
			// actual position of V is to S
			return 4;

		}

		// actual position is also N
		return 0;
	}

	// when ideal is SE:
	if (lastV.i + 1 == idealV.i && lastV.j - 1 == idealV.j) {

		if ((v.i == lastV.i + 1 && v.j == lastV.j) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to E or S
			return 1;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j - 1) || (v.i == lastV.i + 1 && v.j == lastV.j + 1)) {
		
			// actual position of V is to SW or NE
			return 2;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j) || (v.i == lastV.i && v.j == lastV.j + 1)) {
		
			// actual position of V is to W or N
			return 3; 

		} else if (v.i == lastV.i - 1 && v.j == lastV.j + 1) {
		
			// actual position of V is to NW
			return 4;

		}

		// actual position is also SE
		return 0;
	} 

	// when ideal is to S:
	if (lastV.i == idealV.i && lastV.j - 1 == idealV.j) {

		if ((v.i == lastV.i + 1 && v.j == lastV.j - 1) || (v.i == lastV.i - 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to SE or SW
			return 1;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j) || (v.i == lastV.i + 1 && v.j == lastV.j)) {
		
			// actual position of V is to W or E
			return 2;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i + 1 && v.j == lastV.j + 1)) {
		
			// actual position of V is to NW or NE
			return 3; 

		} else if (v.i == lastV.i && v.j == lastV.j + 1) {
		
			// actual position of V is to N
			return 4;

		}

		// actual position is also S
		return 0;
	}

	idealNotHere++;
	return 0;
}

float findProb(struct Point v, struct Point lastV, struct Point idealV) {

	printf("\nin findProb() \n");
	printf("lastV: (%d, %d) current v: (%d, %d) idealV: (%d, %d)\n", lastV.i, lastV.j, v.i, v.j, idealV.i, idealV.j);
	

	// if stayed in place
	if (lastV.i == v.i && lastV.j == v.j) {
		printf("stayed in place\n\n");
		return 1.0/100;	// change this from 0
	}

	// when ideal is to NE
	if (lastV.i + 1 == idealV.i && lastV.j + 1 == idealV.j) {	

		printf("ideal is NE\n");

		if (v.i == lastV.i + 1 && v.j == lastV.j) {
		
			// actual position of V is to E
			printf("actually went to E\n\n");
			return 20.0/100;

		} else if (v.i == lastV.i && v.j == lastV.j + 1) {

			// actual pos of V is to N
			printf("actually went to N\n\n");
			return 12.0/100;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i + 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to NW or SE
			printf("actually went to NW or SE\n\n");
			return 8.0/100;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to W or S
			printf("actually went to W or S\n\n");
			return 4.0/100;

		} else if (v.i == lastV.i - 1 && v.j == lastV.j - 1) {
		
			// actual position of V is to SW
			printf("actually went to SW\n\n");
			return 2.0/100;

		} else {

			// V is ideal
			return 40.0/100;

		}
	}

	// when ideal is directly E:
	if (lastV.i + 1 == idealV.i && lastV.j == idealV.j) {

		printf("ideal is E\n");

		if (v.i == lastV.i + 1 && v.j == lastV.j + 1) {
		
			// actual position of V is to NE
			printf("actually went to NE\n\n");
			return 20.0/100;

		} else if (v.i == lastV.i + 1 && v.j == lastV.j - 1) {

			// actual position is to SE
			printf("actually went to SE\n\n");
			return 12.0/100;

		} else if ((v.i == lastV.i && v.j == lastV.j + 1) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to N or S
			printf("actually went to N or S\n\n");
			return 8.0/100;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i - 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to NW or SW
			printf("actually went to NW or SW\n\n");
			return 4.0/100; 

		} else if (v.i == lastV.i - 1 && v.j == lastV.j) {
		
			// actual position of V is to W
			printf("actually went to W\n\n");
			return 2.0/100;

		} else {

			// ideal
			printf("went ideal\n\n");
			return 40.0/100;

		}
	} 

	// invisible
	return 1.0/100;
}

// returns an integer corresponding with the decision that took the boat
// from last to current point
int findDecision(struct Point lastPoint, struct Point currPoint) {

	/*
	#define N .1
#define NE .2
#define E .3
#define SE .4
#define S .5
#define SW .6
#define W .7 
#define NW .8
#define STAY .9
#define GONE 0
*/

	if (currPoint.i == lastPoint.i && currPoint.j == lastPoint.j + 1) {	// N
		return 1;
	} else if (currPoint.i == lastPoint.i + 1 && currPoint.j == lastPoint.j + 1) {	// NE
		return 2;
	} else if (currPoint.i == lastPoint.i + 1 && currPoint.j == lastPoint.j) { 	// E
		return 3;
	} else if (currPoint.i == lastPoint.i + 1 && currPoint.j == lastPoint.j - 1) { 	// SE
		return 4;
	} else if (currPoint.i == lastPoint.i && currPoint.j == lastPoint.j - 1) {	// S
		return 5;
	} else if (currPoint.i == lastPoint.i - 1 && currPoint.j == lastPoint.j - 1) {	// SW
		return 6;
	} else if (currPoint.i == lastPoint.i - 1 && currPoint.j == lastPoint.j) {	// W
		return 7;
	} else if (currPoint.i == lastPoint.i - 1 && currPoint.j == lastPoint.j + 1) {	// NW
		return 8;
	} else if (currPoint.i == lastPoint.i && currPoint.j == lastPoint.j) {	// STAY
		return 9;
	} else if (currPoint.i == 0 && currPoint.j == 0) {	// INVISIBLE
		return 0;
	}

	return 0;
}

// returns distance between points u and v
float getDistance(struct Point * u, struct Point * v) {
	float dist;
	float x1 = v->i;
	float y1 = v->j;
	float x2 = u->i;
	float y2 = u->j;

	dist = sqrt ((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	printf("Distance between (%0.2f, %0.2f) and (%0.2f, %0.2f) is %0.2f\n", x1, y1, x2, y2, dist);

	return dist;

}

int detect(struct Params * params, struct Point * u, struct Point * v) {

	char line[1024];
	struct Point idealV;
	struct Point lastV;
	int t = 0;
	float distance;
	float probability;
	float entropy;
	int dec;
	int totalStepsAway;

	while (fgets(line, 1024, params->fpt) != NULL) {

		printf("\ncount %d\n", t);
		// store last V
		lastV.i = v->i;
		lastV.j = v->j;
		// find current U and V positions
		u->i = atoi(strtok(line, ","));
		u->j = atoi(strtok(NULL, ","));
		v->i = atoi(strtok(NULL, ","));
		v->j = atoi(strtok(NULL, " "));

		printf("U: (%d, %d) V: (%d, %d)\n", u->i, u->j, v->i, v->j);

		// check distance away
		// have a queue holding the distance?
		if (t != 0) {

			// check if full
			if (Fifo_StatusDist() == FIFO_SIZE - 1) {
				Fifo_GetDist();
				Fifo_GetRank();
			}

			// calculate distance and store in distancQueue
			distance = getDistance(u, v);
			Fifo_PutDist(distance);

			// check how far from bresenham 
			// printf("V: (%d, %d) next best: (%d, %d)\n", v->i, v->j, idealV.i, idealV.j);
			Fifo_PutRank(getStepsAway(*v, lastV, idealV));

			// check if decision queue is full
			if (Fifo_StatusDec() == FIFO_SIZE - 1) {
				Fifo_GetDec();
			}
			
			// store decision taken into queueDecision
			// find decision using last V and current V
			// entropy is calculated from the decision queue
			dec = findDecision(lastV, *v);
			Fifo_PutDec(dec);
			
			totalStepsAway = getTotalStepsAway();
			entropy = getEntropy();
			if (t >= FIFO_SIZE)
				fprintf(params->fpt_detection, "%.4f,%d\n", entropy, totalStepsAway);
			
		}

		// check bresenham
		printf("find best path between V: (%d, %d) U: (%d, %d)\n", v->i, v->j, u->i, u->j);	
		findPath(points, v->i, v->j, u->i, u->j);	// changed from findPathSofie()
		idealV.i = points[1].i;
		idealV.j = points[1].j;
		printf("\tnext best: (%d, %d)\n", idealV.i, idealV.j);

		printf("\n");
		displayDist();
		displayRank();

		// multiply all probabilities
		probability = probabilityScore();
		printf("running probability: %f\n", probability);

		if (t > params->maxsteps) {
			printf("break\n");
			printf("not caught in getStepsAway(): %d\n", idealNotHere);
			break;
		}	
		t++;
		printf("\n ------------------------------ \n");

	}
	printf("not caught in getStepsAway(): %d\n", idealNotHere);
	return 0;
}