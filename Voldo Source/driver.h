#pragma once
#include "main.h"

#define ctl_write    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x432423, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ctl_read    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x432452, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ctl_base    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x64231, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ctl_clear	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x647264, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct info_t {
	int pid = 0;
	DWORD_PTR address;
	void* value;
	SIZE_T size;
	void* data;
}info, * p_info;

DWORD processido;
HANDLE DrverInit;

DWORD64 pidde;

template <typename Type>
Type read(unsigned long long int Address)
{
	info_t Input_Output_Data;

	Input_Output_Data.pid = pidde;

	Input_Output_Data.address = Address;

	Type Return_Value;

	Input_Output_Data.value = &Return_Value;

	Input_Output_Data.size = sizeof(Type);

	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(DrverInit, ctl_read, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);

	return *(Type*)&Return_Value;
}
void writefloat(unsigned long long int Address, float stuff)
{
	info_t Input_Output_Data;

	Input_Output_Data.pid = pidde;

	Input_Output_Data.address = Address;

	Input_Output_Data.value = &stuff;

	Input_Output_Data.size = sizeof(float);

	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(DrverInit, ctl_write, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);
}
void writeint(unsigned long long int Address, int stuff)
{
	info_t Input_Output_Data;

	Input_Output_Data.pid = pidde;

	Input_Output_Data.address = Address;

	Input_Output_Data.value = &stuff;

	Input_Output_Data.size = sizeof(float);

	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(DrverInit, ctl_write, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);
}
void writedouble(unsigned long long int Address, double stuff)
{
	info_t Input_Output_Data;

	Input_Output_Data.pid = pidde;

	Input_Output_Data.address = Address;

	Input_Output_Data.value = &stuff;

	Input_Output_Data.size = sizeof(double);

	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(DrverInit, ctl_write, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);
}
NTSTATUS readarray(uint64_t Address, void* dest, uint32_t size)
{
	info_t Input_Output_Data;

	Input_Output_Data.pid = pidde;

	Input_Output_Data.address = Address;

	Input_Output_Data.value = &dest;

	Input_Output_Data.size = size;

	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(DrverInit, ctl_read, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);

	return 0;
}

const UINT GetProcessThreadNumByID(DWORD dwPID)
{
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return 0;

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(pe32);
	BOOL bRet = ::Process32First(hProcessSnap, &pe32);;
	while (bRet)
	{
		if (pe32.th32ProcessID == dwPID)
		{
			::CloseHandle(hProcessSnap);
			return pe32.cntThreads;
		}
		bRet = ::Process32Next(hProcessSnap, &pe32);
	}
	return 0;
}
auto GetProcessId(const wchar_t* process_name) -> ULONG {
	UINT pid = 0;
	xStartCommunication();
	DWORD dwThreadCountMax = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);
	if (Process32First(snapshot, &process))
	{
		do
		{
			if (wcsstr(process.szExeFile, process_name))
			{
				DWORD dwTmpThreadCount = GetProcessThreadNumByID(process.th32ProcessID);
				if (dwTmpThreadCount > dwThreadCountMax)
				{
					dwThreadCountMax = dwTmpThreadCount;
					pid = process.th32ProcessID;
					break;
				}
			}
		} while (Process32Next(snapshot, &process));
	}
	CloseHandle(snapshot);
	return pid;
}