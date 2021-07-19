#if !defined(DEBUG_H)
#define DEBUG_H


#if NDEBUG
#define DebugPrint 0
#endif

#if _DEBUG

#include <string>
using std::string;

#include <iostream>

#include "windows.h"


void DebugPrint(string s);

#endif

#endif