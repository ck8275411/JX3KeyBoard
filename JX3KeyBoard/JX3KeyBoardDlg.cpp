
// JX3KeyBoardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JX3KeyBoard.h"
#include "JX3KeyBoardDlg.h"
#include "afxdialogex.h"
#include "WinioHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT ClickThread(LPVOID pParam)
{
	ClickRunner *clicker = (ClickRunner *)pParam;
	clicker->Run();
	return 0;
}
UINT RecieveThread(LPVOID pParam)
{
	RecieverRunner *m_reciever = (RecieverRunner *)pParam;
	m_reciever->Run();
	return 0;
}

// CJX3KeyBoardDlg �Ի���



CJX3KeyBoardDlg::CJX3KeyBoardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJX3KeyBoardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJX3KeyBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);

	DDX_Control(pDX, IDC_CHECK1, m_checkbox1);
	DDX_Control(pDX, IDC_CHECK2, m_checkbox2);
	DDX_Control(pDX, IDC_CHECK3, m_checkbox3);
	DDX_Control(pDX, IDC_CHECK4, m_checkbox4);
	DDX_Control(pDX, IDC_CHECK5, m_checkbox5);
	DDX_Control(pDX, IDC_CHECK6, m_checkbox6);

	DDX_Control(pDX, IDC_BUTTON1, m_button1);

	
}

BEGIN_MESSAGE_MAP(CJX3KeyBoardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CJX3KeyBoardDlg::OnBnClickedButton1)
	ON_WM_HELPINFO(WM_HELP, OnHelpInfo)
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_WM_SIZE()
//	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


BOOL CJX3KeyBoardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	

	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

	m_nid.hWnd = this->m_hWnd;

	m_nid.uID = IDR_MAINFRAME;

	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����

	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));

	strcpy(m_nid.szTip, "����������");                // ��Ϣ��ʾ��Ϊ"����������"

	Shell_NotifyIcon(NIM_ADD, &m_nid);                // �����������ͼ��


	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_checkbox1.m_edit = &m_edit1;
	m_checkbox2.m_edit = &m_edit2;
	m_checkbox3.m_edit = &m_edit3;
	m_checkbox4.m_edit = &m_edit4;
	m_checkbox5.m_edit = &m_edit5;
	m_checkbox6.m_edit = &m_edit6;

	m_stop_click = true;
	m_pause_click = false;
	m_start_listen = false;

	m_clicker1.m_pause_click = &m_pause_click;
	m_clicker1.m_stop_click = &m_stop_click;
	m_clicker1.m_start_listen = &m_start_listen;
	m_clicker1.m_key_arr = &m_key_arr;

	m_reciever.m_stop_click = &m_stop_click;
	m_reciever.m_pause_click = &m_pause_click;
	m_reciever.m_start_listen = &m_start_listen;
	m_reciever.m_float_dlg = &m_float_dlg;

	TCHAR  tmp_char[1024];
	GetCurrentDirectory(1024, tmp_char);
	m_app_path = tmp_char;
	m_ini_path = m_app_path + "\\JX3KB.ini";

	GetIniSetKeyCode(m_edit1,m_checkbox1, 1);
	GetIniSetKeyCode(m_edit2,m_checkbox2, 2);
	GetIniSetKeyCode(m_edit3,m_checkbox3, 3);
	GetIniSetKeyCode(m_edit4,m_checkbox4, 4);
	GetIniSetKeyCode(m_edit5,m_checkbox5, 5);
	GetIniSetKeyCode(m_edit6,m_checkbox6, 6);
	if (!InitializeWinIo())
	{
		AfxMessageBox("Winio��ʼ��ʧ��!");
		PostMessage(WM_CLOSE);
	}
	m_float_dlg.Create(IDD_PRESS_DIALOG, GetDesktopWindow());
	m_float_dlg.ShowWindow(SW_SHOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJX3KeyBoardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CJX3KeyBoardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CJX3KeyBoardDlg::OnDestroy()
{
	ShutdownWinIo();
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	CDialogEx::OnDestroy();
	// TODO:  �ڴ˴������Ϣ����������
}


void CJX3KeyBoardDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (m_start_listen == false)
	{
		m_checkbox1.EnableWindow(0);
		m_checkbox2.EnableWindow(0);
		m_checkbox3.EnableWindow(0);
		m_checkbox4.EnableWindow(0);
		m_checkbox5.EnableWindow(0);
		m_checkbox6.EnableWindow(0);
		
		m_key_arr.clear();

		GetKeyCodeSetIni(m_edit1, m_checkbox1, 1);
		GetKeyCodeSetIni(m_edit2, m_checkbox2, 2);
		GetKeyCodeSetIni(m_edit3, m_checkbox3, 3);
		GetKeyCodeSetIni(m_edit4, m_checkbox4, 4);
		GetKeyCodeSetIni(m_edit5, m_checkbox5, 5);
		GetKeyCodeSetIni(m_edit6, m_checkbox6, 6);

		m_button1.SetWindowTextA("ֹͣ");
		ShowWindow(SW_HIDE); // ����С���У����������� 
		m_start_listen = true;
		AfxBeginThread(RecieveThread, (LPVOID)&m_reciever);
		AfxBeginThread(ClickThread, (LPVOID)&m_clicker1);
	}
	else
	{
		m_checkbox1.EnableWindow(1);
		m_checkbox2.EnableWindow(1);
		m_checkbox3.EnableWindow(1);
		m_checkbox4.EnableWindow(1);
		m_checkbox5.EnableWindow(1);
		m_checkbox6.EnableWindow(1);

		m_button1.SetWindowTextA("��ʼ");
		m_start_listen = false;
	}
	
}


BOOL CJX3KeyBoardDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return true;
}
afx_msg LRESULT CJX3KeyBoardDlg::OnShowTask(WPARAM wParam, LPARAM lParam)

{
	if (wParam != IDR_MAINFRAME)
	{
		return 1;
	}
	switch (lParam)
	{
		case WM_RBUTTONUP:   // �Ҽ�����ʱ�����˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // �õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING, WM_DESTROY, "�ر�");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
		case WM_LBUTTONDBLCLK:  // ˫������Ĵ���
		{
			this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������
		}
		break;
	}
	return 0;
}

void CJX3KeyBoardDlg::OnSize(UINT nType, int cx, int cy)
{
	

	// TODO: Add your message handler code here

	if (nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE); // ����С���У�����������              
	}
	CDialog::OnSize(nType, cx, cy);
	// TODO:  �ڴ˴������Ϣ����������
}
void CJX3KeyBoardDlg::GetKeyCodeSetIni(CMyEdit& edit, CMyCheckBox& checkbox, int index)
{
	CString cs;
	CString cs2;
	CString app_name;
	app_name.Format("Key_%d", index);

	edit.GetWindowTextA(cs);
	cs = cs.Trim();

	if (checkbox.GetCheck())
	{
		if (!cs.IsEmpty())
		{
			m_key_arr.push_back(cs);
			DWORD ul = (DWORD)atol(cs2);
		}
		::WritePrivateProfileString(app_name, "Enable", "True", m_ini_path);
	}
	else
	{
		::WritePrivateProfileString(app_name, "Enable", "False", m_ini_path);
	}
	::WritePrivateProfileString(app_name, "Value", cs, m_ini_path);
	::WritePrivateProfileString(app_name, "Interval", cs2, m_ini_path);
}

void CJX3KeyBoardDlg::GetIniSetKeyCode(CMyEdit& edit, CMyCheckBox& checkbox, int index)
{

	TCHAR tmp_char[1024];
	CString cs;
	CString app_name;
	app_name.Format("Key_%d", index);

	::GetPrivateProfileString(app_name, "Value", "", tmp_char, 1024, m_ini_path);
	cs = tmp_char;
	edit.SetWindowTextA(cs);
	::GetPrivateProfileString(app_name, "Enable", "", tmp_char, 1024, m_ini_path);
	cs = tmp_char;
	if (cs == "True")
	{
		checkbox.SetCheck(1);
		edit.EnableWindow(0);
	}
	else if (cs == "False" || cs == "")
	{
		checkbox.SetCheck(0);
	}
}

//void CJX3KeyBoardDlg::OnShowWindow(BOOL bShow, UINT nStatus)
//{
//	CDialogEx::OnShowWindow(bShow, nStatus);
//
//	// TODO:  �ڴ˴������Ϣ����������
//}