#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "cro_first.h"
#include "cro_second.h"
#include "cro_third.h"
#include "cro_cup.h"
#include "cro_super.h"
#include "cro_awards.h"
#include <Helpers/new_league_ids.h>

static DWORD(__thiscall* cro_first_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x513E10);
static DWORD(__thiscall* cro_second_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x515310);
static DWORD(__thiscall* cro_third_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x516430);
static DWORD(__thiscall* cro_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x517480);

DWORD cro_setup_c(BYTE* nation_data) {
	*(WORD*)(nation_data + 0x32) = 24;
	*(BYTE*)(nation_data + 0x34) = 6;
	*(WORD*)(nation_data + 0x35) = *current_year;
	*(WORD*)(nation_data + 0x37) = 5;
	*(WORD*)(nation_data + 0x41) = 14;
	*(BYTE*)(nation_data + 0x43) = 4;
	*(WORD*)(nation_data + 0x44) = *current_year + 1;
	*(WORD*)(nation_data + 0x46) = 5;
	*(DWORD*)(nation_data + 0xc) = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// Restructure
	if (*current_year == 2025) {
		cm3_club_comps* cro_first = &(*club_comps)[Get9CF(0x9CF87C)];
		cm3_club_comps* cro_second = &(*club_comps)[Get9CF(0x9CF880)];
		cm3_club_comps* cro_third = &(*club_comps)[cro_third_id];
		cm3_club_comps* cro_reg_e = &(*club_comps)[Get9CF(0x9CF890)];
		cm3_club_comps* cro_reg_w = &(*club_comps)[Get9CF(0x9CF894)];
		cm3_club_comps* cro_reg_n = &(*club_comps)[Get9CF(0x9CF888)];
		cm3_club_comps* cro_reg_s = &(*club_comps)[Get9CF(0x9CF88C)];
		cm3_club_comps* cro_reg_c = &(*club_comps)[Get9CF(0x9CF884)];
		cm3_club_comps* a_lower = &(*club_comps)[Get9CF(0x9CF764)];

		strcpy_s(cro_third->ClubCompName, "Croatian Druga NL");
		strcpy_s(cro_third->ClubCompNameShort, "2. NL");
		strcpy_s(cro_third->ClubCompNameThreeLetter, "2NL");
		cro_third->ClubCompReputation = 4;
		vector<cm3_clubs*> cro_clubs = find_clubs_of_country(Get9CF(0x9CF2AC));
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
	// start calling each league's functions
	BYTE i = 0;
	// HNL
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_first_init(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF87C)]);
	nation_comps[i++] = (DWORD)pMem;
	// 1.NL
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_second_init(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF880)]);
	nation_comps[i++] = (DWORD)pMem;
	// 2.NL
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cro_third_init(pMem, *current_year, &(*club_comps)[cro_third_id]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	cro_cup_setup(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF898)]);
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	cro_super_init(pMem, *current_year, &(*club_comps)[Get9CF(0x9CF940)]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = *current_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[Get9CF(0x9CF940)];
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
}