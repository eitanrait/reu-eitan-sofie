#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classification.h"

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

void randomwalk(int x, int y, float prob) {

  if (prob >= 0 && prob < N)
    y++;
  else if (prob < NE) {
    x++;
    y++;
  }
  else if (prob < E)
    x++;
  else if ( prob < SE) {
    x++;
    y--;
  }
  else if (prob < S)
    y--;  
  else if (prob < SW) {
    x--;
    y--;
  }
  else if(prob < W)
    x--;
  else if (prob < NW) {
    x--;
    y++;
  }
  else {}    
  
/*  
  p.region = inRegion(p.i,p.j);
  
  if(prob >= STAY && prob < GONE)
    p.region = 'i';
  
  points[t].i = p.i;
  points[t].j = p.j;
  points[t].region = p.region; 
*/
  return 0;
}
