#include<windows.h>
#include<stdio.h>
#include "AutomationServerWithRegFile.h"

//Class Declearation 
//co-class

class CMyMath :public IMyMath {

private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo;

public:
	//Constructor
	CMyMath(void);
	//Destructor
	~CMyMath(void);


	//IUnkown specific method declaration
	
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IDispatch specific method declaration

	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	//ISum specific method declaration

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	//Custom method

	HRESULT InitInstance(void);

};

class CMyMathClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	//constructor
	CMyMathClassFactory(void);

	//Destructor
	~CMyMathClassFactory(void);

	//IUnknown Specific method
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory Specific method
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};


//_____________GLOBAL_____________

long glNumberOfActiveComponents = 0;
long glNumberOfServerLock = 0;

/*
	{E3DFA2A4-0A91-4515-A585-E9F57A7E3521}
	(0xe3dfa2a4, 0xa91, 0x4515, 0xa5, 0x85, 0xe9, 0xf5, 0x7a, 0x7e, 0x35, 0x21)
*/
const GUID LIBID_AutomationServer = { 0xe3dfa2a4, 0xa91, 0x4515, 0xa5, 0x85, 0xe9, 0xf5, 0x7a, 0x7e, 0x35, 0x21 };

//________________________________


//______________________DLL Main_________________________

BOOL WINAPI DllMain(HINSTANCE hdll, DWORD dwReason, LPVOID Reserved) {
	//code

	switch (dwReason) {

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
//_______________________________________________________

CMyMath::CMyMath(void) {
	m_cRef = 1;
	m_pITypeInfo = NULL;
	InterlockedIncrement(&glNumberOfActiveComponents);

}

CMyMath::~CMyMath(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);

}

HRESULT CMyMath::QueryInterface(REFIID riid, void **ppv) {
	
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IMyMath*>(this);
	}
	else if(riid== IID_IDispatch){
		*ppv = static_cast<IMyMath*>(this);
	}
	else if (riid == IID_IMyMath) {
		*ppv = static_cast<IMyMath*>(this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMath::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);

}

ULONG CMyMath::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {

		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	return(m_cRef);
}


HRESULT CMyMath::GetTypeInfoCount(UINT *pCountTypeInfo) {

	*pCountTypeInfo = 1;
	return(S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppITypeInfo) {

	*ppITypeInfo = NULL;

	if (iTypeInfo != NULL) {
	
		return(DISP_E_BADINDEX);
	}

	m_pITypeInfo->AddRef();

	*ppITypeInfo = m_pITypeInfo;

	return(S_OK);

}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId) {
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr) {

	HRESULT hr;
	
	hr = DispInvoke(this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr);
	
	return(hr);

}

HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int* pSum) {
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract) {
	*pSubtract = num1 - num2;
	return(S_OK);
}


HRESULT CMyMath::InitInstance(void) {

	//declaration of funtion
	void ComErrorDescriptionString(HWND, HRESULT);

	HRESULT hr;

	ITypeLib* pITypeLib = NULL;

	if (m_pITypeInfo == NULL) {
		hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypeLib);

		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}

		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);

		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}

		pITypeLib->Release();
	}
	return(S_OK);

}


CMyMathClassFactory::CMyMathClassFactory(void) {
	m_cRef = 1;

}

CMyMathClassFactory::~CMyMathClassFactory(void) {
	//code
}

HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void **ppv) {

	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory*>(this);

	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMathClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMathClassFactory::Release(void) {
	
	InterlockedDecrement(&m_cRef);
	
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	
	return(m_cRef);
}

HRESULT CMyMathClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) {

	MessageBox(NULL, TEXT("1"), TEXT("enrty create in dll"), MB_OK);

	CMyMath *pCMyMath = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL) {
		return (CLASS_E_NOAGGREGATION);
	}
	
	pCMyMath = new CMyMath;
	
	if (pCMyMath == NULL) {
		return(E_OUTOFMEMORY);
	}

	pCMyMath->InitInstance(); // automation related init method

	hr = pCMyMath->QueryInterface(riid,ppv);
	pCMyMath->Release();
	return(hr);

}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock) {
	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLock);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLock);
	}
	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {

	MessageBox(NULL, TEXT("1"), TEXT("enrty"), MB_OK);

	CMyMathClassFactory* pCMyMathClassFactory = NULL;

	HRESULT hr;

	if (rclsid !=CLSID_MyMath) {

		MessageBox(NULL, TEXT("2"), TEXT("return"), MB_OK);
		return(CLASS_E_CLASSNOTAVAILABLE);
	}

	pCMyMathClassFactory = new CMyMathClassFactory;

	if (pCMyMathClassFactory == NULL) {
		MessageBox(NULL, TEXT("3"), TEXT("return"), MB_OK);

		return(E_OUTOFMEMORY);
	}

	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();
	
	MessageBox(NULL, TEXT("4"), TEXT("return"), MB_OK);

	return(hr);

}


extern "C" HRESULT __stdcall DllCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLock == 0)) {
		return(S_OK);
	}
	else {
		return(S_FALSE);
	}
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr) {
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr)) {
		hr = HRESULT_CODE(hr);
	}

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0) {
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else {
		swprintf_s(str, TEXT("[Could not find error dispription string for error # % #x.]\n"), hr);
		MessageBox(hwnd, str, TEXT("COM ERROR"),MB_OK);
	}
}

