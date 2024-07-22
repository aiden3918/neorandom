// neorandom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define OLC_PGE_APPLICATION
#define OLC_PGEX_QUICKGUI

#include "neorandom.h"
#include <iostream>

class App : public NeoRandom {
public:

    // linear congruential algorithm: x = (a * x_0 + c) mod m
    uInt setAlgo(uInt seed) override {

        // x = (x_0) ^ 2 / 3
        // BSD: seed = 1103515245 * seed + 12345;
        // Microsoft: seed = 214013 * seed + 2531011;
        seed = 1103515245 * seed + 12345;

        // std::cout << seed << std::endl;

        return seed;
    }
};


int main() {

    App app;

    if (app.Construct(1280, 720, 1, 1)) {
        app.Start();
    }

    return 0;
}
