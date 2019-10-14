#include<windows.h>

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

#include "ContainmentInnerComponentWithRegFile.h"
#include "ContainmentOuterComponentWithRegFile.h"

#include<iostream>
#include<fstream>

using namespace std;
//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________
ofstream file1;

class CSumSubtract :public ISum, ISubtract ,IMultiplication,IDivision {
private:
	
	long m_cRef;
	
	//____________________________________
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;
	//____________________________________

public:

	CSumSubtract(void);
	~CSumSubtract(void);

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	//____________________________________
	
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
	
	//____________________________________

	HRESULT __stdcall InitializeInnerComponent(void);

	//____________________________________

};


//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________



class CSumSubtractClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};


//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

long glNumberOfActiveComponent = 0;
long glNumberOfServerLocks = 0;


//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {

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

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________


CSumSubtract::CSumSubtract(void) {

	//___________________________
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	//___________________________
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponent);

}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

CSumSubtract::~CSumSubtract(void) {


	InterlockedDecrement(&glNumberOfActiveComponent);
	//___________________________
	if (m_pIMultiplication) {
		
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}

	if (m_pIDivision){

		m_pIDivision->Release();
		m_pIDivision = NULL;

	}
	//___________________________

}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________


HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv) {
	
	if (riid == IID_IUnknown) {
		*ppv = static_cast<ISum *> (this);
	}
	else if (riid == IID_ISum) {
		*ppv = static_cast<ISum *> (this);
	}
	else if (riid == IID_ISubtract) {
		*ppv = static_cast<ISubtract *>(this);
	}
	//___________________________________________________________
	else if (riid == IID_IMultiplication) {
		*ppv = static_cast<IMultiplication *>(this);
	}
	else if (riid == IID_IDivision) {
		*ppv = static_cast<IDivision *>(this);
	}
	//___________________________________________________________

	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	
	return(S_OK);

}


//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

ULONG CSumSubtract::AddRef(void) {

	InterlockedIncrement(&m_cRef);

	return (m_cRef);
}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________


ULONG CSumSubtract::Release(void) {

	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);

		return(0);
	}

	return(m_cRef);
}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________


HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum) {

	*pSum = num1 + num2;


	return (S_OK);
}
//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract) {


	*pSubtract = num1 - num2;


	return (S_OK);
}
//_________________________________________________________________________________________________________________

HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication) {
	
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pMultiplication);


	return(S_OK);

}

HRESULT CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int*pDivision) {

	m_pIDivision ->DivisionOfTwoIntegers(num1,num2,pDivision);


	return(S_OK);

}

//_________________________________________________________________________________________________________________

HRESULT CSumSubtract::InitializeInnerComponent(void) {

	HRESULT hr;

	hr = CoCreateInstance(CLSID_IMultiplicationDivision,NULL,CLSCTX_INPROC_SERVER, IID_IMultiplication,(void **)&m_pIMultiplication);

	if (FAILED(hr)) {
		MessageBox(NULL,TEXT("IMultiplication Interface Cannot Be Obtain"),TEXT("Program Error"),MB_OK);
		return(E_FAIL);
	}
	
	hr = m_pIMultiplication->QueryInterface(IID_IDivision,(void **)&m_pIDivision);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IDivision Interface Cannot Be Obtain"), TEXT("Program Error"), MB_OK);
		return(E_FAIL);
	}

	return(S_OK);
	
}


//_________________________________________________________________________________________________________________

CSumSubtractClassFactory::CSumSubtractClassFactory(void) {

	m_cRef = 1;


}
//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

CSumSubtractClassFactory::~CSumSubtractClassFactory(void) {
	//blank


}
//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv) {
	

	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory *>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory *>(this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();


	return(S_OK);

}
//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

ULONG CSumSubtractClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);

	return (m_cRef);

}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

ULONG CSumSubtractClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);

}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) {

	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL) {
		return(CLASS_E_NOAGGREGATION);
	}
	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL) {
		return(E_OUTOFMEMORY);
	}
	
	hr = pCSumSubtract->InitializeInnerComponent();

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Failed to Initailize Inner Component"),TEXT("PROGRAM ERROR"),MB_OK);
		return(E_FAIL);
		pCSumSubtract->Release();
		return(hr);
	}
	
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return(hr);
}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________


HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock) {

	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLocks);
	}

	return(S_OK);
}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {

	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract) {

		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pCSumSubtractClassFactory == NULL) {

		return(E_OUTOFMEMORY);
	}
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return(hr);

}


//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {


	if ((glNumberOfActiveComponent == 0) && (glNumberOfServerLocks == 0)) {

		return (S_OK);
	}
	else {

		return(S_FALSE);
	}

}
