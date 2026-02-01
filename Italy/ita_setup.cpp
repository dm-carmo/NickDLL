#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "ita_ser_a.h"
#include "ita_ser_b.h"
#include "ita_ser_c.h"
#include "ita_cup.h"
#include "ita_c_cup.h"
#include "ita_c_supercup.h"
#include "ita_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* ita_ser_a_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x6406D0);
static DWORD(__thiscall* ita_supercup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x65F670);

DWORD ita_setup_c(BYTE* nation_data) {
	*(WORD*)(nation_data + 0x32) = 6;
	*(BYTE*)(nation_data + 0x34) = 8;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 6;
	*(WORD*)(nation_data + 0x41) = 8;
	*(BYTE*)(nation_data + 0x43) = 5;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 6;
	BYTE selected = ((cm3_nations*)*(DWORD*)(nation_data))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(DWORD*)(nation_data + 0xc) = 7;
	}
	else { // C2 selected, not used for now
		*(DWORD*)(nation_data + 0xc) = 7;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Serie A
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	ita_ser_a_setup(pMem, *current_year, &(*club_comps)[ITA_SERIE_A_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Serie B
	pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	ita_ser_b_init(pMem, *current_year, &(*club_comps)[ITA_SERIE_B_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	ita_ser_c_init(pMem, *current_year, &(*club_comps)[ITA_SERIE_C_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// not used for now
	}
	// Coppa Italia
	pMem = (BYTE*)sub_944CF1_operator_new(0xB4);
	ita_cup_init(pMem, *current_year, &(*club_comps)[ITA_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Supercoppa Italia
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ita_supercup_setup(pMem, *current_year, &(*club_comps)[ITA_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Coppa Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xB4);
	ita_c_cup_init(pMem, *current_year, &(*club_comps)[ITA_SERIE_C_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Supercoppa Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ita_c_supercup_init(pMem, *current_year, &(*club_comps)[ITA_C1_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[ITA_SUPER_CUP_9CF()];
	return 1;
}

void setup_ita_nation() {
	WriteDWORD(0x668449 + 6, (DWORD)&ita_setup_c);
	WriteBytes(0x66A042, 1, 0xEB); // hide Serie C2 from league select menu
	setup_ita_ser_a();
	setup_ita_ser_b();
	setup_ita_ser_c();
	setup_ita_cup();
	setup_ita_c_cup();
	setup_ita_c_supercup();
	setup_ita_awards();
}