/*
// original server's header file
class ISum:public IDispatch
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int)=0;// pure virtual
};
// CLSID of SumAutomation Component {175E20CF-F4D3-48e2-A8E5-1AFD73797502}
const CLSID CLSID_SumAutomation={0x175e20cf,0xf4d3,0x48e2,0xa8,0xe5,0x1a,0xfd,0x73,0x79,0x75,0x2};
// IID of ISum Interface {57140047-6957-4538-BF77-3208D32BAF63}
const IID IID_ISum={0x57140047,0x6957,0x4538,0xbf,0x77,0x32,0x8,0xd3,0x2b,0xaf,0x63};
*/
// converted for c type client
#undef INTERFACE
#define INTERFACE ISum
DECLARE_INTERFACE_ (ISum,IDispatch)
{
	//IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID,void **) PURE;
	STDMETHOD_ (ULONG,AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG,Release) (THIS) PURE;
	// IDispatch methods
	STDMETHOD (GetTypeInfoCount) (THIS_ UINT *) PURE;
	STDMETHOD (GetTypeInfo) (THIS_ UINT,LCID,ITypeInfo **) PURE;
	STDMETHOD (GetIDsOfNames) (THIS_ const IID *,LPOLESTR *,UINT,LCID,DISPID *) PURE;
	STDMETHOD (Invoke) (THIS_ DISPID,const IID *,LCID,WORD,DISPPARAMS *,VARIANT *,EXCEPINFO *,UINT *) PURE;
	STDMETHOD (SumOfTwoIntegers) (int,int) PURE;
};
// CLSID of SumAutomation Component {175E20CF-F4D3-48e2-A8E5-1AFD73797502}
const CLSID CLSID_SumAutomation={0x175e20cf,0xf4d3,0x48e2,0xa8,0xe5,0x1a,0xfd,0x73,0x79,0x75,0x2};
// IID of ISum Interface {57140047-6957-4538-BF77-3208D32BAF63}
const IID IID_ISum={0x57140047,0x6957,0x4538,0xbf,0x77,0x32,0x8,0xd3,0x2b,0xaf,0x63};
