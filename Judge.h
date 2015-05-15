#pragma once

#include "stdafx.h"
#include "Constant.h"

class Judgement
{
private:
    // 判定幅[ms]
    static const int judgment_perfect = 64;
    static const int judgment_great = 128;

    // ゲージ増加値
    static const int up_gauge = 20;

public:
    // ゲージ増減関数
    static void CalcGauge(int mount, int* cg);
    // Perfect判定関数
    static bool IsPerfect(DWORD click_time, double bpm);
    // Great判定関数
    static bool IsGreat(DWORD click_time, double bpm);
    // 判定執行関数
    static void Judge(DWORD click_time, CString* s, int* cg, double bpm);
};