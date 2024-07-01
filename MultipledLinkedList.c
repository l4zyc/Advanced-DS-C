#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Data Data;
struct Data{
    char nama[100];
    float jmlhpddk;
    bool sudah;
    Data *south, *east, *north, *west;
} *root;

Data* createData(char nama[], float jmlhpddk) {
    Data* newData = (Data*) malloc(sizeof(Data));

    strcpy(newData->nama, nama);
    newData->jmlhpddk = jmlhpddk;
    newData->sudah = false;

    newData->east = newData->north = newData->south = newData->west = NULL;

    return newData;
}

void pushNorth(Data *temp, char nama[], float jmlhpddk) {
    if(temp->north != NULL) {
        return;
    }

    Data* Data = createData(nama, jmlhpddk);
    Data->south = temp;
    temp->north = Data;
}

void pushSouth(Data *temp, char nama[], float jmlhpddk) {
    if(temp->south != NULL) {
        return;
    }

    Data* Data = createData(nama, jmlhpddk);
    Data->north = temp;
    temp->south = Data;
}

void pushWest(Data *temp, char nama[], float jmlhpddk) {
    if(temp->west != NULL) {
        return;
    }

    Data* Data = createData(nama, jmlhpddk);
    Data->east = temp;
    temp->west = Data;
}

void pushEast(Data *temp, char nama[], float jmlhpddk) {
    if(temp->east != NULL) {
        return;
    }

    Data* Data = createData(nama, jmlhpddk);
    Data->west = temp;
    temp->east = Data;
}

void viewData(Data* temp, int level, int maxLevel) {
    if(level == 0) {
        printf("City: ");
    } else if(temp == NULL) {
        printf("-\n");
        return;
    }

    printf("%s (%2.f jt)\n", temp->nama, temp->jmlhpddk);

    if(temp->sudah || level > maxLevel) {
        return;
    }

    temp->sudah = true;

    for(int i = 0; i <= level; i++) printf(" ");
    printf("North: ");
    viewData(temp->north, level+1, maxLevel);

    for(int i = 0; i <= level; i++) printf(" ");
    printf("South: ");
    viewData(temp->south, level+1, maxLevel);

    for(int i = 0; i <= level; i++) printf(" ");
    printf("West: ");
    viewData(temp->west, level+1, maxLevel);

    for(int i = 0; i <= level; i++) printf(" ");
    printf("East: ");
    viewData(temp->east, level+1, maxLevel);
}

void netral(Data *temp) {   
    if(temp == NULL || temp->sudah == false) {
        return;
    }

    temp->sudah = false;

    netral(temp->north);
    netral(temp->south);
    netral(temp->west);
    netral(temp->east);
}

void joinEastWest(Data* east, Data* west){
    east->west = west;
    west->east = east;
}

void joinNorthSouth(Data* south, Data* north) {
    south->north = north;
    north->south = south;
}

int main() {   
    
    root = createData("central city", 2.1);
    pushEast(root, "gotham city", 1.2);
    pushNorth(root, "Starlink city", 2);
    pushWest(root, "Konoha", 0.8);
    pushSouth(root, "Wakanda", 1);
    
    pushNorth(root->east, "bekasi", 9.2);
    joinEastWest(root->east->north, root->north);

    pushSouth(root->east, "Tangerang", 8);
    joinEastWest(root->east->south, root->south);

    pushEast(root->east, "Jakarta Barat", 10);

    viewData(root, 0, 1);

    return 0;
}