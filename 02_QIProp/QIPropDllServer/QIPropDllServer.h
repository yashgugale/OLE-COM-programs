class ISum:public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;// pure virtual
};
class ISubtract:public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;// pure virtual
};
class IMultiply:public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *)=0;// pure virtual
};
// IID Of ISum
const IID IID_ISum={0x835970f9,0xa663,0x44b8,0xa9,0x2b,0xa4,0x87,0x53,0x34,0x95,0x63};
// IID Of ISubtract
const IID IID_ISubtract={0x48d82e54,0x5451,0x40ff,0x80,0x4f,0xe7,0x0,0xa4,0x4a,0x26,0x8a};
// IID Of IMultiply
const IID IID_IMultiply={0xe9df9ebb,0xb9e6,0x4910,0xb2,0x78,0x1b,0x9,0x42,0xc0,0xa2,0x51};
// exported function declaration
extern "C" __declspec (dllexport) HRESULT CreateComponentInstance(REFIID,void **);
