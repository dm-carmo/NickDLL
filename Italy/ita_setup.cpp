#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "ita_ser_a.h"
#include "ita_ser_b.h"
#include "ita_ser_c.h"
#include "ita_cup.h"
#include "ita_super.h"
#include "ita_c_cup.h"
#include "ita_c_supercup.h"
#include "ita_awards.h"

static DWORD(__thiscall* ita_supercup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x65F670);

DWORD ita_setup_c(playable_nation_data* nation_data) {
	// contract start date?
	nation_data->contract_start_day = 6;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 6;
	// contract end date?
	nation_data->contract_end_day = 8;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 7;
	}
	else { // C2 selected, not used for now
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Serie A
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ita_ser_a_init(pMem, *current_year, get_comp(ITA_SERIE_A_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Serie B
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ita_ser_b_init(pMem, *current_year, get_comp(ITA_SERIE_B_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xEF);
	ita_ser_c_init(pMem, *current_year, get_comp(ITA_SERIE_C_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// not used for now
	}
	// Coppa Italia
	pMem = (BYTE*)sub_944CF1_operator_new(0xB4);
	ita_cup_init(pMem, *current_year, get_comp(ITA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercoppa Italia
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ita_supercup_setup(pMem, *current_year, get_comp(ITA_SUPER_CUP_9CF()));
	get_comp(ITA_SUPER_CUP_9CF())->ClubCompBackgroundColour = get_colour(COLOUR_BLUE_4_9CF());
	get_comp(ITA_SUPER_CUP_9CF())->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	nation_comps[i++] = (DWORD)pMem;
	// Coppa Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xB4);
	ita_c_cup_init(pMem, *current_year, get_comp(ITA_SERIE_C_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercoppa Serie C
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ita_c_supercup_init(pMem, *current_year, get_comp(ITA_C1_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(ITA_SUPER_CUP_9CF());
	return 1;
}

void setup_ita_nation() {
	WriteDWORD(0x668449 + 6, (DWORD)&ita_setup_c);
	setup_ita_ser_a();
	setup_ita_ser_b();
	setup_ita_ser_c();
	setup_ita_cup();
	setup_ita_super();
	setup_ita_c_cup();
	setup_ita_c_supercup();
	setup_ita_awards();
	// more loans allowed
	WriteBytes(0x6618a4, 1, 9);
	WriteDWORD(0x6618ba, 0x9C44D4);
}

void italy_restructure() {
	cm3_club_comps* serie_c = get_comp(ITA_SERIE_C_9CF());
	serie_c->ClubCompNation = get_country(NATION_ITALY_9CF());
	serie_c->ClubCompContinent = find_continent("Europe");
	serie_c->ClubCompReputation = 7;

	cm3_club_comps* serie_c_a = get_comp(ITA_SERIE_C_A_9CF());
	serie_c_a->ClubCompReputation = 7;

	cm3_club_comps* serie_c_b = get_comp(ITA_SERIE_C_B_9CF());
	serie_c_b->ClubCompReputation = 7;

	cm3_club_comps* serie_c_c = get_comp(ITA_SERIE_C_C_9CF());
	serie_c_c->ClubCompNation = get_country(NATION_ITALY_9CF());
	serie_c_c->ClubCompContinent = find_continent("Europe");
	serie_c_c->ClubCompReputation = 7;

	vector<cm3_clubs*> orig_clubs = find_clubs_of_comp(ITA_SERIE_C_A_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(ITA_SERIE_D_9CF());
	orig_clubs = find_clubs_of_comp(ITA_SERIE_C_B_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(ITA_SERIE_D_9CF());
	orig_clubs = find_clubs_of_comp(ITA_SERIE_C2_A_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(ITA_SERIE_D_9CF());
	orig_clubs = find_clubs_of_comp(ITA_SERIE_C2_B_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(ITA_SERIE_D_9CF());
	orig_clubs = find_clubs_of_comp(ITA_SERIE_C2_C_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(ITA_SERIE_D_9CF());
	vector<string> c_a_clubs = {
		"UC AlbinoLeffe",
		"Alcione Milano",
		"Arzignano Valchiampo",
		"Union Brescia",
		"AS Cittadella",
		"Dolomiti Bellunesi",
		"AS Giana Erminio",
		"Inter U23",
		"Calcio Lecco 1912",
		"FC Lumezzane",
		"Novara FC",
		"CPR Ospitaletto",
		"US Pergolettese 1932",
		"Aurora Pro Patria",
		"FC Pro Vercelli 1892",
		"AC Renate",
		"AC Trento",
		"US Triestina",
		"LR Vicenza",
		"Virtusvecomp Verona"
	};
	vector<string> c_b_clubs = {
		"SS Arezzo",
		"Ascoli Calcio",
		"Bra",
		"Campobasso FC",
		"AC Carpi",
		"Forlì FC",
		"AS Gubbio 1910",
		"Guidonia Montecelio 1937 FC",
		"Juventus Next Gen",
		"US Livorno 1915",
		"Milan Futuro",
		"AC Perugia Calcio",
		"US Pianese",
		"Pineto Calcio",
		"US Città di Pontedera",
		"Ravenna FC",
		"US Sambenedettese",
		"Ternana Calcio",
		"SEF Torres 1903",
		"Vis Pesaro 1898"
	};
	vector<string> c_c_clubs = {
		"AZ Picerno",
		"ASD Team Altamura",
		"Atalanta U23",
		"Benevento Calcio",
		"Casarano Calcio",
		"Casertana FC",
		"Catania FC",
		"Cavese 1919",
		"Audace Cerignola",
		"Cosenza Calcio",
		"FC Crotone",
		"Calcio Foggia 1920",
		"Giugliano Calcio 1928",
		"Latina Calcio 1932",
		"SS Monopoli 1966",
		"Potenza Calcio",
		"US Salernitana 1919",
		"Siracusa Calcio",
		"Sorrento 1945",
		"FC Trapani 1905"
	};

	cm3_club_comps* c_a = get_comp(ITA_SERIE_C_A_9CF());
	cm3_club_comps* c_b = get_comp(ITA_SERIE_C_B_9CF());
	cm3_club_comps* c_c = get_comp(ITA_SERIE_C_C_9CF());
	for (string s : c_a_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = serie_c;
		club->ClubReserveDivision = c_a;
	}
	for (string s : c_b_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = serie_c;
		club->ClubReserveDivision = c_b;
	}
	for (string s : c_c_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = serie_c;
		club->ClubReserveDivision = c_c;
	}
}