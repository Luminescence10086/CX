#include <stdio.h>

int main(void){
    int sum =0;
    for(int i=1; i<=100; i++){
        if(i%7==0 || i%10==7){
            printf("%d ",i);
            sum += i;
        }
    }
    printf("\nSum: %d\n", sum);
    return 0;
}