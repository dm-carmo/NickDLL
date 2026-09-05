#pragma once
#include <Windows.h>
#include "Helpers\Helper.h"
#include <algorithm>
#include <iterator>

enum VTablePointers {
	VTableInitFree = 1, // Some kind of init/free, called when loading and saving I think
	VTablePostMatchUpdate = 2, // Used in Champions League, gives out money for each win/draw in the group stage
	VTableEoSUpdate = 3, // End of season competition update
	VTable4 = 4,
	VTable5 = 5,
	VTableLeagueSplit = 6, // Related to leagues with a split at the end of the regular season (Scotland), similar to 11 below
	VTable7 = 7,
	VTable8 = 8,
	VTableLoadCompInfo = 9, // Called when loading a save game
	VTableSaveCompInfo = 10, // Called when saving a save game
	VTablePlayoffQual = 11, // Creates any later stages in competitions when needed (playoffs etc)
	VTable12 = 12,
	VTableSetChampion = 13, // Called when competition finishes, creates history entry with winner
	VTable14 = 14, // average points?
	VTableClubLandmarks = 15, // Text that shows in "Competitions" club page (Winners, round they were eliminated in, etc)
	VTableFixtures = 16, // Creates fixtures for the competition
	VTable17 = 17,
	VTableTableFates = 18, // Sets table information (champions, promoted etc)
	VTableStageNews = 19, // Sends out news (champions, promoted etc)
	VTable20 = 20,
	VTableShowThirdInHistory = 21, // returns AL=3 to show third-place teams in history, AL=2 only shows winner and runner-up
	VTable22 = 22,
	VTable23 = 23,
	VTableReputationSetup = 24, // Called during setup and update, is connected to club reputation update
	VTable25 = 25,
	VTable26 = 26,
	VTableReputationCalc = 27, // Called often throughout the season, is connected to club reputation update
	VTable28 = 28,
	VTable29 = 29, // sets initial expectations?
	VTable30 = 30, // calculates board happiness based on final position?
	VTableGetFinalsComp = 31, // returns the corresponding "finals" competition => for World Cup qualifiers, returns World Cup for example
	VTable32 = 32, // used in original Australian NSL?
	VTable33 = 33,
	VTable34 = 34,
	VTableShowHostsInHistory = 35, // AL=1 to show hosts in comp history, AL=0 otherwise
	VTableSubsRounds = 36, // Sets things such as: number of substitutes, number of promoted/relegated teams, etc
	VTable37 = 37,
	VTable38 = 38, // used in original Belgian Second Division?
	VTable39 = 39, // affects board expectations regarding promotion?
	VTable40 = 40, // affects board expectations regarding relegation?
	VTableAwardTeamsSetup = 41, // For leagues with groups, gets all the teams in the league for award purposes
	VTableUpdateLastDivision = 42, // Updates last divisions/positions
	VTable43 = 43,
	VTable44 = 44,
	VTablePromRelUpdate = 45, // Relevant in top leagues with league structures that involve groups
};

enum DisciplineVTablePointers {
	VTableD1 = 1,
	VTableD2 = 2,
	VTableD3 = 3,
	VTableD4 = 4,
	VTableDBanText = 5, // gets part of the text to show in the ban mssage
	VTableD6 = 6,
	VTableD7 = 7,
	VTableD8 = 8,
};

class vtable
{
public:
	//vtable() {
	//	std::fill(std::begin(vtable_bytes), std::end(vtable_bytes), 0xFF);
	//}

	vtable(BYTE* src, int amt) {
		sz = amt;
		vtable_bytes = new BYTE[amt];
		vtable_ptr = vtable_bytes;
		for (int i = 0; i < amt; i++) vtable_bytes[i] = src[i];
	}

	void SetPointer(int pos, DWORD funcAddr)
	{
		if (pos * 4 > sz) return;
		WriteDWORD((DWORD)(&vtable_ptr[(pos - 1) * 4]), funcAddr);
	}

	void PrintVTable()
	{
		for (BYTE i = 0; i < sz / 4; i += 4)
			dprintf("%02X = %08X\n", i, (*(DWORD*)&vtable_bytes[i]));
	}

	BYTE* vtable_ptr;// = vtable_bytes;
	// Cup competitions (with no group stage) only use 0xA0 bytes
	//BYTE vtable_bytes[0xB4] = { 0x0 };
	BYTE* vtable_bytes;

private:
	int sz;
};