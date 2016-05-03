#pragma once
#include "winio.h"
#include "string"
#include "map"
using namespace std;
#ifdef _DEBUG
#pragma comment(lib, "lib_debug/WinIo3DLL.lib")
#else
#pragma comment(lib, "lib_release/WinIo3DLL.lib")
#endif
using namespace std;
class WinioHelper
{
public:
	WinioHelper();
	virtual ~WinioHelper();
	WORD GetKeyCode(CString key_name);
private:
	///�ȴ����̻�����Ϊ��
	void KBCWait4IBE();
public:
	// ģ�������ͨ������
	bool KeyDownNormal(WORD vKeyCode);
	// ģ�������ͨ������
	bool KeyUpNormal(WORD vKeyCode);
	// ģ��һ����ͨ������
	void KeyDownUpNormal(WORD vKeyCode);
	// ģ�������չ������
	bool WinioHelper::KeyDownExtend(WORD vKeyCoad);
	// ģ�������չ������
	bool WinioHelper::KeyUpExtend(WORD vKeyCoad);
	// ģ��һ����չ������
	void WinioHelper::KeyDownUpExtend(WORD vKeyCoad);
private:
	const int KBC_KEY_CMD = 0x64;	//��������˿�
	const int KBC_KEY_DATA = 0x60;	//�������ݶ˿�
	map<CString, WORD> key_string_code_map;
};

/************************************************************************/
/*
InitializeWinIo()ʧ�ܣ��ο����£�
http://www.cnblogs.com/wangqian0realmagic/archive/2012/03/26/2418671.html

Winio64.sysû����ʽ������ǩ����ֻ�в��Եġ�
��Ҫ�޸�һЩ�������������£�

cmd->bcdedit /set testsigning on

Ȼ���޸�WinIo64.sys�Ĳ���ǩ��

1.�� WinIO64.sys�����Կ򣬷���������ǩ����ѡ����������ϸ��Ϣ��
2.���³����ĶԻ����е�����鿴֤�顱
3.�����³����ĶԻ����е������װ֤�顱
4.�������һ������Ȼ��ѡ�񡰽����е�֤��������д洢��
5.��������ѡ�������εĸ�֤�鷢��������
6.�������һ������Ȼ��������ɡ�
7.�ڵ����ġ���ȫ�Ծ��桱�Ի�����ѡ���ǡ������ܵ���ɹ�

Ȼ��������

�ٵ��Գ��򣬾Ϳ��Գɹ���ʼ���ˡ�
*/
/************************************************************************/