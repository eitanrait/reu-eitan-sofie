#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "driver.h"


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

#define I 210
#define J 720
#define STEPS 200

/*
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
*/

struct point{
  int i;
  int j;
  char visible[11];
};

struct point path[STEPS];

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
}

// use to get a random point based on previous point and probability
int* randomPoint(int x, int y, float prob) {

  int p[2];
  int* point_ptr = p;

  if (prob >= 0 && prob < N) {
    y++;
  } else if (prob < NE) {
    x++;
    y++;
  } else if (prob < E) {
    x++;
  } else if ( prob < SE) {
    x++;
    y--;
  } else if (prob < S) {
    y--;  
  } else if (prob < SW) {
    x--;
    y--;
  } else if(prob < W) {
    x--;
  } else if (prob < NW) {
    x--;
    y++;
  }
 
  p[0] = x;
  p[1] = y;

  return point_ptr;

}
