#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "cro_first.h"
#include "cro_second.h"
#include "cro_third.h"
#include "cro_cup.h"
#include "cro_super.h"
#include "cro_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* cro_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x517480);

DWORD cro_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	
	nation_data->contract_end_day = 16;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// HNL
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_first_init(pMem, *current_year, get_comp(CRO_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 1.NL
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_second_init(pMem, *current_year, get_comp(CRO_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 2.NL
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_third_init(pMem, *current_year, get_comp(CRO_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	cro_cup_setup(pMem, *current_year, get_comp(CRO_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	cro_super_init(pMem, *current_year, get_comp(CRO_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(CRO_SUPER_CUP_9CF());
	return 1;
}

void setup_cro_nation() {
	WriteDWORD(0x667C00 + 6, (DWORD)&cro_setup_c);
	setup_cro_first();
	setup_cro_second();
	setup_cro_third();
	setup_cro_cup();
	setup_cro_super();
	setup_cro_awards();

	WriteNOP(0x517552, 7);
}

void croatia_restructure() {
	cm3_club_comps* cro_first = get_comp(CRO_FIRST_9CF());
	cm3_club_comps* cro_second = get_comp(CRO_SECOND_9CF());
	cm3_club_comps* cro_third = get_comp(CRO_THIRD_9CF());
	cm3_club_comps* cro_reg_e = get_comp(CRO_FOURTH_EAST_9CF());
	cm3_club_comps* cro_reg_w = get_comp(CRO_FOURTH_WEST_9CF());
	cm3_club_comps* cro_reg_n = get_comp(CRO_FOURTH_NORTH_9CF());
	cm3_club_comps* cro_reg_s = get_comp(CRO_FOURTH_SOUTH_9CF());
	cm3_club_comps* cro_reg_c = get_comp(CRO_FOURTH_CENTRAL_9CF());
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	cro_third->ClubCompReputation = 4;
	vector<cm3_clubs*> cro_clubs = find_clubs_of_country(NATION_CROATIA_9CF());
	for (cm3_clubs* c : cro_clubs) {
		c->ClubDivision = a_lower;
	}

	vector<string> d1_clubs = {
		"GNK Dinamo Zagreb",
		"HNK Hajduk Split",
		"NK Istra 1961",
		"HNK Rijeka",
		"Slaven Belupo Koprivnica",
		"NK Varazdin",
		"NK Lokomotiva Zagreb",
		"HNK Gorica",
		"HNK Vukovar 1991",
		"NK Osijek"
	};
	vector<string> d2_clubs = {
		"NK BSK Bijelo Brdo",
		"HNK Cibalia Vinkovci",
		"NK Croatia Zmijavci",
		"NK Dubrava Tim kabel",
		"NK Dugopolje",
		"NK Hrvace",
		"NK Jarun",
		"NK Karlovac 1919",
		"NK Opatija",
		"HNK Orijent Rijeka",
		"NK Rudes",
		"NK Sesvete"
	};
	vector<string> d3_clubs = {
		"NK Bjelovar",
		"NK Dugo Selo",
		"NK Croatia Dakovo",
		"NK Grobnican",
		"NK Hrvatski Dragovoljac",
		"NK Jadran Luka Ploce",
		"NK Kustosija Zagreb",
		"NK Lucko",
		"NK Mladost Zdralovi",
		"NK Radnik Krizevci",
		"HNK Segesta Sisak",
		"NK Solin",
		"NK Trnje Zagreb",
		"NK Uljanik",
		"NK Uskok Klis",
		"NK Varteks Varazdin"
	};
	vector<string> d4n_clubs = {
		//"NK Bilogora 91",
		//"NK Daruvar",
		"NK Dinamo Domasinec",
		//"NK Dinamo Predavac",
		//"NK Gari? (G)",
		"NK Granicar Djurdjevac",
		"NK Granicar Kotoriba",
		"NK Koprivnica",
		//"NK Me?imurec (DP)",
		"NK Medjimurje Cakovec",
		//"NK Nedeliš?e",
		"NK Pitomaca",
		"NK Podravina Ludbreg",
		"NK Polet Sveti Martin na Muri",
		"NK Rudar Mursko Sredisce",
		//"NK Slatina"
	};
	vector<string> d4s_clubs = {
		//"HNK Jadran (KS)",
		"NK Primorac Biograd",
		"HNK Sloga Mravince",
		//"HNK Val",
		"HNK Zadar",
		"HNK Sibenik",
		//"NK GOŠK Kaštela",
		"NK GOSK - Dubrovnik 1919",
		"NK Hrvatski vitez Posedarje",
		"NK Junak Sinj",
		//"NK Kamen (P)",
		"NK Neretva Metkovic",
		"NK Neretvanac Opuzen",
		//"NK Omiš",
		"NK Vodice",
		"NK Zagora Unesic"
	};
	vector<string> d4e_clubs = {
		"NK Bedem Ivankovo",
		"NK Belisce",
		//"NK Borac (KV)",
		"NK Kutjevo",
		"NK Marsonia 1909",
		//"NK Radni?ki (D)",
		"NK Slavija Pleternica",
		"NK Slavonija Pozega",
		//"NK Sva?i?",
		//"NK Tomislav (C)",
		//"NK Tomislav (DA)",
		//"NK Valpovka",
		//"NK Vardarac",
		//"NK Vinogorac",
		"NK Vuteks Sloga",
		"NK Cepin"
	};
	vector<string> d4w_clubs = {
		//"NK Banjole",
		"NK Buje",
		"NK Crikvenica",
		//"NK Halubjan",
		"NK Jadran Porec",
		//"NK Kraljevica",
		"NK Krk",
		//"NK Lokomotiva (R)",
		"NK Naprijed Hreljin",
		"NK Nehaj Senj",
		//"NK Novalja",
		//"NK OŠK Omišalj",
		"NK Pazinka Pazin",
		"NK Pomorac Kostrena",
		"Rudar Labin",
		"NK Vinodol"
	};
	vector<string> d4c_clubs = {
		//"GNK Tigar Sveta Nedelja",
		"NK Mladost Petrinja",
		"NK Bistra",
		//"NK Dinamo Odranski Obrež",
		"NK Gaj Mace",
		"NK HASK Zagreb",
		"NK Inter Zapresic",
		"NK Kurilovec Velika Gorica",
		"NK Maksimir",
		"NK Ponikve",
		//"NK Pre?ko",
		"NK Ravnice",
		//"NK Samobor",
		"NK Tresnjevka Zagreb",
		"NK Vrapce",
		"NK Zagorec"
	};

	for (string s : d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = cro_first;
	}
	for (string s : d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = cro_second;
	}
	for (string s : d3_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = cro_third;
	}
	for (string s : d4n_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = cro_reg_n;
	}
	for (string s : d4s_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = cro_reg_s;
	}
	for (string s : d4e_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = cro_reg_e;
	}
	for (string s : d4w_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = cro_reg_w;
	}
	for (string s : d4c_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = cro_reg_c;
	}
}