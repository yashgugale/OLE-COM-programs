// By Using Monikers
#define UNICODE
#include<windows.h>
#include<stdio.h>
#include"MonikerDllServerWithRegFile.h"
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
// global variable declarations
IOddNumber *pIOddNumber=NULL;
IOddNumberFactory *pIOddNumberFactory=NULL;
// WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[]=TEXT("ComClient");
	HRESULT hr;
	// code
    // COM Initialization
    hr=CoInitialize(NULL);
    if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("COM Library Can Not Be Initialized.\nProgram Will Now Exit."),TEXT("Program Error"),MB_OK);
		exit(0);
	}
	// WNDCLASSEX initialization
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
    // COM Un-initialization
    CoUninitialize();
	return((int)msg.wParam);
}
// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	// function declarations
	void SafeInterfaceRelease(void);
	// variable declarations
	IBindCtx *pIBindCtx=NULL;
    IMoniker *pIMoniker=NULL;
    ULONG uEaten;
	HRESULT hr;
	LPOLESTR szCLSID=NULL;
	wchar_t wszCLSID[255],wszTemp[255],*ptr;
	int iFirstOddNumber,iNextOddNumber;
	TCHAR str[255];
	// code
	switch(iMsg)
	{
	case WM_CREATE:
		// create a BindContext
	    if(hr=CreateBindCtx(0,&pIBindCtx)!=S_OK)
		{
			MessageBox(hwnd,TEXT("Failed To Get IBindCtx Interface Pointer"),TEXT("Error"),MB_OK);
		    DestroyWindow(hwnd);
		}
	    // Get String From Of Binary CLSID
		StringFromCLSID(CLSID_OddNumber,&szCLSID);
		wcscpy(wszTemp,szCLSID);
		ptr=wcschr(wszTemp,'{');
		ptr=ptr+1;// to remove first opening '{' from CLSID string
		wcscpy(wszTemp,ptr);
		wszTemp[(int)wcslen(wszTemp)-1]='\0';// to remove last closing '}' from CLSID string
		wsprintf(wszCLSID,TEXT("clsid:%s"),wszTemp);
		// Get Moniker For This CLSID
	    hr=MkParseDisplayName(pIBindCtx,wszCLSID,&uEaten,&pIMoniker);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("Failed To Get IMoniker Interface Pointer"),TEXT("Error"),MB_OK);
			pIBindCtx->Release();
			pIBindCtx=NULL;
		    DestroyWindow(hwnd);
		}
	    // Bind the moniker to the named object
	    hr=pIMoniker->BindToObject(pIBindCtx,NULL,IID_IOddNumberFactory,(void**)&pIOddNumberFactory);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("Failed To Get Custom Activation - IOddNumberFactory Interface Pointer"),TEXT("Error"),MB_OK);
		    pIMoniker->Release();
		    pIMoniker=NULL;
		    pIBindCtx->Release();
		    pIBindCtx=NULL;
		    DestroyWindow(hwnd);
		}
		// release moniker & Binder
		pIMoniker->Release();
		pIMoniker=NULL;
		pIBindCtx->Release();
		pIBindCtx=NULL;
		// initialize arguments hardcoded
		iFirstOddNumber=57;
		// call SetFirstOddNumber() of IOddNumberFactory to get the first odd number
		hr=pIOddNumberFactory->SetFirstOddNumber(iFirstOddNumber,&pIOddNumber);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("Can Not Obtain IOddNumber Interface"),TEXT("Error"),MB_OK);
    		DestroyWindow(hwnd);
		}
		// Release IOddNumberFactory Interface
		pIOddNumberFactory->Release();
		pIOddNumberFactory=NULL;
		// call GetNextOddNumber() Of IOddNumber To Get Next Odd Number Of First Odd Number
		pIOddNumber->GetNextOddNumber(&iNextOddNumber);
		// Release IOddNumber Interface
		pIOddNumber->Release();
        pIOddNumber=NULL;
		// show the results
		wsprintf(str,TEXT("The Next Odd Number From %2d Is %2d"),iFirstOddNumber,iNextOddNumber);
		MessageBox(hwnd,str,TEXT("Result"),MB_OK|MB_TOPMOST);
		// exit the application
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
void SafeInterfaceRelease(void)
{
	// code
	if(pIOddNumber)
	{
		pIOddNumber->Release();
		pIOddNumber=NULL;
	}
	if(pIOddNumberFactory)
	{
		pIOddNumberFactory->Release();
		pIOddNumberFactory=NULL;
	}
}
