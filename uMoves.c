#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "driver.h"
void updateU(struct Point * u, char * s, int t) {
	
	if(strcmp(params->u_activity, "randomwalk") == 0) {
		
		if (t%2 == 1) {
			coordPtr = randomPoint(X.i, X.j, prob);
			u->i = *coordPtr;
			u->j = *(coordPtr + 1);
		}
	}
	if (strcmp(params->u_activity,"straight up") == 0) {		// straight up

		if (t%2 == 1)		// every other step
			u->j += 1;	// move up

	} else if (strcmp(params->u_activity,"diagonal") == 0) {	// diagonally initially

		if (t%2 == 1) {
			u->i += 1;
			u->j += 1;
		}
		
	} else if (strcmp(params->u_activity,"straight down") == 0) {	// straight down

		if (t%2 == 1)
			u->j -= 1;

	} 
	//... (can add different movement patterns)
	
}
