#pragma once

#ifdef HUFFMANLIBRARY_EXPORTS
#define HUFFMANLIBRARY_API __declspec(dllexport)
#else
#define HUFFMANLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>
#include <string>
#include <WTypes.h>

using namespace std;

extern "C" HUFFMANLIBRARY_API void Compress_file(BSTR name, BSTR namef);

extern "C" HUFFMANLIBRARY_API void Decompress_file(BSTR name, BSTR namef);

extern "C" HUFFMANLIBRARY_API void init_progression();

extern "C" HUFFMANLIBRARY_API int  get_progression_interface();

extern "C" HUFFMANLIBRARY_API void get_progression();

extern "C" HUFFMANLIBRARY_API void end_progression();

extern "C" HUFFMANLIBRARY_API void End_Compress_file();

extern "C" HUFFMANLIBRARY_API void End_Decompress_file();