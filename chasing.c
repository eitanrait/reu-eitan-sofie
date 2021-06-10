#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
//#include <windows.h>
#include "randomwalk.h"
#include "classification.h"

#define SIZE 300

typedef struct {
  int i;
  int j;
  char region;
} point_t;

point_t points[SIZE];
point_t X;
point_t Y;

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
// to find the fastest pasth from pixel a to b 
// assuming x0 < x1
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
  
  for (int i=1;i<deltX;i++) {
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
    points[t].i = x;
    points[t].j = y;
  }
   
}

// inputs: int Y_x, int Y_y, int X_x, int X_y
// using global variables point_t X and Y for inputs atm 
// X does random walk
void synthesizeChasingRandom() {
	
  // csv file init
  FILE *fpt;
  fpt = fopen("chasing_random_walk.csv", "w+");
  if(fpt == NULL) {
    // get out code
    exit(1);
  }
  fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");
  
  // calls findPath() which modifies points to get a new line 
  // X can move with a random walk
  float prob = (rand() % 100) *.01;
  
  int* coordPtr;
  int t = 0;	// for testing
  printf("Y              X\n");
  while (1) {
    
    // get current location of X
    coordPtr = randomPoint(X.i, X.j, prob);
    X.i = *coordPtr;
    X.j = *(coordPtr + 1);
    
    // get new line
    findPath(Y.i, Y.j, X.i, X.j);
    
    // could check if first invisible
    Y.i = points[1].i;
    Y.j = points[1].j;
    
    // check the zones 
    // maybe need to change this concept
    // A is pretty much just X since Y is trying to get to X
    Y.region = inRegion(Y.i, Y.j);
    X.region = inRegion(X.i, X.j);
    
    printf("%c: %d, %d  %c: %d, %d\n", Y.region, Y.i, Y.j, X.region, X.i, X.j);
    fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file
    prob = (rand() % 100) *.01;
    t++;
    
    // check for breaking 
    if (Y.i == X.i && Y.j == X.j) {
      break;
    }
    
    //    sleep(1); 	// sleep for 1 second "time driven simulation"
    
  }
  
}

// chasing while X goes diagonally up
// csv file output
void synthesizeChasingDiagonal() {
  
  // csv file init
  FILE *fpt;
  fpt = fopen("chasing_diagonal1.csv", "w+");
  if(fpt == NULL) {
    // get out code
    exit(1);
  }
  fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");
  
  printf("Y              X\n");
  int t = 0;
  while (1) {
    
    // get current location of X
    X.i = X.i + 1;
    X.j = X.j + 1;
    
    // get new line
    findPath(Y.i, Y.j, X.i, X.j);
    
    // could check if first invisible
    Y.i = points[1].i;
    Y.j = points[1].j;
    
    // check the zones 
    // maybe need to change this concept
    // A is pretty much just X since Y is trying to get to X
    Y.region = inRegion(Y.i, Y.j);
    X.region = inRegion(X.i, X.j);
    
    printf("%c: %d, %d  %c: %d, %d\n", Y.region, Y.i, Y.j, X.region, X.i, X.j);
    fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file
    
    // check for breaking 
    if ((Y.i == X.i && Y.j == X.j) || t > 50) {
      break;
    }
    
    //    sleep(1); 	// sleep for 1 second "time driven simulation"
    t++;
    
  }
  
}

void synthesizeChasingStraightUp() {

  // csv file init
  FILE *fpt;
  fpt = fopen("chasing_straight_up.csv", "w+");
  if(fpt == NULL) {
    // get out code
    exit(1);
  }
  fprintf(fpt, "X.i, X.j, Y.i, Y.j\n");
  
  printf("Y              X\n");
  int t = 0;
  while (1) {
    
    // get current location of X
    if(t % 2 == 1)
      X.j = X.j + 1;
    
    // get new line
    findPath(Y.i, Y.j, X.i, X.j);
    
    // could check if first invisible
    Y.i = points[1].i;
    Y.j = points[1].j;
    
    // check the zones 
    // maybe need to change this concept
    // A is pretty much just X since Y is trying to get to X
    Y.region = inRegion(Y.i, Y.j);
    X.region = inRegion(X.i, X.j);
    
    printf("%c: %d, %d  %c: %d, %d\n", Y.region, Y.i, Y.j, X.region, X.i, X.j);
    fprintf(fpt, "%d, %d, %d, %d\n", X.i, X.j, Y.i, Y.j);	// print to csv file
    
    // check for breaking 
    if ((Y.i == X.i && Y.j == X.j) || t > 600) {
      break;
    }
    
    //    sleep(1); 	// sleep for 1 second "time driven simulation"
    t++;
    
  }
  
}


int main() {
  
  // initial points of Boat X and Y
  // note that Boat Y is chasing X 
  // thus Y.i < X.i because we are using Brenenham's algorithm
  
  Y.i = 10;
  Y.j = 10;
  X.i = 100;
  X.j = -30;
  
  // seed time
  srand(0);
  
  //synthesizeChasingRandom();
  //synthesizeChasingDiagonal();
  synthesizeChasingStraightUp();	
  return 0;  
}
