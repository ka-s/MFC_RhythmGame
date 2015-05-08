
// MFC_RhythmGame.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFC_RhythmGameApp:
// このクラスの実装については、MFC_RhythmGame.cpp を参照してください。
//

class CMFC_RhythmGameApp : public CWinApp
{
public:
	CMFC_RhythmGameApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFC_RhythmGameApp theApp;