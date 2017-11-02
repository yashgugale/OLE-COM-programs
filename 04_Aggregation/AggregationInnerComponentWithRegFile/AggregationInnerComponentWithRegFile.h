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
// CLSID of MultiplicationDivision Component {4AC37EEC-DAFD-435d-A1BC-261EFA28EF46}
const CLSID CLSID_MultiplicationDivision={0x4ac37eec,0xdafd,0x435d,0xa1,0xbc,0x26,0x1e,0xfa,0x28,0xef,0x46};
// IID of IMultiplication Interface
const IID IID_IMultiplication={0xa39f8306,0x7a0c,0x4e47,0xb3,0x8a,0xfc,0x8d,0x68,0x5d,0xca,0x90};
// IID of IDivision Interface
const IID IID_IDivision={0x9f7d9e5a,0xab6,0x4a59,0xad,0x22,0xa,0x89,0x88,0x2e,0x46,0x28};
