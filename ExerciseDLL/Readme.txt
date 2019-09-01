Hello,

Contents:

	MyHeader.h
	Debug/ExerciseDLL.lib
	Debug/ExerciseDLL.dll
_____________________________________________________________________________________________


				*** MyHeader.h ***


_____________________________________________________________________________________________

	Incude this header file into you project by following way

	- Copy it to your project directory
	- open clients project in Visual Studio 2017 
	- Right-Click on Solution Explorer >>>Click on Add
	- Click on Add Existing >>> Navigate to Header file >>>Select  it...

	- put Following line in Clients code 

  ** ** ** ** *PLEASE READ HEADER FILE TO KNOW HOW TO USE THE FOLLOWING FUNTION* ** ** ** **
	
	#include "Filename.h"
	
	"in this case"
	
	#include "MyHeader.h"

________________This Header file contains Total 7 functions as follows________________________

					
	a)	int AdditionOfTwoInt(int, int);

	b)	int SubtractionOfTwoInt(int, int);

	c)	int MultiplicationOfTwoInt(int, int);

	d)	int DivisionOfTwoInt(int,int);
		
	e)	int ModOfTwoInt(int, int);
		
	f)	void SwapTwoIntUsingTemp(int, int);
		
	g)	void SwapTwoIntWithoutTemp(int, int);

______________________________________________________________________________________________

					***
_____________________________________________________________________________________________

_____________________________________________________________________________________________


				*** ExerciseDLL.lib ***

__________________________________This is The Lib File________________________________________


	Before Using DLL Include this 'lib' file to your project directory...
	there are two ways to include the lib file to your project

	____________________________-1st way_______________________________________________

	simply copy it to your project directory and put following line in you client's code

	#pragma comment(lib,"FileName.lib")

	>>>"in this case"

	#pragma comment(lib,"ExerciseDLL.lib")

	___________________________-2nd Way________________________________________________

	- Open Clients code in Visual Studio 2017
	- Go to Solution Explorer
	- Right click on Solution Explorer
	- Go to Properties > Go to Linker> go to Command Line > 
	- You Will See White Area There...>>> type your lib file name i.e ExerciseDLL.lib
	- Click on Apply >>> and then click Ok...tadaa!!! All done

______________________________________________________________________________________________

						***
______________________________________________________________________________________________


______________________________________________________________________________________________

					*** ExerciseDLL.dll ***
______________________________________________________________________________________________	



	- This is the DLL which you should include to your project directory
	- Enjoy!!!