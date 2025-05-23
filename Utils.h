#ifndef UTILS_H
#define UTILS_H
#include "Field.h"


class Utils {
public:
    bool check(Point a[4], const Field& field);
    bool checkGameOver(const Field& field);
};

#endif