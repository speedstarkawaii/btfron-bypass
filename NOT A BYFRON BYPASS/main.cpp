#include <Windows.h>
#include <winternl.h>
#include <iostream>

#include "roblox.h"


//PROLLY DETECTED AS SHITT I DONT THINK IT WORKS I DIDNT TEST IT OUT RIP


int NtProcessId = 15932;//INSERT your process ID HERE
#define NtNull 0
typedef NTSTATUS(NTAPI* _NtOpenProcess)(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, CLIENT_ID* ClientId);

//realest nt function evaaarrr
int NtStdCout(const char* real_nt_function) {
    std::cout << "ntdll.dll -> " << real_nt_function << std::endl;
    return 1;
}

int main() {
    SetConsoleTitle(L"ntdll debug console");

    NtStdCout("made by the legendary speedsterkawaii himself :O");

    HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));//load ntdll

    //get the addy of ntopenprocess
    _NtOpenProcess NtOpenProcess = (_NtOpenProcess)GetProcAddress(hNtDll, "NtOpenProcess");//stupid warninings lol
    if (NtOpenProcess == 0x0) {
        NtStdCout("did not open process :c");
        (INT)getchar();
        return FALSE;
        return 1;
    }

    OBJECT_ATTRIBUTES objectAttributes;
    InitializeObjectAttributes(&objectAttributes, 0, 0, 0, 0);


    CLIENT_ID clientId;
    clientId.UniqueProcess = (HANDLE)(ULONG_PTR)NtProcessId;//too lazy to make auto process id grabber
    clientId.UniqueThread = NtNull;//yes a real nt func ;)

    //call ntopenprocess 
    HANDLE processHandle;
    NTSTATUS status = NtOpenProcess(&processHandle, PROCESS_ALL_ACCESS, &objectAttributes, &clientId);

    if (status == 0x00000000L) {//error code or 'STATUS_SUCCESS' apparently my vs is fucked so i cant use macro :rip:
        //now we can access roblox through a handle. write/read memory (NOT DTC 100%)
        NtStdCout("hacked roblox! mewing streak 3000!");   
        
        (INT)getchar();//make console stay. leaving the console closes the handle
        CloseHandle(processHandle);
        return TRUE;
    }
    else {// rip
        NtStdCout("looks like roblox hacked you! failed to open process!");
        //std::cout << "womp womp skid search up this error code: " << std::hex << status << std::endl;
        (INT)getchar();
        return FALSE;
    }

    return 0;
}
