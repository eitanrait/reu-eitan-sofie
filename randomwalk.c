#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "diver.h"

#define N .1
#define NE .2
#define E .3
#define SE .4
#define S .5
#define SW .6
#define W .7 
#define NW .8
#define STAY .9
#define GONE 1 

float movements[10] = {N, NE, E, SE, S, SW, W, NW, STAY, GONE};

/*
#define I 210
#define J 720


#define N .2
#define NE .4
#define E .6
#define SE .7
#define S .75
#define SW .8
#define W .85 
#define NW .9
#define STAY .95
#define GONE 1


struct Point path[STEPS];

int randomwalk() {
  float prob;
  int t;
  struct point p;
  
  srand(time(0));
  prob = (rand() % 100) *.01;
  p.i = I;
  p.j = J;
  
  for(t=0;t<STEPS;t++) {
      if (prob >= 0 && prob < N)
	      p.j++;
      else if (prob < NE) {
      	p.i++;
        p.j++;
      }
      else if (prob < E)
        p.i++;
      else if ( prob < SE) {
      	p.i++;
      	p.j--;
      }
      else if (prob < S)
	      p.j--;  
      else if (prob < SW) {
      	p.i--;
      	p.j--;
      }
      else if(prob < W)
	      p.i--;
      else if (prob < NW) {
      	p.i--;
      	p.j++;
      }
      else {}    

      if(prob >= STAY && prob < GONE) {
      	strcpy(path[t].visible,"not visible");
      	//printf("%s , probability = %.2f\n",points[a].visible, prob);
      }
      else {
      	path[t].i = p.i;
      	path[t].j = p.j;
	      //printf("i= %d, j= %d, probability = %.2f\n",coordinates[t].i,coordinates[t].j, prob);
      }
      prob = (rand() % 100) * .01;
  }

  int index;

  for (index = 0; index < STEPS; index++) {
    if(strcmp(path[index].visible,"") == 0)
      printf("%d,%d\n",path[index].i,path[index].j);
    else 
      printf("not visible\n");
  }
  
  printf("\n");

  return 0;
} */

void randomwalk(struct Params * params, struct Point * u, struct Point * v) {

  // ask if noise should be added to probabilities only initially or keep changing each time
  if (add_noise) {
    printf("offset: %f\n", params->noise_offset);
    addNoise(params->noise_offset);
  }
	
  float prob = (rand() % 100) *.001;

  int* coordPtr;
  int t = 0;

  fprintf(params->fpt, "%d, %d, %d, %d\n", u->i, u->j, v->i, v->j); // print initial to csv file

  while (t < params->maxsteps) {

  	// get new current location of V
		coordPtr = randomPoint(v->i, v->j, prob);
		v->i = *coordPtr;
		v->j = *(coordPtr + 1);

		updateU(u, params->u_activity, t, prob);

    printf("%d, %d, %d, %d\n", u->i, u->j, v->i, v->j);
		fprintf(params->fpt, "%d, %d, %d, %d\n", u->i, u->j, v->i, v->j);	// print to csv file

		prob = (rand() % 100) *.01;
		t++;
  }

}
  	
// use to get a random point based on previous point and probability
int* randomPoint(int x, int y, float prob) {

  int p[2];
  int* point_ptr = p;

  if (prob >= 0 && prob < movements[0]) {   // N
    y++;
  } else if (prob < movements[1]) {         // NE
    x++;
    y++;
  } else if (prob < movements[2]) {         // E
    x++;
  } else if ( prob < movements[3]) {        // SE
    x++;
    y--;
  } else if (prob < movements[4]) {         // S
    y--;  
  } else if (prob < movements[5]) {         // SW
    x--;
    y--;
  } else if(prob < movements[6]) {          // W
    x--;
  } else if (prob < movements[7]) {         // NW
    x--;
    y++;
  }
 
  p[0] = x;
  p[1] = y;

  return point_ptr;

}

void addNoise(float offset) {
  
  offset *= .01;

  // random is added to each index of movements array
  float random;
  int sign;
  for (int i = 0; i < 9; i++) {
    random = (rand() % 100) * offset; // offset controlled by command line 
    sign = (rand() % 100);
    
    if (sign < 50) {
      random *= -1;
    }

    printf("random: %f\n", random); 
    movements[i] += random;
  }

  for (int j = 0; j < 10; j++) {
    printf("%f ", movements[j]);
  }

  printf("\n");
}
