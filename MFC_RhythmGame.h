
// MFC_RhythmGame.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CMFC_RhythmGameApp:
// ���̃N���X�̎����ɂ��ẮAMFC_RhythmGame.cpp ���Q�Ƃ��Ă��������B
//

class CMFC_RhythmGameApp : public CWinApp
{
public:
	CMFC_RhythmGameApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CMFC_RhythmGameApp theApp;