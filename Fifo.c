// implementation of FIFO data structure 
// holds past FIFO_SIZE of geo detections

#include <stdint.h>

// Declare state variables for FiFo
//        size, buffer, put and get indexes
#define FIFO_SIZE 9
static uint8_t PutIndex;
static uint8_t GetIndex;
static char FIFO[FIFO_SIZE];
// *********** FiFo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations
void Fifo_Init() {
	PutIndex = 0;
	GetIndex = 0;
}

// *********** FiFo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint32_t Fifo_Put(char data) {
  if ((PutIndex + 1) % FIFO_SIZE == GetIndex) {
		return (0);
	}
	FIFO[PutIndex] = data;
	PutIndex = (PutIndex + 1) % FIFO_SIZE;
	return (1);
}

// *********** Fifo_Get**********
// Gets an element from the FIFO
// Input: none
// Output: removed character from FIFO
//         0 failure is when the buffer is empty
char Fifo_Get(void){char data;
  if (GetIndex == PutIndex) {
		return (0);
	}
	data = FIFO[GetIndex];
	GetIndex = (GetIndex + 1) % FIFO_SIZE;
	return (data);
}

// *********** Fifo_Status**********
// returns number of elements in the FIFO
// Input: none
// Output: number of entries in FIFO
//         0 failure is when the FIFO is empty
uint32_t Fifo_Status(void){
	if (GetIndex > PutIndex) {
		return (FIFO_SIZE - GetIndex + PutIndex);
	} else {
		return (PutIndex - GetIndex);
	}
}
