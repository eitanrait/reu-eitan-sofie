#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "diver.h"

/*

Queue implementation
no pointers

*/

static int PutIndexYN;
static int GetIndexYN;
static int ynQueue[FIFO_SIZE];

static int PutIndexRank;
static int GetIndexRank;
static float rankQueue[FIFO_SIZE];

static int PutIndexDec;
static int GetIndexDec;
static int decisionQueue[FIFO_SIZE];

static int PutIndexDist;
static int GetIndexDist;
static float distanceQueue[FIFO_SIZE];

// *********** FiFo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations
void Fifo_Init() {
	printf("fifo init\n");
	PutIndexYN = 0;
	GetIndexYN = 0;
	PutIndexRank = 0;
	GetIndexRank = 0;
	PutIndexDec = 0;
	GetIndexDec = 0;
	PutIndexDist = 0;
	GetIndexDist = 0;
}

// head - putIndex (also the 'rear')
// tail - getIndex (the 'front')

// *********** FiFo_Put**********
// Adds an element to the ynQueue
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
int Fifo_PutYN(int data) {
	// checks if FIFO is full
  	if ((PutIndexYN + 1) % FIFO_SIZE == GetIndexYN) {
		return (0);
	}
	ynQueue[PutIndexYN] = data;
	PutIndexYN = (PutIndexYN + 1) % FIFO_SIZE;
	return (1);
}

// *********** Fifo_Get**********
// Gets an element from the ynQueue
// Input: none
// Output: removed character from FIFO
//         0 failure is when the buffer is empty
int Fifo_GetYN(void){int data;
	// checks if FIFO is empty
  if (GetIndexYN == PutIndexYN) {
		return (0);
	}
	data = ynQueue[GetIndexYN];
	GetIndexYN = (GetIndexYN + 1) % FIFO_SIZE;
	return (data);
}


// Adds an element to the rankQueue
int Fifo_PutRank(float data) {
  if ((PutIndexRank + 1) % FIFO_SIZE == GetIndexRank) {
		return (0);
	}
	rankQueue[PutIndexRank] = data;
	PutIndexRank = (PutIndexRank + 1) % FIFO_SIZE;
	return (1);
}

// Gets an element from the rankQueue
float Fifo_GetRank(void){float data;
  if (GetIndexRank == PutIndexRank) {
		return (0);
	}
	data = rankQueue[GetIndexRank];
	GetIndexRank = (GetIndexRank + 1) % FIFO_SIZE;
	return (data);
}


// Adds an element to the decisionQueue
int Fifo_PutDec(int data) {
  if ((PutIndexDec + 1) % FIFO_SIZE == GetIndexDec) {
		return (0);
	}
	decisionQueue[PutIndexDec] = data;
	PutIndexDec = (PutIndexDec + 1) % FIFO_SIZE;
	return (1);
}

// gets an element from decisionQueue
int Fifo_GetDec(void){int data;
  if (GetIndexDec == PutIndexDec) {
		return (0);
	}
	data = decisionQueue[GetIndexDec];
	GetIndexDec = (GetIndexDec + 1) % FIFO_SIZE;
	return (data);
}


// puts an element in distanceQueue
int Fifo_PutDist(float data) {
  if ((PutIndexDist + 1) % FIFO_SIZE == GetIndexDist) {
		return (0);
	}
	distanceQueue[PutIndexDist] = data;
	PutIndexDist = (PutIndexDist + 1) % FIFO_SIZE;
	return (1);
}

// gets element from distance queue
float Fifo_GetDist(void){float data;
  if (GetIndexDist == PutIndexDist) {
		return (0);
	}
	data = distanceQueue[GetIndexDist];
	GetIndexDist = (GetIndexDist + 1) % FIFO_SIZE;
	return (data);
}


// *********** Fifo_Status**********
// returns number of elements in the FIFO
// Input: none
// Output: number of entries in FIFO
//         0 failure is when the FIFO is empty
int Fifo_StatusYN(void)	{
	if (GetIndexYN > PutIndexYN) {
		return (FIFO_SIZE - GetIndexYN + PutIndexYN);
	} else {
		return (PutIndexYN - GetIndexYN);
	}
}

int Fifo_StatusDec(void)	{
	if (GetIndexDec > PutIndexDec) {
		return (FIFO_SIZE - GetIndexDec + PutIndexDec);
	} else {
		return (PutIndexDec - GetIndexDec);
	}
}

int Fifo_StatusDist(void)	{
	if (GetIndexDist > PutIndexDist) {
		return (FIFO_SIZE - GetIndexDist + PutIndexDist);
	} else {
		return (PutIndexDist - GetIndexDist);
	}
}

void displayYN() {

	printf("PutIndexYN: %d  GetIndexYN: %d\n", PutIndexYN, GetIndexYN);
	printf("ynQueue -> \t");
	for (int i = GetIndexYN; i != PutIndexYN; i = (i+1) % FIFO_SIZE) {
		printf("%d ", ynQueue[i]);
	}
	printf("\n");

}

void displayRank() {

	printf("rankQueue -> \t");
	for (int i = GetIndexRank; i != PutIndexRank; i = (i+1) % FIFO_SIZE) {
		printf("%.2f ", rankQueue[i]);
	}
	printf("\n");

}

float probabilityScore() {

	float p = 1;
	for (int i = GetIndexRank; i != PutIndexRank; i = (i+1) % FIFO_SIZE) {
		printf("p = %.10f   rankQueue[i] = %f\n", p, rankQueue[i]);
		p *= rankQueue[i];
	}
	p = -log10f(p);
	return p;

}

void displayDec() {

	printf("decisionQueue -> \t");
	for (int i = GetIndexDec; i != PutIndexDec; i = (i+1) % FIFO_SIZE) {
		printf("%d ", decisionQueue[i]);
	}
	printf("\n");

}

void displayDist() {

	printf("distanceQueue -> \t");
	for (int i = GetIndexDist; i != PutIndexDist; i = (i+1) % FIFO_SIZE) {
		printf("%.2f ", distanceQueue[i]);
	}
	printf("\n");

}

float getEntropy() {
	int i;
	float sum = 0;
	float occurences[10] = {0};
	for (i = GetIndexDec; i != PutIndexDec; i = (i+1) % FIFO_SIZE) {
		occurences[decisionQueue[i]]++;
	}
	//printf("\n 0: %d\n 1: %d\n 2: %d\n 3: %d\n 4: %d\n 5: %d\n 6: %d\n 7: %d\n 8: %d\n 9: %d\n\n",occurences[0],occurences[1],occurences[2],occurences[3],occurences[4],occurences[5],occurences[6],occurences[7],occurences[8],occurences[9]);
	for(i = 0; i < 10; i++) {
		if(occurences[i] != 0) {
			//printf("\nprint i:%d %d/%d: %f\n",i,occurences[i],(temp/QUEUE_SIZE) *log2f(temp/QUEUE_SIZE));
			sum += (occurences[i]/FIFO_SIZE) * log2f(occurences[i]/FIFO_SIZE);
			//printf("\nprint running sum: %f\n",sum);
		}
	}
	//printf("\nprint total sum: %f\n",sum);
	return -sum;
}
