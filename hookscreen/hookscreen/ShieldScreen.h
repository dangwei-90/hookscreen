#pragma once
#ifndef _SHIELDSCREEN_H_
#define _SHIELDSCREEN_H_
#include <windows.h>

//HMODULE hHookDll;

 #ifdef _cplusplus
 extern "C"
 {
	 #endif
	    void WINAPI UnInstallLaunchEv();//��װ����
	    void WINAPI InstallLaunchEv();//ȥ������
	 #ifdef _cplusplus
	 };
 #endif

 #endif