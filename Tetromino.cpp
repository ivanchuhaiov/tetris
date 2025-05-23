//
// Created by Ivan_ on 16.05.2025.
//

#include "Tetromino.h"
#include <cstdlib>

#define M Constants::M
#define N Constants::N
#define figures Constants::figures

Tetromino::Tetromino() {
    figureType = 0;
    colorNum = 1;

    nextFigureType = rand() % 7;
    nextColorNum = 1 + rand() % 7;

    for (int i = 0; i < 4; ++i) {
        a[i].x = 0;
        a[i].y = 0;
        b[i].x = 0;
        b[i].y = 0;
        nextFigure[i].x = 0;
        nextFigure[i].y = 0;
    }

    prepareNextFigure();
}

void Tetromino::spawn() {
    figureType = nextFigureType;
    colorNum = nextColorNum;

    for (int i = 0; i < 4; ++i) {
        a[i].x = figures[figureType][i] % 2 + N / 2 - 1;
        a[i].y = figures[figureType][i] / 2;
    }

    prepareNextFigure();
}

void Tetromino::prepareNextFigure() {
    nextFigureType = rand() % 7;
    nextColorNum = 1 + rand() % 7;

    for (int i = 0; i < 4; ++i) {
        nextFigure[i].x = 0;
        nextFigure[i].y = 0;
    }

    switch(nextFigureType) {
        case 0:
            nextFigure[0].x = 0;
            nextFigure[1].x = 1;
            nextFigure[2].x = 2;
            nextFigure[3].x = 3;

            nextFigure[0].y = 1;
            nextFigure[1].y = 1;
            nextFigure[2].y = 1;
            nextFigure[3].y = 1;
            break;

        case 1:
            nextFigure[0].x = 0;
            nextFigure[1].x = 1;
            nextFigure[2].x = 1;
            nextFigure[3].x = 2;

            nextFigure[0].y = 0;
            nextFigure[1].y = 0;
            nextFigure[2].y = 1;
            nextFigure[3].y = 1;
        break;


        case 2:
            nextFigure[0].x = 1;
            nextFigure[1].x = 2;
            nextFigure[2].x = 0;
            nextFigure[3].x = 1;

            nextFigure[0].y = 0;
            nextFigure[1].y = 0;
            nextFigure[2].y = 1;
            nextFigure[3].y = 1;
        break;

        case 3:
            nextFigure[0].x = 1;
            nextFigure[1].x = 0;
            nextFigure[2].x = 1;
            nextFigure[3].x = 2;

            nextFigure[0].y = 0;
            nextFigure[1].y = 1;
            nextFigure[2].y = 1;
            nextFigure[3].y = 1;
            break;

        case 4:
            nextFigure[0].x = 2;
            nextFigure[1].x = 0;
            nextFigure[2].x = 1;
            nextFigure[3].x = 2;

            nextFigure[0].y = 0;
            nextFigure[1].y = 1;
            nextFigure[2].y = 1;
            nextFigure[3].y = 1;
            break;

        case 5:
            nextFigure[0].x = 0;
            nextFigure[1].x = 0;
            nextFigure[2].x = 1;
            nextFigure[3].x = 2;

            nextFigure[0].y = 0;
            nextFigure[1].y = 1;
            nextFigure[2].y = 1;
            nextFigure[3].y = 1;
            break;

        case 6:
            nextFigure[0].x = 1;
            nextFigure[1].x = 2;
            nextFigure[2].x = 1;
            nextFigure[3].x = 2;

            nextFigure[0].y = 0;
            nextFigure[1].y = 0;
            nextFigure[2].y = 1;
            nextFigure[3].y = 1;
        break;


    }
}

void Tetromino::move(int dx) {
    for (int i = 0; i < 4; ++i) {
        b[i] = a[i];
        a[i].x += dx;
    }
}

void Tetromino::rotate() {
    for (int i = 0; i < 4; ++i) {
        b[i] = a[i];
    }

    Point p = a[1];

    for (int i = 0; i < 4; ++i) {
        int x = a[i].y - p.y;
        int y = a[i].x - p.x;
        a[i].x = p.x - x;
        a[i].y = p.y + y;
    }
}

void Tetromino::drop() {
    for (int i = 0; i < 4; ++i) {
        b[i] = a[i];
        a[i].y += 1;
    }
}

void Tetromino::revert() {
    for (int i = 0; i < 4; ++i) {
        a[i] = b[i];
    }
}

Point* Tetromino::getBlocks() {
    return a;
}

int Tetromino::getColor() {
    return colorNum;
}

Point* Tetromino::getNextFigureBlocks() {
    return nextFigure;
}

int Tetromino::getNextFigureColor() {
    return nextColorNum;
}

int Tetromino::getNextFigureType() {
    return nextFigureType;
}