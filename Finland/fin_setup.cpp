#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "fin_premier.h"
#include "fin_first.h"
#include "fin_second.h"
#include "fin_third.h"
#include "fin_cup.h"
#include "fin_awards.h"

static DWORD(__thiscall* fin_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x592250);

DWORD fin_setup_c(BYTE* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	*(WORD*)(nation_data + 0x32) = 1;
	*(BYTE*)(nation_data + 0x34) = March;
	*(WORD*)(nation_data + 0x35) = start_year;
	*(WORD*)(nation_data + 0x37) = 5;
	// contract end date?
	*(WORD*)(nation_data + 0x41) = 30;
	*(BYTE*)(nation_data + 0x43) = November;
	*(WORD*)(nation_data + 0x44) = start_year;
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
	// Veikkausliiga
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fin_premier_init(pMem, start_year, &(*club_comps)[FIN_PREMIER_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Ykkösliiga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fin_first_init(pMem, start_year, &(*club_comps)[FIN_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Ykkönen
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fin_second_init(pMem, start_year, &(*club_comps)[FIN_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Kakkonen
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		fin_third_init(pMem, start_year, &(*club_comps)[FIN_THIRD_9CF()]);
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	fin_cup_setup(pMem, start_year, &(*club_comps)[FIN_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = start_year;
	*(BYTE*)(nation_data + 0x1D) = 0;
	*(DWORD*)(nation_data + 0x26) = 0;
	return 1;
}

void setup_fin_nation()
{
	WriteDWORD(0x667E85 + 6, (DWORD)&fin_setup_c);
	setup_fin_premier();
	setup_fin_first();
	setup_fin_second();
	setup_fin_third();
	setup_fin_cup();
	setup_fin_awards();
	// Start date
	WriteBytes(0x667EE5, 1, April);
	WriteBytes(0x667EE7, 1, 4);
}
