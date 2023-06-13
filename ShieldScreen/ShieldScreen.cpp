// ShieldScreen.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "ShieldScreen.h"
#include "pch.h"
 #include <stdio.h>

 HHOOK Hook;

 LRESULT CALLBACK LauncherHook(int nCode, WPARAM wParam, LPARAM lParam);
 void strerror(DWORD errno);
 void savelog(const char* s);
 extern HMODULE hHookDll;
 

_declspec(dllexport) void WINAPI StopShieldScreen()//dll的导出函数
{
     BOOL bRet = UnhookWindowsHookEx(Hook);
	 if (bRet == FALSE)
	 {
		 //MessageBox(NULL, (LPCWSTR)"取消hook失败", (LPCWSTR)"取消hook失败", MB_OK);
	 }
}

_declspec(dllexport)void WINAPI StartShieldScreen()//dll的导出函数
{
	Hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LauncherHook, hHookDll, 0);
	
	if (Hook == NULL)
	{
		//strerror(GetLastError());
		//MessageBox(NULL, (LPCWSTR)"hook失败", (LPCWSTR)"hook失败", MB_OK);
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


void savelog(const char* s)//向D盘根目录下的my.log文件写log信息
{
	/*
	100     FILE * p;
	101     errno_t err = fopen_s(&p, "D:\\my.log", "a+");//在d盘根目录下生成my.log文件
	102     fputs(s, p);//fputs是一种函数，具有的功能是向指定的文件写入一个字符串（不自动写入字符串结束标记符‘\0’）。成功写入一个字符串后，文件的位置指针会自动后移，函数返回值为非负整数
	103     fclose(p);
	*/
 }

 void strerror(DWORD errno)//根据GetLastError()返回值，将错误信息转化为中文，写入my.log文件
 {
	    void* lpMsgBuf;
  FormatMessageA(
	        FORMAT_MESSAGE_ALLOCATE_BUFFER |
	     FORMAT_MESSAGE_FROM_SYSTEM |
	       FORMAT_MESSAGE_IGNORE_INSERTS,
	     NULL,
	       errno,
		        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		        (char*)&lpMsgBuf,
		       0,
		        NULL
		);

		   savelog((const char*)lpMsgBuf);
	   // Free the buffer.
		    LocalFree(lpMsgBuf);
 }