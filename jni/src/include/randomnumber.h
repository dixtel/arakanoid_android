#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

#include <random>

inline int GetRandomNumber(int from, int to) {

    static std::mt19937 randomGenerator;

    static bool isSeed = false;

    if (!isSeed) {

        randomGenerator.seed(std::random_device()());
        isSeed = true;
    }

    std::uniform_int_distribution <int> distribution(from, to);

    return distribution(randomGenerator);
}

#endif // RANDOMNUMBER_H
