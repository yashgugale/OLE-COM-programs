// trial code for Shantanu's query of getting client's id which is binding the server
#define UNICODE
#include<windows.h>
#include<tlhelp32.h>// for process snapshot related apis and structures
#include"ExeServerWithRegFile.h"
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
// class declarations
class CSumSubtract:public ISum,ISubtract
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CSumSubtract(void);
	// destructor method declarations
	~CSumSubtract(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
	// ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *);
};
class CSumSubtractClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CSumSubtractClassFactory(void);
	// destructor method declarations
	~CSumSubtractClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);
};
// global variable declarations
long glNumberOfActiveComponents=0;// number of active components
long glNumberOfServerLocks=0;// number of locks on this dll
IClassFactory *gpIClassFactory=NULL;
HWND ghwnd=NULL;
DWORD dwRegister;
// WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	// function declarations
    HRESULT StartMyClassFactories(void);
    void StopMyClassFactories(void);
	// variable declarations
DWORD GetParentProcessID(void);
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	HRESULT hr;
	int DontShowWindow=0;// 0 means show the window
	TCHAR AppName[]=TEXT("ExeServer");
	TCHAR szTokens[]=TEXT("-/");
	TCHAR *pszTokens;
	TCHAR lpszCmdLine[255];
	// com library initialization
GetParentProcessID();
	hr=CoInitialize(NULL);
	if(FAILED(hr))
		return(0);
    MultiByteToWideChar(CP_ACP,0,lpCmdLine,255,lpszCmdLine,255);
	pszTokens=wcstok(lpszCmdLine,szTokens);
	while(pszTokens!=NULL)
	{
		if(wcsicmp(pszTokens,TEXT("Embedding"))==0)// i.e. COM is calling me
		{
			DontShowWindow=1;// dont show window but message loop must
			break;
		}
		else
		{
			MessageBox(NULL,TEXT("Bad Command Line Arguments.\nExitting The Application."),TEXT("Error"),MB_OK);
			exit(0);
		}
		pszTokens=wcstok(NULL,szTokens);
	}
	// window code
	wndclass.cbSize=sizeof(wndclass);
    wndclass.style=CS_HREDRAW|CS_VREDRAW;
    wndclass.cbClsExtra=0;
    wndclass.cbWndExtra=0;
    wndclass.lpfnWndProc=WndProc;
    wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.hInstance=hInstance;
    wndclass.lpszClassName=AppName;
    wndclass.lpszMenuName=NULL;
    wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
    // register window class
    RegisterClassEx(&wndclass);
    // create window
    hwnd=CreateWindow(AppName,
                      TEXT("Exe Server With Reg File For Shantanu"),
				      WS_OVERLAPPEDWINDOW,
				      CW_USEDEFAULT,
				      CW_USEDEFAULT,
				      CW_USEDEFAULT,
				      CW_USEDEFAULT,
                      NULL,
                      NULL,
				      hInstance,
				      NULL);
	// initialize global window handle
	ghwnd=hwnd;
	if(DontShowWindow!=1)
	{
	    // usual functions
	    ShowWindow(hwnd,nCmdShow);
        UpdateWindow(hwnd);
		// increament server lock
		++glNumberOfServerLocks;
	}
	if(DontShowWindow==1)// only when COM calls this program
	{
		// start class factory
        hr=StartMyClassFactories();
	    if(FAILED(hr))
		{
			DestroyWindow(hwnd);
		    exit(0);
		}
	}
    // message loop
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if(DontShowWindow==1)// only when COM calls this program
	{
		// stop class factory
        StopMyClassFactories();
	}
	// com library un-initialization
	CoUninitialize();
	return((int)msg.wParam);

}
// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	// variable declarations
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	// code
	switch(iMsg)
	{
	case WM_PAINT:
		GetClientRect(hwnd,&rc);
		hdc=BeginPaint(hwnd,&ps);
		SetBkColor(hdc,RGB(0,0,0));
		SetTextColor(hdc,RGB(0,255,0));
		DrawText(hdc,
			     TEXT("This Is A COM Exe Server Program. Not For You !!!"),
				 -1,
				 &rc,
				 DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		EndPaint(hwnd,&ps);
		break;
	case WM_DESTROY:
		if(glNumberOfActiveComponents==0 && glNumberOfServerLocks==0)
			PostQuitMessage(0);
		break;
	case WM_CLOSE:
        --glNumberOfServerLocks;
		ShowWindow(hwnd,SW_HIDE);
		// fall through,hence no break
	default:
		return(DefWindowProc(hwnd,iMsg,wParam,lParam));
	}
	return(0L);
}
// Implementation Of CSumSubtract's Constructor Method
CSumSubtract::CSumSubtract(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// Implementation Of CSumSubtract's Destructor Method
CSumSubtract::~CSumSubtract(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
}
// Implementation Of CSumSubtract's IUnknown's Methods
HRESULT CSumSubtract::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISum)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISubtract)
		*ppv=static_cast<ISubtract *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtract::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtract::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
	    if(glNumberOfActiveComponents==0 && glNumberOfServerLocks==0)
			PostMessage(ghwnd,WM_QUIT,(WPARAM)0,(LPARAM)0L);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of ISum's Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1,int num2,int *pSum)
{
	// code
	*pSum=num1-num2;// done deliberately to identify the server is built for shantanu
	return(S_OK);
}
// Implementation Of ISubtract's Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1,int num2,int *pSubtract)
{
	// code
	*pSubtract=num1+num2;// done deliberately to identify the server is built for shantanu
	return(S_OK);
}
// Implementation Of CSumSubtractClassFactory's Constructor Method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}
// Implementation Of CSumSubtractClassFactory's Destructor Method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// code
}
// Implementation Of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<IClassFactory *>(this);
	else if(riid==IID_IClassFactory)
		*ppv=static_cast<IClassFactory *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtractClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtractClassFactory::Release(void)
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
// Implementation Of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	// variable declarations
	CSumSubtract *pCSumSubtract=NULL;
	HRESULT hr;
	// code
	if(pUnkOuter!=NULL)
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CSumSubtract class
	pCSumSubtract=new CSumSubtract;
	if(pCSumSubtract==NULL)
		return(E_OUTOFMEMORY);
	// get the requested interface
	hr=pCSumSubtract->QueryInterface(riid,ppv);
	pCSumSubtract->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	// code
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	if(glNumberOfActiveComponents==0 && glNumberOfServerLocks==0)
		PostMessage(ghwnd,WM_QUIT,(WPARAM)0,(LPARAM)0L);
	return(S_OK);
}
HRESULT StartMyClassFactories(void)
{
	// variable declaraions
	HRESULT hr;
	// code
	gpIClassFactory=new CSumSubtractClassFactory;
	if(gpIClassFactory==NULL)
		return(E_OUTOFMEMORY);
	gpIClassFactory->AddRef();
	// register the class factory
	hr=CoRegisterClassObject(CLSID_SumSubtract,
		                     static_cast<IUnknown *>(gpIClassFactory),
							 CLSCTX_LOCAL_SERVER,
							 REGCLS_MULTIPLEUSE,
							 &dwRegister);
	if(FAILED(hr))
	{
		gpIClassFactory->Release();
		return(E_FAIL);
	}
	return(S_OK);
}
void StopMyClassFactories(void)
{
	// variable declaraions
	// code
	// un-register the class factory
	if(dwRegister!=0)
		CoRevokeClassObject(dwRegister);
	if(gpIClassFactory!=NULL)
		gpIClassFactory->Release();
}
DWORD GetParentProcessID(void)
{
	// variable declarations
    HANDLE hProcessSnapshot=NULL;
    BOOL bRetCode=FALSE;
    PROCESSENTRY32 ProcessEntry={0};
	DWORD dwPPID;
	TCHAR szNameOfThisProcess[_MAX_PATH],szNameOfParentProcess[_MAX_PATH];
	TCHAR szTemp[_MAX_PATH],/*szTemp2[_MAX_PATH],*/str[_MAX_PATH],*ptr=NULL;
	// code
	// first take current system snapshot
    hProcessSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(hProcessSnapshot==INVALID_HANDLE_VALUE)
		return(-1);
	ProcessEntry.dwSize=sizeof(PROCESSENTRY32);
	// walk process hierarchy
	if(Process32First(hProcessSnapshot,&ProcessEntry))
	{
		GetModuleFileName(NULL,szTemp,_MAX_PATH);
		ptr=wcsrchr(szTemp,'\\');
		wcscpy(szNameOfThisProcess,ptr+1);
		do
        {
			if(wcsstr(wcslwr(szNameOfThisProcess),wcslwr(ProcessEntry.szExeFile))!=NULL)
			{
wsprintf(str,TEXT("Current Process Name = %s\nCurrent Process ID = %ld\nParent Process ID = %ld\nParent Process Name = %s"),szNameOfThisProcess,ProcessEntry.th32ProcessID,ProcessEntry.th32ParentProcessID,ProcessEntry.szExeFile);
MessageBox(NULL,str,TEXT("Parent Info"),MB_OK|MB_TOPMOST);
//break;
/*
				GetModuleFileName((HMODULE)ProcessEntry.th32ParentProcessID,szNameOfParentProcess,_MAX_PATH);
                // print process information
				wsprintf(str,TEXT("Parent Process ID = %d\nParent Process's Module Name = %s"),ProcessEntry.th32ParentProcessID,szNameOfParentProcess);
			    MessageBox(NULL,str,TEXT("Parent Info"),MB_OK|MB_TOPMOST);
*/
				dwPPID=ProcessEntry.th32ParentProcessID;
			}
        } 
        while(Process32Next(hProcessSnapshot,&ProcessEntry));
	}
    CloseHandle(hProcessSnapshot);
	return(dwPPID);
}
/*
// correct code
#define UNICODE
#include<windows.h>
#include"ExeServerWithRegFile.h"
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
// class declarations
class CSumSubtract:public ISum,ISubtract
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CSumSubtract(void);
	// destructor method declarations
	~CSumSubtract(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
	// ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *);
};
class CSumSubtractClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CSumSubtractClassFactory(void);
	// destructor method declarations
	~CSumSubtractClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);
};
// global variable declarations
long glNumberOfActiveComponents=0;// number of active components
long glNumberOfServerLocks=0;// number of locks on this dll
IClassFactory *gpIClassFactory=NULL;
HWND ghwnd=NULL;
DWORD dwRegister;
// WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	// function declarations
    HRESULT StartMyClassFactories(void);
    void StopMyClassFactories(void);
	// variable declarations
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	HRESULT hr;
	int DontShowWindow=0;// 0 means show the window
	TCHAR AppName[]=TEXT("ExeServer");
	TCHAR szTokens[]=TEXT("-/");
	TCHAR *pszTokens;
	TCHAR lpszCmdLine[255];
	// com library initialization
	hr=CoInitialize(NULL);
	if(FAILED(hr))
		return(0);
    MultiByteToWideChar(CP_ACP,0,lpCmdLine,255,lpszCmdLine,255);
	pszTokens=wcstok(lpszCmdLine,szTokens);
	while(pszTokens!=NULL)
	{
		if(wcsicmp(pszTokens,TEXT("Embedding"))==0)// i.e. COM is calling me
		{
			DontShowWindow=1;// dont show window but message loop must
			break;
		}
		else
		{
			MessageBox(NULL,TEXT("Bad Command Line Arguments.\nExitting The Application."),TEXT("Error"),MB_OK);
			exit(0);
		}
		pszTokens=wcstok(NULL,szTokens);
	}
	// window code
	wndclass.cbSize=sizeof(wndclass);
    wndclass.style=CS_HREDRAW|CS_VREDRAW;
    wndclass.cbClsExtra=0;
    wndclass.cbWndExtra=0;
    wndclass.lpfnWndProc=WndProc;
    wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.hInstance=hInstance;
    wndclass.lpszClassName=AppName;
    wndclass.lpszMenuName=NULL;
    wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
    // register window class
    RegisterClassEx(&wndclass);
    // create window
    hwnd=CreateWindow(AppName,
                      TEXT("Exe Server With Reg File"),
				      WS_OVERLAPPEDWINDOW,
				      CW_USEDEFAULT,
				      CW_USEDEFAULT,
				      CW_USEDEFAULT,
				      CW_USEDEFAULT,
                      NULL,
                      NULL,
				      hInstance,
				      NULL);
	// initialize global window handle
	ghwnd=hwnd;
	if(DontShowWindow!=1)
	{
	    // usual functions
	    ShowWindow(hwnd,nCmdShow);
        UpdateWindow(hwnd);
		// increament server lock
		++glNumberOfServerLocks;
	}
	if(DontShowWindow==1)// only when COM calls this program
	{
		// start class factory
        hr=StartMyClassFactories();
	    if(FAILED(hr))
		{
			DestroyWindow(hwnd);
		    exit(0);
		}
	}
    // message loop
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if(DontShowWindow==1)// only when COM calls this program
	{
		// stop class factory
        StopMyClassFactories();
	}
	// com library un-initialization
	CoUninitialize();
	return((int)msg.wParam);

}
// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	// variable declarations
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	// code
	switch(iMsg)
	{
	case WM_PAINT:
		GetClientRect(hwnd,&rc);
		hdc=BeginPaint(hwnd,&ps);
		SetBkColor(hdc,RGB(0,0,0));
		SetTextColor(hdc,RGB(0,255,0));
		DrawText(hdc,
			     TEXT("This Is A COM Exe Server Program. Not For You !!!"),
				 -1,
				 &rc,
				 DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		EndPaint(hwnd,&ps);
		break;
	case WM_DESTROY:
		if(glNumberOfActiveComponents==0 && glNumberOfServerLocks==0)
			PostQuitMessage(0);
		break;
	case WM_CLOSE:
        --glNumberOfServerLocks;
		ShowWindow(hwnd,SW_HIDE);
		// fall through,hence no break
	default:
		return(DefWindowProc(hwnd,iMsg,wParam,lParam));
	}
	return(0L);
}
// Implementation Of CSumSubtract's Constructor Method
CSumSubtract::CSumSubtract(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// Implementation Of CSumSubtract's Destructor Method
CSumSubtract::~CSumSubtract(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
}
// Implementation Of CSumSubtract's IUnknown's Methods
HRESULT CSumSubtract::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISum)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISubtract)
		*ppv=static_cast<ISubtract *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtract::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtract::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
	    if(glNumberOfActiveComponents==0 && glNumberOfServerLocks==0)
			PostMessage(ghwnd,WM_QUIT,(WPARAM)0,(LPARAM)0L);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of ISum's Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1,int num2,int *pSum)
{
	// code
	*pSum=num1+num2;
	return(S_OK);
}
// Implementation Of ISubtract's Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1,int num2,int *pSubtract)
{
	// code
	*pSubtract=num1-num2;
	return(S_OK);
}
// Implementation Of CSumSubtractClassFactory's Constructor Method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}
// Implementation Of CSumSubtractClassFactory's Destructor Method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// code
}
// Implementation Of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<IClassFactory *>(this);
	else if(riid==IID_IClassFactory)
		*ppv=static_cast<IClassFactory *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtractClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtractClassFactory::Release(void)
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
// Implementation Of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	// variable declarations
	CSumSubtract *pCSumSubtract=NULL;
	HRESULT hr;
	// code
	if(pUnkOuter!=NULL)
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CSumSubtract class
	pCSumSubtract=new CSumSubtract;
	if(pCSumSubtract==NULL)
		return(E_OUTOFMEMORY);
	// get the requested interface
	hr=pCSumSubtract->QueryInterface(riid,ppv);
	pCSumSubtract->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	// code
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	if(glNumberOfActiveComponents==0 && glNumberOfServerLocks==0)
		PostMessage(ghwnd,WM_QUIT,(WPARAM)0,(LPARAM)0L);
	return(S_OK);
}
HRESULT StartMyClassFactories(void)
{
	// variable declaraions
	HRESULT hr;
	// code
	gpIClassFactory=new CSumSubtractClassFactory;
	if(gpIClassFactory==NULL)
		return(E_OUTOFMEMORY);
	gpIClassFactory->AddRef();
	// register the class factory
	hr=CoRegisterClassObject(CLSID_SumSubtract,
		                     static_cast<IUnknown *>(gpIClassFactory),
							 CLSCTX_LOCAL_SERVER,
							 REGCLS_MULTIPLEUSE,
							 &dwRegister);
	if(FAILED(hr))
	{
		gpIClassFactory->Release();
		return(E_FAIL);
	}
	return(S_OK);
}
void StopMyClassFactories(void)
{
	// variable declaraions
	// code
	// un-register the class factory
	if(dwRegister!=0)
		CoRevokeClassObject(dwRegister);
	if(gpIClassFactory!=NULL)
		gpIClassFactory->Release();
}
*/
