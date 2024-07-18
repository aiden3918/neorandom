// neorandom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define OLC_PGE_APPLICATION
#define OLC_PGEX_QUICKGUI

#include "neorandom.h"
#include <iostream>

class App : public NeoRandom {
public:
    void setAlgo(int seed) override {
        std::cout << "yah" << std::endl;
    }
};


int main() {

    App app;

    if (app.Construct(1280, 720, 1, 1)) {
        app.Start();
    }

    return 0;
}
