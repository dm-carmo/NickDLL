#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "den_premier.h"
#include "den_first.h"
#include "den_second.h"
#include "den_third.h"
#include "den_cup.h"
#include "den_awards.h"

static DWORD(__thiscall* den_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5509B0);

DWORD den_setup_c(BYTE* nation_data) {
	// contract start date?
	*(WORD*)(nation_data + 0x32) = 14;
	*(BYTE*)(nation_data + 0x34) = July;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 6;
	// contract end date?
	*(WORD*)(nation_data + 0x41) = 14;
	*(BYTE*)(nation_data + 0x43) = June;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 6;
	BYTE selected = ((cm3_nations*)*(DWORD*)(nation_data))->NationLeagueSelected;
	*(DWORD*)(nation_data + 0xc) = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Superliga
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	den_premier_init(pMem, *current_year, &(*club_comps)[DEN_PREMIER_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Division 1
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	den_first_init(pMem, *current_year, &(*club_comps)[DEN_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Division 2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	den_second_init(pMem, *current_year, &(*club_comps)[DEN_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Division 3
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	den_third_init(pMem, *current_year, &(*club_comps)[DEN_THIRD_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	den_cup_setup(pMem, *current_year, &(*club_comps)[DEN_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = 0;
	return 1;
}

void setup_den_nation()
{
	WriteDWORD(0x667CA1 + 6, (DWORD)&den_setup_c);
	setup_den_premier();
	setup_den_first();
	setup_den_second();
	setup_den_third();
	setup_den_cup();
	setup_den_awards();
}
