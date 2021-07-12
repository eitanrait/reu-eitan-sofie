#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_WAIT 16	// wait for buffer to be full before starting calculation

int main(int argc, char*argv[])
{
    double average, num = 0, min = 0, max = 0, sum = 0, std_dev, sum_sqs = 0.0;
    char line[256];

    // check for arguments input
    if (argc <= 1)
    {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return 1;
    }

    int i = 0;
    int N = 0;

    // open file from command line
    FILE *pFile = fopen(argv[1], "r");
    if (pFile == 0)
    {
        fprintf(stderr, "%s: failed to open file %s\n", argv[0], argv[1]);
        return 1;
    }

    // start scan and while loop
    while (fgets(line, sizeof(line), pFile)) {

    	if (i > INITIAL_WAIT) {

    		num = atof(strtok(line, " "));

	        if (num < min || N == 0) 
	           	min = num;
	        if (num > max || N == 0)
	            max = num;
	        sum += num;
	        sum_sqs += (num*num);

	        N++;	// increment amount of numbers used in analysis
    	}

    	i++;
       
    }

    fclose(pFile);
    average = sum/N;
    std_dev = sqrt((sum_sqs/N)-(average*average));

    printf("Smallest: %7.3lf\n", min);
    printf("Largest: %7.3lf\n", max);
    printf("Average: %7.3lf\n", average);
    printf("Standard deviation: %7.4lf\n", std_dev);
    return(0);
}

// to compile
// gcc -lm -o getStats

// to run
// ./getStats chasing_entropy.txt
// text doc looks like:
/*
0.2404
0.3632
0.4416
...

*/