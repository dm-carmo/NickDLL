#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "usa_mls.h"
#include "usa_champ.h"
#include "usa_cup.h"
#include "usa_awards.h"

static DWORD(__thiscall* usa_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x90AEB0);

DWORD usa_setup_c(BYTE* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	*(WORD*)(nation_data + 0x32) = 22;
	*(BYTE*)(nation_data + 0x34) = 2;
	*(WORD*)(nation_data + 0x35) = start_year;
	*(WORD*)(nation_data + 0x37) = 5;
	*(WORD*)(nation_data + 0x41) = 6;
	*(BYTE*)(nation_data + 0x43) = 0;
	*(WORD*)(nation_data + 0x44) = start_year;
	*(WORD*)(nation_data + 0x46) = 2;
	*(DWORD*)(nation_data + 0xc) = 3;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// MLS
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	usa_mls_init(pMem, start_year, &(*club_comps)[USA_MLS_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Championship
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	usa_champ_init(pMem, start_year, &(*club_comps)[USA_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	usa_cup_setup(pMem, start_year, &(*club_comps)[USA_OPEN_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = start_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = 0;
	return 1;
}

void setup_usa_nation() {
	WriteDWORD(0x668F51 + 6, (DWORD)&usa_setup_c);
	setup_usa_mls();
	setup_usa_champ();
	setup_usa_cup();
	setup_usa_awards();
	// Start date
	WriteBytes(0x668fa0, 1, February);
	WriteBytes(0x668fa2, 1, 20);
	WriteBytes(0x66900f, 3, 0x6a, 0x0, 0x57);
}