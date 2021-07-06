#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "diver.h"

int is_verbose = 0;

int main(int argc, char * argv[]) {
 	int ch;
 	struct Params params;
	memset(&params, 0, sizeof(struct Params));
	struct Point u;
	struct Point v;

	params.randomseed = DEFAULT_RAND_SEED;
	params.dir = DEFAULT_DIRECTORY;
	params.output_file = DEFAULT_OUTPUT_FILE;
	printf("\nsize of path: %lu\n",sizeof(params.dir));
	memset(params.path,0,sizeof(params.dir) + sizeof(params.output_file));
	printf("\nsegfault\n\n");	

	strcat(strcat(params.path,params.dir),params.output_file);
	printf("\nsegfault\n\n");	

	params.maxsteps = DEFAULT_MAX_STEPS;
	
  	while ((ch = getopt(argc, argv, "VR:o:u:v:t:d:")) != -1) {
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
    			u.i = atoi(strtok(optarg, " "));
 				u.j = atoi(strtok(NULL, " "));
				params.u_activity = strtok(NULL, "\"");
      			break;
   		 	case 'v':
      			v.i = atoi(strtok(optarg," "));
      			v.j = atoi(strtok(NULL," "));
				params.v_activity = strtok(NULL, "\"");
				break;
			case 't':
				params.maxsteps = atoi(optarg);
				break;
			case 'd':
				params.detection = strdup(optarg);
				break;
    		default:
      			printf("%s\n", USAGE_MESSAGE);
      			return 0;
    	}
  	}
  	argc -= optind;
  	argv += optind;
	
	memset(params.path,0,sizeof(params.dir) + sizeof(params.output_file));
	strcat(strcat(params.path,params.dir),params.output_file);
	printf("\nsegfault\n\n");	
	
	if(params.u_activity && params.v_activity && v.i == u.i && v.j == u.j) {
		printf("\nERROR: -u - v coordinates cannot be the same\n\n");	
		exit(1);
	}
	if(params.maxsteps < 1) {
		printf("\nERROR: -t time steps must be a number greater than 1\n");
		exit(1);
	}
		
	if(params.v_activity) {
		if(strcmp(params.v_activity,"randomwalk") == 0 || strcmp(params.v_activity,"approaching") == 0 || strcmp(params.v_activity,"chasing") == 0 || strcmp(params.v_activity,"following") == 0) {
  			
  			if(!(params.fpt = fopen(params.path, "w+"))) {		
  				exit(1);
  			}
			printf("V      U\n");
			printf("%d, %d   %d, %d\n", v.i, v.j, u.i, u.j);        // initial point  
	
			if(strcmp(params.v_activity,"approaching") == 0) {
  				approach(&u, &v);
			} else if(strcmp(params.v_activity,"following") == 0) {
  				follow(&params, &u, &v);
  			} else if(strcmp(params.v_activity,"chasing") == 0) {
    			chase(&params, &u, &v);
  			} 
  			else if(strcmp(params.v_activity,"randomwalk") == 0) {
    			randomwalk(&params, &u, &v);
  			}
  			
  			fclose(params.fpt);
  		} else {
			printf("\nERROR: -v unrecognized activity\n\n");
  			exit(1);
		}
	}

	if(params.detection) {
		if((strcmp(params.detection,"chasing") == 0) || (strcmp(params.detection,"randomwalk") == 0)){
			Fifo_Init();
			if (!(params.fpt = fopen(params.path, "r"))) {
				printf("\nERROR: no file %s\n", params.output_file);
				return 1;
			}		
			if(strcmp(params.detection,"chasing") == 0) {
  				detectChasing(&params, &u, &v);
			} else if(strcmp(params.detection,"randomwalk") == 0) {
		  		detectRandomWalk(&params, &u, &v);
			}
			
			fclose(params.fpt);
		} else {
			printf("\nERROR: -d unrecognized activity\n\n");
  			exit(1);
		} 
	}
	
  	return 0;
}