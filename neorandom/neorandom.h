#pragma once

#ifndef neorandom_h
#define neorandom_h

#include "olcPixelGameEngine.h"
#include "olcPGEX_QuickGUI.h"
#include <chrono>
#include <iostream>

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

        if (generateSeedBtn->bPressed) generateSeed();

        drawGraph();
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

    // algo
    unsigned int _seed;

    unsigned int _min;
    unsigned int _max;
    unsigned int _range;
    unsigned int _iterations;

    // set any parameters to a negative value to keep it the same
    bool setAllParams(int minVal, int maxVal, int numIterations) {
        if (minVal >= maxVal || numIterations < 1) return false;

        if (minVal >= 0) _min = minVal;
        if (maxVal >= 0) _max = maxVal;
        _range = _max - _min;
        _iterations = numIterations;

        return true;
        
    }

    // since we can define the iteraitons every time, it might be better if we defined it
    // as an array
    std::vector<unsigned int> generatedNums;
    std::vector<std::pair<unsigned int, unsigned int>> numFreqPair;

    void generateSeed() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto msSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::cout << msSinceEpoch << std::endl;

        _seed = msSinceEpoch; // possibe overflow in a few years ;)
        seedTextInput->sText = std::to_string(_seed);
    }

    // GUI
    olc::QuickGUI::Manager _guiManager;

    olc::QuickGUI::TextBox* seedTextInput = nullptr;
    olc::QuickGUI::Button* generateSeedBtn = nullptr; // uses current date
    olc::QuickGUI::Button* runAlgoBtn = nullptr;

    void createGUI() {
        seedTextInput = new olc::QuickGUI::TextBox(_guiManager, "Enter seed:", 
            { 50.0f, 50.0f }, { 100.0f, 50.0f });
        generateSeedBtn = new olc::QuickGUI::Button(_guiManager, "Generate seed (ms)",
            { 200.0f, 50.0f }, { 150.0f, 50.0f });
        runAlgoBtn = new olc::QuickGUI::Button(_guiManager, "Run",
            { 400.0f, 50.0f }, { 50.0f, 50.0f });
    }

    void updateGUI() { 
        _guiManager.Update(this);
        _guiManager.Draw(this);
    }

    //graph
    olc::vi2d _graphPos = { 50, 150 };
    olc::vi2d _graphSize = { 700, 500 };

    void drawGraph() {
        DrawRect(_graphPos, _graphSize, olc::BLACK);
    }
};

#endif