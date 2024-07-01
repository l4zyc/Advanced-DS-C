#include <bits/stdc++.h> 
#define HEIGHT 10
#define WIDTH 15

using namespace std;

typedef struct Tile Tile;
typedef struct Path Path;

struct Tile {
    Tile* prev;
    int minDistance, cost;
    int y,x;
    char symbol;
    bool isVisited;

    Tile(int y, int x, char symbol) {
        this->y = y;
        this->x = x;
        this->symbol = symbol;
        this->isVisited = false;
        this->minDistance = INT_MAX;
        this->cost = 1;
        this->prev = nullptr;
    }
};

struct Path {
    Tile *src, *dst;
    double distance;

    bool operator() (const Path* lhs, const Path* rhs) const {
        return lhs->distance > rhs->distance;
    }

    Path(Tile* src, Tile* dst, double distance) {
        this->src = src;
        this->dst = dst;
        this->distance = distance;
    }

    Path() {};
};  

// Character map of the environment
char mapChar[HEIGHT][WIDTH + 1] = {
    "###############",
    "# ###         #",
    "#             #",
    "###       #####",
    "##    #########",
    "#    ##########",
    "###           #",
    "########    ###",
    "#             #",
    "###############"
};

Tile* startTile;
Tile* finishTile;
Tile* currDst;
Path* currPath;
Tile* Map[HEIGHT][WIDTH];
priority_queue<Path*, vector<Path*>, Path> priorityQueue;

const int startY = 2;
const int startX = 1;
const int finishY = 8;
const int finishX = 2;
int moveY[4] = {-1,0,1,0}; 
int moveX[4] = {0,1,0,-1};

void initializeMap() {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            Map[i][j] = new Tile(i,j, mapChar[i][j]);
        }
    }
}

void printMap() {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%c", Map[i][j]->symbol);
        }
        puts("");
    }
}

void MovementQueue(Tile* tile) {
    for(int i = 0; i < 4; i++) {
        int newY = tile->y + moveY[i];
        int newX = tile->x + moveX[i];

        if(newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && Map[newY][newX]->symbol != '#' &&
        !Map[newY][newX]->isVisited) {
            Tile* nextTile = Map[newY][newX];
            double newDistance = nextTile->cost + tile->minDistance;

            Path* newPath = new Path(tile, nextTile, newDistance);
            priorityQueue.push(newPath);
        } 
    }
}

void initializeStartFinish() {
    startTile = Map[startY][startX];
    startTile->isVisited = true;
    startTile->minDistance = 0;
    startTile->symbol = 'S'; 

    MovementQueue(startTile);

    finishTile = Map[finishY][finishX];
    finishTile->symbol = 'E';
}

void backTrack(Tile *tile) {
    if(tile != startTile && tile != finishTile) tile->symbol = '*';
    if(tile != startTile) backTrack(tile->prev);
}

void solve() {
    initializeMap();
    initializeStartFinish();

    while(!priorityQueue.empty() && !finishTile->isVisited) {
        currPath = priorityQueue.top();
        priorityQueue.pop();

        currDst = currPath->dst;

        if(currDst->isVisited) {
            delete currPath;
            continue;
        }

        currDst->prev = currPath->src;
        currDst->isVisited = true;
        currDst->minDistance = currPath->distance;
        
        MovementQueue(currDst);
        delete currPath;
    }

    backTrack(finishTile);
    printMap();
}

int main() {
    solve();
    return 0;
}
