/*
** name: driver.h
**
** author: eitan raitses
** created: 21 jun 2021
** last modified: 21 jun 2021
**
*/

#define USAGE_MESSAGE "usage: maritime [-V -R randomseed -O output_file] (-v vX vY v_activity -u uX uY u_activity)"

#define DEFAULT_RAND_SEED 0
#define DEFAULT_OUTPUT_FILE "output.csv"
#define DEFAULT_SIZE 16

extern int is_verbose;

struct Params {
  int maxsteps;
  int randomseed;
  FILE * fpt;
  char * v_activity;
  char * u_activity;
  char * output_file;
}
struct Point {
  int i;
  int j;
  char region;
}
  
//classification methods
char inRegion(int i, int j);
char inPolarRegion(double x, double y, int u_x, int u_y);

//randomwalk methods
int randomwalk();
int* randomPoint(int x, int y, int prob);

//approaching methods
void approach(struct Point * u, struct Point * v);

#define RIGHT 1
#define LEFT -1
#define ZERO 0

//following methods
struct Point * findPerpendicularPoint(struct Point * u, struct Point * v, double last_i, double last_j);
int directionOfPoint(Point A, Point B, Point P);
int isVBehind(double last_i, double last_j);
void follow(struct Params * params, struct Point * u, struct Point * v);

//bresenham methods
int Sign(int a, int b);
void findPath(struct Point * points[], int x1, int y1, int x2, int y2);
void findPathSofie(int x0, int y0, int x1, int y1);
void MyLine(int xs, int ys, int xe, int ye);

//chasing methods
void chasingRandom();
void chasingDiagonal();
void chasingStraightUp();
void chasingStraightDown();

//uMoves
void updateU(struct Point * u, char * s, int t);
