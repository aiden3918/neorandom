// neorandom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define OLC_PGE_APPLICATION

#include "olcPixelGameEngine.h"
#include "olcPGEX_QuickGUI.h"
#include <iostream>

class App : public olc::PixelGameEngine {
public:
    App() { sAppName = "neorandom"; }

    bool OnUserCreate() override {
        
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(olc::WHITE);
        SetPixelMode(olc::Pixel::MASK);

        return true;
    }

    bool OnUserDestroy() override {
        return true;
    }

private:
    olc::QuickGUI::Manager guiManager;
};


int main() {

    App app;

    if (app.Construct(1280, 720, 1, 1)) {
        app.Start();
    }

    return 0;
}
