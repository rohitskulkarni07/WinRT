#include<windows.h>
#include "Header.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int nCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[255] = TEXT("My Math Client For Explicit Linking");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadCursor(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wndclass)) {
		MessageBox(NULL, TEXT("FAILED TO REGISTER CLASS"), TEXT("ERROR"), MB_ICONEXCLAMATION | MB_OK);
		return(0);
	}
	
	hwnd = CreateWindow(szAppName,
		TEXT("My Math Client For Explicit Linking"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, TEXT("FAILED TO GET HANDLE"), TEXT("ERROR"), MB_ICONEXCLAMATION | MB_OK);
		return(0);
	}

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,WPARAM wParam ,LPARAM lParam) {

	int iNum = 10, square = NULL;
	HINSTANCE hLib;
	typedef int(*FunPtr) (int);
	FunPtr pfnSquare;
	hLib = LoadLibrary(TEXT("MyMath.dll"));
	pfnSquare = (FunPtr)GetProcAddress(hLib,"MakeSquare");
	square = pfnSquare(iNum);
	FreeLibrary(hLib);
	TCHAR str[255];

	switch (iMsg) {

		case WM_CREATE:
			wsprintf(str, TEXT("Square of %d is %d"), iNum, square);
			MessageBox(hwnd,str,TEXT("DLL_EXPLICIT"), MB_OK);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
