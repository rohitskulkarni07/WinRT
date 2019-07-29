//headers
//This Header File Contain Various Api's Prototype Required For This Program...not Only For This Program But also For Every program
//that needs to show its own window and gui related containt like menu caption etc...

//Step 1:
#include<windows.h> 

//callback
//Following funtion is callback function where,
//WndProc	= Window Procedure,
//CALLBACK	= Making our funtion callable by OS itself(Its a MACRO of _far_pascal)(Calling Convetion)
//LRESULT	= Return type of function 
//HWND		= handle of a window (MACRO of _far_pascal)
//UINT		= 32 bit message number
//WPARAM	= WORD paramemter internally unisigned integer
//LPARAM	= LONG parameter

//Step 2:
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//GUI MAIN

//WINAPI			= _far_pasacal (calling Convention)
//HINSTACE			= HANDLE = UINT = unsigned integer 
//LPSTR	lpszCmdLine	= long pointer to string (char* _far) for Command line Argument
//int iCmdShow		= how window should be display	

//Step 3:
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow) {
	
	//decleration
	//WNDCLASS structure oldly WNDCLASS...Newly WNDCLASSEX due to addition on 2 new members to the structure

	//Step 4:
	WNDCLASSEX wndclass; 
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] =TEXT("MyApp");

	//code...
	//variable Initialization

	wndclass.cbSize			= sizeof(WNDCLASSEX);//unsinged int				//1
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;						//2
	wndclass.cbClsExtra		= 0;											//3
	wndclass.cbWndExtra		= 0;											//4
	wndclass.lpfnWndProc	= WndProc;										//5		
	wndclass.hInstance		= hInstance;									//6
	wndclass.hIcon			= LoadIcon ( NULL,IDI_APPLICATION );			//7
	wndclass.hCursor		= LoadCursor ( NULL,IDC_ARROW);					//8
	wndclass.hbrBackground	= ( HBRUSH ) GetStockObject ( BLACK_BRUSH );	//9
	wndclass.lpszClassName	= szAppName;									//10
	wndclass.lpszMenuName	= NULL;											//11
	wndclass.hIconSm		= LoadIcon ( NULL, IDI_APPLICATION );			//12

	//registration of wndclass ( WINDOW CLASS )

	//Step 5:
	RegisterClassEx(&wndclass);

	//Creation of Window in memory

	hwnd = CreateWindow (szAppName, TEXT("My Window With Meassage Box"), WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	//Step 6:
	//Displaying  of window...

	ShowWindow(hwnd,iCmdShow); //Step 7:
	UpdateWindow(hwnd);		   //Step 8:

	//MEssage Loop // Step 9:
	while(GetMessage(&msg ,NULL , 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return((int)msg.wParam);

}
//************WinMain Ends here*******************//

//Window Procedure (Window Function) : Step 10

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (iMsg) {

		//Step 11:
		case WM_CREATE:
			MessageBox(hwnd, TEXT("WM_CREATE has arrived"), TEXT("Message"), MB_OK);
			break;
		case WM_KEYDOWN:
			MessageBox(hwnd,TEXT("WM_KEADOWN has Arrieved"), TEXT("Message"), MB_OK);
			break;
		case WM_LBUTTONDOWN:
			MessageBox(hwnd,TEXT("WM_LBUTTONDOWN has arrived"), TEXT("Message"), MB_OK);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

	}

	//Step 12:
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}