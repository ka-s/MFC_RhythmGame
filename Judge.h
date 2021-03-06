#pragma once

#include "stdafx.h"
#include "Constant.h"

class Judgement
{
private:
    // »θ[ms]
    static const int judgment_perfect = 64;
    static const int judgment_great = 128;

    // Q[WΑl
    static const int up_gauge = 20;

public:
    // Q[WΈΦ
    static void CalcGauge(int mount, int* cg);
    // Perfect»θΦ
    static bool IsPerfect(DWORD click_time, double bpm);
    // Great»θΦ
    static bool IsGreat(DWORD click_time, double bpm);
    // »θ·sΦ
    static void Judge(DWORD click_time, CString* s, int* cg, double bpm);
};