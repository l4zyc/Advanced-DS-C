#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 5

typedef struct Stack Stack;

struct Stack {
    int top;
    int items[SIZE];
};

void initialize(Stack *stack) {
    stack->top = -1;
}

bool isFull(Stack *stack) {
    return stack->top == SIZE - 1;
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int val) {
    if(isFull(stack)) {
        return;
    } 
    stack->items[++stack->top] = val;
}

void pop(Stack *stack) {
    if(isEmpty(stack)) {
        return;
    }
    stack->top--;
}

void printStack(Stack *stack) {
    if(isEmpty(stack)) {
        return;
    }

    for(int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->items[i]);
    }
}

int main() {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    initialize(stack);
    push(stack, 1);
    push(stack, 2);

    printStack(stack);

    return 0;
}