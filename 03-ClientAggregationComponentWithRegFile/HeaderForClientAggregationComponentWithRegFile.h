
class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract :public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};


//	CLSID for CSumSubtract
//	{0680C21C-265F-4925-8F41-952B424C4FF6}
//	0x680c21c, 0x265f, 0x4925, 0x8f, 0x41, 0x95, 0x2b, 0x42, 0x4c, 0x4f, 0xf6);

const CLSID CLSID_SumSubtract = { 0x680c21c, 0x265f, 0x4925, 0x8f, 0x41, 0x95, 0x2b, 0x42, 0x4c, 0x4f, 0xf6 };

//	IID for ISum Interface
//	{A4DFDE2D-B2E1-477E-BE13-4F2EFB3AAEE1}
//	0xa4dfde2d, 0xb2e1, 0x477e, 0xbe, 0x13, 0x4f, 0x2e, 0xfb, 0x3a, 0xae, 0xe1);

const IID IID_ISum = { 0xa4dfde2d, 0xb2e1, 0x477e, 0xbe, 0x13, 0x4f, 0x2e, 0xfb, 0x3a, 0xae, 0xe1 };

//	IID for ISubtract Interface
//	{748633DB-F1BE-4DD1-A8D3-17C162E6D7F3}
//	0x748633db, 0xf1be, 0x4dd1, 0xa8, 0xd3, 0x17, 0xc1, 0x62, 0xe6, 0xd7, 0xf3

const IID IID_ISubtract = { 0x748633db, 0xf1be, 0x4dd1, 0xa8, 0xd3, 0x17, 0xc1, 0x62, 0xe6, 0xd7, 0xf3 };

//	CLSID FOR MultiplicationDivision Component
//	{4479358B-1EBD-4852-8186-B1ABCB4C71B0}
//	0x4479358b, 0x1ebd, 0x4852, 0x81, 0x86, 0xb1, 0xab, 0xcb, 0x4c, 0x71, 0xb0

const CLSID CLSID_IMultiplicationDivision = { 0x4479358b, 0x1ebd, 0x4852, 0x81, 0x86, 0xb1, 0xab, 0xcb, 0x4c, 0x71, 0xb0 };

//	IID for IMultiplication Interface
//	{2291BF12-DC24-4399-8C91-19410672D5D6}
//	0x2291bf12, 0xdc24, 0x4399, 0x8c, 0x91, 0x19, 0x41, 0x6, 0x72, 0xd5, 0xd6

const IID IID_IMultiplication = { 0x2291bf12, 0xdc24, 0x4399, 0x8c, 0x91, 0x19, 0x41, 0x6, 0x72, 0xd5, 0xd6 };

//	IID for IDivsion Interface
//	{D8F68E64-377F-4D8A-B997-BD907F9154C6}
//	0xd8f68e64, 0x377f, 0x4d8a, 0xb9, 0x97, 0xbd, 0x90, 0x7f, 0x91, 0x54, 0xc6

const IID IID_IDivision = { 0xd8f68e64, 0x377f, 0x4d8a, 0xb9, 0x97, 0xbd, 0x90, 0x7f, 0x91, 0x54, 0xc6 };


//"C:\Windows\System32\AggregationInnerComponentWithRegFile.dll"
//"C:\Windows\System32\AggregationOuterComponentWithRegFile.dll"
