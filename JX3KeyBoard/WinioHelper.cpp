#include "stdafx.h"
#include "WinioHelper.h"


WinioHelper::WinioHelper() :key_string_code_map()
{
	
	key_string_code_map[":"] = 186;
	key_string_code_map["+"] = 187;
	key_string_code_map[","] = 188;
	key_string_code_map["-"] = 189;
	key_string_code_map["."] = 190;
	key_string_code_map["/"] = 191;
	key_string_code_map["`"] = 192;

	key_string_code_map["["] = 219;
	key_string_code_map["\\"] = 220;
	key_string_code_map["]"] = 221;
	key_string_code_map["'"] = 222;
	/*
	key_string_code_map["F1"] = VK_F1;
	key_string_code_map["F2"] = VK_F2;
	key_string_code_map["F3"] = VK_F3;
	key_string_code_map["F4"] = VK_F4;
	key_string_code_map["F5"] = VK_F5;
	key_string_code_map["F6"] = VK_F6;
	key_string_code_map["F7"] = VK_F7;
	key_string_code_map["F8"] = VK_F8;
	key_string_code_map["F9"] = VK_F9;
	key_string_code_map["F10"] = VK_F10;
	key_string_code_map["F11"] = VK_F11;
	key_string_code_map["F12"] = VK_F12;
	*/
	key_string_code_map["1"] = '1';
	key_string_code_map["2"] = '2';
	key_string_code_map["3"] = '3';
	key_string_code_map["4"] = '4';
	key_string_code_map["5"] = '5';
	key_string_code_map["6"] = '6';
	key_string_code_map["7"] = '7';
	key_string_code_map["8"] = '8';
	key_string_code_map["9"] = '9';
	key_string_code_map["0"] = '0';
	
	key_string_code_map["a"] = 'A';
	key_string_code_map["b"] = 'B';
	key_string_code_map["c"] = 'C';
	key_string_code_map["d"] = 'D';
	key_string_code_map["e"] = 'E';
	key_string_code_map["f"] = 'F';
	key_string_code_map["g"] = 'G';
	key_string_code_map["h"] = 'H';
	key_string_code_map["i"] = 'I';
	key_string_code_map["j"] = 'J';
	key_string_code_map["k"] = 'K';
	key_string_code_map["l"] = 'L';
	key_string_code_map["m"] = 'M';
	key_string_code_map["n"] = 'N';
	key_string_code_map["o"] = 'O';
	key_string_code_map["p"] = 'P';
	key_string_code_map["q"] = 'Q';
	key_string_code_map["r"] = 'R';
	key_string_code_map["s"] = 'S';
	key_string_code_map["t"] = 'T';
	key_string_code_map["u"] = 'U';
	key_string_code_map["v"] = 'V';
	key_string_code_map["w"] = 'W';
	key_string_code_map["x"] = 'X';
	key_string_code_map["y"] = 'Y';
	key_string_code_map["z"] = 'Z';

	key_string_code_map["A"] = 'A';
	key_string_code_map["B"] = 'B';
	key_string_code_map["C"] = 'C';
	key_string_code_map["D"] = 'D';
	key_string_code_map["E"] = 'E';
	key_string_code_map["F"] = 'F';
	key_string_code_map["G"] = 'G';
	key_string_code_map["H"] = 'H';
	key_string_code_map["I"] = 'I';
	key_string_code_map["J"] = 'J';
	key_string_code_map["K"] = 'K';
	key_string_code_map["L"] = 'L';
	key_string_code_map["M"] = 'M';
	key_string_code_map["N"] = 'N';
	key_string_code_map["O"] = 'O';
	key_string_code_map["P"] = 'P';
	key_string_code_map["Q"] = 'Q';
	key_string_code_map["R"] = 'R';
	key_string_code_map["S"] = 'S';
	key_string_code_map["T"] = 'T';
	key_string_code_map["U"] = 'U';
	key_string_code_map["V"] = 'V';
	key_string_code_map["W"] = 'W';
	key_string_code_map["X"] = 'X';
	key_string_code_map["Y"] = 'Y';
	key_string_code_map["Z"] = 'Z';

	key_string_code_map["Alt"] = VK_LMENU;
	key_string_code_map["Ctrl"] = VK_LCONTROL;
	key_string_code_map["Shift"] = VK_LSHIFT;
}


WinioHelper::~WinioHelper()
{
}
//等待键盘缓冲区为空
void WinioHelper::KBCWait4IBE()
{
	DWORD dwVal = 0;
	do
	{
		GetPortVal(KBC_KEY_CMD, &dwVal, 1);
	} while ((dwVal & 0x2)>0);
}


// 模拟键盘普通键按下
bool WinioHelper::KeyDownNormal(WORD vKeyCode)
{
	UINT btScancode = MapVirtualKey(vKeyCode, 0);
	KBCWait4IBE();
	SetPortVal(KBC_KEY_CMD, 0xD2, 1);
	KBCWait4IBE();
	return SetPortVal(KBC_KEY_DATA, btScancode, 1);
}

// 模拟键盘普通键弹出
bool WinioHelper::KeyUpNormal(WORD vKeyCode)
{
	UINT btScancode = MapVirtualKey(vKeyCode, 0);
	KBCWait4IBE();
	SetPortVal(KBC_KEY_CMD, 0xD2, 1);
	KBCWait4IBE();
	return SetPortVal(KBC_KEY_DATA, (btScancode | 0x80), 1);
}

// 模拟一次普通键按键
void WinioHelper::KeyDownUpNormal(WORD vKeyCode)
{
	KeyDownNormal(vKeyCode);
	KeyUpNormal(vKeyCode);
}

// 模拟键盘扩展键按下
bool WinioHelper::KeyDownExtend(WORD vKeyCoad)
{
	UINT btScancode = MapVirtualKey(vKeyCoad, 0);
	KBCWait4IBE();
	SetPortVal(KBC_KEY_CMD, 0xD2, 1);
	KBCWait4IBE();
	SetPortVal(KBC_KEY_DATA, 0xE0, 1);//写入扩展键标志信息
	KBCWait4IBE();
	SetPortVal(KBC_KEY_CMD, 0xD2, 1);
	KBCWait4IBE();
	return SetPortVal(KBC_KEY_DATA, btScancode, 1);
}

// 模拟键盘扩展键弹出
bool WinioHelper::KeyUpExtend(WORD vKeyCoad)
{
	UINT btScancode = MapVirtualKey(vKeyCoad, 0);
	KBCWait4IBE();
	SetPortVal(KBC_KEY_CMD, 0xD2, 1);
	KBCWait4IBE();
	SetPortVal(KBC_KEY_DATA, 0xE0, 1);//写入扩展键标志信息
	KBCWait4IBE();
	SetPortVal(KBC_KEY_CMD, 0xD2, 1);
	KBCWait4IBE();
	return SetPortVal(KBC_KEY_DATA, (btScancode | 0x80), 1);
}

// 模拟一次扩展键按键
void WinioHelper::KeyDownUpExtend(WORD vKeyCoad)
{
	KeyDownExtend(vKeyCoad);

	//Sleep(100);

	KeyUpExtend(vKeyCoad);
}

//根据字符串获取键盘码
WORD WinioHelper::GetKeyCode(CString key_name)
{
	map<CString, WORD>::iterator it = key_string_code_map.begin();


	if ((it = key_string_code_map.find(key_name)) != key_string_code_map.end())
	{
		return (it->second);
	}
	return -1;
}


