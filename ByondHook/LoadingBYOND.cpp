#define BYOND_RSC_NAME "Hack.rsc"
#include "MeshBYOND.h"
#include "LoadingBYOND.h"

char* fileBuf;
int size;

OBJStruct::OBJStruct(char* p, int s)
{
	fileBuf = new char[s + 1];
	memcpy(fileBuf, p, s);
	fileBuf[s] = '\0';
	size = s;
}

OBJStruct GetFileInResources(std::string rscName)
{
	std::ifstream myFile;
	std::streampos byteOffset = 18; // First rsc size.

	std::string nameStr;

	int fileSize = 0;
	int rscfileSize = 0;

	myFile.open(BYOND_RSC_NAME, std::ios::in | std::ios::binary);

	myFile.seekg(0, std::ios::end);
	fileSize = myFile.tellg();
	myFile.seekg(0, std::ios::beg);

	while (byteOffset < fileSize)
	{
		myFile.clear();
		myFile.seekg(byteOffset);
		myFile.read((char*)&rscfileSize, sizeof(int));
		byteOffset += 4;
		myFile.seekg(byteOffset);
		std::getline(myFile, nameStr, '\0');

		//std::cout << nameStr << std::endl;

		if (nameStr != rscName)
		{
			byteOffset += (rscfileSize + 18) + nameStr.length() + 1;
		}
		else
		{
			byteOffset += nameStr.length() + 1;
			break;
		}
	}
	if (nameStr != rscName)
	{
		std::cout << "Could not find " << rscName << " in resources." << std::endl;
		myFile.close();
	}

	myFile.seekg(byteOffset);

	std::cout << "Found file " << nameStr << std::endl;

	char* buffer = (char*)malloc(rscfileSize);

	if (!myFile.read(buffer, rscfileSize))
	{
		std::cout << "Memory copying failed." << std::endl;
	}


	OBJStruct o = OBJStruct(buffer, rscfileSize);


	delete[] buffer;

	myFile.close();

	return o;
}

OneShotReadBuf::OneShotReadBuf(char* s, std::size_t n)
{
	setg(s, s, s + n);
}



DWORD GetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID) {
	DWORD dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID); // make snapshot of all modules within process
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32)) //store first Module in ModuleEntry32
	{
		do {
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0) // if Found Module matches Module we look for -> done!
			{
				dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32)); // go through Module entries in Snapshot and store in ModuleEntry32


	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}