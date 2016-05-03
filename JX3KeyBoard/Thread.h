#ifndef __THREAD_H__  
#define __THREAD_H__  

#include <string>  

#include   <windows.h>  
#include   <process.h>  

class Runnable
{
public:
	virtual ~Runnable() {};
	virtual void Run() = 0;
};

class CThread : public Runnable
{
private:
	explicit CThread(const CThread & rhs);

public:
	CThread();
	CThread(Runnable * pRunnable);
	CThread(const char * ThreadName, Runnable * pRunnable = NULL);
	CThread(std::string ThreadName, Runnable * pRunnable = NULL);
	~CThread(void);

	/**
	��ʼ�����߳�
	@arg bSuspend ��ʼ����ʱ�Ƿ����
	**/
	bool Start(bool bSuspend = false);

	/**
	���е��̺߳���������ʹ����������д�˺���
	**/
	virtual void Run();

	/**
	��ǰִ�д˺����̵߳ȴ��߳̽���
	@arg timeout �ȴ���ʱʱ�䣬���Ϊ�������ȴ�����ʱ��
	**/
	void Join(int timeout = -1);
	/**
	�ָ�������߳�
	**/
	void Resume();
	/**
	�����߳�
	**/
	void Suspend();
	/**
	��ֹ�̵߳�ִ��
	**/
	bool Terminate(unsigned long ExitCode);

	unsigned int GetThreadID();
	std::string GetThreadName();
	void SetThreadName(std::string ThreadName);
	void SetThreadName(const char * ThreadName);

private:
	static unsigned int WINAPI StaticThreadFunc(void * arg);

private:
	HANDLE m_handle;
	Runnable * const m_pRunnable;
	unsigned int m_ThreadID;
	std::string m_ThreadName;
	volatile bool m_bRun;
};

#endif  