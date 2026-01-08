#include "Helper.h"
#include "inject_club_renames.h"

map<string, string> club_rename_short = {
	{"C.D. Ourense", "Ourense CF"},
};

map<string, string> club_rename_long = {
	{"Dallas Burn", "FC Dallas"},
	{"Kansas City Wizards", "Sporting Kansas City"},
	{"Miami Fusion FC", "Inter Miami CF"},
	{"NY/NJ Metrostars", "New York Red Bulls"},
	{"Tampa Bay Mutiny", "Los Angeles FC"},
	{"Clube Atlético Paranaense", "Club Athletico Paranaense"},
	{"C.D. Ourense", "Ourense CF"},
	{"C.P. Mérida", "AD Mérida"},
	{"Baskonia C.D.", "CD Basconia"},
	{"Extremadura C.F.", "CD Extremadura"},
	{"Merthyr Tydfil", "Merthyr Town"},
	{"Bra", "AC Bra"},
	{"AZ", "AZ Alkmaar"},
};

void inject_names_full()
{
	for (const auto& [key, value] : club_rename_short) {
		cm3_clubs* to_rename = find_club(key.c_str());
		if (to_rename) {
			strcpy((*to_rename).ClubNameShort, value.c_str());
		}
	}
	for (const auto& [key, value] : club_rename_long) {
		cm3_clubs* to_rename = find_club(key.c_str());
		if (to_rename) {
			strcpy((*to_rename).ClubName, value.c_str());
		}
	}
}

extern "C" _declspec(naked) int inject_names()
{
	_asm
	{
		pushad
	}
	inject_names_full();
	_asm
	{
		popad
		ret
	}
}

void setup_name_injection()
{
	// Add call to our name function after all player setups have been loaded
	DWORD func_addr = (DWORD)inject_names;
	PatchFunction(0x005CCCC1, func_addr);
}