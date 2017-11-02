#define UNICODE
#include<windows.h>
#include"AutomationServerWithRegFile.h"
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
	TCHAR AppName[]=TEXT("Client");
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
		              TEXT("Client Of Exe Server"),
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
	return(msg.wParam);
}
// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	// variable declarations
	IDispatch *pIDispatch=NULL;
	HRESULT hr;
	DISPID dispid;
	OLECHAR *szFunctionName=L"SumOfTwoIntegers";
	VARIANT varg[2];
	DISPPARAMS param={varg,0,2,NULL};
	int n1,n2;
	// code
	switch(iMsg)
	{
	case WM_CREATE:
		// initialize COM library
		hr=CoInitialize(NULL);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("COM library can not be initialized"),TEXT("COM Error"),MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}
		// get ISum Interface
		hr=CoCreateInstance(CLSID_SumAutomation,
			                NULL,
							CLSCTX_LOCAL_SERVER,
							IID_IDispatch,
							(void **)&pIDispatch);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("Component Can Not Be Created"),TEXT("COM Error"),MB_OK|MB_ICONERROR|MB_TOPMOST);
			DestroyWindow(hwnd);
			exit(0);
		}
		hr=pIDispatch->GetIDsOfNames(IID_NULL,
	                                 &szFunctionName,
									 1,
	                                 GetUserDefaultLCID(),
								     &dispid);
        if(FAILED(hr))
		{
			MessageBox(NULL,TEXT("Can Not Get ID For Function"),TEXT("Error"),MB_OK|MB_ICONERROR|MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		n1=75;
		n2=25;
		// as DISPPARAMS rgvarg member receives parameters in reverse order
		VariantInit(varg);
	    varg[0].vt=VT_INT;
		varg[0].intVal=n2;
	    varg[1].vt=VT_INT;
		varg[1].intVal=n1;
		param.cArgs=2;
		param.cNamedArgs=0;
		param.rgdispidNamedArgs=NULL;
		// reverse order of parameters
		param.rgvarg=varg;
		hr=pIDispatch->Invoke(dispid,
			                  IID_NULL,
			                  GetUserDefaultLCID(),
							  DISPATCH_METHOD,
							  &param,
							  NULL,
							  NULL,
							  NULL);
		if(FAILED(hr))
		{
			MessageBox(NULL,TEXT("Can Not Invoke Function"),TEXT("Error"),MB_OK|MB_ICONERROR|MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		VariantClear(varg);
		pIDispatch->Release();
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		CoUninitialize();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
