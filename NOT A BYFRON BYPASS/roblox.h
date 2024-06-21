#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>

DWORD NtGetRobloxPid() {//holy shit another ntdll function :o
    int process = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe)) {
        do {
            if (_tcsicmp(pe.szExeFile, L"RobloxPlayerBeta") == 0) {
                process = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe));
    }
    else {
        // Did not get process; probably doesn't exist
    }

    // CloseHandle(hSnapshot);
    return process;
}
