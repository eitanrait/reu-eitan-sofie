#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "driver.h"
int is_verbose = 0;

int main(int argc, char * argv[]) {
 
	int ch;
	struct Params params;
	memset(&params, 0, sizeof(struct Params));
	struct Point u;
	memset(&u, 0, sizeof(struct Point));
	struct Point v;
	memset(&v, 0, sizeof(struct Point));

	params.randomseed = DEFAULT_RAND_SEED;
	params.output_file = DEFAULT_OUTPUT_FILE;
  
  	while ((ch = getopt(argc, argv, "VR:o:u:v:t:")) != -1) {
    	switch(ch) {
    		case 'V':
				is_verbose++;
				break;
    		case 'R':
      			params.randomseed = atoi(optarg);
      			break;
    		case 'o':
      			params.output_file = strdup(optarg);
      			break;
    		case 'u':
      			u.i = atoi(strtok(optarg,' '));
      			u.j = atoi(strtok(NULL, ' '));
      			params.u_activity = optarg+1;
      			break;
   		 	case 'v':
      			v.i = atoi(strtok(optarg,' '));
      			v.j = atoi(strtok(NULL,' '));
      			params.v_activity = optarg+1;
      			break;
			case 't':
				params.maxsteps = atoi(optarg);
				break;
    		default:
      			printf("%s\n", USAGE_MESSAGE);
      			return 0;
    	}
  	}
  	argc -= optind;
  	argv += optind;
  
  	if(!(u.i && u.j && v.i && v.j))
  		return 0;
  	
  	FILE * f;
	f = fopen(strcat("csv_files/",params->output_file), "w+");
	if((params.fpt = f) == NULL)
		exit(1);
	
	fprintf(params.fpt, "U:i, U:j, V:i, V:j\n");
	printf("V      U\n");
	printf("%d, %d   %d, %d\n", v.i, v.j, u.i, u.j);        // initial point  
	
	if(strcmp(v_activity,"approaching") == 0) {
  		approach(&u, &v);
	} else if(strcmp(v_activity,"following") == 0) {
  		follow(&params, &u, &v);
  	} else if(strcmp(v_activity,"chasing") == 0) {
    	chasing(&params, &u, &v);
  	} else if(strcmp(v_activity,"randomwalk") == 0) {
    	randomwalk(&params);
  	}

     
  	return 0;
}
