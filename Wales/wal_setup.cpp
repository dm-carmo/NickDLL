#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "wal_premier.h"
#include "wal_first_n.h"
#include "wal_first_s.h"
#include "wal_cup.h"
#include "wal_league_cup.h"

static DWORD(__thiscall* wal_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x924420);

DWORD wal_setup_c(playable_nation_data* nation_data) {
	// contract start date?
	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	// contract end date?
	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	wal_premier_init(pMem, *current_year, get_comp(WAL_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	wal_first_n_init(pMem, *current_year, get_comp(WAL_FIRST_NORTH_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	wal_first_s_init(pMem, *current_year, get_comp(WAL_FIRST_SOUTH_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	wal_cup_setup(pMem, *current_year, get_comp(WAL_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	wal_league_cup_init(pMem, *current_year, get_comp(WAL_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_wal_nation()
{
	WriteDWORD(0x669047 + 6, (DWORD)&wal_setup_c);
	setup_wal_premier();
	setup_wal_first_n();
	setup_wal_first_s();
	setup_wal_cup();
	setup_wal_league_cup();

	WriteNOP(0x9244ea, 7);
}

void wales_restructure() {
	cm3_club_comps* wal_premier = get_comp(WAL_PREMIER_9CF());
	cm3_club_comps* wal_first_n = get_comp(WAL_FIRST_NORTH_9CF());
	cm3_club_comps* wal_first_s = get_comp(WAL_FIRST_SOUTH_9CF());
	wal_first_s->ClubCompNation = get_country(NATION_WALES_9CF());
	wal_first_s->ClubCompContinent = find_continent("Europe");
	wal_first_s->ClubCompReputation = 1;
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());


	vector<cm3_clubs*> clubs = find_clubs_of_comp(wal_premier->ClubCompID);
	for (cm3_clubs* c : clubs) {
		c->ClubDivision = a_lower;
	}
	clubs = find_clubs_of_comp(wal_first_n->ClubCompID);
	for (cm3_clubs* c : clubs) {
		c->ClubDivision = a_lower;
	}

	vector<string> d1_clubs = {
		"Bala Town",
		"Barry Town United",
		"Briton Ferry Llansawel",
		"Caernarfon Town",
		"Cardiff Metropolitan University",
		"Colwyn Bay",
		"Connah's Quay Nomads",
		"Flint Town United",
		"Haverfordwest County",
		"Llanelli Town AFC",
		"Penybont FC",
		"The New Saints",
	};
	vector<string> d2n_clubs = {
		"Airbus UK Broughton",
		"Brickfield Rangers",
		"Buckley Town",
		"Caersws FC",
		"Denbigh Town",
		"Flint Mountain",
		"Gresford Athletic",
		"Guilsfield FC",
		"Holyhead Hotspur",
		"Holywell Town",
		"Llandudno FC",
		"Mold Alexandra",
		"Newtown AFC",
		"Penrhyncoch FC",
		"Y Rhyl 1879",
		"Ruthin Town",
	};
	vector<string> d2s_clubs = {
		"Aberystwyth Town",
		"Afan Lido",
		"Ammanford AFC",
		"Baglan Dragons",
		"Caerau Ely",
		"Cambrian United",
		"Cardiff Draconians",
		"Carmarthen Town",
		"Cwmbran Celtic",
		"Llantwit Major",
		"Newport City",
		"Pontypridd United",
		"Trefelin Boys & Girls Club",
		"Treowen Stars",
		"Trethomas Bluebirds",
		"Ynyshir Albions",
	};

	for (string s : d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = wal_premier;
	}
	for (string s : d2n_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = wal_first_n;
	}
	for (string s : d2s_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = wal_first_s;
	}
}