#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10

typedef struct Queue Queue;

struct Queue {
    int items[SIZE];
    int front, rear;
};

void initialize(Queue *queue) {
    queue->front = queue->rear = -1;
}

bool isEmpty(Queue *queue) {
    return queue->front == -1;
}

bool isFull(Queue *queue) {
    return queue->rear == SIZE - 1;
}

void enqueue(Queue *queue, int val) {
    if(isFull(queue)) {
        printf("Queue is Full");
        return;
    } else if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->items[++queue->rear] = val;
}

void dequeue(Queue *queue) {
    if(isEmpty(queue)) {
        printf("Stack is empty");
        return;
    }
    queue->front++;
}

void display(Queue *queue)  {
    if(isEmpty(queue)) {
        printf("Stack is Empty");
        return;
    }

    for(int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->items[i]);
    }
}
 
int main() {
    Queue *queue = (Queue*) malloc(sizeof(Queue));

    initialize(queue);
    enqueue(queue, 1);
    enqueue(queue, 2);
    dequeue(queue);
    display(queue);

    return 0;
}