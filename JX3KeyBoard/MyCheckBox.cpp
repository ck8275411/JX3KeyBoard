// MyCheckBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JX3KeyBoard.h"
#include "MyCheckBox.h"


// CMyCheckBox

IMPLEMENT_DYNAMIC(CMyCheckBox, CCheckListBox)

CMyCheckBox::CMyCheckBox() :m_edit(nullptr), m_combobox(nullptr), m_interval_edit(nullptr)
{

}

CMyCheckBox::~CMyCheckBox()
{
}


BEGIN_MESSAGE_MAP(CMyCheckBox, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CMyCheckBox::OnBnClicked)
	ON_WM_ENABLE()
END_MESSAGE_MAP()



// CMyCheckBox ��Ϣ�������


void CMyCheckBox::OnBnClicked()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (GetCheck() == true)
	{
		if (m_edit != nullptr)
		{
			m_edit->EnableWindow(0);
		}
		if (m_interval_edit != nullptr)
		{
			m_interval_edit->EnableWindow(0);
		}
		if (m_combobox != nullptr)
		{
			m_combobox->EnableWindow(0);
		}
	}
	else
	{
		if (m_edit != nullptr)
		{
			m_edit->EnableWindow(1);
		}
		
		if (m_interval_edit != nullptr)
		{
			m_interval_edit->EnableWindow(1);
		}
		if (m_combobox != nullptr)
		{
			m_combobox->EnableWindow(1);
		}
	}
}


void CMyCheckBox::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);
	if (bEnable == 0)
	{
		m_edit->EnableWindow(0);
		m_interval_edit->EnableWindow(0);
	}
	else
	{
		if (GetCheck())
		{
			m_edit->EnableWindow(0);
			m_interval_edit->EnableWindow(0);
		}
		else
		{
			m_edit->EnableWindow(1);
			m_interval_edit->EnableWindow(1);
		}
	}
	// TODO:  �ڴ˴������Ϣ����������
}
