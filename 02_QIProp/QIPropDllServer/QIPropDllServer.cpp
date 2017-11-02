#define UNICODE
#include<windows.h>
#include"QIPropDllServer.h"
// global variable declarations
class CSumSubtractMultiply:public ISum,ISubtract,IMultiply
{
private:
	ULONG m_cRef;
public:
	// constructor method declarations
	CSumSubtractMultiply(void);
	// destructor method declarations
	~CSumSubtractMultiply(void);
	// CSumComponent specific methods
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
	// ISubtraction specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *);
	// IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *);
};
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
// Implementation Of CSumSubtractMultiply's Constructor Method
CSumSubtractMultiply::CSumSubtractMultiply(void)
{
	// code
	m_cRef=0;// initialization
}
// Implementation Of CSumSubtractMultiply's Destructor Method
CSumSubtractMultiply::~CSumSubtractMultiply(void)
{
	// code
}
// Implementation Of IUnknown's Methods
HRESULT CSumSubtractMultiply::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISum)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISubtract)
		*ppv=static_cast<ISubtract *>(this);
	else if(riid==IID_IMultiply)
		*ppv=static_cast<IMultiply *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtractMultiply::AddRef(void)
{
	// code
	++m_cRef;
	return(m_cRef);
}
ULONG CSumSubtractMultiply::Release(void)
{
	// code
	--m_cRef;
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of ISum's Methods
HRESULT CSumSubtractMultiply::SumOfTwoIntegers(int num1,int num2,int *pSum)
{
	// code
	*pSum=num1+num2;
	return(S_OK);
}
// Implementation Of ISubtract's Methods
HRESULT CSumSubtractMultiply::SubtractionOfTwoIntegers(int num1,int num2,int *pSubtraction)
{
	// code
	*pSubtraction=num1-num2;
	return(S_OK);
}
// Implementation Of ISum's Methods
HRESULT CSumSubtractMultiply::MultiplicationOfTwoIntegers(int num1,int num2,int *pMultiplication)
{
	// code
	*pMultiplication=num1*num2;
	return(S_OK);
}
// Implementation of exported function CreateComponentInstance()
extern "C" __declspec(dllexport)HRESULT CreateComponentInstance(REFIID riid,void **ppv)
{
	// variable declarations
	CSumSubtractMultiply *pCSumSubtractMultiply=NULL;
	// code
	pCSumSubtractMultiply=new CSumSubtractMultiply;
	if(pCSumSubtractMultiply==NULL)
		return(E_OUTOFMEMORY);
	pCSumSubtractMultiply->QueryInterface(riid,ppv);
	return(S_OK);
}
