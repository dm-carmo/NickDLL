#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"

static DWORD(__thiscall* cro_first_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x513E10);
static DWORD(__thiscall* cro_second_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x515310);
static DWORD(__thiscall* cro_third_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x516430);
static DWORD(__thiscall* cro_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x517480);

DWORD cro_setup_c(BYTE* nation_data) {
	*(WORD*)(nation_data + 0x32) = 24;
	*(BYTE*)(nation_data + 0x34) = 6;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 5;
	*(WORD*)(nation_data + 0x41) = 14;
	*(BYTE*)(nation_data + 0x43) = 4;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 5;
	BYTE selected = ((cm3_nations*)*(DWORD*)(nation_data))->NationLeagueSelected;
	*(DWORD*)(nation_data + 0xc) = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// HNL
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	cro_first_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF87C)]);
	nation_comps[i++] = (DWORD)pMem;
	// 1.NL
	pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	cro_second_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF880)]);
	nation_comps[i++] = (DWORD)pMem;
	// 2.NL
	pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	cro_third_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF8AC)]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	cro_cup_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF898)]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = 0;
	create_message_box("hi", "hi :)", false);
	return 1;
}

void setup_cro_nation() {
	WriteDWORD(0x667C00 + 6, (DWORD)&cro_setup_c);
}