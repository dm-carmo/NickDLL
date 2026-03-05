#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "den_premier.h"
#include "den_first.h"
#include "den_second.h"
#include "den_third.h"
#include "den_cup.h"
#include "den_awards.h"

static DWORD(__thiscall* den_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5509B0);

DWORD den_setup_c(playable_nation_data* nation_data) {
	// contract start date?
	nation_data->contract_start_day = 14;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 6;
	// contract end date?
	nation_data->contract_end_day = 14;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Superliga
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	den_premier_init(pMem, *current_year, get_comp(DEN_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 1
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	den_first_init(pMem, *current_year, get_comp(DEN_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	den_second_init(pMem, *current_year, get_comp(DEN_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 3
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	den_third_init(pMem, *current_year, get_comp(DEN_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	den_cup_setup(pMem, *current_year, get_comp(DEN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_den_nation()
{
	WriteDWORD(0x667CA1 + 6, (DWORD)&den_setup_c);
	setup_den_premier();
	setup_den_first();
	setup_den_second();
	setup_den_third();
	setup_den_cup();
	setup_den_awards();
}

void denmark_restructure() {
	cm3_club_comps* den_second = get_comp(DEN_SECOND_9CF());
	cm3_club_comps* den_third = get_comp(DEN_THIRD_9CF());
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());
	cm3_club_comps* reserve = get_comp(RESERVE_9CF());

	vector<string> d2_clubs = {
		"FC Helsingør",
		"FC Roskilde",
		"Naestved Boldklub",
		"Vendsyssel FF",
	};
	vector<string> d3_clubs = {
		"BK Frem",
		"FA 2000",
		"Holbaek B&I",
		"IF Lyseng",
		"Naesby Boldklub",
		"Nyköbing FC",
	};
	vector<string> lower_clubs = {
		"AB Taarnby",
		"Alleröd FK",
		"Avarta",
		"Avedøre IF",
		"B1909 Odense",
		"B1913 Odense",
		"Bagsvaerd BK",
		"Ballerup Skovlunde Fodbold",
		"Boldklubben 1908",
		"Boldklubben Herning Fremad",
		"Boldklubben Marienlyst",
		"Boldklubben Skjold",
		"Boldklubben Union",
		"Dalum IF",
		"FC Djursland",
		"FC Sydvest 05",
		"Fjordager IF",
		"Frederikssund IK",
		"Fremad Valby",
		"Gentofte VI",
		"Glostrup FK",
		"Greve IF",
		"Görslev IF",
		"Hedensted BK",
		"Herlev IF",
		"Holstebro Boldklub",
		"IF Skjold Birkerød",
		"Jammerbugt FC",
		"Karlslunde IF",
		"Kjellerup IF",
		"Kolding Boldklub",
		"Kopenhagen KFUM",
		"Köge Nord FC",
		"Ledöje-Smörum Fodbold",
		"Marstal/Rise IF",
		"Nörresundby FB",
		"Odense KS",
		"Otterup B&IK",
		"Ringköbing IF",
		"Ringsted IF",
		"Roskilde KFUM",
		"Skovshoved IF",
		"Slagelse B&I",
		"Svendborg fb - Oure FA",
		"Taastrup FC",
		"Tarup-Paarup IF",
		"Toreby-Graenge BK",
		"Tårnby FF",
		"Varde IF",
		"Vejlby-Risskov Idrætsklub",
		"Viby IF",
		"Vorup FB",
		"Young Boys FD",
		// needed for the cup
		"Aalborg BK Reserves",
		"Aarhus Fremad II",
		"Hobro IK II",
		"Horsens FS",
		"Naestved IF (Naestved BK II)",
	};
	vector<string> reserve_clubs = {
		"Aalborg BK Reserves",
		"Aarhus Fremad II",
		"Hobro IK II",
		"Horsens FS",
		"Naestved IF (Naestved BK II)",
	};

	for (string s : d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = den_second;
	}
	for (string s : d3_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = den_third;
	}
	for (string s : lower_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = a_lower;
	}
	for (string s : reserve_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		//club->ClubDivision = reserve;
	}
}