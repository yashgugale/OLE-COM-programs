class IOddNumber:public IUnknown
{
public:
	// IOddNumber specific method declarations
	virtual HRESULT __stdcall GetNextOddNumber(int *)=0;// pure virtual
};
class IOddNumberFactory:public IUnknown
{
public:
	// IOddNumberFactory specific method declarations
	virtual HRESULT __stdcall SetFirstOddNumber(int,IOddNumber **)=0;// pure virtual
};
// CLSID of OddNumber Component {0A37F4CE-E65D-41d7-9B6C-68CCAB226C6B}
const CLSID CLSID_OddNumber={0xa37f4ce,0xe65d,0x41d7,0x9b,0x6c,0x68,0xcc,0xab,0x22,0x6c,0x6b};
// IID of IOddNumber Interface
const IID IID_IOddNumber={0x831612d,0x7b54,0x4bc1,0xb0,0x6e,0xc6,0x33,0x65,0xac,0xdd,0xcc};
// IID of IOddNumberFactory Interface
const IID IID_IOddNumberFactory={0xbe04438b,0xb142,0x4c52,0x99,0x6b,0xec,0x6,0x84,0x78,0x16,0x81};
