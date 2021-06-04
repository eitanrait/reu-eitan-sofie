#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 0
#define NE 1
#define E 2
#define SE 3
#define S 4
#define SW 5
#define W 6
#define NW 7
#define STAY 8
#define GONE 9
#define STEPS 30
#define init_i 2000
#define init_j 2200

// point has i,j
typedef struct {
    int i;
    int j;
} point_t;

struct FSM {
    int offset[2];	// {i offset, j offset}
    int next[10];	// to access next state by index
};
typedef const struct FSM FSM_t;

FSM_t states[10] = {
	{{0, 1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}}, 	// N
	{{1, 1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}}, 	// NE
	{{1, 0}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},	// E
	{{1, -1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},	// SE
	{{0, -1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},	// S
	{{-1, -1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},	// SW
	{{-1, 0}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},	// W
	{{-1, 1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},	// NW
	{{0, 0}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},	// STAY
	{{0, 0}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},	// GONE (?)

};

int main() {

	// extra info printed
	printf("----\nN 0\nNE 1\nE 2\nSE 3\nS 4\nSW 5\nW 6\nNW 7\nSTAY 8\nGONE 9\ninit point: %d, %d\n----\n", init_i, init_j);

	// init
	srand(time(0));
	int prob = rand() % 10;	// index of next state
	int stateIndex = prob;	// initial state 
	int a;

	// later - read points from a text file
	point_t p;
	p.i = init_i;	// setting initial point
	p.j = init_j;

	// csv file init 
	FILE *fpt;
	fpt = fopen("state_machine_output.csv", "w+");
	if(fpt == NULL) {
    	// get out code
    	exit(1);
	}
	fprintf(fpt, "i, j\n");
		
	// execute state transition
	for (a = 0; a < STEPS; a++) {

		// stateIndex is the index of states array
		// assigned using value from next state array with prob as input
		stateIndex = states[stateIndex].next[prob];

		// modify i,j
		p.i += states[stateIndex].offset[0];
		p.j += states[stateIndex].offset[1];
		
		// check if in region A (or other exeptions for stopping)

		// output 
		printf(" prob: %d  p.i: %d, p.j: %d\n", prob,p.i, p.j);
		fprintf(fpt, "%d, %d\n", p.i, p.j);	// print to csv file

		prob = rand() % 10;	// next state

	} 

	// possible to create graph?
	//fclose(fpt);
	return 0;
}
