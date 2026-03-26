#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "pol_first.h"
#include "pol_second.h"
#include "pol_third.h"
#include "pol_cup.h"
#include "pol_super.h"
#include "pol_awards.h"

static DWORD(__thiscall* pol_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7C7D80);
static DWORD(__thiscall* pol_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7CC920);

DWORD pol_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 17;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	
	nation_data->contract_end_day = 3;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Ekstraklasa
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	pol_first_init(pMem, *current_year, get_comp(POL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// I Liga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	pol_second_init(pMem, *current_year, get_comp(POL_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// II Liga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	pol_third_init(pMem, *current_year, get_comp(POL_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	pol_cup_setup(pMem, *current_year, get_comp(POL_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	pol_super_setup(pMem, *current_year, get_comp(POL_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(POL_SUPER_CUP_9CF());
	return 1;
}

void setup_pol_nation()
{
	WriteDWORD(0x6687E0 + 6, (DWORD)&pol_setup_c);
	setup_pol_first();
	setup_pol_second();
	setup_pol_third();
	setup_pol_cup();
	setup_pol_super();
	setup_pol_awards();
	// Start date
	WriteBytes(0x66882C, 1, 27);

	WriteNOP(0x7c7e52, 7);
}

void poland_restructure() {
	cm3_club_comps* pol_first = get_comp(POL_FIRST_9CF());
	cm3_club_comps* pol_third = get_comp(POL_THIRD_9CF());
	pol_third->ClubCompReputation = 4;
	cm3_club_comps* pol_lower = get_comp(POL_LOWER_9CF());
	pol_lower->ClubCompNation = get_country(NATION_POLAND_9CF());
	pol_lower->ClubCompContinent = get_continent(EUROPE_9CF());
	pol_lower->ClubCompReputation = 2;

	vector<cm3_clubs*> clubs = find_clubs_of_comp(pol_third->ClubCompID);
	for (cm3_clubs* c : clubs) {
		c->ClubDivision = pol_lower;
	}

	vector<string> d1_clubs = {
		"Bruk-Bet Termalica Nieciecza",
		"Piast Gliwice",
	};
	vector<string> d3_clubs = {
		"Chojniczanka Chojnice",
		"GKS Jastrzebie",
		"Hutnik Krakow",
		"KKS 1925 Kalisz",
		"LKS Lodz II",
		"Olimpia Grudziadz",
		"Podbeskidzie Bielsko-Biala",
		"Podhale Nowy Targ",
		"Rekord Bielsko-Biala",
		"Resovia Rzeszow",
		"Sandecja Nowy Sacz",
		"Slask Wroclaw II",
		"Sokol Kleczew",
		"Stal Stalowa Wola",
		"Swit Szczecin",
		"Unia Skierniewice",
		"Warta Poznan",
		"Zaglebie Sosnowiec",
	};

	for (string s : d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = pol_first;
	}
	for (string s : d3_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = pol_third;
	}
}