//Headers
#include<windows.h>
#include "resource.h"
//MACRO
#define U_ERROR TEXT("ERROR")

//prototype

//HWND = handle of the window
//UINT = Specified 32 bit message number
//WPARAM = extra info with msg
//LPARAM = extra msg with msg

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//GUI ENRTY POINT
//HINSTANCE hInstance = Handle to the programs executable module (the .exe file in memory)
//HINSTANCE hPrevInstance = Always NULL for Win32 programs
//LPSTR lpszCmdLine = The command line arguments as a single string. (char*)
//Calling convention >>> WINAPI defined as _stdcall
//

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	//A Window Class stores information about a type of window
	//including it's Window Procedure which controls the window
	//the small and large icons for the window, and the background color...etc 

	WNDCLASSEX wndclass;

	//
	HWND hwnd;

	//object of the struct tagMSG
	MSG msg;


	//Unicode text char array to store the  classname which is use for registering the class...
	TCHAR szAppName[] = TEXT("Pledge");

	//size of the strucutre
	wndclass.cbSize = sizeof(wndclass);

	//style of class (Class Styles)
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	//extra info about class
	wndclass.cbClsExtra = 0;

	//extra info about window
	wndclass.cbWndExtra = 0;

	//Handle to an application
	wndclass.hInstance = hInstance;

	//Pointer to the window procedure for this window class
	wndclass.lpfnWndProc = WndProc;

	//Icon 32x32 for alt+tab or explorer
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//Cursor
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(MYICON));

	//black background
	wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);

	//Class to identify class with
	wndclass.lpszClassName = szAppName;

	//wheather to use Menu resource or not
	wndclass.lpszMenuName = NULL;

	//small icon 16x16 for taskbar
	wndclass.hIconSm = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));

	//Register class... if succesfull ? 0 : errorcode
	//if it fails we pop up a message 
	//which says so and abort the program by returning from the WinMain() function.

	if (!RegisterClassEx(&wndclass)) {

		MessageBox(NULL,
		TEXT("Window Registration Failed!"),
		U_ERROR,
		MB_ICONEXCLAMATION | MB_OK);

		return 0;
	}

	hwnd = CreateWindow(szAppName,	//class name for applying specific style to that window only
		TEXT("Pledge"),				//window application title
		WS_OVERLAPPEDWINDOW,		//window style of overlapped type so that it appears at the top of the other window which already exist on desktop
		CW_USEDEFAULT,				//x co-ordinate
		CW_USEDEFAULT,				//Y co-ordinate
		CW_USEDEFAULT,				//widht
		CW_USEDEFAULT,				//height
		NULL,						//parent window hadle
		NULL,						//Menu handle
		hInstance,					//application instance handle
		NULL);						//pointer to window creation data

	//make sure we have a valid handle 
	if (hwnd == NULL) {
		MessageBox(NULL,
		TEXT("Window Creation Failed"), 
		U_ERROR,
		MB_ICONEXCLAMATION | MB_OK);

		return 0;
	}
	//show the window with normal style or you can also pass iCmdShow as second parameter
	//your program to specify whether or not they want your window to start off visible, maximized, minimized, etc...
	ShowWindow(hwnd,SW_SHOWNORMAL);

	//update it to ensure that it has properly redrawn itself on the screen.
	UpdateWindow(hwnd);

	//Message Loop

	//requesting next msg from queue using GetMessage()
	while (GetMessage(&msg,		// message information from the message queue.
		NULL,					//A handle to the window whose messages are to be retrieved
		0,						//Message filter
		0) > 0) {

		TranslateMessage(&msg); //sending extra info with orignal message for ex: WM_CHAR is send if WM_KEWDOWN is occured
		DispatchMessage(&msg);	//

	}

	return ((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	RECT rc; //RECT structure defines a rectangle by the coordinates of its upper-left and lower-right corners.
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR title[] = TEXT("~ NATIONAL PLEDGE OF INDIA ~");
	TCHAR line1[] = TEXT("India is my country. All Indians are my Brothers and Sisters. I love my country and I am proud of its rich and varied heritage.");
	TCHAR line2[] = TEXT("I shall always strive to be worthy of it.I shall give my parents, teachers and all elders respect and treat everyone with courtesy.");
	TCHAR line3[] = TEXT("To my country and my people, I pledge my devotion.In their well being and prosperity alone, lies my happiness");


	switch (iMsg) {

		case WM_PAINT:
			//Get Changing Reactangle
			GetClientRect(hwnd, &rc);

			//call specialist
			hdc = BeginPaint(hwnd, &ps);

			//set alignment of text to center
			SetTextAlign(hdc, TA_CENTER);

			//set the background	
			SetBkColor(hdc, RGB(0, 0, 0));

			//_____________________TITLE___________________________________

			//Set Text Color
			SetTextColor(hdc, RGB(255, 255, 255));

			//actual rext
			TextOut(hdc, rc.right / 2, rc.bottom / 2 - 20, title, wcsnlen_s(title, 200));

			//_____________________orange___________________________________

			//Set Text Color
			SetTextColor(hdc, RGB(255, 128, 0));

			//actual rext
			TextOut(hdc, rc.right / 2, rc.bottom/ 2, line1, wcsnlen_s(line1,200));
			
			//_____________________WHITE___________________________________
			
			//Set Text Color
			SetTextColor(hdc, RGB(255, 255, 255));

			//actual rext
			TextOut(hdc, rc.right / 2, rc.bottom/2 + 20, line2, wcsnlen_s(line2, 200));
			
			//_____________________GREEN___________________________________
			
			//Set Text Color
			SetTextColor(hdc, RGB(0, 255, 0));

			//actual rext
			TextOut(hdc, rc.right / 2, rc.bottom / 2 + 40, line3, wcsnlen_s(line3, 200));
			//________________________________________________________
			//Send back the Specailist
			EndPaint(hwnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;		
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
