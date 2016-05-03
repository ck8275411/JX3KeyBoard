#pragma once


// CFloatDlg �Ի���
class CFloatDlg : public CDialog
{
	DECLARE_DYNAMIC(CFloatDlg)
	// ����
public:
	CFloatDlg(CWnd* pParent = NULL);	// ��׼���캯��

	//���ô��ڲ�������״
	void SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor);

	//�����Ƿ񿿽���Ļĳ����Ե
	BOOL NearLeftBorder();
	BOOL NearUpBorder();
	BOOL NearRightBorder();

	//�����ڿ���ĳ����Եʱ��ʱ���е��ƶ�����
	void MoveUp();
	void MoveLeft();
	void MoveRight();

	//����Ƿ��ڴ�����
	BOOL MouseInWnd();

	// �Ի�������
	enum { IDD = 127 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
