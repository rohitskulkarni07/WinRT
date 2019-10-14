#include<Windows.h>
#include "HeaderForClientOfContainmentComponentWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;
//___________________________________________________________________________________________________

IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;

//___________________________________________________________________________________________________


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("COMCLIENT");

	HRESULT hr;

	hr = CoInitialize(NULL);
	
	if (FAILED(hr)) {

		MessageBox(NULL, TEXT("Failed To Initialize COM Library"), TEXT("ERROR IN CoInitailize"), MB_OK);
		exit(0);

	}

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hInstance = hInstance;


	if (!RegisterClassEx(&wndclass)) {
		MessageBox(NULL, TEXT("Failed To Register Class"), TEXT("ERROR IN CLASS REGISTRATION"), MB_OK);
		exit(0);
	}

	hwnd = CreateWindow(AppName,
		TEXT("Client Of COM-DLL Server"),
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

		DispatchMessage(&msg);
		TranslateMessage(&msg);

	}

	CoUninitialize();

	return((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];

	switch (iMsg) {
	case WM_CREATE:

		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISum Interface Cannot Be Obtained"), TEXT("ERROR WM_CREATE"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 55;
		iNum2 = 45;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);

		wsprintf(str, TEXT("Sum of %d And %d  = %d "), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubtract Interface Cannot Be Obtained"), TEXT("ERROR WM_CREATE"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 155;
		iNum2 = 145;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);

		wsprintf(str, TEXT("Subtraction of %d And %d  = %d "), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);
		//_____________________________________________________________________________________________

		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IMultiplication Interface Cannot Be Obtained"), TEXT("ERROR WM_CREATE"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISubtract->Release();
		pISubtract = NULL;

		iNum1 = 30;
		iNum2 = 25;

		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Multiplication of %d and %d = %d "), iNum1, iNum2, iSum);
		MessageBox(hwnd,str,TEXT("Result"),MB_OK);

		//______________________________________________________________________________________________

		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IDivision Interface Cannot Be Obtained"), TEXT("ERROR WM_CREATE"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIMultiplication->Release();
		pIMultiplication = NULL;

		iNum1 = 200;
		iNum2 = 25;

		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Division of %d and %d = %d "), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		pIDivision->Release();
		pIDivision = NULL;

		DestroyWindow(hwnd);


		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}