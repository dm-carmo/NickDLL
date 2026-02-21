#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "cro_first.h"
#include "cro_second.h"
#include "cro_third.h"
#include "cro_cup.h"
#include "cro_super.h"
#include "cro_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* cro_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x517480);

DWORD cro_setup_c(BYTE* nation_data) {
	// contract start date?
	*(WORD*)(nation_data + 0x32) = 1;
	*(BYTE*)(nation_data + 0x34) = August;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 5;
	// contract end date?
	*(WORD*)(nation_data + 0x41) = 16;
	*(BYTE*)(nation_data + 0x43) = June;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 5;
	*(DWORD*)(nation_data + 0xc) = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// HNL
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_first_init(pMem, *current_year, &(*club_comps)[CRO_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// 1.NL
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_second_init(pMem, *current_year, &(*club_comps)[CRO_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// 2.NL
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_third_init(pMem, *current_year, &(*club_comps)[CRO_THIRD_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	cro_cup_setup(pMem, *current_year, &(*club_comps)[CRO_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	cro_super_init(pMem, *current_year, &(*club_comps)[CRO_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[CRO_SUPER_CUP_9CF()];
	return 1;
}

void setup_cro_nation() {
	WriteDWORD(0x667C00 + 6, (DWORD)&cro_setup_c);
	setup_cro_first();
	setup_cro_second();
	setup_cro_third();
	setup_cro_cup();
	setup_cro_super();
	setup_cro_awards();
}