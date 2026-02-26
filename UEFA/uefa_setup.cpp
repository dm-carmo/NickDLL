#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "uefa_champions_league.h"

static DWORD(__thiscall* uefa_champions_league_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5837C0);
static DWORD(__thiscall* uefa_europa_league_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x9022E0);
static DWORD(__thiscall* uefa_conference_league_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x632FB0);
static DWORD(__thiscall* uefa_super_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x57A100);

DWORD uefa_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	// contract start date?
	nation_data->contract_start_day = 23;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = -1;
	// contract end date?
	nation_data->contract_end_day = 20;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year;
	nation_data->f70 = 5;
	// call 6699D0 removed so the comps always load
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	uefa_champions_league_init(pMem, *current_year, get_comp(UEFA_CHAMPIONS_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB3);
	uefa_europa_league_setup(pMem, *current_year, get_comp(UEFA_EUROPA_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB6);
	uefa_conference_league_setup(pMem, *current_year, get_comp(UEFA_CONFERENCE_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	uefa_super_cup_setup(pMem, *current_year, get_comp(UEFA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 21, June, 2025, (DWORD*)-1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = 2025;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_uefa_continent() {
	WriteDWORD(0x667404 + 6, (DWORD)&uefa_setup_c);
	char* ucl = "Champions League";
	char* uel = "Europa League";
	WriteDWORD(0x494EA6 + 1, (DWORD)&ucl[0]);
	WriteDWORD(0x494E92 + 1, (DWORD)&uel[0]);
	WriteDWORD(0x494F0D, (DWORD)0x9CF6F0);
	char* ucl_abbrev = "UCL";
	char* uel_abbrev = "UEL";
	char* uecl_abbrev = "UECL";
	WriteDWORD(0x49C884 + 1, (DWORD)&ucl_abbrev[0]);
	WriteDWORD(0x49C8DE + 1, (DWORD)&uel_abbrev[0]);
	WriteDWORD(0x49C93C + 1, (DWORD)&uecl_abbrev[0]);
	WriteDWORD(0x49C94C, (DWORD)0x9CF6EC);
	//0049CCB0   . 83EC 0C        SUB ESP,0C => check how to remove this function! => maybe with below?
	WriteDWORD(0x633777, (DWORD)0x9CF6EC);
	WriteBytes(0x782ED5, 1, 0xeb);
	WriteBytes(0x77FD94, 6, 0xE9, 0x1C, 0x01, 0x00, 0x00, 0x90);
	WriteBytes(0x77FEB8, 6, 0xE9, 0xF9, 0x00, 0x00, 0x00, 0x90);
	WriteDWORD(0x85AA1A, (DWORD)0x9CF6EC);
	WriteDWORD(0x904ECB, (DWORD)0x9CF6EC);
	WriteDWORD(0x904F69, (DWORD)0x9CF6EC);
	WriteDWORD(0x90503F, (DWORD)0x9CF6EC);
	WriteDWORD(0x906190, (DWORD)0x9CF6EC);
	WriteDWORD(0x90609C, (DWORD)0x9CF6EC);

	setup_uefa_champions_league();
}