#pragma once

#ifndef neorandom_h
#define neorandom_h

#include "olcPixelGameEngine.h"
#include "olcPGEX_QuickGUI.h"

class NeoRandom {
public:
	NeoRandom();
	~NeoRandom();

	void update(olc::PixelGameEngine* engine);
	void setAlgo()
};

#endif