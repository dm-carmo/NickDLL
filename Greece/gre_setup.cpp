#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "gre_first.h"
#include "gre_second.h"
#include "gre_cup.h"
#include "gre_super.h"
//#include "gre_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* gre_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5ec040);

DWORD gre_setup_c(BYTE* nation_data) {
	// contract start date?
	*(WORD*)(nation_data + 0x32) = 10;
	*(BYTE*)(nation_data + 0x34) = August;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 5;
	// contract end date?
	*(WORD*)(nation_data + 0x41) = 31;
	*(BYTE*)(nation_data + 0x43) = May;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 5;
	*(DWORD*)(nation_data + 0xc) = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Super League
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	gre_first_init(pMem, *current_year, &(*club_comps)[GRE_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Super League 2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	gre_second_init(pMem, *current_year, &(*club_comps)[GRE_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	gre_cup_init(pMem, *current_year, &(*club_comps)[GRE_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	gre_super_setup(pMem, *current_year, &(*club_comps)[GRE_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[GRE_SUPER_CUP_9CF()];
	return 1;
}

void setup_gre_nation() {
	WriteDWORD(0x66817D + 6, (DWORD)&gre_setup_c);
	setup_gre_first();
	setup_gre_second();
	setup_gre_cup();
	setup_gre_super();
	//setup_gre_awards();
	//Bypass check for 14 teams in Greek leagues
	WriteBytes(0x8283b9, 1, 0xEB);
}