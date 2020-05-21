#include "Native.hpp"
#include "Syscall Hook.hpp"
#define kprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)
NTSTATUS ntCreateFileHook(PHANDLE fileHandle, ACCESS_MASK desiredAccess, POBJECT_ATTRIBUTES objectAttributes,
                          PIO_STATUS_BLOCK ioStatusBlock, PLARGE_INTEGER allocationSize, ULONG fileAttributes,
                          ULONG shareAccess, ULONG createDisposition, ULONG createOptions, PVOID eaBuffer,
                          ULONG eaLength) {

	kprintf("%s call NtCreateFile: %ws\n", PsGetProcessImageFileName(PsGetCurrentProcess()),objectAttributes->ObjectName->Buffer);
	if (wcsstr(objectAttributes->ObjectName->Buffer,L"1.txt"))
	{
		kprintf("ÒÑÀ¹½Ø\n");
		return STATUS_ACCESS_DENIED;
	}
	
	return NtCreateFile(fileHandle, desiredAccess, objectAttributes, ioStatusBlock, allocationSize, fileAttributes,
                        shareAccess, createDisposition, createOptions, eaBuffer, eaLength);

}

void Unload(PDRIVER_OBJECT driverObject)
{
	if (!UnhookSystemCall())
	{
		DbgBreakPoint();
	}
}

NTSTATUS DriverEntry(const PDRIVER_OBJECT driverObject, const PUNICODE_STRING registryPath) {
	// Hook NtCreateFile for this example


	//DbgBreakPoint();
	
	driverObject->DriverUnload = Unload;
	if (hookSystemCall(reinterpret_cast<std::uintptr_t>(&ntCreateFileHook),
		reinterpret_cast<std::uintptr_t>(&NtCreateFile)))
	{
		return STATUS_SUCCESS;

	}
	return STATUS_UNSUCCESSFUL;
}