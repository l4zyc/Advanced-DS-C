#include <stdio.h>
#include <stdlib.h>

int main() {
    char filepath[] = "town.txt";
    FILE* file = fopen(filepath, "r");

    char ch;
    int rows = 0;
    int cols = 0;
    int maxCols = 0;

    while((ch = fgetc(file)) != EOF) {
        if(ch == '\n') {
            rows++;
            if(cols > maxCols) {
                maxCols = cols;
            }
            cols = 0;
        } else {
            cols++;
        }
    }
    
    if(cols > maxCols) {
        maxCols = cols;
    }

    rows++;

    rewind(file);

    char **map = (char**) malloc(rows * sizeof(char*));
    for(int i = 0; i < rows; i++) {
        map[i] = (char*) malloc((maxCols + 1) * sizeof(char));
        for(int j = 0; j < maxCols;j++) {
            map[i][j] = ' ';
        }
        map[i][maxCols] = '\0';
    }

    int row = 0, col = 0;

    while((ch = fgetc(file)) != EOF) {
        if(ch == '\n') {
            map[row++][col] = '\0';
            col = 0;
        } else {
            map[row][col++] = ch;
        }
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < maxCols; j++) {
            printf("%c", map[i][j]);
        }
        puts(" ");
    }


    return 0;
}
