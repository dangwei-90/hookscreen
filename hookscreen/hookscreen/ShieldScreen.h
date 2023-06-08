#pragma once
#ifndef _SHIELDSCREEN_H_
#define _SHIELDSCREEN_H_
#include <windows.h>

//HMODULE hHookDll;

 #ifdef _cplusplus
 extern "C"
 {
	 #endif
	    void WINAPI UnInstallLaunchEv();//安装钩子
	    void WINAPI InstallLaunchEv();//去掉钩子
	 #ifdef _cplusplus
	 };
 #endif

 #endif