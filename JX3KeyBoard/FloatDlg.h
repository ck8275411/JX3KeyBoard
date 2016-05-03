#pragma once


// CFloatDlg 对话框
class CFloatDlg : public CDialog
{
	DECLARE_DYNAMIC(CFloatDlg)
	// 构造
public:
	CFloatDlg(CWnd* pParent = NULL);	// 标准构造函数

	//设置窗口不规则形状
	void SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor);

	//窗口是否靠近屏幕某个边缘
	BOOL NearLeftBorder();
	BOOL NearUpBorder();
	BOOL NearRightBorder();

	//当窗口靠近某个边缘时定时器中的移动处理
	void MoveUp();
	void MoveLeft();
	void MoveRight();

	//鼠标是否在窗口内
	BOOL MouseInWnd();

	// 对话框数据
	enum { IDD = 127 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_static_text;
	CFont m_font;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
