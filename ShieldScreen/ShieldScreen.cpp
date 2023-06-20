// ShieldScreen.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "ShieldScreen.h"
#include "pch.h"
 #include <stdio.h>

 HHOOK Hook;
 bool bStart = false;

 LRESULT CALLBACK LauncherHook(int nCode, WPARAM wParam, LPARAM lParam);
 extern HMODULE hHookDll;
 

_declspec(dllexport) void WINAPI StopShieldScreen()//dll的导出函数
{
	if (bStart)
	{
		bStart = false;
		BOOL bRet = UnhookWindowsHookEx(Hook);
		if (bRet == FALSE)
		{
			//MessageBox(NULL, (LPCWSTR)"取消hook失败", (LPCWSTR)"取消hook失败", MB_OK);
		}
	}
}

_declspec(dllexport)void WINAPI StartShieldScreen()//dll的导出函数
{
	if (!bStart)
	{
		bStart = true;
		Hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LauncherHook, hHookDll, 0);

		if (Hook == NULL)
		{
			//MessageBox(NULL, (LPCWSTR)"hook失败", (LPCWSTR)"hook失败", MB_OK);
		}
	}
}

LRESULT CALLBACK LauncherHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT * Key_Info = (KBDLLHOOKSTRUCT*)lParam;
	
	if (nCode == HC_ACTION)
	{
		if (WM_KEYDOWN == wParam || WM_SYSKEYDOWN == wParam)
		{
			BOOL b_lctrl = ::GetAsyncKeyState(VK_LCONTROL);	//如果左边Ctrl按下
			BOOL b_rctrl = ::GetAsyncKeyState(VK_RCONTROL);	//如果右边Ctrl按下
			BOOL b_lAlt = ::GetAsyncKeyState(VK_LMENU);		//如果左边Alt按下
			BOOL b_rAlt = ::GetAsyncKeyState(VK_RMENU);		//如果右边Alt按下
			BOOL b_lShift = ::GetAsyncKeyState(VK_LSHIFT);	//如果左边Shift按下
			BOOL b_rShift = ::GetAsyncKeyState(VK_RSHIFT);	//如果右边Shift按下
		
			if (Key_Info->vkCode == VK_SNAPSHOT)
			{
				return TRUE;
			}
			else if (b_lctrl && b_lAlt)
			{
				switch (wParam)
				{
					case 41: //('A')
						break;
					default:
						break;
				}
				return TRUE;
			}
			else if (b_rctrl && b_rAlt)
			{
				switch (wParam)
				{
					case 41://('A')
						break;
					default:
						break;
				}
				return TRUE;
			}
			else if (b_lShift && b_lAlt)
			{
				switch (wParam)
				{
				case 41: //('A')
					break;
				default:
					break;
				}
				return TRUE;
			}
			else if (b_rShift && b_rAlt)
			{
				switch (wParam)
				{
				case 41://('A')
					break;
				default:
					break;
				}
				return TRUE;
			}
			else if (b_lAlt)
			{
				switch (wParam)
				{
					case 41://('A')
						break;
					default:
						break;
				}
				return TRUE;
			}
			else if (b_rAlt)
			{
				switch (wParam)
				{
					case 41://('A')
						break;
					default:
						break;
				}
				return TRUE;
			}
		}
	}
	
    return CallNextHookEx(Hook, nCode, wParam, lParam);
}