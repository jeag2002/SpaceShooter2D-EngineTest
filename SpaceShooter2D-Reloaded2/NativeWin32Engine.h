/*
NATIVEWIN32ENGINE.H VENTANA NATIVA DE WINDOWS.
*/

#ifndef NATIVEWIN32ENGINE_H
#define NATIVEWIN32ENGINE_H

#define WIN32_LEAN_AND_MEAN 1

#include "Stdafx.h"

class NativeWin32Engine : public Manager{

public:

NativeWin32Engine(LogEngine *_gLogEngine, GlobalEngine *_global): Manager(_gLogEngine, _global){}
HWND create_window(int uiWidth, int uiHeight);

private:

HWND p_hWnd;
static LRESULT CALLBACK processWindowsStatic(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK processWindows(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);


};

#endif
