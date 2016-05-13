#include "stdafx.h"
#include "RecieverRunner.h"

RecieverRunner::RecieverRunner() :winio_helper()
{
	m_stop_click = nullptr;
}


RecieverRunner::~RecieverRunner()
{
	
}

#define RECORD_INTERVAL 30 //ms
void RecieverRunner::Run()
{
	DWORD _lastVal = 0;
	DWORD  _curTime;
	_curTime = GetTickCount();
	time_t _curNextRecordTime = _curTime + RECORD_INTERVAL;
	while (true)
	{
		if (*m_start_listen == false)
		{
			break;
		}
		DWORD dwKeyVal = 0;
		GetPortVal(0x60, &dwKeyVal, 1);
		DWORD relKey = MapVirtualKey(dwKeyVal, 1);
		if (_lastVal != relKey && GetTickCount() > _curNextRecordTime)
		{
			_lastVal = relKey;
			if (relKey == 192) //"`"
			{
				if (*m_stop_click == true)
				{
					*m_stop_click = false;
					m_float_dlg->m_static_text.SetWindowTextA("¿ªÆô");
				}
				else
				{
					*m_stop_click = true;
					m_float_dlg->m_static_text.SetWindowTextA("¹Ø±Õ");

				}
			}
			else if (relKey == 18)
			{
				*m_pause_click = true;
			}
			else if (relKey == 0)
			{
				*m_pause_click = false;
			}
			_curNextRecordTime = _curNextRecordTime + RECORD_INTERVAL;
		}
		Sleep(RECORD_INTERVAL / 2);
	}
}