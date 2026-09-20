#include <stdio.h>

void hanoi (int n, char source, char target, char auxiliary) {
    if (n == 1) {
        printf(" %c -> %c\n", source, target);
        return;
    }
    hanoi(n - 1, source, auxiliary, target);
    printf(" %c -> %c\n", source, target);
    hanoi(n - 1, auxiliary, target, source);
}

int main (void) {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    if(n <= 0){
        printf("Number of disks must be a positive integer.\n");
        return 1;
    }

    hanoi (n, 'A', 'C', 'B');

    return 0;
}