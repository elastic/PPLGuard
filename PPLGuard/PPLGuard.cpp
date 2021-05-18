#include "exploit.h"

#include <iostream>

BOOL g_bVerbose = FALSE;
BOOL g_bDebug = FALSE;
BOOL g_bForce = FALSE;

int wmain(int argc, wchar_t* argv[])
{
    if (!ParseArguments(argc, argv))
        return 1;

    HardenKnownDlls();

    return 0;
}
