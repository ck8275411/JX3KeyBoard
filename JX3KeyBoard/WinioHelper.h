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
	///等待键盘缓冲区为空
	void KBCWait4IBE();
public:
	// 模拟键盘普通键按下
	bool KeyDownNormal(WORD vKeyCode);
	// 模拟键盘普通键弹出
	bool KeyUpNormal(WORD vKeyCode);
	// 模拟一次普通键按键
	void KeyDownUpNormal(WORD vKeyCode);
	// 模拟键盘扩展键按下
	bool WinioHelper::KeyDownExtend(WORD vKeyCoad);
	// 模拟键盘扩展键弹出
	bool WinioHelper::KeyUpExtend(WORD vKeyCoad);
	// 模拟一次扩展键按键
	void WinioHelper::KeyDownUpExtend(WORD vKeyCoad);
private:
	const int KBC_KEY_CMD = 0x64;	//键盘命令端口
	const int KBC_KEY_DATA = 0x60;	//键盘数据端口
	map<CString, WORD> key_string_code_map;
};

/************************************************************************/
/*
InitializeWinIo()失败，参考如下：
http://www.cnblogs.com/wangqian0realmagic/archive/2012/03/26/2418671.html

Winio64.sys没有正式的数字签名，只有测试的。
需要修改一些东西，具体如下：

cmd->bcdedit /set testsigning on

然后修改WinIo64.sys的测试签名

1.打开 WinIO64.sys的属性框，翻到“数字签名”选项卡，点击“详细信息”
2.在新出来的对话框中点击“查看证书”
3.在又新出来的对话框中点击“安装证书”
4.点击“下一步”，然后选择“将所有的证书放入下列存储”
5.点击浏览，选择“受信任的根证书发布机构”
6.点击“下一步”，然后点击“完成”
7.在弹出的“安全性警告”对话框中选择“是”，才能导入成功

然后重启。

再调试程序，就可以成功初始化了。
*/
/************************************************************************/