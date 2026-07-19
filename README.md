# RAM Memory Reader & Writer Tools

Bu proje, Windows üzerinde çalışan bir işlemin (process) bellek adres uzayını haritalandırmak ve hedeflenen adreslerdeki verileri manipüle etmek için C diliyle geliştirilmiş minimalist araçlar içerir[cite: 1, 2].

This repository contains minimalist C tools designed to map a running process's memory space and manipulate data at targeted RAM addresses on Windows[cite: 1, 2].

---

## Derleme Kılavuzu / Compilation Guide

Projeyi GCC (MinGW) kullanarak terminal üzerinden derlemek için aşağıdaki komutları kullanabilirsiniz:

To compile the projects via terminal using GCC (MinGW), run the following commands:

```bash
# readpid aracını derlemek için / To compile readpid:
gcc readpid.c -o readpic.exe

# yaz aracını derlemek için / To compile yaz:
gcc yaz.c -o yaz.exe  

#using / kullanım  [ADMIN POWERSHELL]  
.\readpic > [blabla].txt and enter the PID
