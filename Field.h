#ifndef FIELD_H
#define FIELD_H
#include "Constants.h"





class Field {
public:
    Field();
    void reset();
    void lockTetromino(Point block[4], int colorNum);
    int clearLines();
    bool isOccupied(int x, int y) const;
    bool isGameOver(Point next[4]) const;

    int field[Constants::M][Constants::N];

};



#endif
