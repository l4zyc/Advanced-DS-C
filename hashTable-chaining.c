#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct User {
    char username[100];
    char email[100];
    char password[100];
    struct User* next;
} *hashTable[26];

int getIndex(char username[]) {
    int sum = 0;
    for (int i = 0; i < strlen(username); i++) {
        sum += username[i];
    }
    return sum % 26;
}

struct User* newNode(char username[], char email[], char password[]) {
    struct User* Node = (struct User*) malloc(sizeof(struct User));
    strcpy(Node->email, email);
    strcpy(Node->password, password);
    strcpy(Node->username, username);
    Node->next = NULL;

    return Node;
}

void insertData(char username[], char email[], char password[]) {
    int index = getIndex(username);

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode(username, email, password);
    } else {
        struct User* tempData = hashTable[index];

        while (tempData->next != NULL) {
            tempData = tempData->next;
        }

        tempData->next = newNode(username, email, password);
    }
}

void printHashTable() {
    for (int i = 0; i < 26; i++) {  // Changed loop to start from 0 to 25
        if (hashTable[i] != NULL) {
            printf("%d. UN: %s, EM: %s, PW: %s", i, hashTable[i]->username, hashTable[i]->email, hashTable[i]->password);
            struct User* temp = hashTable[i]->next;
            while (temp != NULL) {
                printf(" -> UN: %s, EM: %s, PW: %s\n", temp->username, temp->email, temp->password);
                temp = temp->next;
            }
        } else {
            printf("%d. NULL\n", i);  // Added newline for clarity
        }
    }
    printf("\n");
}

int searchData(char email[], char password[]) {
    int tableSize = sizeof(hashTable) / sizeof(hashTable[0]);

    for (int i = 0; i < tableSize; i++) {
        struct User* curr = hashTable[i];
        while (curr != NULL) {
            if (strcmp(curr->email, email) == 0 && strcmp(curr->password, password) == 0) {
                return 1;
            }
            curr = curr->next;
        }
    }
    return 0;
}

void deleteData(char email[], char password[]) {  // Renamed function to avoid conflict with stdlib.h delete
    for (int i = 0; i < 26; i++) {
        struct User* curr = hashTable[i];
        struct User* prev = NULL;

        while (curr) {
            if (strcmp(curr->email, email) == 0 && strcmp(curr->password, password) == 0) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    hashTable[i] = curr->next;
                }
                struct User* temp = curr;
                curr = curr->next;
                free(temp);
                return;  // Exit after deleting the matching node
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

int main() {
    insertData("Glenn", "christiadi.glenn@gmail.com", "Sierra0319");
    printHashTable();

    return 0;
}
