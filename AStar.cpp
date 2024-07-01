#include <stdio.h>
#include <math.h>
#include <list>
#include <stdbool.h>
#include <vector>

using namespace std;

typedef struct Position Position;
typedef struct Map Map;

void clear() {
    system("cls");
}

struct Position {
    int x,y;
};

struct Map {
    Position currPos;
    char value;
    bool isVisited;
    Map *before;
};

Map sMap[10][15];

char MapChar[10][16] = {
"###############",
"# ###        E#",
"#             #",
"###       #####",
"##    #########",
"#    ##########",
"###           #",
"########    ###",
"#            S#",
"###############"
};

Position startPos, endPos;

void buildMap() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 15; j++) {
            char currVal = MapChar[i][j];
            Position currPos;
            currPos.y = i;
            currPos.x = j;

            if(currVal == 'S') {
                startPos = currPos;
            }

            if(currVal == 'E') {
                endPos = currPos;
            }

            sMap[i][j].value = currVal;
            sMap[i][j].before = NULL;
            sMap[i][j].isVisited = false;
            sMap[i][j].currPos = currPos;
        }
    }  
}

void printMap() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 15; j++) {
            printf("%c", sMap[i][j].value);
        }
        puts(" ");
    }
}

//Atas kanan bawah Kiri
int moveY[4] = {-1, 0, 1, 0};
int moveX[4] = {0, 1, 0, -1};

void solve() {
    vector<Map *> listMap;
    listMap.push_back(&sMap[startPos.y][startPos.x]);
    Map* currMap;
    while(!listMap.empty()) {
        int index = 0;
        int heu = sqrt(pow(listMap[0]->currPos.x,2) + pow(listMap[0]->currPos.y,2));

        for(int i = 1; i < listMap.size(); i++) {
            int tempheu = sqrt(pow(listMap[i]->currPos.x,2) + pow(listMap[i]->currPos.y,2));
            if(tempheu < heu) {
                heu = tempheu;
                index = i;
            }
        }

        currMap = listMap[index];
        listMap.erase(listMap.begin() + index);
        currMap->isVisited = true;

        if(currMap->value == 'E') break;

        for(int i = 0; i < 4; i++) {
            Map* newMap = &sMap[currMap->currPos.y + moveY[i]][currMap->currPos.x] + moveX[i];
            bool inList = false;

            for(int j = 0; j < listMap.size(); j++) {
                if(listMap[j] == newMap) {
                    inList = true;
                }
            }

            if(inList || newMap->isVisited || newMap->value == '#') continue;

            listMap.push_back(newMap);
            newMap->before = currMap;
        }
    }

    while(currMap) {
        if(currMap->value != 'S' && currMap->value != 'E') currMap->value = '*';
        currMap = currMap->before;
    }

    printMap();
}

int main() {
    clear();
    buildMap();
    solve();
    return 0;
}