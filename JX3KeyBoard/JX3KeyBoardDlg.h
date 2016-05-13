
// JX3KeyBoardDlg.h : ͷ�ļ�
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
// CJX3KeyBoardDlg �Ի���
class CJX3KeyBoardDlg : public CDialogEx
{
// ����
public:
	CJX3KeyBoardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JX3KEYBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
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

	//��ʼ��
	CButton m_button1;
	//��������ѡ��
	CButton m_radio_button_1;
	CButton m_radio_button_2;
	PressMode m_press_mode;
	//ֹͣ����
	bool m_stop_click;
	//��ͣ����
	bool m_pause_click;
	//��ʼ�������̱���
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
