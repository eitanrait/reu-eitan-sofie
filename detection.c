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
#include "Queue.h"
#include "classification.h"

#define K 10
#define SIZE 17

typedef struct {
  int i;
  int j;
  char region;
} point_t;


point_t points[SIZE];	// points is an array of type point_t
point_t U;
point_t V;

int headYN, tailYN, elemtYN;
int queueYN[SIZE-1];

int headRank, tailRank, elemtRank;
int queueRank[SIZE];

int headDecision, tailDecision, elemtDecision;
int queueDecision[SIZE];

// returns the sign of a - b
int Sign(int a, int b) {
  int c;
  c = a-b;

  if(c > 0)
    return 1;
  else if(c < 0)
    return -1;
  else
    return 0;
}

// use the Bresenham algorithm for drawing a line                                                                                                                                                  
// to find the fastest path from pixel a to b                                                                                                                                                     
void findPath(int x1, int y1, int x2, int y2) {
  int A, B, E, x, y, t, deltX, deltY, s1, s2, temp, interchange;
  t = 0;
  x = x1;
  y = y1;
  deltX = abs(x2-x1);
  deltY = abs(y2-y1);
  s1 = Sign(x2,x1);
  s2 = Sign(y2,y1);
  
  if(deltY > deltX) {
    temp = deltX;
    deltX = deltY;
    deltY = temp;
    interchange = 1;
  }
  else {
    interchange = 0;
  }

  E = 2 * deltY - deltX;
  A = 2 * deltY;
  B = 2 * deltY - 2 * deltX;                                                                                                                                                                         

  points[t].i = x;
  points[t].j = y;

  for (int i=0;i<4;i++) {
    if ( E < 0 ) {
      if ( interchange == 1 ) {
        y = y + s2;
      }
      else {
        x = x + s1;
      }
      E = E + A;
    }
    else {
      y = y + s2;
      x = x + s1;
      E = E + B;
    }
    
    t++;
    points[t].i = x;
    points[t].j = y;
  }
}

// use the Bresenham algorithm for drawing a line
// to find the fastest pasth from pixel a to b 
void findPathBres(int x0, int y0, int x1, int y1) { 
    int A, B, g, x, y, t;

    t = 0;
  B = x0 - x1;
  A = y1 - y0;
 
  x = x0;
  y = y0;
 
  g = 2 * A + B;  // initial biased error
  int diag_inc = 2 * (A + B);
  int right_inc = 2 * A; 
 
  while (x <= x1 && t < SIZE) {
    points[t].i = x;
    points[t].j = y;

    if(g >= 0) {

      // go in y direction
      y = y + 1;
      g = g + diag_inc;

    } else {  // if error is negative

      // go in x direction
      g = g + right_inc;

    }
    x = x + 1;  // increment in x direction
    t = t + 1;  // increment array index

  }

}

// returns a number that represents how far the actual move of V was from the ideal move
// maybe need to change to probabilities (val/100 where val is the return value)
int findRank(point_t lastV, point_t idealV) {
	if (lastV.i + 1 == idealV.i && lastV.j + 1 == idealV.j) {

		if ((V.i == lastV.i + 1 && V.j == lastV.j) || (V.i == lastV.i && V.j == lastV.j + 1)) {
		
			// actual position of V is to N or E
			return 1;

		} else if ((V.i == lastV.i - 1 && V.j == lastV.j + 1) || (V.i == lastV.i + 1 && V.j == lastV.j - 1)) {
		
			// actual position of V is to SE or NW
			return 2;

		} else if ((V.i == lastV.i - 1 && V.j == lastV.j) || (V.i == lastV.i && V.j == lastV.j - 1)) {
		
			// actual position of V is to W or S
			return 3;

		} else if (V.i == lastV.i - 1 && V.j == lastV.j - 1) {
		
			// actual position of V is to SW
			return 4;

		}
	}

	// when ideal is directly E:
	if (lastV.i + 1 == idealV.i && lastV.j == idealV.j) {

		if ((V.i == lastV.i + 1 && V.j == lastV.j + 1) || (V.i == lastV.i + 1 && V.j == lastV.j - 1)) {
		
			// actual position of V is to NE or SE
			return 1;

		} else if ((V.i == lastV.i && V.j == lastV.j + 1) || (V.i == lastV.i && V.j == lastV.j - 1)) {
		
			// actual position of V is to N or S
			return 2;

		} else if ((V.i == lastV.i - 1 && V.j == lastV.j + 1) || (V.i == lastV.i - 1 && V.j == lastV.j - 1)) {
		
			// actual position of V is to NW or SW
			return 3; 

		} else if (V.i == lastV.i - 1 && V.j == lastV.j) {
		
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
#define YES 1
#define NO 0

int detectChasing(char * filename) {

	// taking points from csv_files/chasing_diagonal.csv
	// or csv_files/approaching.csv
	FILE *f;
	point_t * U_ptr = &U;
	char line[1024];
	point_t idealV;
	point_t lastV;
	int count = 0;
	int rankingSum = 0;
	int rank;

	if (!(f = fopen(filename, "r"))) {
		printf("no file: %s\n", filename);
		return 1;
	}
	printf("opened file\n");
	while (fgets(line, 1024, f) != NULL) {

		printf("\ncount %d\n", count);
		// find current U and V positions
		lastV.i = V.i;
		lastV.j = V.j;
		U.i = atoi(strtok(line, ","));
		U.j = atoi(strtok(NULL, ","));
		V.i = atoi(strtok(NULL, ","));
		V.j = atoi(strtok(NULL, " "));
		printf("U(1): (%d, %d)\n", U.i, U.j);

		//printf("U: (%d, %d) V: (%d, %d)\n", U.i, U.j, V.i, V.j);

		// compare with next actual point of V
		// check if first move
		// if not first move, compare
		if (count != 0) {

			// check if full
			if (full(headYN, tailYN, SIZE)) {
				dequeue(queueYN, &headYN);
			}
			printf("before enqueue\n");
			printf("U(2): (%d, %d)\n", U.i, U.j);
			//printf("queueYN: %p\n", queueYN);
			//printf("&tailYN: %p\n", &tailYN);
			// compare
			if (idealV.i == V.i && idealV.j == V.j) {
				// next best point is equal to point actually chosen
				enqueue(queueYN, &tailYN, YES);
				enqueue(queueRank, &tailRank, 0);
			} else {
				printf("V: (%d, %d) next best: (%d, %d)\n", V.i, V.j, idealV.i, idealV.j);
				enqueue(queueYN, &tailYN, NO);
				// add ranking to however far the actual is from ideal
				rank = findRank(lastV, idealV);
				enqueue(queueRank, &tailRank, rank);

			}
			printf("after enqueue\n");
			printf("U(3): (%d, %d)\n", U.i, U.j);
			//printf("U: %p\n", U_ptr);
		}

		// store position of V in position queue

		// find next best point using Bresenham
		// from V (chasing) to U (chasee)
		printf("find best path between V: (%d, %d) U: (%d, %d)\n", V.i, V.j, U.i, U.j);
		findPathBres(V.i, V.j, U.i, U.j);
		printf("U(4): (%d, %d)\n", U.i, U.j);
		idealV.i = points[1].i;
		idealV.j = points[1].j;

		printf("ideal move: (%d, %d)\n", idealV.i, idealV.j);
		printf("U(5): (%d, %d)\n", U.i, U.j);
		//printf("nextBestV: (%d, %d)\n", nextBestV.i, nextBestV.j);

		// classify ranking queue
		// find running sum of a queue :/

		// print contents of queue
		printf("%d - %d = %d: ", tailYN, headYN, tailYN - headYN);
		display(queueYN, headYN, tailYN);
		display(queueRank, headRank, tailRank);

		if (count > SIZE*2) {
			break;
		}
		count++;

	} 

	// find next best point
	// compare with next actual point of V
	return 0;

}

// returns an integer corresponding with the decision that took the boat
// from last to current point
int findDecision(point_t lastPoint, point_t currPoint) {

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

int detectRandomWalk(char * filename) {

	// taking points from csv_files/watch_random_walk_static.csv
	FILE *f;
	char line[1024];
	point_t lastV;
	int count = 0;
	int dec;

	if (!(f = fopen(filename, "r"))) {
		printf("no file: %s\n", filename);
		return 1;
	}
	printf("opened file\n");
	while (fgets(line, 1024, f) != NULL) {

		printf("\ncount %d\n", count);
		// find current U and V positions
		lastV.i = V.i;
		lastV.j = V.j;
		U.i = atoi(strtok(line, ","));
		U.j = atoi(strtok(NULL, ","));
		V.i = atoi(strtok(NULL, ","));
		V.j = atoi(strtok(NULL, " "));
		printf("U(1): (%d, %d)\n", U.i, U.j);

		printf("U: (%d, %d) V: (%d, %d)\n", U.i, U.j, V.i, V.j);

		// compare with next actual point of V
		// check if first move
		// if not first move, compare
		if (count != 0) {

			// check if full
			if (full(headDecision, tailDecision, SIZE)) {
				dequeue(queueDecision, &headDecision);
			}
			printf("before enqueue\n");
			printf("U(2): (%d, %d)\n", U.i, U.j);
			
			// store decision taken into queueDecision
			// find decision using last V and current V
			dec = findDecision(lastV, V);
			enqueue(queueDecision, &tailDecision, dec);
			printf("U(3): (%d, %d)\n", U.i, U.j);

		}

		// print contents of queue
		printf("%d - %d = %d: ", tailDecision, headDecision, tailDecision - headDecision);
		display(queueDecision, headDecision, tailDecision);

		if (count > SIZE*2) {
			break;
		}
		count++;

	} 

	return 0;

}


int main() {

	init(&headYN, &tailYN);
	init(&headRank, &tailRank);
	init(&headDecision, &tailDecision);

	//detectChasing("csv_files/approaching.csv");	// approaching.csv  chasing_diagonal.csv
	detectRandomWalk("csv_files/watch_random_walk_static.csv");
	return 1;
}

// to compile
// gcc -Wall detection.c Queue.c classification.c -lm -o detect
