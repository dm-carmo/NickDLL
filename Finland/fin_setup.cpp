#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "fin_premier.h"
#include "fin_first.h"
#include "fin_second.h"
#include "fin_third.h"
#include "fin_cup.h"
#include "fin_awards.h"

static DWORD(__thiscall* fin_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x592250);

DWORD fin_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = March;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 5;
	// contract end date?
	nation_data->contract_end_day = 30;
	nation_data->contract_end_month = November;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 4;
	}
	else {
		nation_data->num_of_comps = 5;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Veikkausliiga
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fin_premier_init(pMem, start_year, get_comp(FIN_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ykkˆsliiga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fin_first_init(pMem, start_year, get_comp(FIN_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ykkˆnen
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fin_second_init(pMem, start_year, get_comp(FIN_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Kakkonen
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		fin_third_init(pMem, start_year, get_comp(FIN_THIRD_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	fin_cup_setup(pMem, start_year, get_comp(FIN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 0;
	nation_data->super_cup = 0;
	return 1;
}

void setup_fin_nation()
{
	WriteDWORD(0x667E85 + 6, (DWORD)&fin_setup_c);
	setup_fin_premier();
	setup_fin_first();
	setup_fin_second();
	setup_fin_third();
	setup_fin_cup();
	setup_fin_awards();
	// Start date
	WriteBytes(0x667EE5, 1, April);
	WriteBytes(0x667EE7, 1, 4);
}

void finland_restructure() {
	cm3_club_comps* fin_first = get_comp(FIN_FIRST_9CF());
	cm3_club_comps* fin_second = get_comp(FIN_SECOND_9CF());
	fin_second->ClubCompReputation = 2;
	cm3_club_comps* fin_third = get_comp(FIN_THIRD_9CF());
	cm3_club_comps* fin_third_a = get_comp(FIN_THIRD_A_9CF());
	fin_third_a->ClubCompReputation = 1;
	cm3_club_comps* fin_third_b = get_comp(FIN_THIRD_B_9CF());
	fin_third_b->ClubCompReputation = 1;
	cm3_club_comps* fin_third_c = get_comp(FIN_THIRD_C_9CF());
	fin_third_c->ClubCompReputation = 1;
	cm3_club_comps* fin_lower = get_comp(FIN_LOWER_9CF());
	fin_lower->ClubCompReputation = 1;
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	vector<cm3_clubs*> orig_clubs = find_clubs_of_comp(FIN_FIRST_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(FIN_LOWER_9CF());
	orig_clubs = find_clubs_of_comp(FIN_SECOND_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(FIN_LOWER_9CF());
	orig_clubs = find_clubs_of_comp(FIN_THIRD_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(FIN_LOWER_9CF());
	orig_clubs = find_clubs_of_comp(FIN_THIRD_A_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(FIN_LOWER_9CF());
	orig_clubs = find_clubs_of_comp(FIN_THIRD_B_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(FIN_LOWER_9CF());
	orig_clubs = find_clubs_of_comp(FIN_THIRD_C_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(FIN_LOWER_9CF());
	orig_clubs = find_clubs_of_comp(FIN_SECOND_EAST_9CF());
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(FIN_LOWER_9CF());

	vector<string> d2_clubs = {
		"Eken‰s IF",
		"JIPPO Joensuu",
		"J‰rvenp‰‰n Palloseura",
		"HJK Klubi 04 Helsinki",
		"K‰pyl‰n Pallo",
		"FC Lahti",
		"Pallokerho-35",
		"Salon Palloilijat",
		"SJK Sein‰joki II",
		"Turun Palloseura",
	};
	vector<string> d3_clubs = {
		"Atlantis FC",
		"Espoon Palloseura",
		"Vaasa IFK", // Inter Turku II missing
		"FC Jazz",
		"JJK Jyv‰skyl‰",
		"Kokkolan Pallo-Veikot",
		"Kuopion Palloseura II",
		"Mikkelin Palloilijat",
		"Oulun Luistinseura",
		"Pallokerho Keski-Uusimaa",
		"Rovaniemen Palloseura",
		"Tampere United",
	};
	vector<string> d4a_clubs = {
		"FC Honka",
		"Vantaan Jalkapalloseura",
		"Puistolan Urheilijat",
		"PEPO Lappeenranta",
		"Myllykosken Pallo -47",
		"Grankulla IFK",
		"FC Reipas Lahti",
		"FC Vaajakoski",
		"Haminan Pallo-Kissat",
		"Jyv‰skyl‰n Seudun Palloseura",
	};
	vector<string> d4b_clubs = {
		"Tampereen Pallo-Veikot",
		"Ilves Tampere II",
		"H‰meenlinnan Jalkapalloseura",
		"FC Kiffen",
		"Pallo-Iirot",
		//"SC Kufu-98", // Pallo-Iirot
		"Helsingin Palloseura",
		"Musan Salama",
		"PPJ Helsinki",
		"Nurmij‰rven Jalkapalloseura",
		"Helsinki IFK", // Atlantis 2
	};
	vector<string> d4c_clubs = {
		"Vaasan Palloseura II",
		//"SexyPˆxyt", // Vaasan Palloseura II
		"Gamlakarleby Bollklubb",
		"Jakobstads Bollklubb",
		"Tornion Pallo -47",
		"Oulun Tyˆv‰en Palloilijat", // Oulunsalon Pallo
		"Rovaniemen Palloseura II", // SJK 2 different from SJK Akatemia?????????
		"JS Hercules",
		"N‰rpes Kraft",
		"FC Espoo", // Vaasa IFK in D3
		"Kuopion Elo",
	};

	cm3_nations* finland = get_country(NATION_FINLAND_9CF());
	cm3_clubs* elo = find_club("Kuopion Elo");
	if (elo) {
		elo->ClubNation = finland;
	}
	cm3_clubs* p_iirot = find_club("Pallo-Iirot");
	if (p_iirot) {
		p_iirot->ClubNation = finland;
	}
	cm3_clubs* vps2 = find_club("Vaasan Palloseura II");
	if (vps2) {
		vps2->ClubNation = finland;
	}

	for (string s : d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = fin_first;
	}
	for (string s : d3_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = fin_second;
	}
	for (string s : d4a_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = fin_third;
		club->ClubReserveDivision = fin_third_a;
	}
	for (string s : d4b_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = fin_third;
		club->ClubReserveDivision = fin_third_b;
	}
	for (string s : d4c_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = fin_third;
		club->ClubReserveDivision = fin_third_c;
	}
}