
#include "efi/efierr.h"
#include <efi/efi.h>
#include <efi/efiprot.h>
#include <efi/efilib.h>




EFI_STATUS EfiEntry(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);
    Print(L"Hi!");
    return EFI_SUCCESS;
}