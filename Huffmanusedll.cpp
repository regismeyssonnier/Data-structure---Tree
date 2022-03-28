// Huffmanusedll.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../../Huffmandll/Huffmandll/HuffmanLibrary.h"
#pragma comment(lib, "Huffmandll.lib")
#include <Wtypes.h>
int main()
{
    BSTR n1 = SysAllocString(L"text.txt");
    BSTR n2 = SysAllocString(L"enc.txt");
    BSTR n3 = SysAllocString(L"enc.txt");
    BSTR n4 = SysAllocString(L"dec.txt");
    Compress_file(n1, n2);
    Decompress_file(n3, n4);



}

