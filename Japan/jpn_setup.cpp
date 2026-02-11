#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "jpn_first.h"
#include "jpn_second.h"
#include "jpn_third.h"
#include "jpn_jfl.h"
#include "jpn_cup.h"
#include "jpn_league_cup.h"
#include "jpn_super.h"

static DWORD(__thiscall* jpn_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x661D30);
static DWORD(__thiscall* jpn_league_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x665380);
static DWORD(__thiscall* jpn_super_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x665D70);

DWORD jpn_setup_c(BYTE* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	*(WORD*)(nation_data + 0x32) = 1;
	*(BYTE*)(nation_data + 0x34) = February;
	*(WORD*)(nation_data + 0x35) = start_year;
	*(WORD*)(nation_data + 0x37) = 5;
	// contract end date?
	*(WORD*)(nation_data + 0x41) = 20;
	*(BYTE*)(nation_data + 0x43) = December;
	*(WORD*)(nation_data + 0x44) = start_year;
	*(WORD*)(nation_data + 0x46) = 5;
	BYTE selected = ((cm3_nations*)*(DWORD*)(nation_data))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(DWORD*)(nation_data + 0xc) = 6;
	}
	else {
		*(DWORD*)(nation_data + 0xc) = 7;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// J1
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	jpn_first_init(pMem, start_year, &(*club_comps)[JPN_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// J2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	jpn_second_init(pMem, start_year, &(*club_comps)[JPN_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// J3
	pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
	jpn_third_init(pMem, start_year, &(*club_comps)[JPN_THIRD_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// JFL
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		jpn_jfl_init(pMem, start_year, &(*club_comps)[JPN_JFL_9CF()]);
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	jpn_cup_setup(pMem, start_year, &(*club_comps)[JPN_EMPEROR_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	jpn_league_cup_setup(pMem, start_year, &(*club_comps)[JPN_LEAGUE_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	jpn_super_cup_setup(pMem, start_year, &(*club_comps)[JPN_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = start_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[JPN_SUPER_CUP_9CF()];
	return 1;
}

void setup_jpn_nation() {
	WriteDWORD(0x668533 + 6, (DWORD)&jpn_setup_c);
	setup_jpn_first();
	setup_jpn_second();
	setup_jpn_third();
	setup_jpn_jfl();
	setup_jpn_cup();
	setup_jpn_league_cup();
	setup_jpn_super();
	// Start date
	WriteBytes(0x668582, 1, February);
	WriteBytes(0x668584, 1, 14);
}