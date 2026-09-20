#include <stdio.h>

int main(void){
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int b[5];

    printf("Please enter 5 digits(0-9):\n ");
    for(int i=0; i<5; i++){
        scanf("%d", &b[i]);
    }

    printf("Missing digits: ");
    for(int i=0; i<10; i++){
        for(int j=0; j<5; j++){
            if(a[i] == b[j]){
                break;
            }
            if(j == 4){
                printf("%d ", a[i]);
            }
        }
    }
    printf("\n");
    return 0;
}