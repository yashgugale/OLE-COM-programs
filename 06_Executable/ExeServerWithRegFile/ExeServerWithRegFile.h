class ISum:public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;// pure virtual
};
class ISubtract:public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;// pure virtual
};
// CLSID of SumSubtract Component {7ACCABF1-40CE-49a5-8703-0183CDE6B91F}
const CLSID CLSID_SumSubtract={0x7accabf1,0x40ce,0x49a5,0x87,0x3,0x1,0x83,0xcd,0xe6,0xb9,0x1f};
// IID of ISum Interface {8CC14612-CAB1-42dc-8E22-B88F5B2F0CC2}
const IID IID_ISum={0x8cc14612,0xcab1,0x42dc,0x8e,0x22,0xb8,0x8f,0x5b,0x2f,0xc,0xc2};
// IID of ISubtract Interface {B16D9F59-BFA4-4c2d-90C6-7AC06B08BE91}
const IID IID_ISubtract={0xb16d9f59,0xbfa4,0x4c2d,0x90,0xc6,0x7a,0xc0,0x6b,0x8,0xbe,0x91};
