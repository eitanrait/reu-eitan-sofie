/*
** name: diver.h
**
** author: eitan raitses + sofie kardonik
** created: 21 jun 2021
** last modified: 6 july 2021
**
*/

#define USAGE_MESSAGE "usage: maritime [-V -R randomseed -O output_file] (-v \"vX vY v_activity\" -u \"uX uY u_activity\")"
#define DEFAULT_DIRECTORY "./csv_files/"
#define DEFAULT_RAND_SEED 0
#define DEFAULT_OUTPUT_FILE "output.csv"
#define DEFAULT_ENTROPY_FILE "entropy.csv"
#define DEFAULT_SIZE 100
#define DEFAULT_MAX_STEPS 6000
#define DEFAULT_COORD 0 
#define SIZE 1000

extern int is_verbose;
extern int add_noise;
extern int use_chasing_prob;

struct Params {
  int maxsteps;
  int randomseed;
  FILE * fpt;
  FILE * fpt_ent;
  char * v_activity;
  char * u_activity;
  char * output_file;
  char * entropy_file;
  //char * dir;
  //char * output_file;
  //char * path;
  char * detection;
  float noise_offset;
  float chasing_prob;
};
struct Point {
  int i;
  int j;
  char region;
};
  
//classification methods
char inRegion(int i, int j);
char inPolarRegion(double x, double y, int u_x, int u_y);

//randomwalk methods
int* randomPoint(int x, int y, float prob);
void randomwalk(struct Params * params, struct Point * u, struct Point * v);
void addNoise(float offset);

//approaching methods
void approach(struct Point * u, struct Point * v);

#define RIGHT 1
#define LEFT -1
#define ZERO 0
//following and disguised_following methods
struct Point * findPerpendicularPoint(struct Point * u, struct Point * v, double last_i, double last_j);
int directionOfPoint(struct Point A, struct Point B, struct Point P);
int isVBehind(struct Point * u, struct Point * v, double last_i, double last_j);
void follow(struct Params * params, struct Point * u, struct Point * v);

//bresenham methods
int Sign(int a, int b);
void findPath(struct Point * points, int x1, int y1, int x2, int y2);
void findPathSofie(struct Point * points, int x0, int y0, int x1, int y1);
void MyLine(struct Point * points, int xs, int ys, int xe, int ye);

//chasing and chasing_prob methods
void chase(struct Params * params, struct Point * u, struct Point * v);
int switchDirection(int x, int y, struct Point idealV);
int* moveWithProbability(int x, int y, struct Point idealV, float bresenhamP, float * prob);

//uMoves
void updateU(struct Point * u, char * s, int t, int prob);

#define YES 1
#define NO 0
//detection
int findRank(struct Point v, struct Point lastV, struct Point idealV);
int detectChasing(struct Params * params, struct Point * u, struct Point * v);
int findDecision(struct Point lastPoint, struct Point currPoint);
int detectRandomWalk(struct Params * params, struct Point * u, struct Point * v);
int detectFollow(struct Params * params, struct Point * u, struct Point * v);
float getDistance(struct Point * u, struct Point * v);

#define FIFO_SIZE 65
//FIFO Init
void Fifo_Init();
//FIFO Put
int Fifo_PutYN(int data);
int Fifo_PutRank(float data);
int Fifo_PutDec(int data);
int Fifo_PutDist(float data);
//FIFO Get
int Fifo_GetYN();
float Fifo_GetRank();
int Fifo_GetDec();
float Fifo_GetDist();
//FIFO Status
int Fifo_StatusYN();
int Fifo_StatusDec();
int Fifo_StatusDist();
//FIFO Display
void displayYN();
void displayRank();
void displayDec();
void displayDist();
//FIFO Stats
float getEntropy();
float probabilityScore();
