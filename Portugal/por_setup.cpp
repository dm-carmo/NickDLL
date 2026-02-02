#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>


static DWORD(__thiscall* por_first_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7CE720);
static DWORD(__thiscall* por_second_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7D0950);
static DWORD(__thiscall* por_second_b_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7D1920);
static DWORD(__thiscall* por_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7CD980);
static DWORD(__thiscall* por_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7D2E40);

DWORD por_setup_c(BYTE* nation_data) {
	*(WORD*)(nation_data + 0x32) = 19;
	*(BYTE*)(nation_data + 0x34) = 7;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 6;
	*(WORD*)(nation_data + 0x41) = 8;
	*(BYTE*)(nation_data + 0x43) = 5;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 6;
	BYTE selected = ((cm3_nations*)*(DWORD*)(nation_data))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(DWORD*)(nation_data + 0xc) = 4;
	}
	else {
		*(DWORD*)(nation_data + 0xc) = 5;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Liga 1
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	por_first_setup(pMem, *current_year, &(*club_comps)[POR_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Liga 2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	por_second_setup(pMem, *current_year, &(*club_comps)[POR_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Liga 3
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		por_second_b_setup(pMem, *current_year, &(*club_comps)[POR_SECOND_B_9CF()]);
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	por_cup_setup(pMem, *current_year, &(*club_comps)[POR_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	por_super_setup(pMem, *current_year, &(*club_comps)[POR_SUPER_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[POR_SUPER_CUP_9CF()];
	return 1;
}

void setup_por_nation()
{
	WriteDWORD(0x6688D6 + 6, (DWORD)&por_setup_c);
}
