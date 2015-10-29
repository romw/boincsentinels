
#include "stdwx.h"

// Constant values
#define FNV1_32_INIT 0x811c9dc5
#define FNV_32_PRIME 0x01000193

int main(int argc, char* argv[])
{
    wxInitialize();

    wxString strToHash;
    wxChar* pPosition;
    unsigned long lHash = FNV1_32_INIT;

    strToHash = wxString(argv[1], wxConvUTF8);
    pPosition = (wxChar*)strToHash.wx_str();

    while (*pPosition != 0)
    {
        lHash *= FNV_32_PRIME;
        lHash ^= *pPosition++;
    }

    wxPrintf(
        wxT("FNV1Hash: Hash: '0x%x', Name: '%s'"),
        lHash,
        strToHash.wx_str()
    );

    wxUninitialize();

    return EXIT_SUCCESS;
}

