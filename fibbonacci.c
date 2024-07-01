#include <stdio.h>

//Memoization
int memo[100] = {0};

int fibbonacci(int n) {
    if(n <= 1) return 1;
    else if(memo[n] != 0) return memo[n];
    else return memo[n] = fibbonacci(n - 1) + fibbonacci(n - 2);
}

int main() {
    //Tabulation
    int n = 5;
    int memo[100] = {0};
    memo[0] = 1;
    memo[1] = 1;

    for(int i = 2;i <= n; i++) {
        memo[i] = memo[i-1] + memo[i-2];
    }

    printf("%d", memo[n]);

    return 0;
}