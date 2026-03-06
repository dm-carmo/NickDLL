#pragma once
#include <Windows.h>
#include "Helpers\Helper.h"
#include <algorithm>
#include <iterator>

enum VTablePointers {
	VTableInitFree = 1, // Some kind of init/free, called when loading and saving I think
	VTable2 = 2, // Used in Champions League, gives out money for each win/draw in the group stage
	VTableEoSUpdate = 3, // End of season competition update
	VTable4 = 4,
	VTable5 = 5,
	VTableLeagueSplit = 6, // Related to leagues with a split at the end of the regular season (Scotland), similar to 11 below
	VTable7 = 7,
	VTable8 = 8,
	VTable9 = 9,
	VTable10 = 10,
	VTablePlayoffQual = 11, // Creates any later stages in competitions when needed (playoffs etc)
	VTable12 = 12,
	VTableSetChampion = 13, // Called when competition finishes, creates history entry with winner
	VTable14 = 14,
	VTable15 = 15, // Text that shows in "Competitions" club page (Winners, round they were eliminated in, etc)
	VTableFixtures = 16, // Creates fixtures for the competition
	VTable17 = 17,
	VTableTableFates = 18, // Sets table information (champions, promoted etc)
	VTableStageNews = 19, // Sends out news (champions, promoted etc)
	VTable20 = 20,
	VTable21 = 21,
	VTable22 = 22,
	VTable23 = 23,
	VTableReputationSetup = 24, // Called during setup and update, is connected to club reputation update
	VTable25 = 25,
	VTable26 = 26,
	VTableReputationCalc = 27, // Called often throughout the season, is connected to club reputation update
	VTable28 = 28,
	VTable29 = 29,
	VTable30 = 30,
	VTable31 = 31,
	VTable32 = 32,
	VTable33 = 33,
	VTable34 = 34,
	VTable35 = 35,
	VTableSubsRounds = 36, // Sets things such as: number of substitutes, number of promoted/relegated teams, etc
	VTable37 = 37,
	VTable38 = 38,
	VTable39 = 39,
	VTable40 = 40,
	VTableAwardTeamsSetup = 41, // For leagues with groups, gets all the teams in the league for award purposes
	VTable42 = 42,
	VTable43 = 43,
	VTable44 = 44,
	VTablePromRelUpdate = 45, // Relevant in top leagues with league structures that involve groups
};

class vtable
{
public:
	vtable() {
		std::fill(std::begin(vtable_bytes), std::end(vtable_bytes), 0xFF);
	}

	vtable(BYTE* src, int amt) {
		for (int i = 0; i < amt; i++) vtable_bytes[i] = src[i];
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

	// mov eax, dword ptr[vtable_eng_league_2.vtable_ptr]
	// vtable::PrintVTable(0x969E84, "eng_league_2");
	BYTE* vtable_ptr = vtable_bytes;
	// Cup competitions (with no group stage) only use 0xA0 bytes
	BYTE vtable_bytes[0xB4] = { 0x0 };

};