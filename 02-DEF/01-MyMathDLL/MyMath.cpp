#include<windows.h>

BOOL WINAPI DllMain(HINSTANCE hINstanc, DWORD dwReason, LPVOID lpvReserved) {
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

extern "C" int MakeSquare(int num) {
	return(num*num);
}

