
#include "Judge.h"
#include "Constant.h"
#include "stdafx.h"

// --------------------------------
//  ゲージ増減関数
// --------------------------------
void Judgement::CalcGauge(int mount, int* cg)
{
    int c = *cg;

    c += mount;

    // ゲージを0〜100に制限
    if (c > 100)
    {
        c = 100;
    }
    if (c < 0)
    {
        c = 0;
    }

    *cg = c;
}

// --------------------------------
//  Perfect判定関数
// --------------------------------
bool Judgement::IsPerfect(DWORD click_time, double bpm)
{
    // Great判定幅に入っていればTrue
    if (
        (click_time) <= (judgment_perfect) ||
        (click_time) >= (((60.0 / bpm) * 1000.0) - judgment_perfect)
        )
    {
        return true;
    }

    return false;
}

// --------------------------------
//  Great判定関数
// --------------------------------
bool Judgement::IsGreat(DWORD click_time, double bpm)
{
    // Perfect判定幅に入っていればTrue
    if (
        (click_time) <= (judgment_great) ||
        (click_time) >= (((60.0 / bpm) * 1000.0) - judgment_great)
        )
    {
        return true;
    }

    return false;
}

// --------------------------------
//  判定執行関数
// --------------------------------
void Judgement::Judge(DWORD click_time, CString* s, int* cg, double bpm)
{
    int clearGauge = *cg;

    // Perfect判定
    if (IsPerfect(click_time, bpm))
    {
        CalcGauge(up_gauge, &clearGauge);

        s->Format(_T("PERFECT!!\r\n%d"), clearGauge);
    }
    // Great判定
    else if (IsGreat(click_time, bpm))
    {
        CalcGauge(up_gauge / 2, &clearGauge);

        s->Format(_T("GREAT!\r\n%d"), clearGauge);
    }
    // Bad判定
    else
    {
        CalcGauge(-up_gauge / 2, &clearGauge);

        s->Format(_T("Bad...\r\n%d"), clearGauge);
    }

    *cg = clearGauge;
}