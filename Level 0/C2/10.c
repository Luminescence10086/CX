#include <stdio.h>

int main (void){
    int bucket[10] = {0};
    int x;

    printf("Please enter 5 digits(0-9):\n");
    for(int i=0; i<5; i++){
        scanf("%d", &x);
        if(x>=0 && x<=9){
            bucket[x]++;
        }else{
            printf("Invalid input: %d. Please enter a digit between 0 and 9.\n", x);
            i--; 
        }
    }

    printf("Sorted: ");
    for(int i=0; i<10; i++){
        for(int j=0;j<bucket[i]; j++){
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}