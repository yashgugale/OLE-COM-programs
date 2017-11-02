#define UNICODE
#include<windows.h>
#include"QIPropDllServer.h"
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
// WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[]=TEXT("ComClient");
	// code
	wndclass.cbSize=sizeof(wndclass);
	wndclass.style=CS_HREDRAW|CS_VREDRAW;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.lpfnWndProc=WndProc;
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance=hInstance;
	wndclass.lpszClassName=AppName;
	wndclass.lpszMenuName=NULL;
	wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
    // register window class
	RegisterClassEx(&wndclass);
	// create window
	hwnd=CreateWindow(AppName,
		              TEXT("Client Of COM Dll Server"),
					  WS_OVERLAPPEDWINDOW,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
                      NULL,
                      NULL,
					  hInstance,
					  NULL);
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	// message loop
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}
// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	// function declarations
	BOOL CheckIdentity(ISum *,ISubtract *);
	BOOL CheckPredictability(ISum *);
	BOOL CheckSymmetry(ISum *);
	BOOL CheckReflexivity(ISum *);
	BOOL CheckTransitivity(ISum *);
	// variable declarations
	static HMODULE hServerLib=NULL;
	typedef HRESULT (*PFN_FUNCTION) (REFIID,void **);
	PFN_FUNCTION pfnCreateComponentInstance=NULL;
	HRESULT hr;
	ISum *pISum=NULL;
	ISubtract *pISubtract=NULL;
	TCHAR str[255];
	// code
	switch(iMsg)
	{
	case WM_CREATE:
		// load the component's dll
		hServerLib=LoadLibrary(TEXT("QIPropDllServer.dll"));
		if(hServerLib==NULL)
		{
			MessageBox(hwnd,TEXT("Required Library Can Not Be Loaded"),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}
		// get pointer to dll's exported "component's instance creating function"
		pfnCreateComponentInstance=(PFN_FUNCTION)GetProcAddress(hServerLib,"CreateComponentInstance");
		if(pfnCreateComponentInstance==NULL)
		{
			MessageBox(hwnd,TEXT("Required Function Can Not Be Obtained"),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}
		// call "component's instance creating function" to get ISum's pointer
		hr=pfnCreateComponentInstance(IID_ISum,(void **)&pISum);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("ISum Interface Can Not Be Obtained."),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}
		// call ISum's QI() to get ISubtract's pointer
		hr=pISum->QueryInterface(IID_ISubtract,(void **)&pISubtract);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("ISubtract Interface Can Not Be Obtained."),TEXT("Error"),MB_OK);
			pISum->Release();
			pISum=NULL;
			DestroyWindow(hwnd);
		}
		// check identity
		if(CheckIdentity(pISum,pISubtract)==TRUE)
			wcscpy(str,TEXT("ISum And ISubtract Interfaces Belong To The Same Component"));
		else
			wcscpy(str,TEXT("ISum And ISubtract Interfaces Do Not Belong To The Same Component"));
		MessageBox(hwnd,str,TEXT("Message"),MB_OK);
		pISubtract->Release();
		pISubtract=NULL;
		// check predictability
		if(CheckPredictability(pISum)==TRUE)
			wcscpy(str,TEXT("The Component Is Predictable And Its Interfaces Do Not Change Over Time"));
		else
			wcscpy(str,TEXT("The Component Is Not Predictable. Its Interfaces Change Over Time"));
		MessageBox(hwnd,str,TEXT("Message"),MB_OK);
		// check symmetry
		if(CheckSymmetry(pISum)==TRUE)
			wcscpy(str,TEXT("The Component Is Symmetric"));
		else
			wcscpy(str,TEXT("The Component Is Not Symmetric"));
		MessageBox(hwnd,str,TEXT("Message"),MB_OK);
		// check reflexivity
		if(CheckReflexivity(pISum)==TRUE)
			wcscpy(str,TEXT("The Component Is Reflexive"));
		else
			wcscpy(str,TEXT("The Component Is Not Reflexive"));
		MessageBox(hwnd,str,TEXT("Message"),MB_OK);
		// check transitivity
		if(CheckTransitivity(pISum)==TRUE)
			wcscpy(str,TEXT("The Component Is Transitive"));
		else
			wcscpy(str,TEXT("The Component Is Not Transitive"));
		MessageBox(hwnd,str,TEXT("Message"),MB_OK);
		pISum->Release();
		pISum=NULL;
		// exit the application
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		// release the loaded dll
		if(hServerLib)
		{
			FreeLibrary(hServerLib);
			hServerLib=NULL;// make freed module pointer NULL
		}
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
BOOL CheckIdentity(ISum *ptrISum,ISubtract *ptrISubtract)
{
	// variable declarations
	IUnknown *pIUnknownFromISum=NULL;
	IUnknown *pIUnknownFromISubtract=NULL;
	HRESULT hr;
    // code
	hr=ptrISum->QueryInterface(IID_IUnknown,(void **)&pIUnknownFromISum);
	if(FAILED(hr))
		MessageBox(NULL,TEXT("Can Not Obtain Iunknown From ISum"),TEXT("CheckIdentity() Error"),MB_OK);
	hr=ptrISubtract->QueryInterface(IID_IUnknown,(void **)&pIUnknownFromISubtract);
	if(FAILED(hr))
		MessageBox(NULL,TEXT("Can Not Obtain Iunknown From ISubtract"),TEXT("CheckIdentity() Error"),MB_OK);
	if(pIUnknownFromISum==pIUnknownFromISubtract)
		return(TRUE);
	return(FALSE);
}
BOOL CheckPredictability(ISum *ptrISum)
{
	// variable declarations
	ISubtract *pISubtract=NULL;
	HRESULT hr;
    // code
	hr=ptrISum->QueryInterface(IID_ISubtract,(void **)&pISubtract);
	if(FAILED(hr))
		MessageBox(NULL,TEXT("Can Not Get ISubtract Interface From ISum Interface"),TEXT("CheckPredictability() Error"),MB_OK);
	else
	{
		// deliberatly release newly obtained ISubtract interface
		pISubtract->Release();
		pISubtract=NULL;
		// wait for some time
		Sleep(1000);// 1 second
		// again obtain Isubtract interface
	    hr=ptrISum->QueryInterface(IID_ISubtract,(void **)&pISubtract);
	    if(FAILED(hr))
			MessageBox(NULL,TEXT("Can Not Get ISubtract Interface From ISum Interface"),TEXT("CheckPredictability() Error"),MB_OK);
		else
		{
			// this is usual release of ISubtract interface
		    pISubtract->Release();
		    pISubtract=NULL;
			return(TRUE);
		}
	}
	return(FALSE);
}
BOOL CheckSymmetry(ISum *ptrISum)
{
	// variable declarations
	ISubtract *pISubtract=NULL;
	ISum *pISumAgain=NULL;
	HRESULT hr;
    // code
	hr=ptrISum->QueryInterface(IID_ISubtract,(void **)&pISubtract);
	if(FAILED(hr))
		MessageBox(NULL,TEXT("Can Not Get ISubtract Interface From ISum Interface"),TEXT("CheckSymmetry() Error"),MB_OK);
	else
	{
		// again obtain ISum interface
	    hr=pISubtract->QueryInterface(IID_ISum,(void **)&pISumAgain);
	    if(FAILED(hr))
			MessageBox(NULL,TEXT("Can Not Get ISum Interface From ISubtract Interface"),TEXT("CheckSymmetry() Error"),MB_OK);
		else
		{
			if(ptrISum==pISumAgain)
			{
				pISumAgain->Release();
		        pISumAgain=NULL;
			    return(TRUE);
			}
			else
			{
				pISumAgain->Release();
		        pISumAgain=NULL;
			    return(FALSE);
			}
		}
	}
	return(FALSE);
}
BOOL CheckReflexivity(ISum *ptrISum)
{
	// variable declarations
	ISum *pISumAgain=NULL;
	HRESULT hr;
    // code
	hr=ptrISum->QueryInterface(IID_ISum,(void **)&pISumAgain);
	if(FAILED(hr))
		MessageBox(NULL,TEXT("Can Not Get ISum Interface From ISum Interface Itself"),TEXT("CheckReflexivity() Error"),MB_OK);
	else
	{
		if(ptrISum==pISumAgain)
		{
			pISumAgain->Release();
	        pISumAgain=NULL;
		    return(TRUE);
		}
		else
		{
			pISumAgain->Release();
	        pISumAgain=NULL;
		    return(FALSE);
		}
	}
	return(FALSE);
}
BOOL CheckTransitivity(ISum *ptrISum)
{
	// variable declarations
	ISum *pISumAgain=NULL;
	ISubtract *pISubtract=NULL;
	IMultiply *pIMultiply=NULL;
	HRESULT hr;
    // code
	// get ISubtract interface
	hr=ptrISum->QueryInterface(IID_ISubtract,(void **)&pISubtract);
	if(FAILED(hr))
		MessageBox(NULL,TEXT("Can Not Get ISubtract Interface From ISum Interface"),TEXT("CheckTransitivity() Error"),MB_OK);
	// get IMultiply interface
	hr=pISubtract->QueryInterface(IID_IMultiply,(void **)&pIMultiply);
	if(FAILED(hr))
		MessageBox(NULL,TEXT("Can Not Get IMultiply Interface From ISubtract Interface"),TEXT("CheckTransitivity() Error"),MB_OK);
    // again get ISum interface	
	hr=pIMultiply->QueryInterface(IID_ISum,(void **)&pISumAgain);
	if(FAILED(hr))
		MessageBox(NULL,TEXT("Can Not Get ISum Interface From IMultiply Interface"),TEXT("CheckTransitivity() Error"),MB_OK);
	else
	{
		if(ptrISum==pISumAgain)
		{
			pISumAgain->Release();
	        pISumAgain=NULL;
			pIMultiply->Release();
	        pIMultiply=NULL;
			pISubtract->Release();
	        pISubtract=NULL;
		    return(TRUE);
		}
		else
		{
			pISumAgain->Release();
	        pISumAgain=NULL;
			pIMultiply->Release();
	        pIMultiply=NULL;
			pISubtract->Release();
	        pISubtract=NULL;
		    return(FALSE);
		}
	}
	return(FALSE);
}
