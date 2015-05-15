#pragma once

#include "stdafx.h"
#include "Constant.h"

class Judgement
{
private:
    // ���蕝[ms]
    static const int judgment_perfect = 64;
    static const int judgment_great = 128;

    // �Q�[�W�����l
    static const int up_gauge = 20;

public:
    // �Q�[�W�����֐�
    static void CalcGauge(int mount, int* cg);
    // Perfect����֐�
    static bool IsPerfect(DWORD click_time, double bpm);
    // Great����֐�
    static bool IsGreat(DWORD click_time, double bpm);
    // ���获�s�֐�
    static void Judge(DWORD click_time, CString* s, int* cg, double bpm);
};