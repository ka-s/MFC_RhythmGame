
// MFC_RhythmGameDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MFC_RhythmGame.h"
#include "MFC_RhythmGameDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include <thread>
#include "Constant.h"
#include "PlayKeySound.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_RCV (WM_USER + 1)

// �������O���
namespace
{
    // �J�n���Ԃ��L�^����ϐ�
    DWORD time_start;
    // ���g���m�[������ׂ�����
    DWORD time_Metro;
    // ���g���m�[���J�n�t���O
    bool isMetronome = false;
    // ���݂̃e���|��
    double tempoCount = 1.0;
    // �N���A�Q�[�W
    int clear_gauge = 0;
    // ���ݒ@�����m�[�c��
    int now_notes_count = -1;
    // ��ID
    int music_id = 1;

    // �_�C�A���O�p�n���h��
    HWND hDlg;

    // ���g���m�[���̃X���b�h
    std::thread Metronome;
    // �L�[����炷�X���b�h
    std::thread KeySound;
}

// --------------------------------
//  ���g���m�[����炷���\�b�h
// --------------------------------
void PlayMetronome()
{
    while (isMetronome)
    {
        // ����������炷
        //   TODO: ���������P
        if (
            (timeGetTime() - time_start) >= ((DWORD)(((60.0 / bpm) * 1000.0) * tempoCount))
            )
        {
            // �炵�����Ԃ�ۑ�
            time_Metro = (DWORD)(((60.0 / bpm) * 1000.0) * tempoCount);
            // ���b�Z�[�W���M
            PostMessage(hDlg, WM_RCV, (WPARAM)time_Metro, NULL);

            // �e���|�J�E���g��+1
            tempoCount += 1.0;
            // ���t���ȊO�炷
            if (now_notes_count < 0)
            {
                Beep(1000, 50);
            }
        }
    }
}

// --------------------------------
//  �Q�[�W�����֐�
//    TODO: ���ƂŃN���X��
// --------------------------------
void CalcGauge(int mount)
{
    clear_gauge += mount;

    // �Q�[�W��0�`100�ɐ���
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
//  Perfect����֐�
//    TODO: ���ƂŃN���X��
// --------------------------------
bool IsPerfect(DWORD click_time)
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
//    TODO: ���ƂŃN���X��
// --------------------------------
bool IsGreat(DWORD click_time)
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
//    TODO: ���ƂŃN���X��
// --------------------------------
void Judge(DWORD click_time, CString* s)
{
    // Perfect����
    if (IsPerfect(click_time))
    {
        CalcGauge(up_gauge);

        s->Format(_T("PERFECT!!\r\n%d"), clear_gauge);
    }
    // Great����
    else if (IsGreat(click_time))
    {
        CalcGauge(up_gauge / 2);

        s->Format(_T("GREAT!\r\n%d"), clear_gauge);
    }
    // Bad����
    else
    {
        CalcGauge(-up_gauge / 2);

        s->Format(_T("Bad...\r\n%d"), clear_gauge);
    }
}

// --------------------------------
//  ���b�Z�[�W��M���ɕ`�悷��֐�
// --------------------------------
LRESULT CMFC_RhythmGameDlg::OnMessageRCV(WPARAM wParam, LPARAM lParam)
{
    CString s;
    s.Format(_T("%d"), time_Metro);
    EditControl02.SetWindowTextW(s);

    return true;
}

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // �_�C�A���O �f�[�^
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

    // ����
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


// CMFC_RhythmGameDlg �_�C�A���O



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
    DDX_Control(pDX, IDC_EDIT3, EditControl03);
}

BEGIN_MESSAGE_MAP(CMFC_RhythmGameDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMFC_RhythmGameDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMFC_RhythmGameDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMFC_RhythmGameDlg::OnBnClickedButton3)
    ON_MESSAGE(WM_RCV, &OnMessageRCV)
    ON_BN_CLICKED(IDC_BUTTON4, &CMFC_RhythmGameDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CMFC_RhythmGameDlg::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CMFC_RhythmGameDlg::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CMFC_RhythmGameDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CMFC_RhythmGameDlg ���b�Z�[�W �n���h���[

BOOL CMFC_RhythmGameDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    hDlg = this->m_hWnd;

    // "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

    // IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

    // ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
    //  Framework �́A���̐ݒ�������I�ɍs���܂��B
    SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
    SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

    // TODO: �������������ɒǉ����܂��B

    return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CMFC_RhythmGameDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // �N���C�A���g�̎l�p�`�̈���̒���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // �A�C�R���̕`��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CMFC_RhythmGameDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// --------------------------------
//  �N���b�N�{�^��
//    TODO: ���G�ɂȂ����̂Ő���
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton1()
{
    // �����̎���
    static DWORD time_click_delta;
    // ���������Ԃ��i�[
    static DWORD now;
    // �N���b�N���X�^�[�g��������
    static DWORD time_click_start;
    // �o�͂��镶����̍쐬
    CString str;

    // �N���b�N�������Ԃ��擾
    now = timeGetTime();

    // �����̎��Ԍv�Z
    //   TODO: �v�Z���킩��₷��
    time_click_delta = now - time_start - time_Metro;

    // �m�[�c�����v���X
    now_notes_count++;

    // �L�[����炷
    switch (music_id)
    {
    case 1:
        KeySound = std::thread(PlayKeySound::CDE, now_notes_count);
        KeySound.detach();
        break;
    case 2:
        KeySound = std::thread(PlayKeySound::Daiku, now_notes_count);
        KeySound.detach();
        break;
    }

    // �X�^�[�g�̎��������珉����
    if (now_notes_count == 0)
    {
        // ���������̎��Ԃ��L�^
        time_click_start = now;
    }

    // �K��m�[�c���ȓ��Ŕ�������
    if (now_notes_count > 0 &&
        now_notes_count <= notes)
    {
        // ����
        Judge(time_click_delta, &str);
    }

    // �������`��
    EditControl01.SetWindowTextW(str);
}

// --------------------------------
//  ���g���m�[���X�^�[�g�{�^��
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton2()
{
    // TODO: ���������֐���
    // ���������̎��Ԃ��L�^
    time_start = timeGetTime();
    // ���g���m�[���t���O���I��
    isMetronome = true;
    // �e���|�J�E���g��������
    tempoCount = 1.0;
    // �m�[�c����������
    now_notes_count = -1;
    // �Q�[�W��������
    clear_gauge = 0;

    // �X���b�h����
    if (Metronome.get_id() == std::thread::id())
    {
        // ���g���m�[����炷�X���b�h�𑖂点��
        Metronome = std::thread(PlayMetronome);
    }
}

// --------------------------------
//  ���g���m�[���X�g�b�v�{�^��
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton3()
{
    // ���g���m�[���t���O���I�t
    isMetronome = false;
    // ���g���m�[���X���b�h�����
    if (Metronome.get_id() != std::thread::id())
    {
        Metronome.detach();
    }
}

// --------------------------------
//  �h���~�t�@�I���{�^��
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton4()
{
    music_id = 1;
    notes = 8;
}

// --------------------------------
//  ���I���{�^��
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton5()
{
    music_id = 2;
    notes = 15;
}

// --------------------------------
//  BPM�v���X�{�^��
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton6()
{
    CString s;

    bpm += 1;

    s.Format(_T("BPM = %f"), bpm);
    EditControl03.SetWindowTextW(s);
}

// --------------------------------
//  BPM�}�C�i�X�{�^��
// --------------------------------
void CMFC_RhythmGameDlg::OnBnClickedButton7()
{
    CString s;

    bpm -= 1;

    s.Format(_T("BPM = %f"), bpm);
    EditControl03.SetWindowTextW(s);
}
