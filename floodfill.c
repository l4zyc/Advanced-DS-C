#include <stdio.h>

int arr[][8] = { 
    {1, 1, 1, 1, 1, 1, 1, 1}, 
    {1, 1, 1, 1, 1, 1, 0, 0}, 
    {1, 0, 0, 1, 1, 0, 1, 1}, 
    {1, 2, 2, 2, 2, 0, 1, 0}, 
    {1, 1, 1, 2, 2, 0, 1, 0}, 
    {1, 1, 1, 2, 2, 2, 2, 0}, 
    {1, 1, 1, 1, 1, 2, 1, 1}, 
    {1, 1, 1, 1, 1, 2, 2, 1}
};

void display() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%d", arr[i][j]);
        }
        puts(" ");
    }
}

void floodFill(int array[][8], int y, int x, int prev, int new) {
    if(y < 0 || y > 7 || x < 0 || x > 7) return;
    if(array[y][x] != prev) return;
    if(array[y][x] == new) return;

    array[y][x] = new;

    floodFill(array, y+1, x, prev, new);
    floodFill(array, y-1, x, prev, new);
    floodFill(array, y, x+1, prev, new);
    floodFill(array, y, x-1, prev, new);
}


int main() {
    floodFill(arr, 1, 1, 1, 2);
    display();
    return 0;
}
