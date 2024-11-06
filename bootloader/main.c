
#include "efi/efierr.h"
#include <efi/efi.h>
#include <efi/efiprot.h>
#include <efi/efilib.h>




EFI_STATUS EfiEntry(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    //SystemTable->BootServices->Stall(100000);
    while(1){continue;}
    return EFI_SUCCESS;
}