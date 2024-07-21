// neorandom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define OLC_PGE_APPLICATION
#define OLC_PGEX_QUICKGUI

#include "neorandom.h"
#include <iostream>

class App : public NeoRandom {
public:
    void setAlgo(int seed) override {
        // std::time_t time = std::time(nullptr);
        std::cout << "yah" << std::endl;
        // std::cout << std::asctime_s(std::localtime(&time)) << time << std::endl;

    }
};


int main() {

    App app;

    if (app.Construct(1280, 720, 1, 1)) {
        app.Start();
    }

    return 0;
}
