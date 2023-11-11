#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 20
#define COLS 40

// Функция для инициализации игрового поля случайными значениями
void initialize_board(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % 2;
        }
    }
}

// Функция для отображения текущего состояния игрового поля
void print_board(int board[ROWS][COLS]) {
    system("clear");  // Очистка экрана (работает в Unix-подобных системах, под Windows замените на "cls")
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 1) {
                printf("■ ");
            } else {
                printf("□ ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Функция для вычисления следующего поколения игрового поля
void next_generation(int current[ROWS][COLS], int next[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = 0;

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;  // Игнорировать текущую клетку
                    int ni = (i + x + ROWS) % ROWS;  // Обработка периодических граничных условий
                    int nj = (j + y + COLS) % COLS;  // Обработка периодических граничных условий
                    neighbors += current[ni][nj];
                }
            }

            // Применение правил игры "Жизнь"
            next[i][j] = (neighbors == 3 || (current[i][j] == 1 && neighbors == 2)) ? 1 : 0;
        }
    }
}

int main() {
    int current_board[ROWS][COLS];
    int next_board[ROWS][COLS];

    initialize_board(current_board);

    while (1) {
        print_board(current_board);
        next_generation(current_board, next_board);
        usleep(200000);  // Задержка между поколениями (200 миллисекунд)
        // Можно использовать функцию sleep(1) для секундной задержки, но это делает игру менее интересной
        // sleep(1);
        
        // Копирование следующего поколения в текущее
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                current_board[i][j] = next_board[i][j];
            }
        }
    }

    return 0;
}
