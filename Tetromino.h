#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include "Field.h"
#include "Constants.h"

class Tetromino {
private:
    Point a[4], b[4], nextFigure[4];

    int figureType, nextFigureType;

    int colorNum, nextColorNum;

    void prepareNextFigure();

public:
    Tetromino();

    void spawn();

    void move(int dx);

    void rotate();

    void drop();

    void revert();

    Point* getBlocks();

    int getColor();

    Point* getNextFigureBlocks();

    int getNextFigureColor();

    int getNextFigureType();
};

#endif