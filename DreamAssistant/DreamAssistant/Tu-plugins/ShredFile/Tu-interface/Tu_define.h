#ifndef TU_DEFINE_H
#define TU_DEFINE_H

#include <windows.h>

#ifdef STATUS_INVALID_PARAMETER
#undef STATUS_INVALID_PARAMETER
#endif

#define STATUS_SUCCESS			         ((NTSTATUS)0x00000000L)
#define STATUS_BUFFER_OVERFLOW           ((NTSTATUS)0x80000005L)
#define STATUS_INVALID_PARAMETER         ((NTSTATUS)0xC000000DL)
#define STATUS_BUFFER_TOO_SMALL          ((NTSTATUS)0xC0000023L)
#define STATUS_ACCESS_DENIED	         ((NTSTATUS)0xC0000011L)
#define STATUS_ALREADY_COMMITTED         ((NTSTATUS)0xC0000021L)
#define STATUS_INVALID_DEVICE_REQUEST    ((NTSTATUS)0xC0000010L)

//--------------------------------------------------------------------
//       F S C T L  S P E C I F I C   T Y P E D E F S  
//--------------------------------------------------------------------

//
// This is the definition for a VCN/LCN (virtual cluster/logical cluster)
// mapping pair that is returned in the buffer passed to 
// FSCTL_GET_RETRIEVAL_POINTERS
//
typedef struct {
	ULONGLONG			Vcn;
	ULONGLONG			Lcn;
} MAPPING_PAIR, *PMAPPING_PAIR;

//
// This is the definition for the buffer that FSCTL_GET_RETRIEVAL_POINTERS
// returns. It consists of a header followed by mapping pairs
//
typedef struct {
	ULONG				NumberOfPairs;
	ULONGLONG			StartVcn;
	MAPPING_PAIR		Pair[1];
} GET_RETRIEVAL_DESCRIPTOR, *PGET_RETRIEVAL_DESCRIPTOR;

//
// This is the definition of the buffer that FSCTL_GET_VOLUME_BITMAP
// returns. It consists of a header followed by the actual bitmap data
//
typedef struct {
	ULONGLONG			StartLcn;
	ULONGLONG			ClustersToEndOfVol;
	BYTE				Map[1];
} BITMAP_DESCRIPTOR, *PBITMAP_DESCRIPTOR;

//
// This is the definition for the data structure that is passed in to
// FSCTL_MOVE_FILE
//
typedef struct {
	HANDLE            FileHandle;
	ULONG             Reserved;
	ULONGLONG         StartVcn;
	ULONGLONG         TargetLcn;
	ULONG             NumVcns;
	ULONG             Reserved1;
} MOVEFILE_DESCRIPTOR, *PMOVEFILE_DESCRIPTOR;

//
typedef struct _IO_STATUS_BLOCK {
	NTSTATUS Status;
	ULONG Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

//
// Apc Routine (see NTDDK.H)
//
typedef VOID(*PIO_APC_ROUTINE) (
	PVOID ApcContext,
	PIO_STATUS_BLOCK IoStatusBlock,
	ULONG Reserved
	);

//
// The undocumented NtFsControlFile
//
// This function is used to send File System Control (FSCTL)
// commands into file system drivers. Its definition is 
// in ntdll.dll (ntdll.lib), a file shipped with the NTDDK.
//
typedef LONG(__stdcall *PNtFsControlFile)
(
HANDLE FileHandle,
HANDLE Event,					// optional
PIO_APC_ROUTINE ApcRoutine,		// optional
PVOID ApcContext,				// optional
PIO_STATUS_BLOCK IoStatusBlock,
ULONG FsControlCode,
PVOID InputBuffer,				// optional
ULONG InputBufferLength,
PVOID OutputBuffer,				// optional
ULONG OutputBufferLength
);

typedef ULONG(__stdcall *PRtlNtStatusToDosError) ( IN NTSTATUS Status );

typedef BOOL(__stdcall *PGetDiskFreeSpaceEx)(
	LPCTSTR lpDirectoryName,                 // pointer to the directory name
	PULARGE_INTEGER lpFreeBytesAvailableToCaller, // receives the number of bytes on
	PULARGE_INTEGER lpTotalNumberOfBytes,    // receives the number of bytes on disk
	PULARGE_INTEGER lpTotalNumberOfFreeBytes // receives the free bytes on disk
	);

#endif // TU_DEFINE_H
