#pragma once
#include <string>
#include <wtypes.h>

struct OBJStruct
{
public:
	char* fileBuf;
	int size;

	OBJStruct(char* p, int s);
};

OBJStruct GetFileInResources(std::string rscName);

struct OneShotReadBuf : public std::streambuf
{
	OneShotReadBuf(char* s, std::size_t n);
};

DWORD GetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID);