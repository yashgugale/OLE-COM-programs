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
// CLSID of SumSubtract Component {DFB1278D-20D3-4388-A83D-B2F2DE4EF59B}
const CLSID CLSID_SumSubtract={0xdfb1278d,0x20d3,0x4388,0xa8,0x3d,0xb2,0xf2,0xde,0x4e,0xf5,0x9b};
// IID of ISum Interface
const IID IID_ISum={0x791876b8,0x4bd,0x4202,0x91,0x8d,0xc2,0x66,0x30,0x96,0xfe,0xbf};
// IID of ISubtract Interface
const IID IID_ISubtract={0x9f2a8316,0x4eda,0x4113,0xac,0x4c,0x64,0x52,0x24,0x18,0x78,0x47};
