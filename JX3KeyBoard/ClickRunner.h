#pragma once
#include "Thread.h"
#include "WinioHelper.h"
#include <vector>
class ClickRunner : public Runnable
{
public:
	ClickRunner();
	~ClickRunner();
	void Run();
public:
	bool *m_stop_click;
	bool *m_pause_click;
	bool *m_start_listen;
	vector<CString>* m_key_arr;
	int m_press_index;
private:
	WinioHelper winio_helper;
};

