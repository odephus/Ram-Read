#include <windows.h>
#include <stdio.h>

void BellekBolgeleriniYazdir(DWORD pid) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    
    if (hProcess == NULL) {
        printf("Kanka, PID %lu olan surece baglanilamadi.\n", pid);
        printf("Hata Kodu: %lu\n", GetLastError());
        printf("Not: Visual Studio'yu veya terminali 'Yonetici Olarak' calistirdigindan emin ol!\n");
        return;
    }

    MEMORY_BASIC_INFORMATION mbi;
    PVOID adres = 0; 

    printf("\n--- PID %lu ICIN BELLEK HARITASI ---\n", pid);
    printf("%-20s %-20s %-15s\n", "Taban Adresi (Base)", "Boyut (Byte)", "Durum");
    printf("------------------------------------------------------------\n");

    while (VirtualQueryEx(hProcess, adres, &mbi, sizeof(mbi)) != 0) {

        if (mbi.State == MEM_COMMIT) {
            printf("0x%-18p %-20llu %-15s\n", 
                   mbi.BaseAddress, 
                   (unsigned long long)mbi.RegionSize, 
                   "KULLANIMDA");
        }
  
        adres = (PBYTE)mbi.BaseAddress + mbi.RegionSize;
    }

    CloseHandle(hProcess);
    printf("------------------------------------------------------------\n");
    printf("Tarama tamamlandi.\n");
}

int main() {
    DWORD hedefPid;
    
    printf("Hedef uygulamanin PID degerini gir kanka: ");
    if (scanf("%lu", &hedefPid) == 1) {
        BellekBolgeleriniYazdir(hedefPid);
    } else {
        printf("Gecerli bir sayi girmedin!\n");
    }

    printf("\nCikmak icin ENTER'a bas...\n");
    getchar();
    getchar(); // Bekler
    
    return 0;
}
