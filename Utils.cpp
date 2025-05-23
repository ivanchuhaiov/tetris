#include "Utils.h"
#include <cstdlib>

#define M Constants::M
#define N Constants::N
#define figures Constants::figures


bool Utils::check(Point a[4], const Field& field) {
    for (int i = 0; i < 4; ++i) {
        if (field.isOccupied(a[i].x, a[i].y)) {
            return false;
        }
    }
    return true;
}

bool Utils::checkGameOver(const Field& field) {
    Point temp[4];
    int n = rand() % 7;

    for (int i = 0; i < 4; ++i) {
        temp[i].x = figures[n][i] % 2 + N / 2 - 1;
        temp[i].y = figures[n][i] / 2;
    }

    return field.isGameOver(temp);
}