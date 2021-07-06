/*
** name: diver.h
**
** author: eitan raitses + sofie kardonik
** created: 21 jun 2021
** last modified: 6 july 2021
**
*/

#define USAGE_MESSAGE "usage: maritime [-V -R randomseed -O output_file] (-v \"vX vY v_activity\" -u \"uX uY u_activity\")"

#define DEFAULT_RAND_SEED 0
#define DEFAULT_OUTPUT_FILE "output.csv"
#define DEFAULT_SIZE 100
#define DEFAULT_MAX_STEPS 600
#define DEFAULT_COORD 0 
#define SIZE 1000

extern int is_verbose;
extern int add_noise;

struct Params {
  int maxsteps;
  int randomseed;
  FILE * fpt;
  char * v_activity;
  char * u_activity;
  char * output_file;
  char * detection;
  float noise_offset;
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

//following methods
struct Point * findPerpendicularPoint(struct Point * u, struct Point * v, double last_i, double last_j);
int directionOfPoint(struct Point A, struct Point B, struct Point P);
int isVBehind(struct Point * u, struct Point * v, double last_i, double last_j);
void follow(struct Params * params, struct Point * u, struct Point * v);

//bresenham methods
int Sign(int a, int b);
void findPath(struct Point * points, int x1, int y1, int x2, int y2);
void findPathSofie(struct Point * points, int x0, int y0, int x1, int y1);
void MyLine(struct Point * points, int xs, int ys, int xe, int ye);

//chasing methods
void chase(struct Params * params, struct Point * u, struct Point * v);

//uMoves
void updateU(struct Point * u, char * s, int t, int prob);

#define YES 1
#define NO 0
#define QUEUE_SIZE 16

//detection
int findRank(struct Point v, struct Point lastV, struct Point idealV);
int detectChasing(struct Params * params, struct Point * u, struct Point * v);
int findDecision(struct Point lastPoint, struct Point currPoint);
int detectRandomWalk(struct Params * params, struct Point * u, struct Point * v);

//queue
void init(int * head, int * tail);
int isFull(int head, int tail);
int isEmpty(int head);
void enQueue(int * head, int * tail, int element, int * queue);
int deQueue(int * head, int * tail, int * queue);
void display(int head, int tail, int * queue);
//float getEntropy(int head, int tail, int * queue);

#define FIFO_SIZE 17

//fifo
void Fifo_Init();
int Fifo_PutYN(int data);
int Fifo_PutRank(float data);
int Fifo_PutDec(int data);
int Fifo_GetYN();
float Fifo_GetRank();
int Fifo_GetDec();
int Fifo_StatusYN();
int Fifo_StatusDec();
void displayYN();
void displayRank();
void displayDec();
float getEntropy();
float probabilityScore();
