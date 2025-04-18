#ifndef GENERATE
#define GENERATE

#include <cstdlib>
#include <ctime>

int generateVelocity(int from, int to) {
    srand(static_cast<unsigned int>(time(nullptr)));
    return rand() % (to - from + 1) + from;
}

#endif