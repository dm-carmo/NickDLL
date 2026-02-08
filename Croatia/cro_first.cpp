#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* cro_first_vtable = (DWORD*)0x9690C4;

void cro_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 4;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = 4;
	comp_data->tiebreaker_2 = 1;
	comp_data->tiebreaker_3 = 2;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 1;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = CRO_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) cro_first_subs_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call cro_first_subs
		add esp, 0x4
		ret
	}
}

DWORD cro_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * ((comp_stats*)_this)->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 22), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 23), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) cro_first_fixtures_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call cro_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void croatia_restruct_2025() {
	cm3_club_comps* cro_first = &(*club_comps)[CRO_FIRST_9CF()];
	cm3_club_comps* cro_second = &(*club_comps)[CRO_SECOND_9CF()];
	cm3_club_comps* cro_third = &(*club_comps)[CRO_THIRD_9CF()];
	cm3_club_comps* cro_reg_e = &(*club_comps)[CRO_FOURTH_EAST_9CF()];
	cm3_club_comps* cro_reg_w = &(*club_comps)[CRO_FOURTH_WEST_9CF()];
	cm3_club_comps* cro_reg_n = &(*club_comps)[CRO_FOURTH_NORTH_9CF()];
	cm3_club_comps* cro_reg_s = &(*club_comps)[CRO_FOURTH_SOUTH_9CF()];
	cm3_club_comps* cro_reg_c = &(*club_comps)[CRO_FOURTH_CENTRAL_9CF()];
	cm3_club_comps* a_lower = &(*club_comps)[A_LOWER_9CF()];

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

void cro_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = cro_first_vtable;
	data->year = year;
	data->rules = 0x21;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	if (year == 2025) croatia_restruct_2025();
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	cro_first_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	reputation_setup_generic_68A850(_this);
}

void __fastcall cro_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(CRO_THIRD_9CF());
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegated_clubs.push_back(table_pos.club);
		}
	}

	vector<cm3_clubs*> available_clubs;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[0];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		if (t.f6 == 1) {
			cm3_clubs* promote = t.club;
			if (promote->ClubDivision && promote->ClubDivision != comp_data->competition_db) {
				promote_club_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
				promoted_teams++;
			}
		}
	}

	if (promoted_teams != relegated_clubs.size()) create_message_box("Error", "Promoted and relegated club count does not match for cro_third", false);

	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		relegate_club_6831A0((BYTE*)relegated_clubs[i], (DWORD)get_comp(CRO_FOURTH_NORTH_9CF()), 1);
	}
}

void sort_cro_non_league_clubs() {
	vector<cm3_clubs*> available_clubs;

	for (int i = 0; i < get_club_count(); i++)
	{
		cm3_clubs* club = get_club(i);
		if (club)
		{
			if (club->ClubDivision && club->ClubNation)
			{
				DWORD compID = club->ClubDivision->ClubCompID;
				DWORD nationID = club->ClubNation->NationID;
				if (nationID == NATION_CROATIA_9CF() &&		// Croatia
					(compID == CRO_FOURTH_CENTRAL_9CF() ||		// Non-leagues
						compID == CRO_FOURTH_NORTH_9CF() ||
						compID == CRO_FOURTH_SOUTH_9CF() ||
						compID == CRO_FOURTH_EAST_9CF() ||
						compID == CRO_FOURTH_WEST_9CF()))
				{
					available_clubs.push_back(club);
				}
			}
		}
	}
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);
	sort(available_clubs.begin() + 10, available_clubs.end() - 10, compareClubLongitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 10) available_clubs[i]->ClubDivision = get_comp(CRO_FOURTH_NORTH_9CF());
		else if (i < 20) available_clubs[i]->ClubDivision = get_comp(CRO_FOURTH_EAST_9CF());
		else if (i < 30) available_clubs[i]->ClubDivision = get_comp(CRO_FOURTH_CENTRAL_9CF());
		else if (i < 40) available_clubs[i]->ClubDivision = get_comp(CRO_FOURTH_WEST_9CF());
		else available_clubs[i]->ClubDivision = get_comp(CRO_FOURTH_SOUTH_9CF());
	}
}

char cro_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(void(__thiscall**)(BYTE*, int))(v1 + 0xB0))(_this, 1);
	cro_non_league_promotion(_this);
	sort_cro_non_league_clubs();

	sub_687970(_this, ebx);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
		}
	}
	data->year++;
	data->current_stage = -1;
	cro_first_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	BYTE* cro_second = get_loaded_league(CRO_SECOND_9CF());
	BYTE* cro_third = get_loaded_league(CRO_THIRD_9CF());

	v1 = *(DWORD*)cro_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(cro_second);

	v1 = *(DWORD*)cro_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(cro_third);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) cro_first_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call cro_first_update
		add esp, 0x4
		ret
	}
}

void setup_cro_first()
{
	WriteVTablePtr(cro_first_vtable, VTableSubsRounds, (DWORD)&cro_first_subs_c);
	WriteVTablePtr(cro_first_vtable, VTableFixtures, (DWORD)&cro_first_fixtures_c);
	WriteVTablePtr(cro_first_vtable, VTableEoSUpdate, (DWORD)&cro_first_update_c);
	WriteVTablePtr(cro_first_vtable, VTablePromRelUpdate, (DWORD)0x689C20);
}
