/*
* File   : queue.c
* Author : zentut.com
* Purpose: stack implement file
*/
/*
    initialize queue pointers
*/

#include <stdio.h>

void init(int *head, int *tail)
{
    *head = *tail = 0;
}
 
/*
   enqueue an element
   precondition: the queue is not full
*/
void enqueue(int *q,int *tail, int element, int size)
{

    (*tail)++;
    *tail %= size;
    q[*tail] = element;

    // PutIndex = (PutIndex + 1) % FIFO_SIZE;
    //*tail = (*tail + 1) % size;
}
 
/*
    dequeue an element
    precondition: queue is not empty
*/
int dequeue(int *q,int *head, int size)
{

    (*head)++;
    *head %= size;
    printf("*head: %d\n", *head);
    return q[*head];

    //return q[(*head)++];
}
 
/*
    return 1 if queue is full, otherwise return 0
*/
int full(int head, int tail, const int size)
{
/*
    if (tail - head == size) {
      return 1;
    }
    return 0;*/
    return tail == size-1;

    // (PutIndex + 1) % FIFO_SIZE == GetIndex
}
 
/*
  return 1 if the queue is empty, otherwise return 0
*/
int empty(int head, int tail)
{
    return tail == head;
}
 
/*
  display queue content
*/
void display(int *q,int head,int tail)
{
    // how to alter i
    int i = tail - 1;
    printf("i: %d  head: %d\n", i, head);

    while(i >= head) {
        printf("%d ",q[i--]);
    }

    printf("\n");
}

int findSum(int *q,int head,int tail)
{
  int i = tail - 1;
  int sum = 0;
  
  while (i >= head) {
    sum += q[i--];
  }
  return sum;
}

// used for detecting randomness of the sequence in the set
double findEntropy(int *q,int head,int tail) {

  double entropy;

  // create array of size 10
  int occurances[10];

  int i = tail - 1;

    while(i >= head) {

        printf("%d ",q[i--]);
    }

  return entropy;

}

// to compile
// gcc -Wall Queue.c -o qB
