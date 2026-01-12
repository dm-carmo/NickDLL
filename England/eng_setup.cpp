#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "eng_third.h"
#include "eng_conf.h"
#include "eng_fa_cup.h"

static DWORD(__thiscall* eng_prm_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x573380);
static DWORD(__thiscall* eng_first_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x571680);
static DWORD(__thiscall* eng_second_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5754A0);
static DWORD(__thiscall* eng_third_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x576DD0);
static DWORD(__thiscall* eng_fa_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x56F040);
static DWORD(__thiscall* eng_league_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x56C2A0);
static DWORD(__thiscall* eng_charity_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x56D380);
static DWORD(__thiscall* eng_fa_trophy_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x570C00);
static DWORD(__thiscall* eng_league_trophy_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x56AA30);

DWORD eng_setup_c(BYTE* nation_data) {
	// 83374c
	// 1 arg: 0xb64150 for england
	*(WORD*)(nation_data + 0x37) = 5;
	*(WORD*)(nation_data + 0x32) = 10;
	*(BYTE*)(nation_data + 0x34) = 7;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x46) = 5;
	*(WORD*)(nation_data + 0x41) = 24;
	*(BYTE*)(nation_data + 0x43) = 4;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	BYTE selected = ((cm3_nations*)*(DWORD*)(nation_data))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(DWORD*)(nation_data + 0xc) = 8;
	}
	else {
		*(DWORD*)(nation_data + 0xc) = 10;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// Add the 2 missing teams to the National League in the first year only
	if (*current_year == 2025) {
		cm3_club_comps* nat_lge = find_club_comp("English National League");
		if (nat_lge) {
			cm3_clubs* club1 = find_club("Boston United");
			if (club1) {
				club1->ClubDivision = nat_lge;
			}
			cm3_clubs* club2 = find_club("Braintree Town");
			if (club2) {
				club2->ClubDivision = nat_lge;
			}
		}
	}
	// start calling each league's functions
	BYTE i = 0;
	// Premier League
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_prm_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF5BC]);
	nation_comps[i++] = (DWORD)pMem;
	// Championship
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_first_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF5C0]);
	nation_comps[i++] = (DWORD)pMem;
	// League One
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_second_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF5C4]);
	nation_comps[i++] = (DWORD)pMem;
	// League Two
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	//eng_third_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF5C8]);
	eng_third_init(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF5C8]);
	nation_comps[i++] = (DWORD)pMem;
	// National League
	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		eng_conf_init(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF69C]);
		nation_comps[i++] = (DWORD)pMem;
	}
	// FA Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB5);
	//eng_fa_cup_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF74C]);
	eng_fa_cup_init(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF74C]);
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB3);
	eng_league_cup_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF750]);
	nation_comps[i++] = (DWORD)pMem;
	// League Trophy
	/*pMem = (BYTE*)sub_944CF1_operator_new(0xBA);
	eng_league_trophy_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF758]);
	nation_comps[i++] = (DWORD)pMem;*/
	// Charity Shield
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	eng_charity_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF754]);
	nation_comps[i++] = (DWORD)pMem;
	// FA Trophy
	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
		eng_fa_trophy_setup(pMem, *current_year, &(*club_comps)[*(DWORD*)0x9CF6A0]);
		nation_comps[i++] = (DWORD)pMem;
	}
	BYTE* cm_date = new BYTE[4];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[*(DWORD*)0x9CF6A0];
	return 1;
}

void setup_eng_nation() {
	WriteDWORD(0x667D97 + 6, (DWORD)&eng_setup_c);
	setup_eng_third();
	setup_eng_conf();
	setup_eng_fa_cup();
}