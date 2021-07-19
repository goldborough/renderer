#include "Debug.h"

#if _DEBUG

char printbuffer[500];

void DebugPrint(string s)
{
    sprintf_s(printbuffer, sizeof(printbuffer), "Debug Print: %s ", s.c_str());
    OutputDebugStringA(printbuffer);

    std::cout << printbuffer << std::endl;

    return;
}

#endif