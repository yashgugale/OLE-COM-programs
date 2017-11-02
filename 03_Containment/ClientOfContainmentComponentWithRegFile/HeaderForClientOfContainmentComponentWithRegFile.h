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
class IMultiplication:public IUnknown
{
public:
	// IMultiplication specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *)=0;// pure virtual
};
class IDivision:public IUnknown
{
public:
	// IDivision specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *)=0;// pure virtual
};
// CLSID of SumSubtract Component {6D9B9F18-1DD6-4377-946A-5ED883B78031}
const CLSID CLSID_SumSubtract={0x6d9b9f18,0x1dd6,0x4377,0x94,0x6a,0x5e,0xd8,0x83,0xb7,0x80,0x31};
// IID of ISum Interface
const IID IID_ISum={0x791876b8,0x4bd,0x4202,0x91,0x8d,0xc2,0x66,0x30,0x96,0xfe,0xbf};
// IID of ISubtract Interface
const IID IID_ISubtract={0x9f2a8316,0x4eda,0x4113,0xac,0x4c,0x64,0x52,0x24,0x18,0x78,0x47};
// IID of IMultiplication Interface
const IID IID_IMultiplication={0xa39f8306,0x7a0c,0x4e47,0xb3,0x8a,0xfc,0x8d,0x68,0x5d,0xca,0x90};
// IID of IDivision Interface
const IID IID_IDivision={0x9f7d9e5a,0xab6,0x4a59,0xad,0x22,0xa,0x89,0x88,0x2e,0x46,0x28};
