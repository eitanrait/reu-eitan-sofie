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
#include "driver.h"

#define K 10

struct Point points[SIZE];

int headYN, tailYN, elemtYN;
int queueYN[QUEUE_SIZE-1];

int headRank, tailRank, elemtRank;
int queueRank[QUEUE_SIZE-1];

int headDecision, tailDecision, elemtDecision;
int queueDecision[QUEUE_SIZE -1];

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
	//int rankingSum = 0;

	init(&headYN,&tailYN);
	init(&headRank,&tailRank);
	
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
			if (isFull(headYN, tailYN))
				deQueue(&headYN,&tailYN,queueYN);

			if (isFull(headRank, tailRank))
				deQueue(&headRank, &tailRank, queueRank);

			//printf("before enQueue\n");
			//printf("queueYN: %p\n", queueYN);
			//printf("&tailYN: %p\n", &tailYN);
			
			printf("\n\n idealV.i: %d, idealV.j: %d\n\n v->i: %d, v->j: %d\n\n",idealV.i,idealV.j,v->i,v->j); // compare
			
			if (idealV.i == v->i && idealV.j == v->j) {
				// next best point is equal to point actually chosen
				enQueue(&headYN, &tailYN, YES, queueYN);
				enQueue(&headRank, &tailRank, NO, queueRank);
				//enQueue(queueYN, &tailYN, y_ptr);
				//enQueue(queueRank, &tailRank, n_ptr);
			} else {
				//printf("V: (%d, %d) next best: (%d, %d)\n", v->i, v.j, idealV.i, idealV.j);
				//enQueue(queueYN, &tailYN, n_ptr);
				enQueue(&headYN, &tailYN, NO, queueYN);
				enQueue(&headRank, &tailRank, findRank(*v, lastV, idealV), queueRank); // add ranking to however far the actual is from ideal
			}
			//rankingSum = findSum(queueRank, headRank, tailRank);
			//printf("sum: %d\n", rankingSum);
			//printf("after enQueue\n");
		}
		// store position of V in position queue
		// find next best point using Bresenham
		// from V (chasing) to U (chasee)
		printf("\nfind best path between V: (%d, %d) U: (%d, %d)\n", v->i, v->j, u->i, u->j);	
		findPathSofie(points, v->i, v->j, u->i, u->j);
		//printf("U: (%d, %d)\n", U.i, U.j);
		idealV.i = points[1].i;
		idealV.j = points[1].j;

		// classify ranking queue
		// find running sum of a queue :/

		// print contents of queue
		display(headYN, tailYN, queueYN);
		display(headRank, tailRank, queueRank);
		
		printf("\n\n v->i:    %d\n v->j:    %d\n\n\n",v->i,v->j);
		
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
		// find current U and V positions
		lastV.i = v->i;
		lastV.j = v->j;
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
			if (isFull(headDecision, tailDecision)) {
				deQueue(&headDecision,&tailDecision, queueDecision);
			}
			printf("before enQueue\n");
			
			// store decision taken into queueDecision
			// find decision using last V and current V
			dec = findDecision(lastV, *v);
			enQueue(&headDecision, &tailDecision, dec, queueDecision);

			// 
			//runningSum = findSum(queueDecision, headDecision, tailDecision);
			//printf("sum: %d\n", runningSum);

		}
		entropy = getEntropy(headDecision, tailDecision, queueDecision);
		// print contents of queue
		//printf("%d - %d = %d: ", tailDecision, headDecision, tailDecision - headDecision);
		display(headDecision, tailDecision, queueDecision);
		printf("\nEntropy: %f\n\n", entropy);

		if (t > params->maxsteps) {
			printf("break\n");
			break;
		}	
		t++;
	} 
	return 0;
}