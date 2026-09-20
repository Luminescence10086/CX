#include <stdio.h>

int main(){
    int n, max, temp;
    printf("Please enter the number of integers(n): ");
    scanf("%d", &n);

    if(n <= 0){
        printf("Invalid input. Please enter a positive integer for n.\n");
        return 1;
    }

    printf("Please enter %d integers: ", n);
    scanf("%d", &max); 

    for(int i = 1; i < n; i++){
        scanf("%d", &temp);
        if(temp > max)
            max = temp;
    }
    printf("The maximum integer is %d.\n", max);
    
    return 0;
}