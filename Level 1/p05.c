#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

/* 数组最大尺寸，实际尺寸由用户输入决定 */
#define MAX_ROWS 51
#define MAX_COLS 101

char maze[MAX_ROWS][MAX_COLS + 1];
int visited[MAX_ROWS][MAX_COLS];

int ROWS;   /* 实际行数（奇数） */
int COLS;   /* 实际列数（奇数） */

int playerR, playerC;
int exitR, exitC;

int openCells[MAX_ROWS * MAX_COLS][2];
int openCount = 0;

HANDLE hOut;

#define COLOR_WALL   (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COLOR_PLAYER (FOREGROUND_RED   | FOREGROUND_INTENSITY)
#define COLOR_EXIT   (FOREGROUND_BLUE  | FOREGROUND_INTENSITY)

void setColor(WORD attr) {
    SetConsoleTextAttribute(hOut, attr);
}

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, c);
}

int dr[4] = { -2, 2, 0, 0 };
int dc[4] = { 0, 0, -2, 2 };

void shuffle(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

void carve(int r, int c) {
    visited[r][c] = 1;
    maze[r][c] = ' ';

    openCells[openCount][0] = r;
    openCells[openCount][1] = c;
    openCount++;

    int dirs[4] = {0, 1, 2, 3};
    shuffle(dirs, 4);

    for (int k = 0; k < 4; k++) {
        int d = dirs[k];
        int nr = r + dr[d];
        int nc = c + dc[d];

        if (nr <= 0 || nr >= ROWS - 1 || nc <= 0 || nc >= COLS - 1) continue;
        if (visited[nr][nc]) continue;

        maze[r + dr[d] / 2][c + dc[d] / 2] = ' ';
        carve(nr, nc);
    }
}

void generateMaze(void) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze[i][j] = '#';
            visited[i][j] = 0;
        }
        maze[i][COLS] = '\0';
    }

    openCount = 0;
    carve(1, 1);

    playerR = 1;
    playerC = 1;
    maze[playerR][playerC] = 'P';

    /* 选离起点曼哈顿距离最远的可走格子当出口 */
    int bestDist = -1;
    exitR = 1;
    exitC = 1;
    for (int i = 0; i < openCount; i++) {
        int r = openCells[i][0];
        int c = openCells[i][1];
        if (r == 1 && c == 1) continue;

        int dist = (r - 1) + (c - 1);
        if (dist > bestDist) {
            bestDist = dist;
            exitR = r;
            exitC = c;
        }
    }
    maze[exitR][exitC] = 'E';
}

void draw(void) {
    gotoxy(0, 0);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char c = maze[i][j];

            if (c == 'P') {
                setColor(COLOR_PLAYER);
                putchar(c);
                setColor(COLOR_WALL);
            } else if (c == 'E') {
                setColor(COLOR_EXIT);
                putchar(c);
                setColor(COLOR_WALL);
            } else {
                putchar(c);
            }
        }
        printf("\n");
    }

    setColor(COLOR_WALL);
    printf("\nArrow keys: move    Q: quit\n");
}

int tryMove(int ddr, int ddc) {
    int nr = playerR + ddr;
    int nc = playerC + ddc;

    if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) return 0;
    if (maze[nr][nc] == '#') return 0;

    int reachedExit = (maze[nr][nc] == 'E');

    maze[playerR][playerC] = ' ';
    playerR = nr;
    playerC = nc;
    maze[playerR][playerC] = 'P';

    draw();
    return reachedExit;
}

/* 输入一个奇数，范围 [min, max] */
int inputOdd(const char *prompt, int min, int max) {
    int v;
    while (1) {
        printf("%s (%d-%d, odd): ", prompt, min, max);
        if (scanf("%d", &v) != 1) {
            while (getchar() != '\n');   /* 清掉非法输入 */
            continue;
        }
        if (v < min || v > max) {
            printf("Out of range, try again.\n");
            continue;
        }
        if (v % 2 == 0) {
            v++;                          /* 偶数自动 +1 变成奇数 */
            printf("Adjusted to odd: %d\n", v);
            if (v > max) v -= 2;
        }
        return v;
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    printf("=== Maze Generator ===\n");
    ROWS = inputOdd("Rows", 5, MAX_ROWS);
    COLS = inputOdd("Cols", 5, MAX_COLS);

    printf("\nGenerating %dx%d maze...\n", ROWS, COLS);
    printf("Make sure your terminal window is at least %d cols x %d rows.\n",
           COLS + 2, ROWS + 4);
    printf("Press any key to start...");
    getch();

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hOut, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &info);

    system("color 0a");
    system("cls");

    generateMaze();
    draw();

    int ch;
    while (1) {
        ch = getch();
        if (ch == 'q' || ch == 'Q') break;

        int won = 0;
        if (ch == 0 || ch == 224) {
            ch = getch();
            switch (ch) {
                case 72: won = tryMove(-1, 0); break;
                case 80: won = tryMove(1, 0);  break;
                case 75: won = tryMove(0, -1); break;
                case 77: won = tryMove(0, 1);  break;
            }
        }

        if (won) {
            setColor(COLOR_EXIT);
            gotoxy(0, ROWS + 1);
            printf("*** You win! ***\n");
            setColor(COLOR_WALL);
            printf("Press any key to exit...");
            getch();
            break;
        }
    }

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    info.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &info);
    gotoxy(0, ROWS + 4);
    return 0;
}