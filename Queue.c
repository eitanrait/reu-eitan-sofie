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
void enqueue(int *q,int *tail, int element)
{
    q[(*tail)++] = element;
}
 
/*
    dequeue an element
    precondition: queue is not empty
*/
int dequeue(int *q,int *head)
{
    return q[(*head)++];
}
 
/*
    return 1 if queue is full, otherwise return 0
*/
int full(int head, int tail, const int size)
{

    if (tail - head == size-1) {
      return 1;
    }
    return 0;
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
    int i = tail - 1;

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


// to compile
// gcc -Wall Queue.c -o qB
