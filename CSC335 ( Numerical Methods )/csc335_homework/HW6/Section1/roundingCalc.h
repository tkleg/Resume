#ifndef ROUNDINGCALC_H
#define ROUNDINGCALC_H

#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>
using namespace std;

enum RoundingMode { NONE, CHOP, ROUND };

enum Operation { ADD, SUBTRACT, MULTIPLY, DIVIDE };

double safeBasicOps(double a, double b, RoundingMode mode, Operation op, int precision = -1);

double applyRounding(double value, RoundingMode mode, int precision = -1);

float safeBasicOps(float a, float b, RoundingMode mode, Operation op, int precision = -1);

float applyRounding(float value, RoundingMode mode, int precision = -1);

#endif