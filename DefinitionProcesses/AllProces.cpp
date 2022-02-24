// deadProces.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <psapi.h>
int main()
{
	/*
	STARTUPINFOA        startupInfo = {};
	BOOL res = CreateProcessA(
		"D:\\Антон\\ардуино\\Arduino\\arduino.exe",
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		&startupInfo,
		&processInformation
	);
	*/
	//res = TerminateProcess(processInformation.hProcess, -1);
	DWORD sizeArr = 500;
	DWORD sizeArrNeeded;
	DWORD idProces[500] = {};

	char adress[500];

	HANDLE vib=0;
	DWORD* id = idProces;
	BOOL proces = EnumProcesses(id, sizeArr, &sizeArrNeeded);
	for (int i = 0; i < sizeArr; i++) {
		if (idProces[i]) {
			vib = OpenProcess(PROCESS_ALL_ACCESS, 1, idProces[i]);
		std::cout << idProces[i] << "       " << vib << std::endl;
		}
	}

	DWORD nameFile = GetModuleBaseNameA(
		vib,
		0,
		&adress[0],
		500
	);
	int Error = GetLastError();


	for (int i = 0; i < 1; i++) {
		
	std::cout << Error;
	}
	}





