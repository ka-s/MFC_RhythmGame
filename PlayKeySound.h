#pragma once

#include "stdafx.h"

// --------------------------------
//  キー音を鳴らすクラス
// --------------------------------
class PlayKeySound
{
private:

public:
    // ドレミファソラシド
    static void CDE(int notes);
    // 第九
    static void Daiku(int notes);
};