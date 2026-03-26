#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "spa_first.h"
#include "spa_second.h"
#include "spa_third.h"
#include "spa_fourth.h"
#include "spa_cup.h"
#include "spa_super.h"

static DWORD(__thiscall* spa_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x8586B0);

DWORD spa_setup_c(playable_nation_data* nation_data) {

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
		nation_data->num_of_comps = 5;
	}
	else {
		nation_data->num_of_comps = 6;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	spa_first_init(pMem, *current_year, get_comp(SPA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	spa_second_init(pMem, *current_year, get_comp(SPA_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	spa_third_init(pMem, *current_year, get_comp(SPA_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		spa_fourth_init(pMem, *current_year, get_comp(SPA_FOURTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	spa_cup_init(pMem, *current_year, get_comp(SPA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	spa_super_setup(pMem, *current_year, get_comp(SPA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(SPA_SUPER_CUP_9CF());
	return 1;
}

void setup_spa_nation()
{
	WriteDWORD(0x668c8f + 6, (DWORD)&spa_setup_c);
	setup_spa_first();
	setup_spa_second();
	setup_spa_third();
	setup_spa_fourth();
	setup_spa_cup();
	setup_spa_super();

	WriteNOP(0x84d036, 7);
	// disable offsets related to the inactive Spanish lower leagues
	WriteBytes(0x7E62FC, 1, 0xeb);
	WriteNOP(0x7e6f4a, 2);
	WriteNOP(0x4b070c, 2);
	WriteNOP(0x4c037d, 2);
	WriteNOP(0x4c03e0, 2);
}

void spain_restructure() {
	cm3_nations* spain = get_country(NATION_SPAIN_9CF());
	cm3_club_comps* spa_third = get_comp(SPA_THIRD_9CF());
	cm3_club_comps* spa_third_1 = get_comp(SPA_THIRD_G1_9CF());
	spa_third_1->ClubCompReputation = 8;
	cm3_club_comps* spa_third_2 = get_comp(SPA_THIRD_G2_9CF());
	spa_third_2->ClubCompReputation = 8;
	cm3_club_comps* spa_fourth = get_comp(SPA_FOURTH_9CF());
	cm3_club_comps* spa_fourth_1 = get_comp(SPA_FOURTH_G1_9CF());
	spa_fourth_1->ClubCompNation = spain;
	spa_fourth_1->ClubCompContinent = get_continent(EUROPE_9CF());
	spa_fourth_1->ClubCompReputation = 5;
	cm3_club_comps* spa_fourth_2 = get_comp(SPA_FOURTH_G2_9CF());
	spa_fourth_2->ClubCompNation = spain;
	spa_fourth_2->ClubCompContinent = get_continent(EUROPE_9CF());
	spa_fourth_2->ClubCompReputation = 5;
	cm3_club_comps* spa_fourth_3 = get_comp(SPA_FOURTH_G3_9CF());
	spa_fourth_3->ClubCompNation = spain;
	spa_fourth_3->ClubCompContinent = get_continent(EUROPE_9CF());
	spa_fourth_3->ClubCompReputation = 5;
	cm3_club_comps* spa_fourth_4 = get_comp(SPA_FOURTH_G4_9CF());
	spa_fourth_4->ClubCompNation = spain;
	spa_fourth_4->ClubCompContinent = get_continent(EUROPE_9CF());
	spa_fourth_4->ClubCompReputation = 5;
	cm3_club_comps* spa_fourth_5 = get_comp(SPA_FOURTH_G5_9CF());
	spa_fourth_5->ClubCompNation = spain;
	spa_fourth_5->ClubCompContinent = get_continent(EUROPE_9CF());
	spa_fourth_5->ClubCompReputation = 5;
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	for (DWORD id = 0x36; id < 0x3a; id++) {
		vector<cm3_clubs*> clubs = find_clubs_of_comp(id);
		for (cm3_clubs* c : clubs) {
			c->ClubDivision = a_lower;
		}
	}
	vector<cm3_clubs*> club_list = find_clubs_of_comp(SPA_FOURTH_9CF());
	for (cm3_clubs* c : club_list) {
		c->ClubDivision = a_lower;
	}

	cm3_clubs* castellon_b = find_club("C.D. Castellón B");
	if (castellon_b) {
		castellon_b->ClubNation = spain;
	}
	cm3_clubs* reus = find_club("CF Reus Deportiu");
	if (reus) {
		reus->ClubNation = spain;
	}

	vector<string> d3_1_clubs = {
		"Arenas Getxo Bilbao",
		"CD Arenteiro",
		"Real Avilés Industrial",
		"Barakaldo C.F.",
		"Athletic Club de Bilbao B",
		"CP Cacereño",
		"Real Club Celta de Vigo B",
		"CD Guadalajara",
		"CD Lugo",
		"C.P. Mérida",
		"Club Atlético Osasuna B",
		"C.D. Ourense",
		"SD Ponferradina",
		"Pontevedra CF",
		"Racing Ferrol",
		"Real Madrid C.F. B",
		"CF Talavera de la Reina",
		"C.D. Tenerife",
		"Unionistas CF",
		"Zamora CF",
	};
	vector<string> d3_2_clubs = {
		"AD Alcorcón",
		"Algeciras CF",
		"Antequera CF",
		"Atlético de Madrid B",
		"Atlético Sanluqueño CF",
		"Real Betis Balompié B",
		"FC Cartagena",
		"CD Eldense",
		"CE Europa",
		"Gimnàstic de Tarragona",
		"Hércules CF",
		"UD Ibiza",
		"Juventud Torremolinos CF",
		"Marbella FC",
		"Real Murcia C.F.",
		"CE Sabadell FC",
		"Sevilla C.F. B",
		"SD Tarazona",
		"CD Teruel",
		"Villarreal CF B",
	};
	vector<string> d4_1_clubs = {
		"Atlético Astorga",
		"Real Ávila CF",
		"Bergantiños FC",
		"Burgos CF Promesas",
		"Coruxo FC",
		"Deportivo de La Coruña B",
		"Gimnástica Segoviana CF",
		"UP Langreo",
		"CD Lealtad",
		"Marino Luanco",
		"CD Numancia",
		"S.D. Compostela", // replaces UD Ourense
		"Real Oviedo C.F. B",
		"Rayo Cantabria",
		"U.D. Salamanca",
		"UD Sámano",
		"SD Sarriana",
		"Real Valladolid B",
	};
	vector<string> d4_2_clubs = {
		"Deportivo Alavés B",
		"CD Alfaro",
		"S.D. Amorebieta",
		"Baskonia C.D.",
		"S.D. Beasaín",
		"Real Zaragoza B",
		"CD Ebro",
		"S.D. Éibar B",
		"SD Ejea",
		"Gernika Club",
		"SD Logroñés",
		"UD Logroñés",
		"UD Mutilvera",
		"Náxara CD",
		"Real Unión de Irún",
		"Sestao River Club",
		"CD Tudelano",
		"Utebo FC",
	};
	vector<string> d4_3_clubs = {
		"CD Alcoyano",
		"CE Andratx",
		"CE Atlètic Lleida",
		"CD Atlético Baleares",
		"UD Barbastro",
		"F.C. Barcelona B",
		"C.D. Castellón B",
		"R.C.D. Espanyol B",
		"Girona FC B",
		"CD Ibiza Islas Pitiusas",
		"UE Olot",
		"UD Poblense",
		"UE Cornellà", // replaces Porreres
		"CF Reus Deportiu",
		"UE Sant Andreu",
		"Terrassa FC",
		"Torrent CF",
		"Valencia C.F. B",
	};
	vector<string> d4_4_clubs = {
		"Águilas FC",
		"UD Almería B",
		"Club Atlético Antoniano",
		"Málaga C.F. B",
		"CD Estepona FS",
		"Extremadura C.F.",
		"Real Jaén CF",
		"Linares Deportivo",
		"CF Lorca Deportiva",
		"FC La Unión Atlético",
		"UD Melilla",
		"Deportiva Minera",
		"Real Balompédica Linense", // replaces Puerte Genil
		"Recreativo de Huelva",
		"UCAM Murcia CF",
		"Xerez CD",
		"Xerez Deportivo FC",
		"Yeclano Deportivo",
	};
	vector<string> d4_5_clubs = {
		"RSD Alcalá",
		"UB Conquense",
		"CD Coria",
		"Elche C.F. B",
		"CF Fuenlabrada",
		"Getafe CF B",
		"CF Intercity",
		"U.D. Las Palmas B",
		"Colonia Moscardó",
		"CDA Navalcarnero",
		"Orihuela CF",
		"CD Quintanar del Rey",
		"CF Rayo Majadahonda",
		"Rayo Vallecano de Madrid B",
		"Real Madrid C",
		"UD San Sebastián de los Reyes",
		"UD Socuéllamos",
		"C.D. Tenerife B",
	};

	for (string s : d3_1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = spa_third_1;
		club->ClubDivision = spa_third;
	}
	for (string s : d3_2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = spa_third_2;
		club->ClubDivision = spa_third;
	}
	for (string s : d4_1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = spa_fourth_1;
		club->ClubDivision = spa_fourth;
	}
	for (string s : d4_2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = spa_fourth_2;
		club->ClubDivision = spa_fourth;
	}
	for (string s : d4_3_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = spa_fourth_3;
		club->ClubDivision = spa_fourth;
	}
	for (string s : d4_4_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = spa_fourth_4;
		club->ClubDivision = spa_fourth;
	}
	for (string s : d4_5_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = spa_fourth_5;
		club->ClubDivision = spa_fourth;
	}
}