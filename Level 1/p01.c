#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(void){
    const char *text = "idiot hdq";
    const int width = 120;

    int pos = 0;
    int dir = 1;
    int sleep_time = 100;

    while (1){
        printf("\r");
        for (int i = 0; i < width; i++){
            if (i == pos){
                printf("%s", text);
            } else {
                printf(" ");
            }
        }
        fflush(stdout);

        pos += dir;
        if (pos <= 0){
            dir = 1;
        } else if (pos >= width - 1){
            dir = -1;
        }
        Sleep(sleep_time);
    }
    return 0;
}