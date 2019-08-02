#include<windows.h>


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow){

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("RGBCMYWK");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wndclass)) {
		MessageBox(NULL,TEXT("Failde To Register Class"),TEXT("ERROR"),MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("RGBCMYWKw"),
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
		MessageBox(NULL, TEXT("Window Creation Failed"), TEXT("ERROR"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,WPARAM wParam,LPARAM lParam) {
	
	static int iPaintFlag = NULL; //using acrross the message
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;

	GetClientRect(hwnd, &rc);

	switch (iMsg) {

		case WM_CHAR:

			switch (LOWORD(wParam)) {

				case 'R':
				case 'r':
					iPaintFlag = 1;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'G':
				case 'g':
					iPaintFlag = 2;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'B':
				case 'b':
					iPaintFlag = 3;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'C':
				case 'c':
					iPaintFlag = 4;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'M':
				case 'm':
					iPaintFlag = 5;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'Y':
				case 'y':
					iPaintFlag = 6;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'W':
				case 'w':
					iPaintFlag = 7;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'O':
				case 'o':
					iPaintFlag = 8;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'A':
				case 'a':
					iPaintFlag = 9;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'S':
				case 's':
					iPaintFlag = 10;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'D':
				case 'd':
					iPaintFlag = 11;
					InvalidateRect(hwnd, &rc, 0);
					break;

				case 'K':
				case 'k':
				default:
					iPaintFlag = 0;
					InvalidateRect(hwnd, &rc, 0);
					break;
			}
		case WM_PAINT:

			hdc = BeginPaint(hwnd,&ps);
			HBRUSH hBrush;

			switch (iPaintFlag){
				case 1:
					hBrush = CreateSolidBrush(RGB(255, 0, 0)); //red
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 2:
					hBrush = CreateSolidBrush(RGB(0, 255, 0)); // green
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 3:
					hBrush = CreateSolidBrush(RGB(0, 0, 255)); //blue
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 4:
					hBrush = CreateSolidBrush(RGB(0, 255, 255)); //cyan
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 5:
					hBrush = CreateSolidBrush(RGB(255, 0, 255)); //magenta
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 6:
					hBrush = CreateSolidBrush(RGB(255, 255, 0)); //yellow
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 7:
					hBrush = CreateSolidBrush(RGB(255, 255, 255)); //white
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 8:
					hBrush = CreateSolidBrush(RGB(255, 128, 0)); //orange
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 9:
					hBrush = CreateSolidBrush(RGB(192, 192, 192)); //light gray
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 10:
					hBrush = CreateSolidBrush(RGB(128, 128, 128)); // mid gray
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 11:
					hBrush = CreateSolidBrush(RGB(64, 64, 64)); //dark gray
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;

				case 0:
				default:
					hBrush = CreateSolidBrush(RGB(0, 0, 0)); //black
					SelectObject(hdc, hBrush);
					FillRect(hdc, &rc, hBrush);
					break;
			}
			EndPaint(hwnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
