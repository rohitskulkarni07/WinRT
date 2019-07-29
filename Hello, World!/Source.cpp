//Header
//Step 1
#include<windows.h>

//prototype
//callback
//Step 2

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Entry to GUI Main i.e WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Hello, World!");

	wndclass.cbSize = sizeof(WNDCLASSEX);	//1
	wndclass.style = CS_HREDRAW | CS_VREDRAW;							//2
	wndclass.cbClsExtra = 0;								//3
	wndclass.cbWndExtra = 0;								//4
	wndclass.lpfnWndProc = WndProc;//5
	wndclass.hInstance = hInstance;//6
	wndclass.hIcon = LoadIcon( NULL ,IDI_APPLICATION);//7
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//8
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//9
	wndclass.lpszClassName = szAppName;//10
	wndclass.lpszMenuName = NULL;//11
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//12

	RegisterClassEx(&wndclass);

	//Create a window 

	hwnd = CreateWindow(szAppName, 
		TEXT("Hello, World !"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	RECT rc;
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[] = TEXT("Hello, World!");

	//switch

	switch (iMsg) {

		case WM_PAINT:

			//Get Changing Reactangle
			GetClientRect(hwnd, &rc);

			//call specialist
			hdc = BeginPaint(hwnd, &ps);
	
			//Set Text Color
			SetTextColor(hdc, RGB(0,255,0));

			//set the background
			SetBkColor(hdc,RGB(0,0,0));

			//Draw Text
			DrawText(hdc, str, -1, &rc,DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			//Send back the Specailist
			EndPaint(hwnd, &ps);
			break;

		case WM_DESTROY:

			PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}