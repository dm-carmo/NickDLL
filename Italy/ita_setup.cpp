#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "ita_ser_a.h"
#include "ita_ser_b.h"
#include "ita_ser_c.h"
#include "ita_cup.h"
#include "ita_c_cup.h"
#include "ita_awards.h"
#include <Helpers/new_league_ids.h>

static DWORD(__thiscall* ita_ser_a_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x6406D0);
static DWORD(__thiscall* ita_ser_b_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x645810);
static DWORD(__thiscall* ita_ser_c1a_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x64AA70);
static DWORD(__thiscall* ita_ser_c1b_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x64EC20);
static DWORD(__thiscall* ita_ser_c2a_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x652E90);
static DWORD(__thiscall* ita_ser_c2b_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x657350);
static DWORD(__thiscall* ita_ser_c2c_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x65B4E0);
static DWORD(__thiscall* ita_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x63E900);
static DWORD(__thiscall* ita_supercup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x65F670);
static DWORD(__thiscall* ita_c_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x63CC40);
static DWORD(__thiscall* ita_c_supercup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x63C5E0);

DWORD ita_setup_c(BYTE* nation_data) {
	*(BYTE*)(nation_data + 0x34) = 8;
	*(WORD*)(nation_data + 0x37) = 6;
	*(WORD*)(nation_data + 0x32) = 6;
	*(WORD*)(nation_data + 0x46) = 6;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x41) = 8;
	*(BYTE*)(nation_data + 0x43) = 5;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	BYTE selected = ((cm3_nations*)*(DWORD*)(nation_data))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(DWORD*)(nation_data + 0xc) = 8;
	}
	else {
		*(DWORD*)(nation_data + 0xc) = 11;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Serie A
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	ita_ser_a_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF570)]);
	nation_comps[i++] = (DWORD)pMem;
	// Serie B
	pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	ita_ser_b_init(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF574)]);
	nation_comps[i++] = (DWORD)pMem;
	// Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	ita_ser_c_init(pMem, *current_year, &(*club_comps)[serie_c_id]);
	nation_comps[i++] = (DWORD)pMem;
	/*
	// Serie C1/A
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ita_ser_c1a_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF578)]);
	nation_comps[i++] = (DWORD)pMem;
	// Serie C1/B
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ita_ser_c1b_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF57C)]);
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Serie C2/A
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		ita_ser_c2a_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF580)]);
		nation_comps[i++] = (DWORD)pMem;
		// Serie C2/B
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		ita_ser_c2b_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF584)]);
		nation_comps[i++] = (DWORD)pMem;
		// Serie C2/C
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		ita_ser_c2c_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF588)]);
		nation_comps[i++] = (DWORD)pMem;
	}
	*/
	// Coppa Italia
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ita_cup_init(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF71C)]);
	nation_comps[i++] = (DWORD)pMem;
	// Supercoppa Italia
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ita_supercup_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF724)]);
	nation_comps[i++] = (DWORD)pMem;
	// Coppa Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ita_c_cup_init(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF720)]);
	nation_comps[i++] = (DWORD)pMem;
	/*
	// Supercoppa Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ita_c_supercup_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF938)]);
	nation_comps[i++] = (DWORD)pMem;
	*/
	BYTE* cm_date = new BYTE[4];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[Get9CF(0x9CF724)];
	return 1;
}

void setup_ita_nation() {
	WriteDWORD(0x668449 + 6, (DWORD)&ita_setup_c);
	setup_ita_ser_a();
	setup_ita_ser_b();
	setup_ita_ser_c();
	setup_ita_cup();
	setup_ita_c_cup();
	setup_ita_awards();
}