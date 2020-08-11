// device_hvvm.h : definitions related the Hyper-V live memory diving.
//
// (c) Ulf Frisk, 2018
// Author: Ulf Frisk, pcileech@frizk.net
//
// (c) Arthur Khudyaev, 2020
// Author: Arthur Khudyaev, @gerhart_x
//
#ifndef __DEVICE_HVMM_H__
#define __DEVICE_HVMM_H__
#include "LiveCloudKdSdkHandle.h"
#include <stdio.h>
#include "leechcore.h"
#include "conio.h"
//#include "oscompatibility.h"

//
// The number of runs may vary if Dynamic Memory is enabled inside the Hyper-V virtual machine.
//
#define MAX_NUMBER_OF_RUNS MAX_NUMBER_OF_RUNS_BYTES / sizeof(PHYSICAL_MEMORY_RANGE) //correlation with MAX_NUMBER_OF_RUNS_BYTES from LiveCloudKdSdkMisc.h

#define HVMM_PROBE_MAXPAGES 0x1

typedef struct pmem_info_runs {
    __int64 start;
    __int64 length;
} PHYSICAL_MEMORY_RANGE;

struct PmemMemoryInfo {
    LARGE_INTEGER CR3;
    LARGE_INTEGER NtBuildNumber;
    LARGE_INTEGER KernBase;
    LARGE_INTEGER KDBG;
    LARGE_INTEGER KPCR[MAX_PROCESSORS];
    LARGE_INTEGER PfnDataBase;
    LARGE_INTEGER PsLoadedModuleList;
    LARGE_INTEGER PsActiveProcessHead;
    LARGE_INTEGER NtBuildNumberAddr;
    LARGE_INTEGER Padding[0xfe];
    LARGE_INTEGER NumberOfRuns;
    PHYSICAL_MEMORY_RANGE Run[MAX_NUMBER_OF_RUNS];
};

typedef struct tdDEVICE_CONTEXT_HVMM {
    HANDLE hFile;
	ULONG64 Partition;
    QWORD paMax;
    struct PmemMemoryInfo MemoryInfo;
} DEVICE_CONTEXT_HVMM, *PDEVICE_CONTEXT_HVMM;

/*
* Open a "connection" to the Hyper-V partition.
* -- result
*/
//BOOL DeviceHVMM_Open();
BOOL HVMMStart(PDEVICE_CONTEXT_HVMM ctx);
BOOLEAN HVMM_ReadFile(
	ULONG64 PartitionHandle,
    UINT64 StartPosition, 
    PVOID lpBuffer, 
    UINT64 nNumberOfBytesToRead
);

BOOLEAN HVMM_WriteFile(
	ULONG64 PartitionHandle,
	UINT64 StartPosition,
	PVOID lpBuffer,
	UINT64 nNumberOfBytesToRead
);

#endif /* __DEVICE_PMEM_H__ */