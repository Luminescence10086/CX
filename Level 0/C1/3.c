#include <stdio.h>

int main(){
    int num;
    printf("please enter an integer: ");
    scanf("%d", &num);

    if(num % 13 ==0)
        printf("%d is a multiple of 13.\n", num);
    else
        printf("%d is not a multiple of 13.\n", num);

    return 0;
}