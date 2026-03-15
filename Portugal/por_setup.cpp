#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "por_first.h"
#include "por_second.h"
#include "por_third.h"
#include "por_fourth.h"
#include "por_cup.h"
#include "por_league_cup.h"
#include "por_super.h"
#include "por_awards.h"

static DWORD(__thiscall* por_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7CD980);
static DWORD(__thiscall* por_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7D2E40);

DWORD por_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 6;
	
	nation_data->contract_end_day = 10;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 6;
	}
	else {
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Liga 1
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	por_first_init(pMem, *current_year, get_comp(POR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Liga 2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	por_second_init(pMem, *current_year, get_comp(POR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Liga 3
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	por_third_init(pMem, *current_year, get_comp(POR_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Campeonato de Portugal
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		por_fourth_init(pMem, *current_year, get_comp(POR_FOURTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	por_cup_setup(pMem, *current_year, get_comp(POR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	por_league_cup_init(pMem, *current_year, get_comp(POR_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	por_super_setup(pMem, *current_year, get_comp(POR_SUPER_CUP_9CF()));
	get_comp(POR_SUPER_CUP_9CF())->ClubCompBackgroundColour = get_colour(COLOUR_ORANGE_1_9CF());
	get_comp(POR_SUPER_CUP_9CF())->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(POR_SUPER_CUP_9CF());
	return 1;
}

void setup_por_nation()
{
	WriteDWORD(0x6688D6 + 6, (DWORD)&por_setup_c);
	setup_por_first();
	setup_por_second();
	setup_por_third();
	setup_por_fourth();
	setup_por_cup();
	setup_por_league_cup();
	setup_por_super();
	setup_por_awards();

	WriteNOP(0x7cda4a, 7);
}

void portugal_restructure() {
	cm3_staff_comps* data = &(*awards)[POR_THIRD_MANAGER_OF_YEAR_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_PORTUGAL_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 2;
	}

	cm3_club_comps* por_third = get_comp(POR_THIRD_9CF());
	por_third->ClubCompReputation = 6;
	cm3_club_comps* por_third_a = get_comp(POR_THIRD_A_9CF());
	por_third_a->ClubCompReputation = 6;
	cm3_club_comps* por_third_b = get_comp(POR_THIRD_B_9CF());
	por_third_b->ClubCompReputation = 6;
	cm3_club_comps* por_fourth = get_comp(POR_FOURTH_9CF());
	cm3_club_comps* por_fourth_a = get_comp(POR_FOURTH_A_9CF());
	por_fourth_a->ClubCompReputation = 3;
	cm3_club_comps* por_fourth_b = get_comp(POR_FOURTH_B_9CF());
	por_fourth_b->ClubCompNation = get_country(NATION_PORTUGAL_9CF());
	por_fourth_b->ClubCompContinent = find_continent("Europe");
	por_fourth_b->ClubCompReputation = 3;
	cm3_club_comps* por_fourth_c = get_comp(POR_FOURTH_C_9CF());
	por_fourth_c->ClubCompNation = get_country(NATION_PORTUGAL_9CF());
	por_fourth_c->ClubCompContinent = find_continent("Europe");
	por_fourth_c->ClubCompReputation = 3;
	cm3_club_comps* por_fourth_d = get_comp(POR_FOURTH_D_9CF());
	por_fourth_d->ClubCompNation = get_country(NATION_PORTUGAL_9CF());
	por_fourth_d->ClubCompContinent = find_continent("Europe");
	por_fourth_d->ClubCompReputation = 3;
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	vector<cm3_clubs*> club_list = find_clubs_of_comp(POR_THIRD_A_9CF());
	for (cm3_clubs* c : club_list) {
		c->ClubDivision = a_lower;
	}
	club_list = find_clubs_of_comp(POR_THIRD_B_9CF());
	for (cm3_clubs* c : club_list) {
		c->ClubDivision = a_lower;
	}
	club_list = find_clubs_of_comp(POR_FOURTH_9CF());
	for (cm3_clubs* c : club_list) {
		c->ClubDivision = a_lower;
	}
	club_list = find_clubs_of_comp(POR_FOURTH_A_9CF());
	for (cm3_clubs* c : club_list) {
		c->ClubDivision = a_lower;
	}

	vector<string> liga3a_clubs = {
		"CD Trofense",
		"Amarante FC",
		"Vitória Guimarães SC B",
		"Sporting Clube de Braga B",
		"Varzim SC",
		"USC Paredes",
		"AD Fafe",
		"AD Marco 09",
		"AD Sanjoanense",
		"SC São João de Ver",
	};
	vector<string> liga3b_clubs = {
		"CF Os Belenenses",
		"CD Mafra",
		"Académica Coimbra",
		"Atlético CP",
		"Caldas SC",
		"Amora FC",
		"UD Santarém",
		"SU 1º Dezembro",
		"Associação Lusitano de Évora 1911",
		"SC Covilhã",
	};
	vector<string> cdpa_clubs = {
		"AD Limianos",
		"GD Bragança",
		"GD Chaves Satelite",
		"FC Tirsense",
		"SC Mirandela",
		"CD Celoricense",
		"SC Vianense",
		"AR São Martinho",
		"AD Camacha",
		"Brito SC",
		"Vilaverdense FC",
		"AD Machico",
		"Desportivo Monção",
		"Clube Sport Marítimo B", // Ribeira Brava
	};
	vector<string> cdpb_clubs = {
		"Rebordosa AC",
		"Leça FC",
		"AC Vila Meã",
		"FC Alpendorada",
		"SC Salgueiros",
		"Florgrade FC",
		"CF União Lamas",
		"CD Cinfães",
		"SC Beira-Mar",
		"SC Vila Real",
		"Anadia FC",
		"Aparecida FC",
		"GD Resende",
		"CD Gouveia",
	};
	vector<string> cdpc_clubs = {
		"GD Vitória Sernache",
		"Benfica Castelo Branco",
		"Associação Naval 1893",
		"FC Oliveira do Hospital",
		"UD Serra",
		"Mortágua FC",
		"GD Peniche",
		"JD Lajense",
		"CD Fátima",
		"CF Os Marialvas",
		"Eléctrico FC",
		"SC Lusitânia dos Açores",
		"AC Marinhense",
		"GD Samora Correia",
	};
	vector<string> cdpd_clubs = {
		"AC Malveira",
		"Juventude Évora SC",
		"FC Alverca B",
		"GC Alcochetense",
		"FC Serpa",
		"Louletano DC",
		"Clube Oriental Lissabon",
		"O Elvas CAD",
		"GD Lagoa",
		"Portimonense SC",
		"SU Sintrense",
		"LGC Moncarapachense",
		"CF Vasco da Gama",
		"UF Comércio e Indústria",
	};

	for (string s : liga3a_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = por_third;
		club->ClubReserveDivision = por_third_a;
	}
	for (string s : liga3b_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = por_third;
		club->ClubReserveDivision = por_third_b;
	}
	for (string s : cdpa_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = por_fourth;
		club->ClubReserveDivision = por_fourth_a;
	}
	for (string s : cdpb_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = por_fourth;
		club->ClubReserveDivision = por_fourth_b;
	}
	for (string s : cdpc_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = por_fourth;
		club->ClubReserveDivision = por_fourth_c;
	}
	for (string s : cdpd_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = por_fourth;
		club->ClubReserveDivision = por_fourth_d;
	}

	cm3_club_comps* por_league_cup = get_comp(POR_LEAGUE_CUP_9CF());
	por_league_cup->ClubCompNation = get_country(NATION_PORTUGAL_9CF());
	por_league_cup->ClubCompContinent = find_continent("Europe");
	por_league_cup->ClubCompReputation = 7;
}