#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n;
    scanf("%d", &n);

    int *a = (int*)malloc(n * sizeof(int));
    if(a == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n ;i++){
        scanf("%d", &a[i]);
    }

    for (int j = n-1 ;j >= 0; j--){
        printf("%d ", a[j]);
    }
    printf("\n");

    free(a);
    return 0;
}