
#include "efi/efierr.h"
#include <efi/efi.h>
#include <efi/efiprot.h>
#include <efi/efilib.h>




EFI_STATUS EfiEntry(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->SetMode(SystemTable->ConOut, 0);
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->EnableCursor(SystemTable->ConOut, TRUE);
    while(1){
        EFI_INPUT_KEY s;
        SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &s);
        SystemTable->ConOut->OutputString(SystemTable->ConOut, &s.UnicodeChar);

    }
    //SystemTable->RuntimeServices->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, L"Error");
    while(1){continue;}
    return EFI_SUCCESS;
}