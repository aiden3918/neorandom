#pragma once

#ifndef neorandom_h
#define neorandom_h

#include "olcPixelGameEngine.h"
#include "olcPGEX_QuickGUI.h"
#include <chrono>
#include <algorithm>

typedef unsigned long int uInt;

struct GraphPoint {
    olc::vi2d pos;
    uInt value;
    uInt relFreq;
    float relFreqPercent;
    float weightedRelFreqPercent; // its relative frequency compared to the highest actual relative frequency
};

// a prng, linear noncongruential rng algorithm
class NeoRandom : public olc::PixelGameEngine {
public:
    NeoRandom() { sAppName = "neorandom"; }

    bool OnUserCreate() override {
        setAllParams(5, 10, 1000);
        _createGUI();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(olc::GREY);
        SetPixelMode(olc::Pixel::MASK);

        if (_runAlgoBtn->bPressed) {

            if (_validateInputs()) {
                _errorLabel->sText = "";
                std::cout << "Valid inputs" << std::endl;
                _runAlgo();
                std::cout << "Successfuly ran algorithm" << std::endl;

                _getResultData();
                _updateGraphPoints();
            }
            else {
                _errorLabel->sText = "Invalid input. Make sure all parameters are positive integers";
                std::cout << "Invalid input" << std::endl;
            }

        }

        if (_generateSeedBtn->bPressed) _generateSeed();

        _drawGraph();
        _updateGUI();

        return true;
    }

    bool OnUserDestroy() override {
        return true;
    }

    virtual uInt setAlgo(uInt seed) {
        std::cout << "Algo undefined" << std::endl;
        return seed;
    }

    // set any parameters to a negative value to keep it the same
    // range: [min, max]
    bool setAllParams(int minVal, int maxVal, int numIterations) {
        if (minVal >= maxVal || numIterations < 1) return false;

        if (minVal >= 0) _min = minVal;
        if (maxVal >= 0) _max = maxVal + 1;
        _range = _max - _min;
        _iterations = numIterations;

        return true;

    }

private:

    // algo
    uInt _seed;

    uInt _min = 0;
    uInt _max = 11;
    uInt _range = _max - _min;
    uInt _iterations = 10;

    // since we can define the iteraitons every time, it might be better if we defined it
    // as an array
    std::vector<uInt> _generatedNums;
    std::map<uInt, uInt> _numFreqPair;

    uInt _highestRelFreq;
    float _highestRelFreqDec;

    float _idealFrequencyDec; // the theoretical frequency of all generated nums if the algo is "fair"

    void _runAlgo() {

        uInt x = std::stoul(_seedTextInput->sText);
        _min = std::stoul(_minInput->sText);
        _max = std::stoul(_maxInput->sText);
        _iterations = std::stoul(_iterationsInput->sText);
        _range = _max - _min;

        std::cout << "min: " << _min << " | max: " << _max << " | iterations: " << _iterations << std::endl;
        std::cout << "first x successfully created" << std::endl;

        _generatedNums.clear();
        _numFreqPair.clear();

        // custom algo
        for (int i = 0; i < _iterations; i++) {
            //x = (setAlgo(x) % _range) + _min;
            //_generatedNums.push_back(x);

            x = setAlgo(x);
            int result = (x % _range) + _min;
            _generatedNums.push_back(result);
        }

        std::cout << "algo done" << std::endl;
        //for (auto &e : _generatedNums) {
        //    std::cout << e << std::endl;
        //}
    }

    // O(nlog(n))
    void _getResultData() {
       
        std::cout << "sorting..." << std::endl;

        // get frequency of each generated num
        for (auto& e : _generatedNums) {
            if (_numFreqPair.find(e) == _numFreqPair.end()) {
                _numFreqPair[e] = 1;
            }
            else {
                _numFreqPair[e]++;
            }
        }

        for (auto &p : _numFreqPair) {
            std::cout << "Value: " << p.first << " | Frequency: " << p.second << std::endl;
        }

        // get highest relative frequency
        // not exactly sure how the lambda contributes to all this, but ok
        // https://stackoverflow.com/questions/9370945/finding-the-max-value-in-a-map
        auto max_e = std::max_element(_numFreqPair.begin(), _numFreqPair.end(),
            [](const std::pair<uInt, uInt>& a, const std::pair<uInt, uInt>& b) {
                return a.second < b.second; }
        );

        _highestRelFreq = max_e->second;
        _highestRelFreqDec = (float)_highestRelFreq / (float)_generatedNums.size(); // * 100%

        _idealFrequencyDec = 1.0f / (float)_numFreqPair.size(); // * 100%
        _idealDisplacementY = (float)_maxYDisplacement * _idealFrequencyDec / _highestRelFreqDec;

        std::cout << "highest relative frequency: " << _highestRelFreq << " (" << 
            _highestRelFreqDec << ") / 1" << std::endl;
    }

    void _generateSeed() {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::system_clock::duration duration = now.time_since_epoch();
        long long msSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::cout << msSinceEpoch << std::endl;

        // theres overflow
        _seed = msSinceEpoch; 
        _seedTextInput->sText = std::to_string(_seed);

        std::cout << _seed << std::endl;
    }

    // GUI
    olc::QuickGUI::Manager _guiManager;

    olc::QuickGUI::TextBox* _seedTextInput = nullptr;
    olc::QuickGUI::Button* _generateSeedBtn = nullptr; // uses current date
    olc::QuickGUI::Button* _runAlgoBtn = nullptr;
    olc::QuickGUI::Label* _errorLabel = nullptr;
    olc::QuickGUI::Label* _suggestionLabel = nullptr;

    olc::QuickGUI::Label* _paramLabel = nullptr;
    olc::QuickGUI::TextBox* _minInput = nullptr;
    olc::QuickGUI::TextBox* _maxInput = nullptr;
    olc::QuickGUI::TextBox* _iterationsInput = nullptr;
    olc::QuickGUI::Button* _updateParamsBtn = nullptr;

    bool _validateInputs() {
        for (char& c : _seedTextInput->sText) if (!std::isdigit(c)) return false;
        std::cout << "seed is valid" << std::endl;
        for (char& c : _minInput->sText) if (!std::isdigit(c)) return false;
        std::cout << "min is valid" << std::endl;
        for (char& c : _maxInput->sText) if (!std::isdigit(c)) return false;
        std::cout << "max is valid" << std::endl;
        for (char& c : _iterationsInput->sText) if (!std::isdigit(c)) return false;
        std::cout << "iter is valid" << std::endl;

        return true;
    }

    void _createGUI() {
        _seedTextInput = new olc::QuickGUI::TextBox(_guiManager, "Enter seed:", 
            { 50.0f, 50.0f }, { 100.0f, 50.0f });
        _generateSeedBtn = new olc::QuickGUI::Button(_guiManager, "Generate seed (ms)",
            { 200.0f, 50.0f }, { 150.0f, 50.0f });
        _runAlgoBtn = new olc::QuickGUI::Button(_guiManager, "Run",
            { 400.0f, 50.0f }, { 50.0f, 50.0f });
        _errorLabel = new olc::QuickGUI::Label(_guiManager, "", 
            { 100.0f, 120.0f }, { 200.0f, 30.0f });
        _suggestionLabel = new olc::QuickGUI::Label(_guiManager,
            "For the \"fairest\" RNG algorithm, the graph lie near the green line",
            { 150.0f, 650.0f }, { 200.0f, 50.0f });

        _paramLabel = new olc::QuickGUI::Label(_guiManager, "Set result parameters [min, max)",
            {850.0f, 50.0f}, {100.0f, 50.0f});
        _minInput = new olc::QuickGUI::TextBox(_guiManager, std::to_string(_min),
            { 850.0f, 120.0f }, { 50.0f, 50.0f });
        _maxInput = new olc::QuickGUI::TextBox(_guiManager, std::to_string(_max),
            { 920.0f, 120.0f }, { 50.0f, 50.0f });
        _iterationsInput = new olc::QuickGUI::TextBox(_guiManager, std::to_string(_iterations),
            { 990.0f, 120.0f }, { 50.0f, 50.0f });
        // _updateParamsBtn = new olc::QuickGUI::Button(_guiManager, "Update", { 850.0f, 200.0f },
            // { 50.0f, 50.0f });
    }

    void _updateGUI() { 
        _guiManager.Update(this);
        _guiManager.Draw(this);
    }

    //graph
    olc::vi2d _graphPos = { 50, 150 };
    olc::vi2d _graphSize = { 700, 400 };
    int _maxYDisplacement = 0.75f * _graphSize.y;
    int _highestPointY = _graphPos.y + _graphSize.y - _maxYDisplacement;
    int _idealDisplacementY;
    
    std::vector<GraphPoint> _graphPoints;

    void _drawGraph() {
        // graph outline
        DrawRect(_graphPos, _graphSize, olc::BLACK);

        // axis labels
        DrawString({ (int)((_graphPos.x + _graphSize.x) * 0.33f), _graphPos.y + _graphSize.y + 20 },
            "Possible Value Range", olc::WHITE, 2U);
        DrawString({ _graphPos.x - 30, (int)((_graphPos.y + _graphSize.y) * 0.5f) }, 
            "R\ne\nl.\n\nF\nr\ne\nq.", olc::WHITE, 2U);

        olc::vi2d minMaxOffset = { -3, 5 };

        // min and max labels
        DrawString({ _graphPos.x + minMaxOffset.x, _graphPos.y + _graphSize.y + minMaxOffset.y }, 
            std::to_string(_min));
        DrawString(_graphPos + _graphSize + minMaxOffset, std::to_string(_max - 1));
        
        // highest rel freq label and ideal freq line
        DrawLine({ _graphPos.x - 5, _highestPointY }, { _graphPos.x + 5, _highestPointY }, 
            olc::BLACK);
        DrawString({ _graphPos.x - 45, _highestPointY - 3 }, 
            std::to_string(_highestRelFreqDec * 100).substr(0, 4) + "%"); // always 3 decimals
        DrawLine({ _graphPos.x, _graphPos.y + _graphSize.y - _idealDisplacementY },
            { _graphPos.x + _graphSize.x, _graphPos.y + _graphSize.y - _idealDisplacementY }, 
            olc::GREEN);
        DrawString({ _graphPos.x - 45, _graphPos.y + _graphSize.y - _idealDisplacementY },
            std::to_string(_idealFrequencyDec * 100).substr(0, 4) + "%");

        if (_graphPoints.empty()) return;
        for (int i = 0; i < _graphPoints.size() - 1; i++) {
            DrawLine(_graphPoints[i].pos, _graphPoints[i + 1].pos, olc::RED);
        }

        for (GraphPoint& p : _graphPoints) {
            FillCircle(p.pos, 2, olc::RED);
        }
    }

    void _updateGraphPoints() {
        _graphPoints.clear();

        int graphXSpace = _graphSize.x / (_range - 1);

        int currentXPos = _graphPos.x;
        int graphXAxis = _graphPos.y + _graphSize.y;
        for (uInt i = _min; i < _max; i++) {
            GraphPoint gp = GraphPoint();
            gp.value = i;
            gp.relFreq = _numFreqPair[i];
            gp.relFreqPercent = (float)gp.relFreq / (float)_generatedNums.size();
            gp.weightedRelFreqPercent = (float)gp.relFreq / (float)_highestRelFreq;

            gp.pos = { currentXPos, (int)(graphXAxis - (gp.weightedRelFreqPercent * _maxYDisplacement))};
            _graphPoints.push_back(gp);

            currentXPos += graphXSpace;
        }
    }
};

#endif