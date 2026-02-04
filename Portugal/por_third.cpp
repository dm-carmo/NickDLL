#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

// Playoffs and fixtures

DWORD* por_third_vtable = (DWORD*)0x96E858;

void por_third_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = 4;
	comp_data->tiebreaker_2 = 2;
	comp_data->tiebreaker_3 = 1;
	comp_data->f82 = 2;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 4;
	comp_data->rele_playoff = 6;
	comp_data->relegations = 0;

	comp_data->promotes_to = POR_SECOND_9CF();
	BYTE selected = find_country("Portugal")->NationLeagueSelected;
	if ((selected & 4) == 0) {
		comp_data->relegates_to = -1;
	}
	else {
		comp_data->relegates_to = POR_FOURTH_9CF();
	}

	comp_data->f217 = 0x2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) por_third_subs_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_third_subs
		add esp, 0x4
		ret
	}
}

DWORD por_third_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		BYTE numberOfLeagueTeams = 10;
		*num_rounds = (numberOfLeagueTeams - 1) * ((comp_stats*)_this)->n_rounds;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 10), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 17), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 24), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 24), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 28), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 5), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 2), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 4), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 18), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);

		if (fixture_id != 18) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		WORD numberOfLeagueTeams = 8;
		*num_rounds = (numberOfLeagueTeams - 1) * 2;
		*stage_name_id = PromotionPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 3), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 10), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);

		if (fixture_id != 14) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx <= 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		WORD numberOfLeagueTeams = 6;
		*num_rounds = (numberOfLeagueTeams - 1) * 2;
		*stage_name_id = 0x47C + (stage_idx - 2);

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 3), year, Sunday);

		if (fixture_id != 10) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) por_third_fixtures_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call por_third_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void por_third_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = POR_THIRD_B_9CF();
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == data->competition_db->ClubCompID
			&& club->ClubReserveDivision && club->ClubReserveDivision->ClubCompID == group_id)
		{
			*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)club;
		}
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, 10, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void por_third_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
			vector<cm3_clubs*> clubs;
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				clubs.push_back(table_teams[i].club);
			}
			sort(clubs.begin(), clubs.end(), compareClubRep);
			for (size_t i = 0; i < clubs.size(); i++) {
				cm3_clubs* c = clubs[i];
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 2 + 1));
			}
		}
	}
}

void __declspec(naked) por_third_reputation_setup_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_third_reputation_setup
		add esp, 0x4
		ret
	}
}

char por_third_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
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
	por_third_subs(_this);
	AddTeamsGroupLeague(_this, POR_THIRD_A_9CF());
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		por_third_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) por_third_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_third_update
		add esp, 0x4
		ret
	}
}

void BlockReservePromotionLiga3(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	curr_stage = (comp_stats*)(data->stages[1]);
	WORD total_teams = curr_stage->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
		if (ret_club && !is_main_club) {
			if (ret_club->ClubDivision->ClubCompID != POR_FIRST_9CF() &&
				ret_club->ClubDivision->ClubCompID != POR_SECOND_9CF())
				table_teams[i].league_fate = CantBePromoted;
		}
	}
}

void por_third_restruct_2025() {
	cm3_staff_comps* data = &(*awards)[POR_THIRD_MANAGER_OF_YEAR_9CF()];
	if (data) {
		data->StaffCompNation = find_country("Portugal");
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 2;
	}

	cm3_club_comps* por_third = &(*club_comps)[POR_THIRD_9CF()];
	por_third->ClubCompReputation = 6;
	cm3_club_comps* por_third_a = &(*club_comps)[POR_THIRD_A_9CF()];
	por_third_a->ClubCompReputation = 6;
	cm3_club_comps* por_third_b = &(*club_comps)[POR_THIRD_B_9CF()];
	por_third_b->ClubCompReputation = 6;
	cm3_club_comps* por_fourth = &(*club_comps)[POR_FOURTH_9CF()];
	cm3_club_comps* por_fourth_a = &(*club_comps)[POR_FOURTH_A_9CF()];
	por_fourth_a->ClubCompReputation = 3;
	cm3_club_comps* por_fourth_b = &(*club_comps)[POR_FOURTH_B_9CF()];
	por_fourth_b->ClubCompNation = find_country("Portugal");
	por_fourth_b->ClubCompContinent = find_continent("Europe");
	por_fourth_b->ClubCompReputation = 3;
	cm3_club_comps* por_fourth_c = &(*club_comps)[POR_FOURTH_C_9CF()];
	por_fourth_c->ClubCompNation = find_country("Portugal");
	por_fourth_c->ClubCompContinent = find_continent("Europe");
	por_fourth_c->ClubCompReputation = 3;
	cm3_club_comps* por_fourth_d = &(*club_comps)[POR_FOURTH_D_9CF()];
	por_fourth_d->ClubCompNation = find_country("Portugal");
	por_fourth_d->ClubCompContinent = find_continent("Europe");
	por_fourth_d->ClubCompReputation = 3;
	cm3_club_comps* a_lower = &(*club_comps)[A_LOWER_9CF()];

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
}

void por_third_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = por_third_vtable;
	data->year = year;
	data->rules = 0x17;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	if (year == 2025) por_third_restruct_2025();
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 4;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	por_third_subs(_this);
	AddTeamsGroupLeague(_this, POR_THIRD_A_9CF());
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		por_third_setup_groups(_this, i);
	}
	por_third_reputation_setup(_this);
}

void por_third_playoffs_prom(BYTE* _this) {
	char stage_num = 1;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;
	clubs.clear();

	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
		}
	}

	for (size_t i = 0; i < playoff_teams; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
	}

	WORD year = comp_data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	BYTE prom_rel[4] = { 2, 1, 0, 0 };
	short f217 = 3;
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
		comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), &prom_rel[0],
		year, stage_num, stage_name_id, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	BlockReservePromotionLiga3(_this);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void por_third_playoffs_rele(BYTE* _this) {
	char stage_num = 2;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;
	BYTE playoff_teams = 6;

	comp_stats* curr_stage = comp_data;

	BYTE prom_rel[4] = { 0, 0, 0, 2 };

	for (int g = 0; g < 2; g++) {
		vector<cm3_clubs*> clubs;
		map<cm3_clubs*, short> bonus_pts;
		short pts_calc = 6;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

		char al = g - 1;
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == BottomPlayoff) {
				short final_pts = tls.points;
				if (final_pts < 10) final_pts = 0;
				else if (final_pts < 15) final_pts = pts_calc;
				else if (final_pts < 20) final_pts = pts_calc + 1;
				else if (final_pts < 25) final_pts = pts_calc + 2;
				else if (final_pts < 30) final_pts = pts_calc + 3;
				else final_pts = pts_calc + 4;
				clubs.push_back(tls.club);
				bonus_pts.emplace(tls.club, final_pts);
				pts_calc--;
			}
		}

		for (size_t i = 0; i < playoff_teams; i++) {
			*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		//short f217 = 0;
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, comp_data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;

		team_league_stats* stage_table_teams = (team_league_stats*)((comp_stats*)pStage)->team_league_table;
		for (int i = 0; i < playoff_teams; i++) {
			team_league_stats tls = stage_table_teams[i];
			auto find_bonus = bonus_pts.find(stage_table_teams[i].club);
			if (find_bonus != bonus_pts.end()) {
				stage_table_teams[i].points = find_bonus->second;
				stage_table_teams[i].points_away = find_bonus->second;
			}
		}

		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	comp_data->current_stage = stage_num - 1;
}

void por_third_playoffs_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 1) {
			por_third_playoffs_prom(_this);
			por_third_playoffs_rele(_this);
		}
	}
}

void __declspec(naked) por_third_playoffs_create_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_third_playoffs_create
		add esp, 0x4
		ret
	}
}

int Liga3TableIndicators(BYTE* _this, DWORD* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	cm3_club_comps* por_second = &(*club_comps)[POR_SECOND_9CF()];
	if (stage < 1) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_868DD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, PromotionPlayoff, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_868DD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RelegationPlayoff, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				DWORD* c = (DWORD*)table[i].club;
				if (c != club) continue;
				switch (fate) {
				case Champions:
					staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Champions;
					return 0;
				case Promoted:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x32);
					table[i].league_fate = Promoted;
					return 0;
				case TopPlayoff:
					staff_history_qualified_868DD0(staff_hist_ptr, club, (DWORD)(por_second), None, Playoff, 0x1E);
					table[i].league_fate = TopPlayoff;
					return 0;
				case Eliminated:
					table[i].league_fate = Eliminated;
					return 0;
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else if (stage <= 3) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				DWORD* c = (DWORD*)table[i].club;
				if (c != club) continue;
				switch (fate) {
				case Relegated:
					staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Relegated;
					return 0;
				case Eliminated:
					table[i].league_fate = Eliminated;
					return 0;
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) por_third_set_table_fate()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call Liga3TableIndicators
		add esp, 0x1c
		ret 0x18
	}
}

int por_third_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[1];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) por_third_set_champion_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_third_set_champion
		add esp, 0x4
		ret 0
	}
}

void por_7D2B80(BYTE* _this, DWORD** team_list, WORD* total_teams) {
	*total_teams = 20;
	DWORD* pMem = (DWORD*)sub_944E46_malloc(4 * (*total_teams));
	*team_list = pMem;

	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* curr_stage = comp_data;
	WORD idx = 0;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			cm3_clubs* club = ((team_league_stats*)curr_stage->team_league_table)[num].club;
			pMem[idx++] = (DWORD)club;
		}
	}
}

void __declspec(naked) por_7D2B80_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call por_7D2B80
		add esp, 0xc
		ret 8
	}
}

void por_third_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 1) {
		ret_current = 1 + 2 * (current - 1);
		ret_min = 1 + 2 * (min - 1);
		ret_max = 1 + 2 * (max - 1);
	}
	else if (stage == 1) {
		ret_current = current;
		ret_min = min;
		ret_max = max;
	}
	else if (stage <= 3) {
		ret_current = current + 8;
		ret_min = min + 8;
		ret_max = max + 8;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) por_third_reputation_calc_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call por_third_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_por_third()
{
	WriteVTablePtr(por_third_vtable, VTableEoSUpdate, (DWORD)&por_third_update_c);
	WriteVTablePtr(por_third_vtable, VTableFixtures, (DWORD)&por_third_fixtures_c);
	WriteVTablePtr(por_third_vtable, VTableSetChampion, (DWORD)&por_third_set_champion_c);
	WriteVTablePtr(por_third_vtable, VTable24, (DWORD)&por_third_reputation_setup_c);
	WriteVTablePtr(por_third_vtable, VTable27, (DWORD)&por_third_reputation_calc_c);
	WriteVTablePtr(por_third_vtable, VTable41, (DWORD)&por_7D2B80_c);
	WriteVTablePtr(por_third_vtable, VTableSubsRounds, (DWORD)&por_third_subs_c);
	WriteVTablePtr(por_third_vtable, VTableTableFates, (DWORD)&por_third_set_table_fate);
	WriteVTablePtr(por_third_vtable, VTablePlayoffQual, (DWORD)&por_third_playoffs_create_c);
	char* rel_grp_a_text = "Relegation Group A";
	char* rel_grp_a_text_short = "Rel. Grp A";
	WriteDWORD(0x4B689B + 1, (DWORD)&rel_grp_a_text[0]);
	WriteDWORD(0x4B93ED + 1, (DWORD)&rel_grp_a_text_short[0]);
	char* rel_grp_b_text = "Relegation Group B";
	char* rel_grp_b_text_short = "Rel. Grp B";
	WriteDWORD(0x4B68B5 + 1, (DWORD)&rel_grp_b_text[0]);
	WriteDWORD(0x4B9407 + 1, (DWORD)&rel_grp_b_text_short[0]);
}