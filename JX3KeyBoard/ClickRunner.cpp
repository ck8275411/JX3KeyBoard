#include "stdafx.h"
#include "ClickRunner.h"

void InitConsoleWindow()
{
	AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE * hf = _fdopen(hCrt, "w");
	*stdout = *hf;
}

ClickRunner::ClickRunner() :winio_helper()
{
	m_stop_click = nullptr;
	//InitConsoleWindow();
}


ClickRunner::~ClickRunner()
{
}

void ClickRunner::Run()
{
	//Í¬Ê±°´¼ü
	while (true)
	{
		if (*m_stop_click == true)
		{
			Sleep(200);
			continue;
		}
		if (*m_start_listen == false)
		{
			break;
		}
		if (*m_pause_click == false)
		{
			if (m_press_index == -1)
			{
				for (int i = 0; i < m_key_arr->size(); i++)
				{
					CString cs = (*m_key_arr)[i];
					DWORD key_code = winio_helper.GetKeyCode(cs);
					if (key_code < 0)
					{
						continue;
					}
					winio_helper.KeyDownNormal(key_code);
				}
				for (int i = 0; i < m_key_arr->size(); i++)
				{
					CString cs = (*m_key_arr)[i];
					DWORD key_code = winio_helper.GetKeyCode(cs);
					if (key_code < 0)
					{
						continue;
					}
					winio_helper.KeyUpNormal(key_code);
				}
			}
			else if (m_press_index > -1)
			{
				CString cs = (*m_key_arr)[m_press_index];
				DWORD key_code = winio_helper.GetKeyCode(cs);
				if (key_code < 0)
				{
					continue;
				}
				winio_helper.KeyDownUpNormal(key_code);
			}
			
			Sleep(200);
		}
		else
		{
			Sleep(200);
		}
	}
}