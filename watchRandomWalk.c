// watchRandomWalk.c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "diver.h"

#define STEPS 200

struct Point points[SIZE];

void randomwalk(struct Params * params, struct Point * u, struct Point * v) {

	float prob = (rand() % 100) *.01;

  	int* coordPtr;
  	int t = 0;

  	while (t < params->maxsteps) {

  		// get new current location of V
		coordPtr = randomPoint(v->i, v->j, prob);
		v->i = *coordPtr;
		v->j = *(coordPtr + 1);

		updateU(u, params->u_activity, t, prob);

		fprintf(params->fpt, "%d, %d, %d, %d\n", u->i, u->j, v->i, v->j);	// print to csv file

		prob = (rand() % 100) *.01;
		t++;

  	}

}