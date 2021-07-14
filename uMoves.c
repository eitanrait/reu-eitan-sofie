#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "diver.h"
void updateU(struct Point * u, char * s, int t, int prob) {
	int * coordPtr;
	//printf("\n%s %d\n",s,t);

	if(t%2 == 0) {
		if(strcmp(s, "randomwalk") == 0) {
			coordPtr = randomPoint(u->i, u->j, prob);
			u->i = *coordPtr;
			u->j = *(coordPtr + 1);
		} else if (strcmp(s,"up") == 0) {		// straight up
			//if (u->i == u->j) {
			//	u->i += 1;	// if at the diagonal, move to side 
			//} else {
				u->j += 1;	// move up
			//}
			
		} else if (strcmp(s,"diagonal") == 0) {	// diagonally initially
			u->i += 1;
			u->j += 1;
		} else if (strcmp(s,"down") == 0) {	// straight down
			u->j -= 1;
		}
		 else if (strcmp(s,"right") == 0) {	// right
			u->i += 1;
		}
		else {
			printf("\n ERROR: -u INVALID ACTIVITY\n");
			exit(1);
		}
	} 
	//... (can add different movement patterns)
}