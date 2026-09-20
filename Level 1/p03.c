#include <stdio.h>
#include <time.h>

#define N 1000

int main(void){
    int is_Prime[N+1];
    for(int i=0; i<=N; i++){
        is_Prime[i] = 1;
    }
    is_Prime[0]=is_Prime[1]=0;

    clock_t start = clock();
    for(int i = 2; i*i <= N; i++){
        if(is_Prime[i]){
            for(int j = i*i; j <= N; j += i){
                is_Prime[j] = 0;
            }
        }
    }
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Prime numbers between 2 and %d:\n", N);
    for(int i = 2; i <= N; i++){
        if(is_Prime[i]){
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Elapsed time: %f seconds\n", elapsed);

    return 0;
}