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
// CLSID of SumSubtract Component {FA5EC586-38C0-4d05-9744-A52D4B13292A}
const CLSID CLSID_SumSubtract={0xfa5ec586, 0x38c0, 0x4d05, 0x97, 0x44, 0xa5, 0x2d, 0x4b, 0x13, 0x29, 0x2a};
// IID of ISum Interface
const IID IID_ISum={0x791876b8,0x4bd,0x4202,0x91,0x8d,0xc2,0x66,0x30,0x96,0xfe,0xbf};
// IID of ISubtract Interface
const IID IID_ISubtract={0x9f2a8316,0x4eda,0x4113,0xac,0x4c,0x64,0x52,0x24,0x18,0x78,0x47};
