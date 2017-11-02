#define UNICODE
#include<windows.h>
#include"MonikerDllServerWithRegFile.h"
// class declarations
class COddNumber:public IOddNumber
{
private:
	long m_cRef;
	int m_iFirstOddNumber;
public:
	// constructor method declarations
	COddNumber(int);
	// destructor method declarations
	~COddNumber(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// this class's custom method
	BOOL _stdcall IsOdd(int);
	// IOddNumber specific method declarations (inherited)
	HRESULT __stdcall GetNextOddNumber(int *);
};
class COddNumberFactory:public IOddNumberFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	COddNumberFactory(void);
	// destructor method declarations
	~COddNumberFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IOddNumberFactory specific method declarations (inherited)
	HRESULT __stdcall SetFirstOddNumber(int,IOddNumber **);
};
// global variable declarations
long glNumberOfActiveComponents=0;// number of active components
long glNumberOfServerLocks=0;// number of locks on this dll
// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
{
	// code
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
return(TRUE);
}
// Implementation Of COddNumber's Constructor Method
COddNumber::COddNumber(int iFirstOddNumber)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
	m_iFirstOddNumber=iFirstOddNumber;// initialize to user input
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// Implementation Of COddNumber's Destructor Method
COddNumber::~COddNumber(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
}
// Implementation Of COddNumber's IUnknown's Methods
HRESULT COddNumber::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<IOddNumber *>(this);
	else if(riid==IID_IOddNumber)
		*ppv=static_cast<IOddNumber *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG COddNumber::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG COddNumber::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// implementation of custom method of this class
BOOL COddNumber::IsOdd(int iFirstOddNumber)
{
	// code
	if(iFirstOddNumber!=0 && iFirstOddNumber%2!=0)
		return(TRUE);
	else
		return(FALSE);
}
// Implementation Of IOddNumber's Methods
HRESULT COddNumber::GetNextOddNumber(int *pNextOddNumber)
{
	// variable declarations
	BOOL bResult;
	// code
	bResult=IsOdd(m_iFirstOddNumber);
	if(bResult==TRUE)
		*pNextOddNumber=m_iFirstOddNumber+2;// this gives next odd number
	else
		return(S_FALSE);
	return(S_OK);
}
// Implementation Of COddNumberFactory's Constructor Method
COddNumberFactory::COddNumberFactory(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}
// Implementation Of COddNumberFactory's Destructor Method
COddNumberFactory::~COddNumberFactory(void)
{
	// code
}
// Implementation Of COddNumberFactory's IUnknown's Methods
HRESULT COddNumberFactory::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<IOddNumberFactory *>(this);
	else if(riid==IID_IOddNumberFactory)
		*ppv=static_cast<IOddNumberFactory *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG COddNumberFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG COddNumberFactory::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of COddNumberFactory's IOddNumberFactory's method
HRESULT COddNumberFactory::SetFirstOddNumber(int iFirstOddNumber,IOddNumber **ppIOddNumber)
{
	// variable declarations
	HRESULT hr;
	// code
	COddNumber* pCOddNumber=new COddNumber(iFirstOddNumber);
	if(pCOddNumber==NULL)
		return(E_OUTOFMEMORY);
	hr=pCOddNumber->QueryInterface(IID_IOddNumber,(void**)ppIOddNumber);
	pCOddNumber->Release();
	return(hr);
}
// Implementation Of Exported Functions From This Dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,void **ppv)
{
	// variable declaraions
	COddNumberFactory *pCOddNumberFactory=NULL;
	HRESULT hr;
	// code
	if(rclsid!=CLSID_OddNumber)
		return(CLASS_E_CLASSNOTAVAILABLE);
	// create class factory
	pCOddNumberFactory=new COddNumberFactory;
	if(pCOddNumberFactory==NULL)
		return(E_OUTOFMEMORY);
	hr=pCOddNumberFactory->QueryInterface(riid,ppv);
	pCOddNumberFactory->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT __stdcall DllCanUnloadNow(void)
{
	// code
	if((glNumberOfActiveComponents==0) && (glNumberOfServerLocks==0))
		return(S_OK);
	else
		return(S_FALSE);
}
