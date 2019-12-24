#include<windows.h>
#include<stdio.h>		//for swprintf_s()
#include "AutomationServerWithRegFile.h"

//prototype of callback for window
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//global variable declaration
IMyMath* pIMyMath = NULL;

int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR AppName[] = TEXT("COM CLIENT-1");
	

	//COM INITIALIZATION
	HRESULT hr;
	hr = CoInitialize(NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("COM Library Cannot Be Initailize\nProgram Will Exit Now..."), TEXT("PROGRAM ERROR"),MB_OK);
		exit(0);
	}


	//WNDCLASS Initialization

	wndclass.cbSize = sizeof(wndclass);								//1
	wndclass.cbClsExtra = 0;										//2
	wndclass.cbWndExtra = 0;										//3
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//4
	wndclass.hInstance = hInstance;									//5
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//6
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);					//7
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);				//8
	wndclass.lpfnWndProc = WndProc;									//9
	wndclass.lpszClassName = AppName;								//10
	wndclass.lpszMenuName = NULL;									//11
	wndclass.style = CS_VREDRAW | CS_HREDRAW;						//12

	if (!RegisterClassEx(&wndclass)) {
		MessageBox(NULL, TEXT("Failed to Register Class\nProgram Will Exit Now..."), TEXT("PROGRAM ERROR"), MB_OK);
		exit(0);
	}

	hwnd = CreateWindow(AppName,
		TEXT("COM CLIENT-1"),
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
		MessageBox(NULL, TEXT("Window Creation Failed\nProgram Will Exit Now..."), TEXT("PROGRAM ERROR"), MB_OK);
		exit(0);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	CoUninitialize();

	return((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	void ComErrorDescriptionString(HWND,HRESULT);
	void SafeInterfaceRelease(void);

	HRESULT hr;

	int iNum1, iNum2, iSum, iSubtract;
	TCHAR str[255];

	switch (iMsg) {
	case WM_CREATE:
		
		hr = CoCreateInstance(CLSID_MyMath,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IMyMath,
			(void **)&pIMyMath);

		
		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}

		iNum1 = 155;
		iNum2 = 145;

		//call SumOfTwoIntegers
		pIMyMath->SumOfTwoIntegers(iNum1, iNum2, &iSum);

		//Dipslay Result
		wsprintf(str,TEXT("Sum of %d and %d is %d"),iNum1,iNum2,iSum);
		MessageBox(hwnd,str,TEXT("Sum of Two Integers"),MB_OK);

		//call SubtractionOfTwoInteger
		pIMyMath->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);

		//Dipslay Result
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iSubtract);
		MessageBox(hwnd, str, TEXT("Subtraction of Two Integers"), MB_OK);

		//release
		pIMyMath->Release();
		pIMyMath = NULL;

		DestroyWindow(hwnd);
		MessageBox(NULL, TEXT("EXIT"), TEXT("COCREATE INSTANCE"), MB_OK);

		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;

	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

void ComErrorDescriptionString(HWND hwnd,HRESULT hr) {

	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr)) {

		hr = HRESULT_CODE(hr);
	}

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,NULL,hr,MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),(LPTSTR)&szErrorMessage,0,NULL)!=0) {
		swprintf_s(str, TEXT("%s"), szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else {
		swprintf_s(str,TEXT("[Could Not Find Error Description For # %#x.]\n"),hr);
	}

	MessageBox(hwnd, str, TEXT("Program ERROR"), MB_OK);

}
void SafeInterfaceRelease() {

	if (pIMyMath) {
		pIMyMath->Release();
		pIMyMath = NULL;
	}

}
