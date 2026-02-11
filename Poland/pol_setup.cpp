#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "pol_first.h"
#include "pol_second.h"
#include "pol_cup.h"
#include "pol_super.h"

static DWORD(__thiscall* pol_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7C7D80);
static DWORD(__thiscall* pol_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7CC920);

DWORD pol_setup_c(BYTE* nation_data) {
	// contract start date?
	*(WORD*)(nation_data + 0x32) = 17;
	*(BYTE*)(nation_data + 0x34) = July;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 5;
	// contract end date?
	*(WORD*)(nation_data + 0x41) = 3;
	*(BYTE*)(nation_data + 0x43) = June;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 5;
	*(DWORD*)(nation_data + 0xc) = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Ekstraklasa
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	pol_first_init(pMem, *current_year, &(*club_comps)[POL_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// I Liga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	pol_second_init(pMem, *current_year, &(*club_comps)[POL_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	pol_cup_setup(pMem, *current_year, &(*club_comps)[POL_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	pol_super_setup(pMem, *current_year, &(*club_comps)[POL_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[POL_SUPER_CUP_9CF()];
	return 1;
}

void setup_pol_nation()
{
	WriteDWORD(0x6687E0 + 6, (DWORD)&pol_setup_c);
	setup_pol_first();
	setup_pol_second();
	setup_pol_cup();
	setup_pol_super();
}
