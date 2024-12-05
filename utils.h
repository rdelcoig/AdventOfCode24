//
// Created by romain on 3/12/24.
//

#ifndef UTILS_H
#define UTILS_H

#define COMPARE(l,r) ((l < r) ? -1 : (l > r))

typedef struct {
    int part_1;
    int part_2;
} Answer2Parts;

inline int min(const int left, const int right) {
    return left < right ? left : right;
}

#endif //UTILS_H
