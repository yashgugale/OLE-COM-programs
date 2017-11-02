class ISum:public IDispatch// *************************
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int)=0;// pure virtual
};
// CLSID of SumAutomation Component {175E20CF-F4D3-48e2-A8E5-1AFD73797502}
const CLSID CLSID_SumAutomation={0x175e20cf,0xf4d3,0x48e2,0xa8,0xe5,0x1a,0xfd,0x73,0x79,0x75,0x2};
// IID of ISum Interface {57140047-6957-4538-BF77-3208D32BAF63}
const IID IID_ISum={0x57140047,0x6957,0x4538,0xbf,0x77,0x32,0x8,0xd3,0x2b,0xaf,0x63};
