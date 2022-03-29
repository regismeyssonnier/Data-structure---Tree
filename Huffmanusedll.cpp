// Huffmanusedll.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../../Huffmandll/Huffmandll/HuffmanLibrary.h"
#pragma comment(lib, "Huffmandll.lib")
#include <Wtypes.h>
int main()
{
    BSTR n1 = SysAllocString(L"rm.pdf");
    BSTR n2 = SysAllocString(L"rm.rm");
    BSTR n3 = SysAllocString(L"rm.rm");
    BSTR n4 = SysAllocString(L"dec.pdf");
	init_progression();
	get_progression();
	Compress_file(n1, n2);
	End_Compress_file();
	cout << "get " << get_progression_interface() << endl;
	end_progression();
	 
	init_progression();
	get_progression();
	Decompress_file(n3, n4);
	End_Decompress_file();
	end_progression();


}

