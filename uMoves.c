#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "driver.h"
void updateU(struct Point * u, char * s, int t, int prob) {
	int * coordPtr;
	printf("\n%s %d\n",s,t);
	if(t%2 == 1) {
		if(strcmp(s, "randomwalk") == 0) {
			coordPtr = randomPoint(u->i, u->j, prob);
			u->i = *coordPtr;
			u->j = *(coordPtr + 1);
		} else if (strcmp(s,"straight up") == 0) {		// straight up
			u->j += 1;	// move up
		} else if (strcmp(s,"diagonal") == 0) {	// diagonally initially
			u->i += 1;
			u->j += 1;
		} else if (strcmp(s,"straight down") == 0) {	// straight down
			u->j -= 1;
		}
	} 
	//... (can add different movement patterns)
}