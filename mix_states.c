#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "diver.h"

// call all three states for k +/- random number steps 

void mix_states(struct Params * params, struct Point * u, struct Point * v) {
  
 	int t, k = 0;
 	int total_t = params->maxsteps;
 	double prob = rand() % 20;
 	k = 30 + prob;

 	//int chase_at_end = 0;
  	while (1) {    
    	

    	params->maxsteps = k - 1;	
    	prob = rand() % 5;		// this prob is to choose which activity to do

    	// if in region A
  		// only chase
  		v->region = inPolarRegion(v->i, v->j, u->i, u->j);
		printf("region: %c\n", v->region);
		printf(" t = %d, k= %d\n", t, k);
		/*
		if (v->region == 'a' || t == total_t) {
			is_verbose = 0;
			use_chasing_prob = 1;
			params->chasing_prob =  0.95;
			params->maxsteps = 1000;
			chase(params, u, v);
		} else {
*/
			if (prob == 0 || prob == 1) {
  				// random walk
  				randomwalk(params, u, v);
  			} else if (prob == 2) {
  				// chasing
  				//params->maxsteps = k;
  				chase(params, u, v);
  			} else if (prob == 3 || prob == 4) {
  				// zigzag/follow
  				follow(params, u, v);
  			}

/*		} else {

			if (prob == 0) {
  				// random walk
  				randomwalk(params, u, v);
  			} else if (prob == 1) {
  				// chasing
  				params->maxsteps = k/2;
  				chase(params, u, v);
  			} 

		}*/
    	
    	//printf("%d, %d  %d, %d  %d\n", v->i, v->j, u->i, u->j, t);
		//fprintf(params->fpt, "%d, %d, %d, %d, %c, %d\n", u->i, u->j,  v->i, v->j, v->region, t);	// print to csv file
    	/*
    	t += (k - 1);
    	double prob = rand() % 20;
 		k = 30 + prob;
 		if (k + t >= total_t - 1) {	// not to surpass total_t in command line
    		k = total_t - t;
    		params->maxsteps = k - 1;
    		chase(params, u, v);
    	}
    	printf(" --> t = %d, k= %d\n", t, k);
		*/
  		
    	if (t >= (total_t - 1) || (v->i == u->i && v->j == u->j)) {
      		printf("\n-------\nbreak\nt = %d\n", t);

      		break;
		}	

    	t += (k - 1);
    	double prob = rand() % 20;
 		k = 30 + prob;
 		
 		if (k + t >= total_t - 1) {	// not to surpass total_t in command line
    		k = total_t - t;
    	}
    	printf(" --> t = %d, k= %d\n", t, k);


  }
  params->maxsteps = total_t;
}
