# Neorandom

## A graphic visualizer for self-inserted RNG algorithms

### Aiden Li
### Note: Does require some coding and technical know-how

Compatible with Windows 10/11 (so far)

Neorandom is a PGE application that allows the user to input a congruential algorithm and view the 
stastical distrubtion of its results on a graph. 

The goal of this program is to provide insight on self-implemented RNG algorithms by allowing the
user to input their own algorithm and see the potential results, biases, or issues with the algorithm.

## Tutorial (How to Use)

1. Download all files
2. Open .sln file in Visual Studio (or left-click with Visual Studio installed). C++ desktop development plugins should be installed.
3. Navigate to neorandom.cpp
4. Edit the ```setAlgo()``` function to implement RNG algorithm
5. Run


## Example: 

```
// neorandom.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define OLC_PGE_APPLICATION
#define OLC_PGEX_QUICKGUI

#include "neorandom.h"
#include <iostream>

class App : public NeoRandom {
public:

    // linear congruential algorithm: x = (a * x_0 + c) mod m
    uInt setAlgo(uInt seed) override {

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
```

This program does utilize the OLC PixelGameEngine.

# License (OLC-3)
Copyright 2018 - 2024 OneLoneCoder.com

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions or derivations of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions or derivative works in binary form must reproduce the above copyright notice. This list of conditions and the following disclaimer must be reproduced in the documentation and/or other materials provided with the distribution.

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.