
// MFC_RhythmGameDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MFC_RhythmGame.h"
#include "MFC_RhythmGameDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 匿名名前空間
namespace
{
    // 開始時間を記録する変数
    DWORD time_start;
    DWORD time_now;
    // メトロノーム開始フラグ
    bool isMetronome = false;
    // BPM
    double bpm = 100.0;

    // メトロノームのスレッド
    std::thread Metronome;
}

// メトロノームを鳴らす関数
//   TODO: あとでクラス化
void PlayMetronome()
{
    while (isMetronome) {
        if (
            (timeGetTime() - time_start) >= ((DWORD)((60.0 / bpm) * 1000))
            ) {
            // タイマーをリセット
            time_start = timeGetTime();
            // 鳴らす
            Beep(1000, 100);
        }
    }
}

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_RhythmGameDlg ダイアログ



CMFC_RhythmGameDlg::CMFC_RhythmGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_RhythmGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_RhythmGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_RhythmGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMFC_RhythmGameDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMFC_RhythmGameDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMFC_RhythmGameDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFC_RhythmGameDlg メッセージ ハンドラー

BOOL CMFC_RhythmGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFC_RhythmGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFC_RhythmGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFC_RhythmGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// クリックボタン
void CMFC_RhythmGameDlg::OnBnClickedButton1()
{
    // TODO: ここにコントロール通知ハンドラー コードを追加します。
}


// メトロノームスタートボタン
void CMFC_RhythmGameDlg::OnBnClickedButton2()
{
    // 押した時の時間を記録
    time_start = timeGetTime();
    // メトロノームフラグをオン
    isMetronome = true;

    // スレッド制御
    if (Metronome.get_id() == std::thread::id()) {
        // メトロノームを鳴らすスレッドを走らせる
        Metronome = std::thread(PlayMetronome);
    }
}


// メトロノームストップボタン
void CMFC_RhythmGameDlg::OnBnClickedButton3()
{
    // メトロノームフラグをオフ
    isMetronome = false;
    // メトロノームスレッドを放棄
    Metronome.detach();
}
