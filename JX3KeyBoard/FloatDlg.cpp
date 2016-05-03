// FloatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JX3KeyBoard.h"
#include "FloatDlg.h"
#include "afxdialogex.h"


// CFloatDlg �Ի���

IMPLEMENT_DYNAMIC(CFloatDlg, CDialog)
#define TIMER_MOVE 1

CFloatDlg::CFloatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFloatDlg::IDD, pParent)
{

}


void CFloatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFloatDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFloatDlg ��Ϣ�������

BOOL CFloatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	//���ô�����״
	SetRegion(GetDC(), IDB_BACKGROUND_STOP_BMP, RGB(0, 0, 1));
	CRect  rect;
	GetWindowRect(&rect);
	m_static_text.Create(_T("�ر�"), WS_CHILD | WS_VISIBLE | SS_CENTER,
		rect, this);
	m_font.CreatePointFont(140, "΢���ź�");
	m_static_text.SetFont(&m_font);
	//��ʼʱ����
	CenterWindow();
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);  
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//���ö�ʱ���������������������ƶ�
	SetTimer(TIMER_MOVE, 10, NULL);
	return TRUE;
}

void CFloatDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFloatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFloatDlg::SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor)
{
	CDC dcMem;
	if (!dcMem.CreateCompatibleDC(pDC))
	{
		MessageBox(_T("��������DCʧ�ܣ�"));
	}

	CBitmap bitmap;
	if (!bitmap.LoadBitmap(BackBitmapID))
	{
		MessageBox(_T("����λͼʧ�ܣ�"));
	}

	if (!dcMem.SelectObject(&bitmap))
	{
		MessageBox(_T("ѡ���豸������ʧ�ܣ�"));
	}
	CRect rc;
	BITMAP bitmapinfo;
	bitmap.GetBitmap(&bitmapinfo);

	//ȥ������Ļ�����ô����ָ�᲻��ȷ
	MoveWindow(0, 0, bitmapinfo.bmWidth, bitmapinfo.bmHeight, true);
	//����Ҫ��MoveWindow�������ı䴰�ڵĴ�С
	GetWindowRect(&rc);

	CRgn m_WndRgn;
	CRgn m_TempRgn;
	m_WndRgn.CreateRectRgn(0, 0, bitmapinfo.bmWidth, bitmapinfo.bmHeight);

	for (int i = 0; i < bitmapinfo.bmWidth; i++)
	{
		for (int j = 0; j < bitmapinfo.bmHeight; j++)
		{
			COLORREF cl = dcMem.GetPixel(i, j);
			if (cl == TransColor)
			{
				m_TempRgn.CreateRectRgn(i, j, i + 1, j + 1);
				m_WndRgn.CombineRgn(&m_WndRgn, &m_TempRgn, RGN_XOR);
				m_TempRgn.DeleteObject();
			}
		}
	}
	SetWindowRgn(m_WndRgn, true);

}


void CFloatDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);

	// ʵ���϶�����
	// ����WM_NCLBUTTONDOWN��Ϣ
	// ʹWindows��Ϊ����ڱ�������
	// ��SendMessage(WM_SYSCOMMAND,SC_MOVE | HTCAPTION,0);   
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

BOOL CFloatDlg::NearLeftBorder()
{
	CRect rc;
	GetWindowRect(rc);
	if (rc.left < 15)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CFloatDlg::NearUpBorder()
{
	CRect rc;
	GetWindowRect(rc);
	if (rc.top < 15)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CFloatDlg::NearRightBorder()
{
	CRect rc;
	GetWindowRect(rc);
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);
	if (rc.left > nWidth - rc.Width())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CFloatDlg::MouseInWnd()
{
	CRect rc;
	GetWindowRect(rc);
	POINT pt;
	GetCursorPos(&pt);
	if (PtInRect(&rc, pt))
	{
		return TRUE;
	}
	return FALSE;
}

void CFloatDlg::MoveUp()
{
	CRect rc;
	GetWindowRect(rc);
	//�����������ƣ���ʾ����
	if (MouseInWnd())
	{
		int height = rc.Height();
		if (rc.top >= 0)
		{
			rc.top = 0;
		}
		else
		{
			rc.top++;
		}
		rc.bottom = rc.top + height;
		MoveWindow(rc);
	}
	//����ڱ𴦣����ھ������Ƴ���Ļ
	else
	{
		int height = rc.Height();
		//���������ƶ�һ���أ����������(¶20)�Ͳ�����
		if (rc.top <= 20 - height)
		{
			rc.top = 20 - height;
		}
		else
		{
			rc.top--;
		}
		rc.bottom = rc.top + height;
		MoveWindow(rc);
	}
}
void CFloatDlg::MoveLeft()
{
	CRect rc;
	GetWindowRect(rc);
	//�����������ƣ���ʾ����
	if (MouseInWnd())
	{
		int width = rc.Width();
		if (rc.left >= 0)
		{
			rc.left = 0;
		}
		else
		{
			rc.left++;
		}
		rc.right = rc.left + width;
		MoveWindow(rc);
	}
	//����ڱ𴦣����ھ������Ƴ���Ļ
	else
	{
		int width = rc.Width();
		//���������ƶ�һ���أ����������(��20����)�Ͳ�����
		if (rc.left <= 20 - width)
		{
			rc.left = 20 - width;
		}
		else
		{
			rc.left--;
		}
		rc.right = rc.left + width;
		MoveWindow(rc);
	}
}
void CFloatDlg::MoveRight()
{
	CRect rc;
	GetWindowRect(rc);
	int sysWidth = GetSystemMetrics(SM_CXSCREEN);
	//����ڴ������򴰿����ƣ���ʾ����
	if (MouseInWnd())
	{
		int width = rc.Width();
		if (rc.left <= sysWidth - width)
		{
			rc.left = sysWidth - width;
		}
		else
		{
			rc.left--;
		}
		rc.right = rc.left + width;
		MoveWindow(rc);
	}
	//���û�ڴ����ϣ����ھ������Ƴ���Ļ
	else
	{
		int width = rc.Width();
		//���������ƶ�һ���أ�����������ˣ�����20���أ��Ͳ�����
		if (rc.left >= sysWidth - 20)
		{
			rc.left = sysWidth - 20;
		}
		else
		{
			rc.left++;
		}
		rc.right = rc.left + width;
		MoveWindow(rc);
	}

}
void CFloatDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_MOVE)
	{
		//��갴�ŵģ�����ô�����ƶ�
		if (GetKeyState(VK_LBUTTON) < 0)
		{
			return;
		}
		//������Ļ�ϱ�Ե
		if (NearUpBorder())
		{
			//������궯�����д��ڵ��ƶ������������������ƽ����ʾ������뿪������ƽ�����أ�
			MoveUp();
			return;
		}
		//������Ļ���Ե
		if (NearLeftBorder())
		{
			//������궯�����д��ڵ��ƶ������������������ƽ����ʾ������뿪������ƽ�����أ�
			MoveLeft();
			return;
		}
		//������Ļ�ұ�Ե
		if (NearRightBorder())
		{
			//������궯�����д��ڵ��ƶ������������������ƽ����ʾ������뿪������ƽ�����أ�
			MoveRight();
			return;
		}
	}
	CDialog::OnTimer(nIDEvent);
}


void CFloatDlg::OnSize(UINT nType, int cx, int cy)
{
	//CDialog::OnSize(nType, cx, cy);
	switch (nType)
	{
	case SIZE_MINIMIZED:
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		break;
	}
	// TODO:  �ڴ˴������Ϣ����������
}
