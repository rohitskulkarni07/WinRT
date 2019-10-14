class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract :public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};


//CLSID for CSumSubtract
// {19F85E77-F788-4500-A94F-B32F69F783BE}
const CLSID CLSID_SumSubtract = { 0x19f85e77, 0xf788, 0x4500, 0xa9, 0x4f, 0xb3, 0x2f, 0x69, 0xf7, 0x83, 0xbe };

// IID for ISum Interface
// {F82D1A3E-F1BC-49C1-A658-5363F0F212CA}
const IID IID_ISum = { 0xf82d1a3e, 0xf1bc, 0x49c1, 0xa6, 0x58, 0x53, 0x63, 0xf0, 0xf2, 0x12, 0xca };

//IID for ISubtract Interface
// {6A81D90B-89D0-472F-9F47-3695950D7587}
const IID IID_ISubtract = { 0x6a81d90b, 0x89d0, 0x472f, 0x9f, 0x47, 0x36, 0x95, 0x95, 0xd, 0x75, 0x87 };
