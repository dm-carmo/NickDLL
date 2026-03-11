#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "nir_premier.h"
#include "nir_first.h"
#include "nir_second.h"
#include "nir_cup.h"
#include "nir_league_cup.h"
#include "nir_charity.h"

static DWORD(__thiscall* nir_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x78a5b0);
static DWORD(__thiscall* nir_charity_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x789df0);

DWORD nir_setup_c(playable_nation_data* nation_data) {
	// contract start date?
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	// contract end date?
	nation_data->contract_end_day = 6;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 6;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nir_premier_init(pMem, *current_year, get_comp(NIR_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nir_first_init(pMem, *current_year, get_comp(NIR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nir_second_init(pMem, *current_year, get_comp(NIR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	nir_cup_setup(pMem, *current_year, get_comp(NIR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	nir_league_cup_init(pMem, *current_year, get_comp(NIR_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	nir_charity_setup(pMem, *current_year, get_comp(NIR_CHARITY_SHIELD_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(NIR_CHARITY_SHIELD_9CF());
	return 1;
}

void setup_nir_nation()
{
	WriteDWORD(0x668629 + 6, (DWORD)&nir_setup_c);
	setup_nir_premier();
	setup_nir_first();
	setup_nir_second();
	setup_nir_cup();
	setup_nir_league_cup();
	setup_nir_charity();
}

void n_ireland_restructure() {
	cm3_club_comps* nir_premier = get_comp(NIR_PREMIER_9CF());
	cm3_club_comps* nir_first = get_comp(NIR_FIRST_9CF());
	cm3_club_comps* nir_second = get_comp(NIR_SECOND_9CF());
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	vector<string> d1_clubs = {
		"Bangor FC",
		"Carrick Rangers FC",
	};
	vector<string> d2_clubs = {
		"Ballinamallard United FC",
		"Newington FC",
		"Queen's University Belfast AFC",
		"Warrenpoint Town FC",
	};
	vector<string> d3_clubs = {
		"Strabane Athletic FC",
	};
	vector<string> lower_clubs = {
		"Tobermore United FC",
		"Lurgan Celtic FC",
	};

	for (string s : d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nir_premier;
	}
	for (string s : d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nir_first;
	}
	for (string s : d3_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nir_second;
	}
	for (string s : lower_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = a_lower;
	}
}