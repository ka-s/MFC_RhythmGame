// --------------------------------
//  キー音を鳴らす関数
// --------------------------------

#include "stdafx.h"
#include "PlayKeySound.h"

// ドレミファソラシド
void PlayKeySound::CDE(int notes)
{
    switch (notes)
    {
    case 1:
        Beep(262, 100);
        break;
    case 2:
        Beep(294, 100);
        break;
    case 3:
        Beep(330, 100);
        break;
    case 4:
        Beep(349, 100);
        break;
    case 5:
        Beep(392, 100);
        break;
    case 6:
        Beep(440, 100);
        break;
    case 7:
        Beep(494, 100);
        break;
    case 8:
        Beep(523, 100);
        break;
    default:
        break;
    }
}

// 第九
void PlayKeySound::Daiku(int notes)
{
    switch (notes)
    {
    case 1:
        Beep(660, 100);
        break;
    case 2:
        Beep(660, 100);
        break;
    case 3:
        Beep(698, 100);
        break;
    case 4:
        Beep(784, 100);

        break;
    case 5:
        Beep(784, 100);
        break;
    case 6:
        Beep(698, 100);
        break;
    case 7:
        Beep(660, 100);
        break;
    case 8:
        Beep(588, 100);

        break;
    case 9:
        Beep(524, 100);
        break;
    case 10:
        Beep(524, 100);
        break;
    case 11:
        Beep(588, 100);
        break;
    case 12:
        Beep(660, 100);

        break;
    case 13:
        Beep(660, 100);
        break;
    case 14:
        Beep(588, 100);
        break;
    case 15:
        Beep(588, 100);
        break;
    default:
        break;
    }
}