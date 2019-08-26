#include<windows.h>
#include"Header.h"

#pragma comment(lib,"MyMathDllDef.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int nCmdShow ) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[255] = TEXT("MY_WINDOW_DLL_DEF_IMP");
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	if (!RegisterClassEx(&wndclass)) {
		MessageBox(NULL,TEXT("Failed to register class"),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return(0);
	}

	hwnd = CreateWindow(
		szAppName,
		TEXT("MY_WINDOW_DLL_DEF_IMP"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, TEXT("Failed to get handle"), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return(0);
	}
	
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam) {
	int square = NULL;
	int num = 100;
	TCHAR str[255];

	switch (iMsg) {

	case WM_CREATE:
		square = MakeSquare(num);
		wsprintf(str,TEXT("Square of %d is %d"),num,square);
		MessageBox(hwnd,str,TEXT("ANSWER"),MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}