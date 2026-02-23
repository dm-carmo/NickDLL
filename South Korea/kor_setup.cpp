#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "kor_first.h"
#include "kor_second.h"
#include "kor_cup.h"
#include "kor_super.h"
#include "kor_awards.h"

static DWORD(__thiscall* kor_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x66A460);
static DWORD(__thiscall* kor_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x66D820);

DWORD kor_setup_c(BYTE* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	*(WORD*)(nation_data + 0x32) = 1;
	*(BYTE*)(nation_data + 0x34) = February;
	*(WORD*)(nation_data + 0x35) = start_year;
	*(WORD*)(nation_data + 0x37) = 6;
	// contract end date?
	*(WORD*)(nation_data + 0x41) = 20;
	*(BYTE*)(nation_data + 0x43) = December;
	*(WORD*)(nation_data + 0x44) = start_year;
	*(WORD*)(nation_data + 0x46) = 5;
	*(DWORD*)(nation_data + 0xc) = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// K1
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	kor_first_init(pMem, start_year, &(*club_comps)[KOR_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// K2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	kor_second_init(pMem, start_year, &(*club_comps)[KOR_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	kor_cup_setup(pMem, start_year, &(*club_comps)[KOR_FA_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	kor_super_setup(pMem, start_year, &(*club_comps)[KOR_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = start_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[KOR_SUPER_CUP_9CF()];
	return 1;
}

void setup_kor_nation() {
	WriteDWORD(0x668B99 + 6, (DWORD)&kor_setup_c);
	setup_kor_first();
	setup_kor_second();
	setup_kor_cup();
	setup_kor_super();
	setup_kor_awards();
	// Start date
	WriteBytes(0x668BE8, 1, February);
	WriteBytes(0x668BEA, 1, 14);
}