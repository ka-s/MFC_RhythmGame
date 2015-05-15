
#include "Judge.h"
#include "Constant.h"
#include "stdafx.h"

// --------------------------------
//  ƒQ[ƒW‘Œ¸ŠÖ”
// --------------------------------
void Judgement::CalcGauge(int mount, int* cg)
{
    int c = *cg;

    c += mount;

    // ƒQ[ƒW‚ğ0`100‚É§ŒÀ
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
//  Perfect”»’èŠÖ”
// --------------------------------
bool Judgement::IsPerfect(DWORD click_time, double bpm)
{
    // Great”»’è•‚É“ü‚Á‚Ä‚¢‚ê‚ÎTrue
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
//  Great”»’èŠÖ”
// --------------------------------
bool Judgement::IsGreat(DWORD click_time, double bpm)
{
    // Perfect”»’è•‚É“ü‚Á‚Ä‚¢‚ê‚ÎTrue
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
//  ”»’è·sŠÖ”
// --------------------------------
void Judgement::Judge(DWORD click_time, CString* s, int* cg, double bpm)
{
    int clearGauge = *cg;

    // Perfect”»’è
    if (IsPerfect(click_time, bpm))
    {
        CalcGauge(up_gauge, &clearGauge);

        s->Format(_T("PERFECT!!\r\n%d"), clearGauge);
    }
    // Great”»’è
    else if (IsGreat(click_time, bpm))
    {
        CalcGauge(up_gauge / 2, &clearGauge);

        s->Format(_T("GREAT!\r\n%d"), clearGauge);
    }
    // Bad”»’è
    else
    {
        CalcGauge(-up_gauge / 2, &clearGauge);

        s->Format(_T("Bad...\r\n%d"), clearGauge);
    }

    *cg = clearGauge;
}