#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ROWS 11
#define COLS 21


char maze[ROWS][COLS + 1] = {
    "####################",
    "#P                 #",
    "# ### ##### ### ## #",
    "#   #     #   #    #",
    "### # ### # ### ## #",
    "#   # #   #   #    #",
    "# ### # ##### #### #",
    "#     #     #      #",
    "# ##### ### # #### #",
    "#                 E#",
    "####################"
};

int playerR = 1;
int playerC = 1;

/* 重画整张地图 */
void draw(void) {
    system("cls");
    for (int i = 0; i < ROWS; i++) {
        printf("%s\n", maze[i]);
    }
    printf("\nArrow keys: move    Q: quit\n");
}


int tryMove(int dr, int dc) {
    int nr = playerR + dr;
    int nc = playerC + dc;

    if (maze[nr][nc] == '#') return 0;      

    int reachedExit = (maze[nr][nc] == 'E');

    maze[playerR][playerC] = ' ';           
    playerR = nr;
    playerC = nc;
    maze[playerR][playerC] = 'P';           

    draw();
    return reachedExit;
}

int main(void) {
    system("color 0a");     
    draw();

    int ch;
    while (1) {
        ch = getch();

        if (ch == 'q' || ch == 'Q') break;

        int won = 0;
        if (ch == 0 || ch == 224) {            
            ch = getch();
            switch (ch) {
                case 72: won = tryMove(-1, 0); break;  /* 上 */
                case 80: won = tryMove(1, 0);  break;  /* 下 */
                case 75: won = tryMove(0, -1); break;  /* 左 */
                case 77: won = tryMove(0, 1);  break;  /* 右 */
            }
        }

        if (won) {
            printf("\n*** You win! ***\n");
            printf("Press any key to exit...");
            getch();
            break;
        }
    }

    return 0;
}