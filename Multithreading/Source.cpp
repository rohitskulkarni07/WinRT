#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Declearing prototype of funtion which are going to be our two thread.

DWORD WINAPI ThreadProcOne(LPVOID); //thread-1
DWORD WINAPI ThreadProcTwo(LPVOID); //thread-2

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[255] = TEXT("Multi-Threading");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	if (!RegisterClassEx(&wndclass)) {
		MessageBox(NULL,TEXT("Failed to register class"),TEXT("ERROR"),MB_OK | MB_ICONEXCLAMATION);
		return(0);
	}

	hwnd = CreateWindow(
		szAppName,
		TEXT("Multi-Threadig"),
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

	if (hwnd == NULL) {
		MessageBox(NULL, TEXT("Failed to get the window handle"), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return(0);
	}

	while(GetMessage(&msg,hwnd,NULL,NULL)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	switch (iMsg)
	{
	case WM_CREATE:
		
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("HELLO WORLD:MULTITHREADED"), TEXT("MESSAGE BY MULTI_THREADING"), MB_OK);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {
	HDC hdc;
	long int i;
	TCHAR str[255];
	
	hdc = GetDC((HWND)param);

	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc, RGB(0 ,255, 0));

	for (i = 0; i < 429496729; i++) {
		wsprintf(str, TEXT("Thread One->Increasing Order: %ld"),i);
		TextOut(hdc, 5, 5, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);

	return(0);
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {
	HDC hdc2;
	long int i;
	TCHAR str[255];

	hdc2 = GetDC((HWND)param);

	SetBkColor(hdc2, RGB(0, 0, 0));
	SetTextColor(hdc2, RGB(0, 255, 0));

	for (i = 429496729; i>0 ; i--) {
		wsprintf(str, TEXT("Thread One->Increasing Order: %ld"),i);
		TextOut(hdc2, 5, 20, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc2);

	return(0);
}