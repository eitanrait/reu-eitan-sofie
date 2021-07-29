#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_WAIT 16	// wait for buffer to be full before starting calculation

int main(int argc, char*argv[])
{
    double average_ent, num_ent = 0, min_ent = 0, max_ent = 0, sum_ent = 0, std_dev_ent, sum_sqs_ent = 0.0;
    double average_steps, num_steps = 0, min_steps = 0, max_steps = 0, sum_steps = 0, std_dev_steps, sum_sqs_steps = 0.0;
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
    if (pFile == 0) {
        fprintf(stderr, "%s: failed to open file %s\n", argv[0], argv[1]);
        return 1;
    }

    // start scan and while loop
    while (fgets(line, sizeof(line), pFile)) {

		num_ent = atof(strtok(line, ","));
		num_steps = atof(strtok(NULL, " "));
		if (num_ent < min_ent || N == 0) 
			min_ent = num_ent;
		if (num_ent > max_ent || N == 0)
			max_ent = num_ent;
		sum_ent += num_ent;
		sum_sqs_ent += (num_ent*num_ent);
	
		if (num_steps < min_steps || N == 0) 
			min_steps = num_steps;
		if (num_steps > max_steps || N == 0)
			max_steps = num_steps;
		sum_steps += num_steps;
		sum_sqs_steps += (num_steps*num_steps);

		N++;	// increment amount of numbers used in analysis
	}

    i++;
    fclose(pFile);
    average_ent = sum_ent/N;
    std_dev_ent = sqrt((sum_sqs_ent/N)-(average_ent*average_ent));
    float var_ent = (sum_sqs_ent/N)-(average_ent*average_ent);

	average_steps = sum_steps/N;
	std_dev_steps = sqrt((sum_sqs_steps/N)-(average_steps*average_steps));
	float var_steps = (sum_sqs_steps/N)-(average_steps*average_steps);
	
	printf("Smallest Entropy: %7.3lf\n", min_ent);
    printf("Largest Entropy: %7.3lf\n", max_ent);
    printf("Average Entropy: %7.3lf\n", average_ent);
    printf("Standard Deviation of Entropy: %7.4lf\n", std_dev_ent);
    printf("Variance of Entropy: %7.4f\n", var_ent);

    printf("Smallest Steps Away: %7.3lf\n", min_steps);
    printf("Largest Steps Away: %7.3lf\n", max_steps);
    printf("Average Steps Away: %7.3lf\n", average_steps);
    printf("Standard Deviation of Steps Away: %7.4lf\n", std_dev_steps);
    printf("Variance of Steps Away: %7.4f\n", var_steps);
    
    return(0);
}
