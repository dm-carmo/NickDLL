#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "ger_first.h"
#include "ger_second.h"
#include "ger_third.h"
#include "ger_regional.h"
#include "ger_cup.h"
#include "ger_super.h"
#include "ger_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* ger_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5D8C20);
static DWORD(__thiscall* ger_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x92B4B0);

DWORD ger_setup_c(BYTE* nation_data) {
	*(WORD*)(nation_data + 0x32) = 10;
	*(BYTE*)(nation_data + 0x34) = 7;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 5;
	*(WORD*)(nation_data + 0x41) = 14;
	*(BYTE*)(nation_data + 0x43) = 5;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 5;
	BYTE selected = ((cm3_nations*)*(DWORD*)(nation_data))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(DWORD*)(nation_data + 0xc) = 5;
	}
	else {
		*(DWORD*)(nation_data + 0xc) = 6;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Bundesliga
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_first_init(pMem, *current_year, &(*club_comps)[GER_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// 2. Bundesliga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_second_init(pMem, *current_year, &(*club_comps)[GER_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// 3. Liga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_third_init(pMem, *current_year, &(*club_comps)[GER_THIRD_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Regionalliga
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		ger_regional_init(pMem, *current_year, &(*club_comps)[GER_REGIONAL_9CF()]);
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ger_cup_setup(pMem, *current_year, &(*club_comps)[GER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ger_super_setup(pMem, *current_year, &(*club_comps)[GER_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[GER_SUPER_CUP_9CF()];
	return 1;
}

void setup_ger_nation()
{
	WriteDWORD(0x66807B + 6, (DWORD)&ger_setup_c);
	char* regionalliga_text = "Regionalliga";
	WriteDWORD(0x66A022 + 1, (DWORD)&regionalliga_text[0]);
	setup_ger_first();
	setup_ger_second();
	setup_ger_third();
	setup_ger_regional();
	setup_ger_cup();
	setup_ger_super();
	setup_ger_awards();
}
