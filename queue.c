#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "driver.h"

//Initializes values of head and tail to -1, meaning the queue is empty
void init (int *head, int*tail) {
	*head = -1;
	*tail = -1;
}
	
//Checks to see if the head is 1 position past the tail, also checks if head is at 0 and tail is at max position
//If true, return 1, else return 0
int isFull(int head, int tail) {
	if((head == tail + 1) || (head == 0 && tail == QUEUE_SIZE - 1)) 
		return 1;
	return 0;	
}

//Checks if the head position is at -1 and returns true/1 if so
int isEmpty(int head) {
	if (head == -1) 
		return 1;
	return 0;
}

// &int, &int, int, &int[0]
//enQueue takes in the address of the head and tail, the integer value of the element to be inserted, and the address of the first element in the queue
// Function will first check if queue is full, and will NOT insert the element 
// Otherwise, if the queue is empty (checking if head index is -1), will set the index to 0 and "create" the queue
// Will increase value of tail, limited to the [QUEUE_SIZE - 1] position, and then reset back to 0 using modulo the max QUEUE_SIZE
// Then set the value of the queue at the tail index equal to the element to be inserted
void enQueue(int * head, int * tail, int element, int * queue) {
	if(isFull(*head, *tail) && is_verbose)
		printf("\n Queue is full! \n");
	else {
		if(*head == -1)
			*head = 0;
		*tail = (*tail + 1) % QUEUE_SIZE;
		queue[*tail] = element;
		if(is_verbose) printf(" Inserted -> %d\n\n", element);
	}
}
// &int, &int, &int[0] 
// deQueue gets passed in: the address of the head and tail, and the address to the first element in the queue
// Function will first check for emptiness, and return -1 if true
// Otherwise, set element (variable) to the address of the element at the head of the queue 
// Check if the head is equal to the tail, and empty the queue if true
// Otherwise, set value of head to the next position, modulo the QUEUE_SIZE of the queue
int deQueue(int * head, int * tail, int * queue) {
	int element;
	if(isEmpty(*head)) {
		if(is_verbose) printf("\n Queue is empty !! \n");
		return(-1);
	} else {
		element = queue[*head];
		if(*head == *tail) {
			*head = -1;
			*tail = -1;
		}
		else {
			*head = (*head + 1) % QUEUE_SIZE;
		}
		if(is_verbose) printf("\n Deleted element -> %d \n", element);
		return(element);
	}
}

// int, int, &int[0]
void display(int head, int tail, int * queue) {
	int i;
	if (isEmpty(head))
		printf("\n Empty Queue\n");
	else {
		printf("\n Head -> %d ", head);
		printf("\n Queue -> ");
		for (i = head; i != tail; i = (i+1) % QUEUE_SIZE) {
			printf("%d ", queue[i]);
		}
		printf("%d ", queue[i]);
		printf("\n Tail -> %d \n", tail);
	}
}

float getEntropy(int head, int tail, int * queue) {
	int i;
	float sum = 0;
	int occurences[10] = {0};
	for (i = head; i != tail; i = (i+1) % QUEUE_SIZE) {
		occurences[queue[i]]++;
	}
	//printf("\n 0: %d\n 1: %d\n 2: %d\n 3: %d\n 4: %d\n 5: %d\n 6: %d\n 7: %d\n 8: %d\n 9: %d\n\n",occurences[0],occurences[1],occurences[2],occurences[3],occurences[4],occurences[5],occurences[6],occurences[7],occurences[8],occurences[9]);
	for(i = 0; i < 10; i++) {
		if(occurences[i] != 0) {
		//	printf("\n%f\n",(float)i/10);
			sum += (float)i/10 * log2f((float)i/10);
		}
	}
//	printf("%f",sum);
	return -sum;	
}