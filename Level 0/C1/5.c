#include <stdio.h>

int main(){
    int a,b,max;
    printf("Please enter two integers: ");
    scanf("%d %d", &a, &b);

    if(a>b)
        max = a;
    else
        max = b;

    printf("The maximum of %d and %d is %d.\n", a, b, max);

    return 0;
}