#include <windows.h>
#include "YearChanger.h"
#include <vector>
#include "Helper.h"

using namespace std;

void ApplyExtraPatches()
{
}

void ApplyYearChange(WORD year)
{
	vector<DWORD> startYear = { 0x413386, 0x4140e5, 0x4224f0, 0x444270, 0x444297, 0x455830, 0x45583d, 0x45f4ee, 0x45f97c, 0x45f981, 0x56fc63, /*0x58b387,*/ 0x5aee53, 0x5bab86, 0x5bac32, 0x5BACE7, 0x5bb6ab, 
        0x5BC2C1, 0x5BC420, 0x5bc8b2, 0x5BF0AE, 0x5C070E, 0x5c3068, 0x5db242, 0x6673c3, 0x667495, 0x667582, 0x66766d, 0x66775a, 0x667829, 0x6678f8, 0x6679c6, 0x667aa1, 0x667b81, 0x667c6d, 0x667d5a, 0x667e55, 0x667f50,
        0x668043, 0x668149, 0x668236, 0x668324, 0x668411, 0x6684ff, 0x6685ed, 0x6686bc, 0x6687ac, 0x668899, 0x668987, 0x668a77, 0x668b65, 0x668c54, 0x668d40, 0x668e2f, 0x668f1d, 0x66900b, 0x6690da, /*0x77d858,*/ 0x7d2410,
        0x81b93d, 0x830591, 0x830598, 0x8305dc, 0x830a64, 0x830f8e, 0x830fb4, 0x83129a, 0x8312b4, 0x831608, 0x831622, 0x8318ad, 0x8318c6, 0x831b54, 0x831b6d, 0x831e66, 0x831e80, 0x8320b3, 0x8320cd, 0x832324, 0x832577,
        0x83290d, 0x833055, 0x83339d, 0x8336eb, 0x833c84, 0x833f8e, 0x834382, 0x83475d, 0x834aad, 0x834dfd, 0x835297, 0x835c39, 0x835fca, 0x8362EF, 0x83668e, 0x836a55, 0x836d68, 0x8371a5, 0x8371d5, 0x8374e9, 0x83805d,
        0x838357, 0x83869f, 0x856ce0, 0x8fddd2, 0x9041f3, 0x9059B9, 0x9291B4,
		/* Ballon d'Or from Xeno: */ 0x5836c6, 0x632e32,
		/* UEFA Coefficients: */ 0x903b76 };
	vector<DWORD> startYearMinus19 = { 0x52638d, 0x5263Ba };
	vector<DWORD> startYearMinus3 = { 0x7e6819, 0x861E36 };
	vector<DWORD> startYearMinus2 = { 0x535d83, 0x535df2 };
	vector<DWORD> startYearMinus1 = { 0x495fd1, 0x4dc02c, 0x52d2e2, 0x6B4FF4, 0x7e68fe, 0x7e691f, 0x85e98f };
	vector<DWORD> startYearPlus1 = { 0x4dc135, /* Zero Season Ticket Money First Year */ 0x59B56C };
	vector<DWORD> startYearPlus2 = { 0x52d321, 0x69e84e /*, 0x85b841, 0x85b898,  0x85c40c */ };
	vector<DWORD> startYearPlus3 = { 0x4dc113, 0x59ba24 };
	vector<DWORD> startYearPlus9 = { 0x535d89, 0x535df8, 0x7A3D64, 0x7A3FD1, 0x7A4224, 0x7A4844, 0x7A4CB4, 0x7A4F68, 0x7A4FA1 };

    for (DWORD offset : startYear)
    {
        WriteWORD(offset, (year));
    }
    for (DWORD offset : startYearMinus19)
    {
        WriteWORD(offset, (year - 19));
    }
    for (DWORD offset : startYearMinus3)
    {
        WriteWORD(offset, (year - 3));
    }
    for (DWORD offset : startYearMinus2)
    {
        WriteWORD(offset, (year - 2));
    }
    for (DWORD offset : startYearMinus1)
    {
        WriteWORD(offset, (year - 1));
    }
    for (DWORD offset : startYearPlus1)
    {
        WriteWORD(offset, (year + 1));
    }
    for (DWORD offset : startYearPlus2)
    {
        WriteWORD(offset, (year + 2));
    }
    for (DWORD offset : startYearPlus3)
    {
        WriteWORD(offset, (year + 3));
    }
    for (DWORD offset : startYearPlus9)
    {
        WriteWORD(offset, (year + 9));
    }

    // Special
    WORD mod4year = ((year + 1) - ((year - 1) % 4));
    WriteWORD(0x58B387, (mod4year));

    // Special - When looking at the Fixtures view, if you change the date, you cannot look at the first season played. This fixes that.
    WriteBytes(0x5AEE52, 1, 0xB8);

    // Special 2 (the calc for season selection can cause England 18/09 without this)
    WriteBytes(0x81e9ca, 1, 0x64);

    // Special 3 - Need to fix Euro for 2019
    if ((year % 4) == 3)
    {
        WriteWORD(0x5f9c0a, year - 7);
    }

    // Special 4 - World Cup - Oceania League Fix - So 2012, etc will work
    if ((year % 4) == 0)
    {
        WriteWORD(0x9182dc, year); // Euro Qualifier Start
        WriteBytes(0x918473, 1, 0xeb);
        WriteWORD(0x92036e, year); // South America Qualifier Start
        WriteBytes(0x9204b8, 1, 0xeb);
        // Asia is at 0x511CB7
    }

    // Fix Yugoslavia not to be a Euro host (set to be Poland - like the Tapani patch does)
    WriteBytes(0x5F9DAD, 2, 0x30, 0xf4 );

    ApplyExtraPatches();
}
