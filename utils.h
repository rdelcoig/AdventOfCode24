//
// Created by romain on 3/12/24.
//

#ifndef UTILS_H
#define UTILS_H

int min(int left, int right) {
    return left < right ? left : right;
}

int compare(const void* left, const void* right)
{
    const int int_left = * (int*) left;
    const int int_right = * (int*) right;

    if ( int_left > int_right ) return 1;
    if ( int_left < int_right ) return -1;
    return 0;
}

#endif //UTILS_H
