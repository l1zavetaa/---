#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char f[20][20];
int n, m;
int winH, winV, winD;
int br, bc;

void clr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int inp(const char* t, int lo, int hi) {
    int x;
    while (1) {
        printf("%s", t);
        if (scanf("%d", &x) == 1 && x >= lo && x <= hi) {
            while (getchar() != '\n');
            return x;
        }
        while (getchar() != '\n');
        printf("Ошибка! Введите число от %d до %d.\n", lo, hi);
    }
}

void draw() {
    printf("\n    ");
    for (int j = 0; j < m; j++) {
        printf("%2d ", j + 1);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d  ", i + 1);
        for (int j = 0; j < m; j++) {
            printf(" %c ", f[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int win(char p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m - winH; j++) {
            int s = 0;
            for (int k = 0; k < winH; k++) {
                if (f[i][j + k] == p) s++;
            }
            if (s == winH) return 1;
        }
    }

    for (int i = 0; i <= n - winV; i++) {
        for (int j = 0; j < m; j++) {
            int s = 0;
            for (int k = 0; k < winV; k++) {
                if (f[i + k][j] == p) s++;
            }
            if (s == winV) return 1;
        }
    }

    for (int i = 0; i <= n - winD; i++) {
        for (int j = 0; j <= m - winD; j++) {
            int s = 0;
            for (int k = 0; k < winD; k++) {
                if (f[i + k][j + k] == p) s++;
            }
            if (s == winD) return 1;
        }
    }

    for (int i = 0; i <= n - winD; i++) {
        for (int j = winD - 1; j < m; j++) {
            int s = 0;
            for (int k = 0; k < winD; k++) {
                if (f[i + k][j - k] == p) s++;
            }
            if (s == winD) return 1;
        }
    }

    return 0;
}

int full() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (f[i][j] == '.') return 0;
        }
    }
    return 1;
}

void bm(char p) {
    while (1) {
        int r = rand() % n;
        int c = rand() % m;
        if (f[r][c] == '.') {
            f[r][c] = p;
            br = r;
            bc = c;
            break;
        }
    }
}

void hm(char p) {
    while (1) {
        printf("Ход игрока %c.\n", p);
        int r = inp("  Строка: ", 1, n) - 1;
        int c = inp("  Столбец: ", 1, m) - 1;

        if (f[r][c] != '.') {
            printf("Клетка занята, выберите другую.\n");
        }
        else {
            f[r][c] = p;
            break;
        }
    }
}

int main() {
#ifdef _WIN32
    system("chcp 1251 > nul");
#endif
    srand((unsigned)time(NULL));

    printf("Крестики-нолики \n\n");

    n = inp("Количество строк (3-20): ", 3, 20);
    m = inp("Количество столбцов (3-20): ", 3, 20);

    winH = m;
    winV = n;
    winD = (n < m) ? n : m;

    printf("\nРежим игры:\n  1 - против бота\n  2 - два игрока\n");
    int md = inp("Выбор: ", 1, 2);

    char h = 'X';
    char b = 'O';
    if (md == 1) {
        printf("\nЗа кого играть?\n  1 - крестики (X, ходят первыми)\n  2 - нолики (O)\n");
        int ch = inp("Выбор: ", 1, 2);
        if (ch == 2) {
            h = 'O';
            b = 'X';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            f[i][j] = '.';
        }
    }

    char cur = 'X';
    int mv = 0;

    while (1) {
        if (md == 1 && cur == b) {
            bm(b);
            mv = 1;
        }
        else {
            clr();
            printf("Поле %dx%d | Победа: гор. %d, верт. %d, диаг. %d\n",
                n, m, winH, winV, winD);
            draw();
            if (mv == 1) {
                printf("Бот (%c) сходил: строка %d, столбец %d.\n",
                    b, br + 1, bc + 1);
            }
            hm(cur);
            mv = 0;
        }

        if (win(cur) == 1) {
            clr();
            draw();
            if (mv == 1) {
                printf("Бот (%c) сходил: строка %d, столбец %d.\n",
                    b, br + 1, bc + 1);
            }
            if (md == 1) {
                if (cur == h) {
                    printf("Вы победили!\n");
                }
                else {
                    printf("Бот победил!\n");
                }
            }
            else {
                printf("Победил игрок %c!\n", cur);
            }
            break;
        }

        if (full() == 1) {
            clr();
            draw();
            if (mv == 1) {
                printf("Бот (%c) сходил: строка %d, столбец %d.\n",
                    b, br + 1, bc + 1);
            }
            printf("Ничья!\n");
            break;
        }

        cur = (cur == 'X') ? 'O' : 'X';
    }

    printf("\nНажмите Enter для выхода...");
    while (getchar() != '\n');
    getchar();

    return 0;
}