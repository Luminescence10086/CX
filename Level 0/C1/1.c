#include <stdio.h>

int main(){
    int num;
    printf("Please enter an integer: ");
    scanf("%d", &num);
    
    if(num>0)
        printf("%d is a positive number\n", num);
    else if(num<0)
        printf("%d is a negative number\n", num);
    else
        printf("%d is zero\n", num);
    return 0;
}