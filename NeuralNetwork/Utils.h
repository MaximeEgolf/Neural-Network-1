#pragma once
#include <iostream>

class Utils
{
public:
	static void Print1D(float* inputs1D, int bounds, std::string message = "");
	static void Print2D(float** inputs2D, int boundsROW, int boundsCOL, std::string message = "");
	static float GenerateFraction(float minBounds, float maxBounds);
};