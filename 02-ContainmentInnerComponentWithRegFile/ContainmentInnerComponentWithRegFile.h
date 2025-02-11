class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};


//	CLSID FOR MultiplicationDivision Component
//	{FE0317BB-6615-4399-BC6E-F6D72857AAAA}
//	0xfe0317bb, 0x6615, 0x4399, 0xbc, 0x6e, 0xf6, 0xd7, 0x28, 0x57, 0xaa, 0xaa

const CLSID CLSID_IMultiplicationDivision = {0xfe0317bb, 0x6615, 0x4399, 0xbc, 0x6e, 0xf6, 0xd7, 0x28, 0x57, 0xaa, 0xaa};

//	IID for IMultiplication Interface
//	{71F39302-8811-435E-A90F-0D15ED1F96CB}
//	0x71f39302, 0x8811, 0x435e, 0xa9, 0xf, 0xd, 0x15, 0xed, 0x1f, 0x96, 0xcb

const IID IID_IMultiplication = { 0x71f39302, 0x8811, 0x435e, 0xa9, 0xf, 0xd, 0x15, 0xed, 0x1f, 0x96, 0xcb };

//	IID for IDivsion Interface
//	{33B0FB90-D46C-484E-AA35-E3BBF288572E}
//	0x33b0fb90, 0xd46c, 0x484e, 0xaa, 0x35, 0xe3, 0xbb, 0xf2, 0x88, 0x57, 0x2e
	
const IID IID_IDivision = { 0x33b0fb90, 0xd46c, 0x484e, 0xaa, 0x35, 0xe3, 0xbb, 0xf2, 0x88, 0x57, 0x2e };
