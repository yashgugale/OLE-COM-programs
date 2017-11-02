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
// CLSID of SumSubtract Component {7AD1FE35-0DD6-4E86-BAD5-C1FE9205ACF5}
const CLSID CLSID_SumSubtract={0x7ad1fe35,0xdd6,0x4e86,0xba,0xd5,0xc1,0xfe,0x92,0x5,0xac,0xf5};
// IID of ISum Interface
const IID IID_ISum={0x791876b8,0x4bd,0x4202,0x91,0x8d,0xc2,0x66,0x30,0x96,0xfe,0xbf};
// IID of ISubtract Interface
const IID IID_ISubtract={0x9f2a8316,0x4eda,0x4113,0xac,0x4c,0x64,0x52,0x24,0x18,0x78,0x47};
// CLSID of MultiplicationDivision Component {709C630C-485B-4073-9AD1-12F30AC033D8}
const CLSID CLSID_MultiplicationDivision={0x709c630c,0x485b,0x4073,0x9a,0xd1,0x12,0xf3,0x0a,0xc0,0x33,0xd8};
// IID of IMultiplication Interface
const IID IID_IMultiplication={0xa39f8306,0x7a0c,0x4e47,0xb3,0x8a,0xfc,0x8d,0x68,0x5d,0xca,0x90};
// IID of IDivision Interface
const IID IID_IDivision={0x9f7d9e5a,0xab6,0x4a59,0xad,0x22,0xa,0x89,0x88,0x2e,0x46,0x28};
