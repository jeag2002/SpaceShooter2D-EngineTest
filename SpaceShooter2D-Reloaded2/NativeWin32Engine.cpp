#include "NativeWin32Engine.h"

HWND NativeWin32Engine::create_window(int uiWidth, int uiHeight) {
	WNDCLASS wc;
	RECT wRect;
	HWND sWindow;
	HINSTANCE hInstance;

	wRect.left = 0L;
	wRect.right = (long)uiWidth;
	wRect.top = 0L;
	wRect.bottom = (long)uiHeight;

	hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)processWindowsStatic;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OGLES";

	RegisterClass(&wc);

	AdjustWindowRectEx(&wRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	sWindow = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, "OGLES", "SpaceShooter2DReloaded2-v1.00.000.1", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, uiWidth, uiHeight, NULL, NULL, hInstance, this);

	ShowWindow(sWindow, SW_SHOW);
	SetForegroundWindow(sWindow);
	SetFocus(sWindow);

	return sWindow;
}

//http://www.gamedev.net/topic/303854-pointer-to-wndproc-in-a-class/

LRESULT CALLBACK NativeWin32Engine::processWindowsStatic(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {

   NativeWin32Engine* pParent;

   // Get pointer to window
   if(uiMsg == WM_CREATE)
   {
      pParent = (NativeWin32Engine*)((LPCREATESTRUCT)lParam)->lpCreateParams;
      SetWindowLongPtr(hWnd,GWL_USERDATA,(LONG_PTR)pParent);
   }
   else
   {
      pParent = (NativeWin32Engine*)GetWindowLongPtr(hWnd,GWL_USERDATA);
      if(!pParent) return DefWindowProc(hWnd,uiMsg,wParam,lParam);
   }

   pParent->p_hWnd = hWnd;
   return pParent->processWindows(hWnd,uiMsg,wParam,lParam);

}


LRESULT CALLBACK NativeWin32Engine::processWindows(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam){
    switch(uiMsg) {
		case WM_CLOSE:
				PostQuitMessage(0);
				return 0;

		case WM_ACTIVATE:
		case WM_KEYDOWN:
            switch (wParam) {

                    case VK_LEFT:
                    global->setGlobalM(0,0,1,0,0,0,0,0);
                    break;

                    case VK_RIGHT:
                    global->setGlobalM(0,0,0,1,0,0,0,0);
                    break;

                    case VK_UP:
                    global->setGlobalM(1,0,0,0,0,0,0,0);
                    break;

                    case VK_DOWN:
                    global->setGlobalM(0,1,0,0,0,0,0,0);
                    break;

                    default:

                    break;
            }
		case WM_KEYUP:
		case WM_SIZE:
				return 0;
	}

	return DefWindowProc(hWnd, uiMsg, wParam, lParam);

}
