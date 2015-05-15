
#include "Judge.h"
#include "Constant.h"
#include "stdafx.h"

// --------------------------------
//  �Q�[�W�����֐�
// --------------------------------
void Judgement::CalcGauge(int mount, int* cg)
{
    int c = *cg;

    c += mount;

    // �Q�[�W��0�`100�ɐ���
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
//  Perfect����֐�
// --------------------------------
bool Judgement::IsPerfect(DWORD click_time, double bpm)
{
    // Great���蕝�ɓ����Ă����True
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
//  Great����֐�
// --------------------------------
bool Judgement::IsGreat(DWORD click_time, double bpm)
{
    // Perfect���蕝�ɓ����Ă����True
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
//  ���获�s�֐�
// --------------------------------
void Judgement::Judge(DWORD click_time, CString* s, int* cg, double bpm)
{
    int clearGauge = *cg;

    // Perfect����
    if (IsPerfect(click_time, bpm))
    {
        CalcGauge(up_gauge, &clearGauge);

        s->Format(_T("PERFECT!!\r\n%d"), clearGauge);
    }
    // Great����
    else if (IsGreat(click_time, bpm))
    {
        CalcGauge(up_gauge / 2, &clearGauge);

        s->Format(_T("GREAT!\r\n%d"), clearGauge);
    }
    // Bad����
    else
    {
        CalcGauge(-up_gauge / 2, &clearGauge);

        s->Format(_T("Bad...\r\n%d"), clearGauge);
    }

    *cg = clearGauge;
}