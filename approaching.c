#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 150

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

  //int diag_inc = 2 * (A + B);                                                                  //int right_inc = 2 * A;                                                                                                                                                   
  points[t].i = x;
  points[t].j = y;

  for (int i=0;i<deltX;i++) {
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

int main() {

        // csv file init
        FILE *fpt;
        fpt = fopen("csv_files/approaching.csv", "w+");
        if(fpt == NULL) {
            // get out code
            exit(1);
        }

        // call draw line with two points                                                                                                                                                           
        // find the path from p1 to p2 assuming p1.x < p2.x and slope is 0 < m <= 1                                                                                                                 
        // (10, 10) -> (25, 10)                                                                                                                                                                     
        int xi = 40;
        int xj = 30;
        findPathBres(0, 0, xi, xj);
        for (int k = 0; k < SIZE; k++) {
                printf("%d, %d, %d, %d\n", xi, xj, points[k].i, points[k].j);
                fprintf(fpt, "%d, %d, %d, %d\n", xi, xj, points[k].i, points[k].j); // print to csv file
        }

        return 0;
}
