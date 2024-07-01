#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Node {
    int value;
    struct Node* next;
} *head = NULL, *tail = NULL;

struct Node* newNode(int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    return node;
};

void pushHead(int value) {
    struct Node* node = newNode(value);

    if(head == NULL) {
        head = tail = node;
    } else {
        node->next = head;
        head = node;
    }
}


void pushTail(int value) {
    struct Node* node = newNode(value);
    if(head == NULL) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}


void pushMid(int value) {
    struct Node* node = newNode(value);

    if(head == NULL) {
        head = tail = node;
    } else if(value <= head->value) {
        pushHead(value);
    } else if(value >= tail->value) {
        pushTail(value);
    } else {
        struct Node* curr = head;
        while(curr->next != NULL && curr->next->value < value) {
            curr = curr->next;
        }
        
        node->next = curr->next;
        curr->next = node;
    }
}

void popHead() {
    if(head == NULL) {
        return;
    }

    struct Node* temp = head;
    head = head->next;
    free(temp);
    temp = NULL;
}

void popTail() {
    if(head == NULL) {
        return;
    }

    struct Node* curr = head;
    while(curr->next != tail) curr = curr->next;

    tail = curr;
    free(curr->next);
    curr->next = NULL;
}

void popMid(int val) {
    if(head == NULL) {
        return;
    } else if(head->value == val) {
        popHead();
    } else if(tail->value == val) {
        popTail();
    } else {

        struct Node* curr = head;

        while(curr != tail || curr->next->value != val) {
            curr = curr->next;
        }

        struct Node* temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
        temp = NULL;
    }
}

void printLinkedList(struct Node* curr) {
    if(head == NULL) {
        printf("No Data\n");
        return;
    }

    if(curr == NULL) {
        printf("NULL");
        return;
    }

    printf("%d -> ", curr->value);
    printLinkedList(curr->next);
}


int main() {
    pushHead(1);
    pushTail(2);
    pushMid(3);

    printLinkedList(head);

    return 0;
}