//Headers
#include<windows.h>
#include"Header.h"
#include<iostream>

using namespace std;

//global funtion declearations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//WinMain() entry point for GUI programming in cpp
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	//Variable Declearation
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//CODE

	//Initilization of WNDCLASSEX

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//Register Above Class
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	//
	static HBITMAP hBitmap = NULL;
	static BITMAP bmp = { };
	RECT rc;
	HDC hdc,hMemdc;
	PAINTSTRUCT ps;
	//code
	switch (iMsg) {
		case WM_CREATE:
			hBitmap = (HBITMAP)LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP));
			if (hBitmap==NULL) {
				MessageBox(hwnd, TEXT("NULL"), TEXT("Message"), MB_OK);
			} 
			else {
				MessageBox(hwnd, TEXT("NOT NULL"), TEXT("Message"), MB_OK);
			}
			break;

		case WM_PAINT:
			//client height
			GetClientRect(hwnd, &rc);
			//start the painting
			hdc = BeginPaint(hwnd, &ps);
			//DeviceContext
			hMemdc = CreateCompatibleDC(hdc);
			//Selecct object
			SelectObject(hMemdc, hBitmap);
			//get object
			GetObject(hBitmap,sizeof(bmp),&bmp);
			//Source to destination rectangle
			StretchBlt(hdc, rc.left, rc.top, rc.right, rc.bottom, hMemdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			//now no need of Object... delete the object
			DeleteObject(hMemdc);
			//End Paint
			EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}



