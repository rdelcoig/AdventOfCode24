//
// Created by romain on 3/12/24.
//

#ifndef UTILS_H
#define UTILS_H

inline int min(const int LEFT, const int RIGHT) {
    return LEFT < RIGHT ? LEFT : RIGHT;
}

int compare(const void *LEFT, const void *RIGHT) {
    const int INT_LEFT = *(int *) LEFT;
    const int INT_RIGHT = *(int *) RIGHT;

    if (INT_LEFT > INT_RIGHT) return 1;
    if (INT_LEFT < INT_RIGHT) return -1;
    return 0;
}

#endif //UTILS_H
