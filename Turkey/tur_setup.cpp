#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "tur_first.h"
#include "tur_second.h"
#include "tur_third.h"
#include "tur_fourth.h"
#include "tur_cup.h"
#include "tur_super.h"
//#include "tur_awards.h"
#include <Helpers\9cf_constants.h>

DWORD tur_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
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
	tur_first_init(pMem, *current_year, get_comp(TUR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	tur_second_init(pMem, *current_year, get_comp(TUR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	tur_third_init(pMem, *current_year, get_comp(TUR_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		tur_fourth_init(pMem, *current_year, get_comp(TUR_FOURTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	tur_cup_init(pMem, *current_year, get_comp(TUR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	tur_super_init(pMem, *current_year, get_comp(TUR_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(TUR_SUPER_CUP_9CF());
	return 1;
}

void setup_tur_nation() {
	WriteDWORD(0x668e81 + 6, (DWORD)&tur_setup_c);
	setup_tur_first();
	setup_tur_second();
	setup_tur_third();
	setup_tur_fourth();
	setup_tur_cup();
	setup_tur_super();
	//setup_tur_awards();

	WriteNOP(0x8fc482, 7);
}

void turkey_restructure() {
	cm3_nations* turkey = get_country(NATION_TURKEY_9CF());
	cm3_club_comps* tur_third = get_comp(TUR_THIRD_9CF());
	cm3_club_comps* tur_third_1 = get_comp(TUR_THIRD_G1_9CF());
	cm3_club_comps* tur_third_2 = get_comp(TUR_THIRD_G2_9CF());
	cm3_club_comps* tur_fourth = get_comp(TUR_FOURTH_9CF());
	cm3_club_comps* tur_fourth_1 = get_comp(TUR_FOURTH_G1_9CF());
	tur_fourth_1->ClubCompReputation = 2;
	cm3_club_comps* tur_fourth_2 = get_comp(TUR_FOURTH_G2_9CF());
	tur_fourth_2->ClubCompReputation = 2;
	cm3_club_comps* tur_fourth_3 = get_comp(TUR_FOURTH_G3_9CF());
	tur_fourth_3->ClubCompReputation = 2;
	cm3_club_comps* tur_fourth_4 = get_comp(TUR_FOURTH_G4_9CF());
	tur_fourth_4->ClubCompReputation = 2;
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	vector<DWORD> move_to_lower = {
		TUR_THIRD_G1_9CF(),
		TUR_THIRD_G2_9CF(),
		TUR_FOURTH_G1_9CF(),
		TUR_FOURTH_G2_9CF(),
		TUR_FOURTH_G3_9CF(),
		TUR_FOURTH_9CF(),
	};
	for (DWORD id : move_to_lower) {
		vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(id);
		for (cm3_clubs* c : lower_clubs) {
			c->ClubDivision = a_lower;
		}
	}

	cm3_clubs* bingolspor = find_club("Bingölspor");
	if (bingolspor) {
		bingolspor->ClubNation = turkey;
	}

	vector<string> d3a_teams = {
		"24 Erzincanspor",
		"Adana 01 FK",
		"Altinordu FK",
		"Sincan Belediyesi Ankaraspor",
		"Batman Petrolspor",
		"Beykoz Anadolu Spor",
		"Beyoglu Yeni Carsi FK",
		"Bucaspor 1928",
		"Elazigspor",
		"Erbaaspor",
		"Inegölspor",
		"Iskenderunspor",
		"Karacabey Belediye Spor",
		"Karaman FK",
		"GMG Kastamonuspor",
		"Kepez Spor Futbol",
		"MKE Ankaragücü",
		"Muglaspor",
		"Sanliurfaspor",
	};
	vector<string> d3b_teams = {
		"1461 Trabzon FK",
		"68 Aksarayspor",
		"Adanaspor",
		"Aliaga FK",
		"Ankara Demirspor",
		"Arnavutköy Belediyesi FSK",
		"Bursaspor",
		"Fethiyespor",
		"Güzide Gebze Spor Kulübü",
		"Isparta 32 Spor",
		"Kahramanmaras Istiklal Spor",
		"Kirklarelispor",
		"Mardin 1969 Spor",
		"Menemen FK",
		"Mus Spor Kulübü",
		"Somaspor",
		"Yeni Malatyaspor",
		"Yeni Mersin Idmanyurdu",
	};
	vector<string> d4a_teams = {
		"Beykoz Ishakli Spor",
		"Bulvarspor",
		"Bursa Nilüfer FK",
		"Bursa Yildirim Spor Kulübü",
		"Cankaya SK",
		"Corlu Spor 1947",
		"Edirnespor",
		"Etimesgut Spor Kulübü",
		"Galata Spor Kulübü",
		"Inegöl Kafkas Spor Kulübü",
		"Inkilap Futbol Spor Kulübü",
		"Kestel Cilek Spor Kulübü",
		"Kücükcekmece Sinop Spor",
		"Polatli 1926 Spor Kulübü",
		"Silivrispor",
		"Yalova FK 77 Spor Kulübü",
	};
	vector<string> d4b_teams = {
		"Bingölspor",
		"Agri 1970 Spor",
		"Diyarbekir Spor",
		"Erciyes 38 Futbol Spor Kulübü",
		"Kahramanmaras Spor",
		"Karaköprü Belediye Spor",
		"Kirikkale FK Spor Kulübü",
		"Kirsehir Futbol Spor Kulübü",
		"Kelkit Hürriyet Spor Kulübü", // Kilis 1984
		"Malatya Yesilyurt Belediyespor",
		"Mazidagi Fosfat Spor",
		"Nigde Anadolu FK",
		"Osmaniyespor FK",
		"Silifke Belediye Spor",
		"Nevsehir Belediye Spor", // Suvermez Kapadokyaspor
		"Türk Metal 1963 Spor",
	};
	vector<string> d4c_teams = {
		"Bayburt Özel Idare Spor", // 1926 Bulancakspor
		"52 Orduspor FK",
		"Amasyaspor FK",
		"Artvin Hopaspor",
		"Cayeli Spor",
		"Düzcespor",
		"Fatsa Belediyespor",
		"Giresunspor",
		"Karabük Idmanyurdu Spor",
		"Karadeniz Eregli Belediye Spor",
		"Orduspor 1967 SK",
		"Pazarspor",
		"Sebat Gençlik Spor",
		"Tokat Belediye Spor Kulübü",
		"Yozgat Belediyesi Bozok Spor",
		"Zonguldak Spor FK",
	};
	vector<string> d4d_teams = {
		"Afyonspor",
		"Alanya 1221 Futbol Spor Kulübü",
		"Altay SK",
		"Ayvalikgücü Belediyespor",
		"Balikesirspor",
		"Bornova 1877 SK",
		"Denizlispor", // Denizli Idman Yurdu
		"Eskisehir Anadolu Spor FK",
		"Eskisehirspor",
		"Izmir Coruhlu Futbol Kulübü",
		"Karsiyaka",
		"Kütahyaspor Futbol SK",
		"Nazilli Spor",
		"Büyükcekmece Tepecik Spor", // Söke 1970,
		"Tire 2021 FK",
		"Usak Spor",
	};

	for (string s : d3a_teams) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = tur_third_1;
		club->ClubDivision = tur_third;
	}
	for (string s : d3b_teams) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = tur_third_2;
		club->ClubDivision = tur_third;
	}
	for (string s : d4a_teams) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = tur_fourth_1;
		club->ClubDivision = tur_fourth;
	}
	for (string s : d4b_teams) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = tur_fourth_2;
		club->ClubDivision = tur_fourth;
	}
	for (string s : d4c_teams) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = tur_fourth_3;
		club->ClubDivision = tur_fourth;
	}
	for (string s : d4d_teams) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = tur_fourth_4;
		club->ClubDivision = tur_fourth;
	}
}