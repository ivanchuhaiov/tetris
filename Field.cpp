#include "Field.h"

#define M Constants::M
#define N Constants::N

Field::Field() {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            field[i][j] = 0;
        }
    }
}


void Field::reset() {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            field[i][j] = 0;
        }
    }
}

void Field::lockTetromino(Point block[4], int colorNum) {
    for (int i = 0; i < 4; ++i) {
        int x = block[i].x;
        int y = block[i].y;
        if (x >= 0 && x < N && y >= 0 && y < M) {
            field[y][x] = colorNum;
        }
    }
}

int Field::clearLines() {
    int linesCleared = 0;

    for (int i = M - 1; i >= 0; --i) {
        bool isFull = true;
        for (int j = 0; j < N; ++j) {
            if (field[i][j] == 0) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            linesCleared++;

            for (int row = i; row > 0; --row) {
                for (int col = 0; col < N; ++col) {
                    field[row][col] = field[row - 1][col];
                }
            }

            for (int col = 0; col < N; ++col) {
                field[0][col] = 0;
            }
            ++i;
        }
    }
    return linesCleared;
}

bool Field::isOccupied(int x, int y) const {
    if (x < 0 || x >= N || y < 0 || y >= M) {
        return true;
    }
    return field[y][x] != 0;
}

bool Field::isGameOver(Point next[4]) const {
    for (int i = 0; i < 4; ++i) {
        int x = next[i].x;
        int y = next[i].y;
        if (x >= 0 && x < N && y >= 0 && y < M) {
            if (field[y][x] != 0) {
                return true;
            }
        }
    }
    return false;
}