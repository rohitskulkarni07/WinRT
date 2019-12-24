#include<windows.h>
#include<stdio.h>		//for swprintf_s()
#include "AutomationServerWithRegFile.h"

//prototype of callback for window
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR AppName[] = TEXT("COM CLIENT-2");
	
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
		TEXT("COM CLIENT-2"),
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
	
	IDispatch* pIDispatch = NULL;
	HRESULT hr;
	DISPID dispid;
	
	/*
		You need to make your string literal type const because in C++ or in C
		it is a constant array of char, unlike in early(98 std) C where it is just an array of char.
		You cannot change a string literal, so making it const is preferred in C++ for extra safety. 
	*/

	const OLECHAR* szFunctionName1 = L"SumOfTwoIntegers";//L menas literal 
	const OLECHAR* szFunctionName2 = L"SubtractionOfTwoIntegers";
	
	VARIANT vArg[2], vRet;
	DISPPARAMS param = { vArg,0,2,NULL };
	
	int n1, n2;
	TCHAR str[255];

	switch (iMsg) {
	case WM_CREATE:
		
		hr = CoInitialize(NULL);

		if (FAILED(hr)) {
			
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("COM LIBRARY CANNOT BE INITIALIZE"), TEXT("COM ERROR"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);

		}

		//GET ISum Interface

		hr = CoCreateInstance(CLSID_MyMath,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IDispatch,
			(void **)&pIDispatch);

		
		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Component Cannot Be Created"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			DestroyWindow(hwnd);
			exit(0);
		}

		/**		COMMAON CODE FOR SumOfTwoInteger and SubtractionOFTwoInteger	**/

		n1 = 75;
		n2 = 25;

		//as DISPPARAMS rgvarg Recieves param in reverce order

		VariantInit(vArg);
		
		vArg[0].vt = VT_INT;
		vArg[0].intVal = n2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal= n1;

		param.cArgs = 2;
		param.cNamedArgs = 0;
		
		//reverse order of param
		param.rgvarg = vArg;
		
		//return value
		VariantInit(&vRet);


		/*
			*** Code for IMyMath->SumOfTwoInteger() ***
		*/

		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			(LPOLESTR*)&szFunctionName1,
			1, 
			GetUserDefaultLCID(), 
			&dispid);

		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Cannot Get ID for SumOfTwoInteger"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&param,
			&vRet,
			NULL,
			NULL);

		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Cannot Invoke Funtion"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		else {
			//Dipslay Result
			wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("Sum of Two Integers"), MB_OK);
		}


		//call SubtractionOfTwoInteger
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			(LPOLESTR*)&szFunctionName2,
			1,
			GetUserDefaultLCID(),
			&dispid);

		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Cannot Get ID for SubtractionOfTwoInteger"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&param,
			&vRet,
			NULL,
			NULL);

		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Cannot Invoke Funtion"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		else {
			//Dipslay Result
			wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("Subtraction of Two Integers"), MB_OK);
		}
	
		//clean up
		VariantClear(vArg);
		VariantClear(&vRet);

		//release
		pIDispatch->Release();
		pIDispatch = NULL;

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
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


