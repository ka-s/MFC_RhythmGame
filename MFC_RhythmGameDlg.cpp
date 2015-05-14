
// MFC_RhythmGameDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MFC_RhythmGame.h"
#include "MFC_RhythmGameDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include <thread>
#include "Constant.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_RCV (WM_USER + 1)

// 匿名名前空間
namespace
{
    // 開始時間を記録する変数
    DWORD time_start;
    // メトロノームが鳴るべき時間
    DWORD time_Metro;
    // メトロノーム開始フラグ
    bool isMetronome = false;
    // 現在のテンポ数
    double tempoCount = 1.0;
    // クリアゲージ
    int clear_gauge = 0;
    // 現在叩いたノーツ数
    int now_notes_count = -1;

    // ダイアログ用ハンドル
    HWND hDlg;

    // メトロノームのスレッド
    std::thread Metronome;
}

// --------------------------------
//  メトロノームを鳴らすメソッド
//    TODO: あとでクラス化
// --------------------------------
void PlayMetronome()
{
    while (isMetronome)
    {
        // 時が来たら鳴らす
        //   TODO: 条件文改善
        if (
            (timeGetTime() - time_start) >= ((DWORD)(((60.0 / bpm) * 1000.0) * tempoCount))
            )
        {
            // 鳴らした時間を保存
            time_Metro = (DWORD)(((60.0 / bpm) * 1000.0) * tempoCount);
            // メッセージ送信
            PostMessage(hDlg, WM_RCV, (WPARAM)time_Metro, NULL);

            // テンポカウントを+1
            tempoCount += 1.0;
            // 鳴らす
            Beep(1000, 50);
        }
    }
}

// --------------------------------
//  ゲージ増減関数
//    TODO: あとでクラス化
// --------------------------------
void CalcGauge(int mount)
{
    clear_gauge += mount;

    // ゲージを0〜100に制限
    if (clear_gauge > 100)
    {
        clear_gauge = 100;
    }
    if (clear_gauge < 0)
    {
        clear_gauge = 0;
    }
}

// --------------------------------
//  Perfect判定関数
//    TODO: あとでクラス化
// --------------------------------
bool IsPerfect(DWORD click_time)
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
//    TODO: あとでクラス化
// --------------------------------
bool IsGreat(DWORD click_time)
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
//    TODO: あとでクラス化
// --------------------------------
void Judge(DWORD click_time, CString* s)
{
    // Perfect判定
    if (IsPerfect(click_time))
    {
        CalcGauge(up_gauge);

        s->Format(_T("PERFECT!!\r\n%d"), clear_gauge);
    }
    // Great判定
    else if (IsGreat(click_time))
    {
        CalcGauge(up_gauge / 2);

        s->Format(_T("GREAT!\r\n%d"), clear_gauge);
    }
    // Bad判定
    else
    {
        CalcGauge(-up_gauge / 2);

        s->Format(_T("Bad...\r\n%d"), clear_gauge);
    }
}

// --------------------------------
//  メッセージ受信時に描画する関数
// --------------------------------
LRESULT CMFC_RhythmGameDlg::OnMessageRCV(WPARAM wParam, LPARAM lParam)
{
    CString s;
    s.Format(_T("%d"), time_Metro);
    EditControl02.SetWindowTextW(s);

    return true;
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
    DDX_Control(pDX, IDC_EDIT1, EditControl01);
    DDX_Control(pDX, IDC_EDIT2, EditControl02);
}

BEGIN_MESSAGE_MAP(CMFC_RhythmGameDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMFC_RhythmGameDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMFC_RhythmGameDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMFC_RhythmGameDlg::OnBnClickedButton3)
    ON_MESSAGE(WM_RCV, &OnMessageRCV)
END_MESSAGE_MAP()


// CMFC_RhythmGameDlg メッセージ ハンドラー

BOOL CMFC_RhythmGameDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    hDlg = this->m_hWnd;

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

// --------------------------------
//  クリックボタン
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton1()
{
    // 差分の時間
    static DWORD time_click_delta;
    // 出力する文字列の作成
    CString str;

    // 差分の時間計算
    //   TODO: 計算をわかりやすく
    time_click_delta = timeGetTime() - time_start - time_Metro;

    // ノーツ数をプラス
    now_notes_count++;

    // 規定ノーツ数以内で判定を取る
    if (now_notes_count > 0 &&
        now_notes_count <= notes)
    {
        // 判定
        Judge(time_click_delta, &str);
    }

    // 文字列を描画
    EditControl01.SetWindowTextW(str);
}

// --------------------------------
//  メトロノームスタートボタン
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton2()
{
    // 押した時の時間を記録
    time_start = timeGetTime();
    // メトロノームフラグをオン
    isMetronome = true;
    // テンポカウントを初期化
    tempoCount = 1.0;
    // ノーツ数を初期化
    now_notes_count = -1;

    // スレッド制御
    if (Metronome.get_id() == std::thread::id())
    {
        // メトロノームを鳴らすスレッドを走らせる
        Metronome = std::thread(PlayMetronome);
    }
}

// --------------------------------
//  メトロノームストップボタン
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton3()
{
    // メトロノームフラグをオフ
    isMetronome = false;
    // メトロノームスレッドを放棄
    Metronome.detach();
}
