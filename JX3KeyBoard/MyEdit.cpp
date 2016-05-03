// MyEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "JX3KeyBoard.h"
#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{

}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
//	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
//	ON_WM_SYSCHAR()
	ON_WM_SYSKEYDOWN()
END_MESSAGE_MAP()



// CMyEdit 消息处理程序




//void CMyEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	MessageBox("你试试","嘿嘿",MB_OK);
//	CEdit::OnLButtonDblClk(nFlags, point);
//}

//void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	CEdit::OnChar(nChar, nRepCnt, nFlags);
//	CString cs;
//	this->SetWindowText("");
//	if (nChar >= 'a' && nChar <= 'z')
//	{
//		nChar = nChar - 32;
//	}
//	cs.Format("%c", nChar);
//	this->SetWindowText(cs);
//}


//void CMyEdit::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	CEdit::OnSysChar(nChar, nRepCnt, nFlags);
//	CString cs;
//	this->SetWindowText("");
//	switch (nChar)
//	{
//	case VK_F1:
//		cs = "F1";
//		break;
//	case VK_F2:
//		cs = "F2";
//		break;
//	case VK_F3:
//		cs = "F3";
//		break;
//	case VK_F4:
//		cs = "F4";
//		break;
//	case VK_F5:
//		cs = "F5";
//		break;
//	case VK_F6:
//		cs = "F6";
//		break;
//	case VK_F7:
//		cs = "F7";
//		break;
//	case VK_F8:
//		cs = "F8";
//		break;
//	case VK_F9:
//		cs = "F9";
//		break;
//	case VK_F10:
//		cs = "F10";
//		break;
//	case VK_F11:
//		cs = "F12";
//		break;
//	case VK_F12:
//		cs = "F12";
//		break;
//	default:
//		break;
//	}
//	this->SetWindowText(cs);
//}

