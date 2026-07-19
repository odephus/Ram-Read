#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <stdint.h>

int main() {
    setlocale(LC_ALL, "tr_TR.UTF-8");

    DWORD processID;
    printf("Hedef Uygulamanin PID degerini girin (Decimal): ");
    if (scanf("%lu", &processID) != 1) return 1;

    // DİKKAT: Bu kez sadece OKUMA değil, YAZMA (WRITE ve OPERATION) yetkisi alıyoruz!
    HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID);

    if (hProcess == NULL) {
        printf("\nHATA: Süreç açılamadı! (Yönetici olarak çalıştırın). Hata Kodu: %lu\n", GetLastError());
        return 1;
    }

    uintptr_t memoryAddress;
    printf("Mudahale edilecek RAM Adresini girin (Orn: 1F30BBE5F20): ");
    scanf("%llx", &memoryAddress);

    int newValue;
    printf("Yazmak istediginiz YENI DEGERI girin: ");
    scanf("%d", &newValue);

    SIZE_T bytesWritten;

    // İŞTE SİHRİN GERÇEKLEŞTİĞİ YER: Hedefin belleğini zorla değiştiriyoruz!
    if (WriteProcessMemory(hProcess, (LPVOID)memoryAddress, &newValue, sizeof(newValue), &bytesWritten)) {
        printf("\n==========================================\n");
        printf("HACK BASARILI!\n");
        printf("Adres: 0x%llX\n", (unsigned long long)memoryAddress);
        printf("Yeni Deger %d olarak RAM'e islendi.\n", newValue);
        printf("==========================================\n");
    } else {
        printf("\nHATA: Belleğe yazılamadı! Hata Kodu: %lu\n", GetLastError());
    }

    CloseHandle(hProcess);
    
    printf("\nCikmak icin ENTER tusuna basin...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    getchar(); 
    
    return 0;
}