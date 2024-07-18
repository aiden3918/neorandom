#pragma once

#ifndef neorandom_h
#define neorandom_h

#include "olcPixelGameEngine.h"
#include "olcPGEX_QuickGUI.h"

class NeoRandom : public olc::PixelGameEngine {
public:
    NeoRandom() { sAppName = "neorandom"; }

    bool OnUserCreate() override {
        createGUI();
        setAlgo(seed);
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(olc::GREY);
        SetPixelMode(olc::Pixel::MASK);

        updateGUI();

        return true;
    }

    bool OnUserDestroy() override {
        return true;
    }

    virtual void setAlgo(int seed) {
        std::cout << "Algo undefined" << std::endl;
    }

    int seed = 0;
private:
    void createGUI() {
        seedTextInput = new olc::QuickGUI::TextBox(_guiManager, "asdfsa", { 50.0f, 50.0f }, { 100.0f, 50.0f });
    }

    void updateGUI() { 
        _guiManager.Update(this);
        _guiManager.Draw(this);
    }

    olc::QuickGUI::Manager _guiManager;

    olc::QuickGUI::TextBox* seedTextInput = nullptr;
    olc::QuickGUI::Button* generateSeedBtn = nullptr; // uses current date
};

#endif