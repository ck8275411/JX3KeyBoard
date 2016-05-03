#pragma once
#include "MyEdit.h"

// CMyCheckBox

class CMyCheckBox : public CButton
{
	DECLARE_DYNAMIC(CMyCheckBox)

public:
	CMyCheckBox();
	virtual ~CMyCheckBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchange();
	afx_msg void OnBnClicked();
public:
	CMyEdit* m_edit;
	CMyEdit* m_interval_edit;
	CComboBox* m_combobox;
	afx_msg void OnEnable(BOOL bEnable);
};


