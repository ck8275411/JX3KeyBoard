#pragma once
#include "Thread.h"
#include "WinioHelper.h"
#include "FloatDlg.h"
class RecieverRunner : public Runnable
{
public:
	RecieverRunner();
	~RecieverRunner();
	void Run();
public:
	bool *m_stop_click;
	bool *m_pause_click;
	bool *m_start_listen;

	CFloatDlg* m_float_dlg;
private:
	WinioHelper winio_helper;
};

