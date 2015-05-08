
// MFC_RhythmGameDlg.h : ヘッダー ファイル
//

#pragma once


// CMFC_RhythmGameDlg ダイアログ
class CMFC_RhythmGameDlg : public CDialogEx
{
// コンストラクション
public:
	CMFC_RhythmGameDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_MFC_RHYTHMGAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
