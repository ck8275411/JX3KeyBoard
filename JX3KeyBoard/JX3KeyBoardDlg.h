
// JX3KeyBoardDlg.h : 头文件
//

#pragma once

#include "MyEdit.h"
#include "MyCheckBox.h"
#include "afxwin.h"
#include "vector"
#include "ClickRunner.h"
#include "RecieverRunner.h"
#include "FloatDlg.h"

enum PressMode{
	SAMETIME = 1,
	DIFFTIME = 2
};
// CJX3KeyBoardDlg 对话框
class CJX3KeyBoardDlg : public CDialogEx
{
// 构造
public:
	CJX3KeyBoardDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JX3KEYBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void GetKeyCodeSetIni(CMyEdit& edit, CMyCheckBox& checkbox, int index);
	void GetIniSetKeyCode(CMyEdit& edit, CMyCheckBox& checkbox, int index);
	void InitClicker(ClickRunner* clicker, int index);
	void DestroyClicker();
private:
	CMyCheckBox m_checkbox1;
	CMyCheckBox m_checkbox2;
	CMyCheckBox m_checkbox3;
	CMyCheckBox m_checkbox4;
	CMyCheckBox m_checkbox5;
	CMyCheckBox m_checkbox6;

	CMyEdit m_edit1;
	CMyEdit m_edit2;
	CMyEdit m_edit3;
	CMyEdit m_edit4;
	CMyEdit m_edit5;
	CMyEdit m_edit6;

	//开始键
	CButton m_button1;
	//按键方案选择
	CButton m_radio_button_1;
	CButton m_radio_button_2;
	PressMode m_press_mode;
	//停止变量
	bool m_stop_click;
	//暂停变量
	bool m_pause_click;
	//开始监听键盘变量
	bool m_start_listen;
	vector<ClickRunner*> m_clicker_arr;
	RecieverRunner m_reciever;
	vector<CString> m_key_arr;

	NOTIFYICONDATA m_nid;
	CString m_app_path;
	CString m_ini_path;
	CFloatDlg m_float_dlg;
	bool m_thread_created;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
