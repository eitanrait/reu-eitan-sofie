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

float findProb(struct Point v, struct Point lastV, struct Point idealV) {

	printf("v: (%d, %d) lastV: (%d, %d)\n", v.i, v.j, lastV.i, lastV.j);
	
	// if stayed in place
	if (lastV.i == v.i && lastV.j == v.j) {
		return 1.0/100;	// change this from 0
	}

	// when ideal is to NE
	if (lastV.i + 1 == idealV.i && lastV.j + 1 == idealV.j) {	

		printf("ideal is NE\n");

		if (v.i == lastV.i + 1 && v.j == lastV.j) {
		
			// actual position of V is to E
			return 20.0/100;

		} else if (v.i == lastV.i && v.j == lastV.j + 1) {

			// actual pos of V is to N
			return 12.0/100;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i + 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to NW or SE
			return 8.0/100;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to W or S
			return 4.0/100;

		} else if (v.i == lastV.i - 1 && v.j == lastV.j - 1) {
		
			// actual position of V is to SW
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
			return 20.0/100;

		} else if (v.i == lastV.i + 1 && v.j == lastV.j - 1) {

			// actual position is to SE
			return 12.0/100;

		} else if ((v.i == lastV.i && v.j == lastV.j + 1) || (v.i == lastV.i && v.j == lastV.j - 1)) {
		
			// actual position of V is to N or S
			return 8.0/100;

		} else if ((v.i == lastV.i - 1 && v.j == lastV.j + 1) || (v.i == lastV.i - 1 && v.j == lastV.j - 1)) {
		
			// actual position of V is to NW or SW
			return 4.0/100; 

		} else if (v.i == lastV.i - 1 && v.j == lastV.j) {
		
			// actual position of V is to W
			return 2.0/100;

		} else {

			// ideal
			return 40.0/100;

		}
	} 

	// invisible
	return 1.0/100;
}

// classify which region V is in
// if in B,
// needs to know current location of V, draw bresenham using current locations, compare with actual next movement of V
// push "yes" (1) and "no" (0) to queue
// classify as chasing if... 
// consider:
// more yes's than no's
// consecuitive no's to disqualify

// two queues, one storing locations and one storing yes or nos 
// might be limited if just storing hits and misses

int detectChasing(struct Params * params, struct Point * u, struct Point * v) {

	char line[1024];
	struct Point idealV;
	struct Point lastV;
	int t = 0;
	float probability;
	//int rankingSum = 0;
	
	while (fgets(line, 1024, params->fpt) != NULL) {

		printf("\n\ncount %d\n", t);
		// find current U and V positions
		lastV.i = v->i;
		lastV.j = v->j;
		u->i = atoi(strtok(line, ","));
		u->j = atoi(strtok(NULL, ","));
		v->i = atoi(strtok(NULL, ","));
		v->j = atoi(strtok(NULL, " "));
		
		//printf("U: (%d, %d) V: (%d, %d)\n", u->i, u->j, v->i, v->j);

		// compare with next actual point of V
		// check if first move
		// if not first move, compare
		if (t != 0) {

			// check if full
			if (Fifo_StatusYN() == FIFO_SIZE - 1) {
				Fifo_GetYN();
				Fifo_GetRank();
			}

			//printf("before enQueue\n");
			
			//printf("\nidealV.i: %d idealV.j: %d\n\n    v->i: %d     v->j: %d\n\n",idealV.i,idealV.j,v->i,v->j); // compare
			
			if (idealV.i == v->i && idealV.j == v->j) {
				// next best point is equal to point actually chosen
				printf("V: (%d, %d) next best: (%d, %d)\n", v->i, v->j, idealV.i, idealV.j);
				printf("--YES--\n");
				Fifo_PutYN(YES);
				Fifo_PutRank(findProb(*v, lastV, idealV));

			} else {
				printf("V: (%d, %d) next best: (%d, %d)\n", v->i, v->j, idealV.i, idealV.j);

				Fifo_PutYN(NO);
				Fifo_PutRank(findProb(*v, lastV, idealV));
				
			}
			//rankingSum = findSum(queueRank, headRank, tailRank);
			//printf("sum: %d\n", rankingSum);
			//printf("after enQueue\n");
		}

		// multiply all probabilities
		probability = probabilityScore();
		printf("running probability: %f\n", probability);

		// store position of V in position queue
		// find next best point using Bresenham
		// from V (chasing) to U (chasee)
		printf("find best path between V: (%d, %d) U: (%d, %d)\n", v->i, v->j, u->i, u->j);	
		findPathSofie(points, v->i, v->j, u->i, u->j);
		//printf("U: (%d, %d)\n", U.i, U.j);
		idealV.i = points[1].i;
		idealV.j = points[1].j;

		// classify ranking queue
		// find running sum of a queue :/

		// print contents of queue
		if(is_verbose) {
			displayYN();
			displayRank();

		}
		
		if (t > params->maxsteps) {
			printf("break\n");
			break;
		}
		
		t++;
	} 

	// find next best point
	// compare with next actual point of V
	return 0;

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

int detectRandomWalk(struct Params * params, struct Point * u, struct Point * v) {

	char line[1024];
	struct Point lastV;
	int t = 0;
	float entropy;
	int dec;
	
	while (fgets(line, 1024, params->fpt) != NULL) {

		printf("\ncount %d\n", t);
		// store last coordinates of V
		lastV.i = v->i;
		lastV.j = v->j;
		// find current U and V positions
		u->i = atoi(strtok(line, ","));
		u->j = atoi(strtok(NULL, ","));
		v->i = atoi(strtok(NULL, ","));
		v->j = atoi(strtok(NULL, " "));

		printf("U: (%d, %d) V: (%d, %d)\n", u->i, u->j, v->i, v->j);
	
		// compare with next actual point of V	
		// check if first move
		// if not first move, compare
		if (t != 0) {

			// check if full
			if (Fifo_StatusDec() == FIFO_SIZE - 1) {
				Fifo_GetDec();
			}
			//printf("before enQueue\n");
			
			// store decision taken into queueDecision
			// find decision using last V and current V
			dec = findDecision(lastV, *v);
			Fifo_PutDec(dec);

			// 
			//runningSum = findSum(queueDecision, headDecision, tailDecision);
			//printf("sum: %d\n", runningSum);

		}
		entropy = getEntropy();
		// print contents of queue
		//printf("%d - %d = %d: ", tailDecision, headDecision, tailDecision - headDecision);
		
		displayDec();
		//display(headDecision, tailDecision, queueDecision);
		printf("\nEntropy: %f\n\n", entropy);

		if (t > params->maxsteps) {
			printf("break\n");
			break;
		}	
		t++;
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

int detectFollow(struct Params * params, struct Point * u, struct Point * v) {

	char line[1024];
	struct Point lastV;
	int t = 0;
	int dec;
	float distance;
	
	while (fgets(line, 1024, params->fpt) != NULL) {

		printf("\ncount %d\n", t);
		// find current U and V positions
		lastV.i = v->i;
		lastV.j = v->j;
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
			}

			// calculate distance and store in distancQueue
			distance = getDistance(u, v);
			Fifo_PutDist(distance);

			// check how far from bresenham 

		}

		// check bresenham
		// check randomwalk
		displayDist();

		if (t > params->maxsteps) {
			printf("break\n");
			break;
		}	
		t++;

	}

	return 0;

}