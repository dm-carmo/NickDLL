#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "hol_first.h"
#include "hol_second.h"
#include "hol_cup.h"
#include "hol_super.h"

static DWORD(__thiscall* hol_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5F8820);

DWORD hol_setup_c(BYTE* nation_data) {
	// contract start date?
	*(WORD*)(nation_data + 0x32) = 1;
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
	// Eredivisie
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	hol_first_init(pMem, *current_year, &(*club_comps)[HOL_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Eerste Divisie
	pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
	hol_second_init(pMem, *current_year, &(*club_comps)[HOL_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	hol_cup_init(pMem, *current_year, &(*club_comps)[HOL_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	hol_super_setup(pMem, *current_year, &(*club_comps)[HOL_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[HOL_SUPER_CUP_9CF()];
	return 1;
}

void setup_hol_nation() {
	WriteDWORD(0x668273 + 6, (DWORD)&hol_setup_c);
	setup_hol_first();
	setup_hol_second();
	setup_hol_cup();
	setup_hol_super();
}