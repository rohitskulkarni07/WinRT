#include<windows.h>
#include "MyHeader.h"

BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved) {
	
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return(TRUE);

}

//Following Function Does the addition of two integers 
//Funtion Require 2 arguments i.e 2 numbers to be add
//Funtion returns Addition of two given numbera which is also a int

int AdditionOfTwoInt(int num1, int num2) {
	return(num1 + num2);
}

//Following Function Does the Subtraction of two integers 
//Funtion Require 2 arguments i.e 2 numbers to be subtract
//Funtion returns Subtraction of two given numbers which is also a integer.

int SubtractionOfTwoInt(int num1, int num2) {
	return(num1 - num2);
}

//Following Function Does the Multiplication of two integers 
//Funtion Require 2 arguments i.e 2 numbers to be Multiply.
//Funtion returns Multiplication of two given numbera which is also a integer.

int MultiplicationOfTwoInt(int num1, int num2) {
	return(num1 * num2);
}

//Following Function Does the Division of two Numbers
//Funtion Require 2 arguments i.e 2 numbers to be divide
//Funtion returns Divsion of two given numbers which is a integer

int DivisionOfTwoInt(int num1, int num2) {
	return(num1 / num2);
}

//Following Function Does the Modulus of two Numbers
//Funtion Require 2 arguments i.e 2 numbers to be mod
//Funtion returns modulus of two given numbers which are integers

int ModOfTwoInt(int num1, int num2) {
	return(num1 % num2);
}

//Following function Swaps the two integer given to as a parameter to it.
//Funtion requires 2 paramenter i.e. 2 number which we want swap
//Funtion returns nothing but it display the message box to indicate that swapping is done.

void SwapTwoIntUsingTemp(int num1, int num2) {
	int temp;
	TCHAR str[255];

	wsprintf(str, TEXT("num1 = %d and num2 = %d"), num1, num2);
	MessageBox(NULL, str, TEXT("Before Swapping"), MB_OK);


	temp = num1;
	num1 = num2;
	num2 = temp;


	wsprintf(str, TEXT("num1 = %d and num2 = %d"), num1, num2);
	MessageBox(NULL,str,TEXT("After swapping"),MB_OK);

}

//Following function Swaps the two integer given to as a parameter to it without using extra variable.
//Funtion requires 2 paramenter i.e. 2 number which we want swap
//Funtion returns nothing but it display the message box to indicate that swapping is done.

void SwapTwoIntWithoutTemp(int num1, int num2) {
	TCHAR str[255];

	wsprintf(str, TEXT("num1 = %d and num2 = %d"), num1, num2);
	MessageBox(NULL, str, TEXT("Before Swapping"), MB_OK);

	num1 = num1 + num2;
	num2 = num1 - num2;
	num1 = num1 - num2;


	wsprintf(str, TEXT("num1 = %d and num2 = %d"), num1, num2);
	MessageBox(NULL, str, TEXT("After swapping"), MB_OK);
}

