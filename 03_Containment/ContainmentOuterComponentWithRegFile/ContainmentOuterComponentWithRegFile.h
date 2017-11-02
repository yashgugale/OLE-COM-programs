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
// CLSID of SumSubtract Component {6D9B9F18-1DD6-4377-946A-5ED883B78031}
const CLSID CLSID_SumSubtract={0x6d9b9f18,0x1dd6,0x4377,0x94,0x6a,0x5e,0xd8,0x83,0xb7,0x80,0x31};
// IID of ISum Interface
const IID IID_ISum={0x791876b8,0x4bd,0x4202,0x91,0x8d,0xc2,0x66,0x30,0x96,0xfe,0xbf};
// IID of ISubtract Interface
const IID IID_ISubtract={0x9f2a8316,0x4eda,0x4113,0xac,0x4c,0x64,0x52,0x24,0x18,0x78,0x47};
