#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_ROWS 20
#define MAX_COLS 20

/* 静态地图：'#' 墙，'.' 目标，' ' 空地 */
char staticMap[MAX_ROWS][MAX_COLS];
/* 箱子位置：1 表示有箱子 */
int hasBox[MAX_ROWS][MAX_COLS];
int ROWS, COLS;
int playerR, playerC;
int steps;

/* ---------- 加载关卡 ---------- */
int loadLevel(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    /* 初始化 */
    for (int i = 0; i < MAX_ROWS; i++)
        for (int j = 0; j < MAX_COLS; j++) {
            staticMap[i][j] = ' ';
            hasBox[i][j] = 0;
        }

    int row = 0;
    char line[256];
    int maxCols = 0;

    while (fgets(line, sizeof(line), fp) && row < MAX_ROWS) {
        line[strcspn(line, "\r\n")] = '\0';   /* 去掉换行 */
        int len = strlen(line);
        if (len > maxCols) maxCols = len;

        for (int j = 0; j < len && j < MAX_COLS; j++) {
            char c = line[j];
            switch (c) {
                case '#': staticMap[row][j] = '#'; break;
                case '.': staticMap[row][j] = '.'; break;
                case ' ': staticMap[row][j] = ' '; break;
                case 'P': playerR = row; playerC = j; staticMap[row][j] = ' '; break;
                case '+': playerR = row; playerC = j; staticMap[row][j] = '.'; break;
                case 'B': hasBox[row][j] = 1; staticMap[row][j] = ' '; break;
                case '*': hasBox[row][j] = 1; staticMap[row][j] = '.'; break;
                default:  staticMap[row][j] = ' '; break;
            }
        }
        row++;
    }
    fclose(fp);

    ROWS = row;
    COLS = maxCols;
    return 1;
}

/* ---------- 绘制地图 ---------- */
void draw(void) {
    system("cls");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (staticMap[i][j] == '#') {
                putchar('#');
            } else if (hasBox[i][j]) {
                if (staticMap[i][j] == '.') putchar('*');   /* 箱子在目标上 */
                else putchar('B');
            } else if (i == playerR && j == playerC) {
                if (staticMap[i][j] == '.') putchar('+');   /* 玩家在目标上 */
                else putchar('P');
            } else if (staticMap[i][j] == '.') {
                putchar('.');
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
    printf("Steps: %d\n", steps);
    printf("Arrow keys: move    Q: quit\n");
}

/* ---------- 检查是否胜利 ---------- */
int checkWin(void) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (staticMap[i][j] == '.' && !hasBox[i][j])
                return 0;   /* 还有目标点没被箱子占 */
    return 1;
}

/* ---------- 移动玩家，返回 1 表示胜利 ---------- */
int movePlayer(int dr, int dc) {
    int nr = playerR + dr;
    int nc = playerC + dc;

    if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) return 0;
    if (staticMap[nr][nc] == '#') return 0;

    if (hasBox[nr][nc]) {
        int br = nr + dr;
        int bc = nc + dc;
        if (br < 0 || br >= ROWS || bc < 0 || bc >= COLS) return 0;
        if (staticMap[br][bc] == '#' || hasBox[br][bc]) return 0;

        /* 推箱子 */
        hasBox[nr][nc] = 0;
        hasBox[br][bc] = 1;
    }

    playerR = nr;
    playerC = nc;
    steps++;
    return checkWin();
}

/* ---------- 主程序 ---------- */
int main(void) {
    const char *levels[] = {"level1.txt", "level2.txt", "level3.txt"};
    int levelCount = 3;

    for (int i = 0; i < levelCount; i++) {
        if (!loadLevel(levels[i])) {
            printf("Cannot load %s, skipping.\n", levels[i]);
            continue;
        }

        steps = 0;
        draw();

        int won = 0;
        while (!won) {
            int ch = getch();
            if (ch == 'q' || ch == 'Q') {
                printf("Quit.\n");
                return 0;
            }
            if (ch == 0 || ch == 224) {          /* 方向键前缀 */
                ch = getch();
                switch (ch) {
                    case 72: won = movePlayer(-1, 0); break;  /* 上 */
                    case 80: won = movePlayer(1, 0);  break;  /* 下 */
                    case 75: won = movePlayer(0, -1); break;  /* 左 */
                    case 77: won = movePlayer(0, 1);  break;  /* 右 */
                }
            }
            draw();
        }

        printf("Level %d complete! Steps: %d\n", i + 1, steps);

        /* 记录分数到文件 */
        FILE *fp = fopen("scores.txt", "a");
        if (fp) {
            fprintf(fp, "Level %d: %d steps\n", i + 1, steps);
            fclose(fp);
        }

        printf("Press any key to continue...\n");
        getch();
    }

    printf("All levels completed!\n");
    return 0;
}