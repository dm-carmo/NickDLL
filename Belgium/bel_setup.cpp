#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "bel_first.h"
//#include "bel_second.h"
//#include "bel_cup.h"
//#include "bel_super.h"
//#include "bel_awards.h"

static DWORD(__thiscall* bel_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5F8820);

DWORD bel_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 1;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bel_first_init(pMem, *current_year, get_comp(BEL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
	//bel_second_init(pMem, *current_year, get_comp(BEL_SECOND_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	//bel_cup_init(pMem, *current_year, get_comp(BEL_CUP_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	//bel_super_setup(pMem, *current_year, get_comp(BEL_SUPER_CUP_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(BEL_SUPER_CUP_9CF());
	return 1;
}

void setup_bel_nation() {
	WriteDWORD(0x6679f9 + 6, (DWORD)&bel_setup_c);
	setup_bel_first();
	//setup_bel_second();
	//setup_bel_cup();
	//setup_bel_super();
	//setup_bel_awards();
}

void belgium_restructure() {
	cm3_club_comps* bel_second= get_comp(BEL_SECOND_9CF());

	vector<string> d2_clubs = {
		"Beerschot VA",
		"KV Kortrijk",
	};

	for (string s : d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bel_second;
	}
}