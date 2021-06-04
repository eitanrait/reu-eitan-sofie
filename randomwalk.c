#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

struct point{
  int i;
  int j;
  char visible[11];
};

struct point points[STEPS];

int main(int argc, char* argv[]) {
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
	strcpy(points[t].visible,"not visible");
	//printf("%s , probability = %.2f\n",points[a].visible, prob);
      }
      else {
	points[t].i = p.i;
	points[t].j = p.j;
	//printf("i= %d, j= %d, probability = %.2f\n",coordinates[t].i,coordinates[t].j, prob);
      }
      prob = (rand() % 100) * .01;
  }

  int index;

  for (index = 0; index < STEPS; index++) {
    if(strcmp(points[index].visible,"") == 0)
      printf("%d,%d\n",points[index].i,points[index].j);
    else 
      printf("not visible\n");
  }
  
  printf("\n");

  return 0;
}
