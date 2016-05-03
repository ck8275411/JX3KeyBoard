// FloatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JX3KeyBoard.h"
#include "FloatDlg.h"
#include "afxdialogex.h"


// CFloatDlg 对话框

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


// CFloatDlg 消息处理程序

BOOL CFloatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	//设置窗口形状
	SetRegion(GetDC(), IDB_BACKGROUND_STOP_BMP, RGB(0, 0, 1));
	CRect  rect;
	GetWindowRect(&rect);
	m_static_text.Create(_T("关闭"), WS_CHILD | WS_VISIBLE | SS_CENTER,
		rect, this);
	m_font.CreatePointFont(140, "微软雅黑");
	m_static_text.SetFont(&m_font);
	//初始时居中
	CenterWindow();
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);  
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//设置定时器，处理悬浮窗的显隐移动
	SetTimer(TIMER_MOVE, 10, NULL);
	return TRUE;
}

void CFloatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFloatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFloatDlg::SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor)
{
	CDC dcMem;
	if (!dcMem.CreateCompatibleDC(pDC))
	{
		MessageBox(_T("创建兼容DC失败！"));
	}

	CBitmap bitmap;
	if (!bitmap.LoadBitmap(BackBitmapID))
	{
		MessageBox(_T("加载位图失败！"));
	}

	if (!dcMem.SelectObject(&bitmap))
	{
		MessageBox(_T("选进设备描述表失败！"));
	}
	CRect rc;
	BITMAP bitmapinfo;
	bitmap.GetBitmap(&bitmapinfo);

	//去掉这个的话，那么程序分割会不正确
	MoveWindow(0, 0, bitmapinfo.bmWidth, bitmapinfo.bmHeight, true);
	//所以要用MoveWindow函数来改变窗口的大小
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

	// 实现拖动窗口
	// 发送WM_NCLBUTTONDOWN消息
	// 使Windows认为鼠标在标题条上
	// 或SendMessage(WM_SYSCOMMAND,SC_MOVE | HTCAPTION,0);   
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
	//鼠标进入则下移，显示出来
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
	//鼠标在别处，窗口就往上移出屏幕
	else
	{
		int height = rc.Height();
		//窗口向上移动一像素，如果快隐藏(露20)就不移了
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
	//鼠标进入则下移，显示出来
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
	//鼠标在别处，窗口就往上移出屏幕
	else
	{
		int width = rc.Width();
		//窗口向左移动一像素，如果快隐藏(留20像素)就不移了
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
	//鼠标在窗口内则窗口左移，显示出来
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
	//鼠标没在窗口上，窗口就往右移出屏幕
	else
	{
		int width = rc.Width();
		//窗口向右移动一像素，如果快隐藏了（还留20像素）就不移了
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
		//鼠标按着的，就怎么都不移动
		if (GetKeyState(VK_LBUTTON) < 0)
		{
			return;
		}
		//靠近屏幕上边缘
		if (NearUpBorder())
		{
			//根据鼠标动作进行窗口的移动（鼠标进入区域就向下平移显示，鼠标离开就向上平移隐藏）
			MoveUp();
			return;
		}
		//靠近屏幕左边缘
		if (NearLeftBorder())
		{
			//根据鼠标动作进行窗口的移动（鼠标进入区域就向右平移显示，鼠标离开就向左平移隐藏）
			MoveLeft();
			return;
		}
		//靠近屏幕右边缘
		if (NearRightBorder())
		{
			//根据鼠标动作进行窗口的移动（鼠标进入区域就向左平移显示，鼠标离开就向右平移隐藏）
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
	// TODO:  在此处添加消息处理程序代码
}
