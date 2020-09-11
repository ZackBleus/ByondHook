#include "HooksBYOND.h"

void __fastcall hkInitClient(void* This, void* _EDX, const char* a, const char* b, int c)
{
	return oInitClient(This, a, b, c);
}

int __cdecl hkReadIcon(struct iobuf* iobuf, struct DMIcon* icon, int a, unsigned long b, struct IconContextCallback* callback, int c)
{
	return oReadIcon(iobuf, icon, a, b, callback, c);
	int v = oReadIcon(iobuf, icon, a, b, callback, c);
	return v;
}

int __cdecl hkReadIconPixels(struct iobuf* _iobuf, struct DMIcon* _icon, struct ColRGBA** _colArray, int* _height, int* _width, struct IconContextCallback** _callbackArray, int _c)
{
	//DWORD* dwPngRscPtr;

	int v = oReadIconPixels(_iobuf, _icon, _colArray, _height, _width, _callbackArray, _c);

	if (_colArray == NULL)
		return v;

	ColRGBA** colors = _colArray;
	DMIcon* icon = _icon;

	//icons.push_back(Icon(32, 32, _colArray));
	return v;
}


void __fastcall hkCommandEvent(void* This, void* _EDX, unsigned char a, unsigned short b, unsigned char c)
{
	DWORD* dwCommandPtr;
	DWORD dwCommandLength;


	__asm // This is to basically get the CommandEvent string.
	{
		push eax
		mov eax, esi
		mov dwCommandPtr, eax
		mov eax, edx
		mov dwCommandLength, eax
		pop eax
	}

	if (dwCommandLength > 1000)
		return oCommandEvent(This, a, b, c);

	char* commandString = new char[dwCommandLength - 1];

	commandString = (char*)dwCommandPtr;

	//std::stringstream sstr; sstr << dwCommand; std::string str = sstr.str();

	//dwCommand = *(DWORD*)(*(DWORD*)(dwCommandPtr));

	//BOOL bReturn = ReadProcessMemory(processHandle, (LPVOID)dwCommandPtr, &commandString, dwCommandLength * sizeof(char), NULL);

	if (true)
	{
		DWORD lastError = GetLastError();
		// error 
		std::cout << commandString << std::endl;
	}

	//delete commandString;

	//ReadProcessMemory(processHandle, (LPVOID)dwCommand, &str, 4, NULL);

	return oCommandEvent(This, a, b, c);
}