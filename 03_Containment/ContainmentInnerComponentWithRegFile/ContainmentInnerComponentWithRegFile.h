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
// CLSID of MultiplicationDivision Component {764E7C57-1737-4f19-927A-6081C39EF514}
const CLSID CLSID_MultiplicationDivision={0x764e7c57,0x1737,0x4f19,0x92,0x7a,0x60,0x81,0xc3,0x9e,0xf5,0x14};
// IID of IMultiplication Interface
const IID IID_IMultiplication={0xa39f8306,0x7a0c,0x4e47,0xb3,0x8a,0xfc,0x8d,0x68,0x5d,0xca,0x90};
// IID of IDivision Interface
const IID IID_IDivision={0x9f7d9e5a,0xab6,0x4a59,0xad,0x22,0xa,0x89,0x88,0x2e,0x46,0x28};
