#pragma once
#include <Windows.h>
#include "Helpers\Helper.h"
#include <algorithm>
#include <iterator>

/*
* Notes on these function pointers: (example is Brazilian Bahia State league)
F0 F4 42 00 => Some kind of init/free?
30 5D 68 00 => Related to periods maybe? (check Netherlands D2)
10 FE 42 00 => Called to update at the end of the season
10 CE 48 00 
D0 9A 68 00 
C0 47 68 00 
10 7B 68 00 
C0 91 68 00 
B0 CE 48 00 
A0 CE 48 00 => Set table fates and send news
C0 FF 42 00 => Qualifies teams for playoffs and sets up the stages
70 CE 48 00 
70 29 43 00 => Related to periods maybe? (check Netherlands D2)
70 34 58 00 
B0 CA 48 00 
D0 F5 42 00 => Sets up fixtures
70 66 68 00 
10 02 43 00 => Sets teams as promoted/relegated in the table, used if there's multiple stages
70 27 43 00 => Sends out news about promotion, relegation, etc
A0 DF 48 00 
80 E1 48 00 
E0 A3 68 00 
C0 E1 48 00 
40 03 43 00 => Related to highest/lowest position a club can achieve I think
60 E3 48 00 
50 B5 5B 00 
F0 2A 43 00 => Related to highest/lowest position a club can achieve I think
70 34 58 00 
C0 11 40 00 
D0 11 40 00 
00 CE 5D 00 
D0 F2 48 00 
D0 AB 68 00 
40 AC 68 00 
00 CE 5D 00 
D0 22 43 00 => Function that defines things such as number of times teams play each other, number of promotions/relegation, etc
A0 C4 43 00 => ?
D0 4C 68 00 
90 47 68 00 
B0 47 68 00 
20 7A 68 00 
30 AA 68 00 
E0 11 40 00 
F0 11 40 00 
20 9C 68 00 => Some kind of promotion/relegation update? Usually only in top leagues, others use 00689C20
*/

enum VTablePointers {
	VTableInitFree = 1,
	VTable2 = 2,
	VTableEoSUpdate = 3,
	VTable4 = 4,
	VTable5 = 5,
	VTable6 = 6,
	VTable7 = 7,
	VTable8 = 8,
	VTable9 = 9,
	VTable10 = 10,
	VTablePlayoffQual = 11,
	VTable12 = 12,
	VTable13 = 13,
	VTable14 = 14,
	VTable15 = 15,
	VTableFixtures = 16,
	VTable17 = 17,
	VTableTableFates = 18,
	VTableStageNews = 19,
	VTable20 = 20,
	VTable21 = 21,
	VTable22 = 22,
	VTable23 = 23,
	VTable24 = 24,
	VTable25 = 25,
	VTable26 = 26,
	VTable27 = 27,
	VTable28 = 28,
	VTable29 = 29,
	VTable30 = 30,
	VTable31 = 31,
	VTable32 = 32,
	VTable33 = 33,
	VTable34 = 34,
	VTable35 = 35,
	VTableSubsRounds = 36,
	VTable37 = 37,
	VTable38 = 38,
	VTable39 = 39,
	VTable40 = 40,
	VTable41 = 41,
	VTable42 = 42,
	VTable43 = 43,
	VTable44 = 44,
	VTablePromRelUpdate = 45,
};

class vtable
{
public:
	vtable() {
		std::fill(std::begin(vtable_bytes), std::end(vtable_bytes), 0xFF);
	}

	void SetPointer(int pos, DWORD funcAddr)
	{
		WriteDWORD((DWORD)(&vtable_ptr[(pos - 1) * 4]), funcAddr);
	}

	static void PrintVTable(DWORD addr, const char* tableName = "")
	{
		BYTE* ptr = (BYTE*)addr;
		dprintf("%s VTable at %08X:\n", tableName, addr);
		for (BYTE i = 0; i < sizeof(addr); i += 4)
			dprintf("%02X = %08X\n", i, (*(DWORD*)&ptr[i]));
	}

	void PrintVTable()
	{
		for (BYTE i = 0; i < sizeof(vtable_bytes); i += 4)
			dprintf("%02X = %08X\n", i, (*(DWORD*)&vtable_bytes[i]));
	}

	// mov eax, dword ptr[vtable_eng_third.vtable_ptr]
	// vtable::PrintVTable(0x969E84, "eng_third");
	BYTE* vtable_ptr = vtable_bytes;
	// Cup competitions (with no group stage) only use 0xA0 bytes
	BYTE vtable_bytes[0xB4] = { 0x0 };

};