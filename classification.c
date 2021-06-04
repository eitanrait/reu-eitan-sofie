#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// input of i,j coordinate
// determine in which region
// output a,b,c,d accordingly
char inRegion(int i, int j) {

	// region A: (1792, 1792) -> (1792, 2304)
	//           (1792, 2304) -> (2304, 2304)
	// region B: (1536, 1536) -> (2560, 1536)
	//           (1536, 2560) -> (2560, 2560)
	// region C: (1024, 1024) -> (3072, 1024)
	//           (1024, 3072) -> (3072, 3072)
	// region d: (0, 0)       -> (4096, 0)
	//           (0, 4096)    -> (4096, 4096)
	
	if (i >= 1792 && i <= 2304 && j >= 1792 && j <= 2304) {
		return 'a';
	} else if (i >= 1536 && i <= 2560 && j >= 1536 && j <= 2560) {
		return 'b';
	} else if (i >= 1024 && i <= 3072 && j >= 1024 && j <= 3072) {
		return 'c';
	} else if (i >= 0 && i <= 4096 && j >= 0 && j <= 4096) {
		return 'd';
	}

	return 'i';	// invisible
}
