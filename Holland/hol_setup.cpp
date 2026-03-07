#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "hol_first.h"
#include "hol_second.h"
#include "hol_cup.h"
#include "hol_super.h"
#include "hol_awards.h"

static DWORD(__thiscall* hol_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5F8820);

DWORD hol_setup_c(playable_nation_data* nation_data) {
	// contract start date?
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	// contract end date?
	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Eredivisie
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	hol_first_init(pMem, *current_year, get_comp(HOL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Eerste Divisie
	pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
	hol_second_init(pMem, *current_year, get_comp(HOL_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	hol_cup_init(pMem, *current_year, get_comp(HOL_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	hol_super_setup(pMem, *current_year, get_comp(HOL_SUPER_CUP_9CF()));
	get_comp(HOL_SUPER_CUP_9CF())->ClubCompForegroundColour = 0;
	get_comp(HOL_SUPER_CUP_9CF())->ClubCompBackgroundColour = 0;
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(HOL_SUPER_CUP_9CF());
	return 1;
}

void setup_hol_nation() {
	WriteDWORD(0x668273 + 6, (DWORD)&hol_setup_c);
	setup_hol_first();
	setup_hol_second();
	setup_hol_cup();
	setup_hol_super();
	setup_hol_awards();
}

void holland_restructure() {
	cm3_club_comps* hol_second = get_comp(HOL_SECOND_9CF());

	vector<string> d2_clubs = {
		"AZ Alkmaar U21",
		"FC Utrecht U21"
	};
	for (string s : d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = hol_second;
	}
}