#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

DWORD* swe_second_vtable = (DWORD*)0x9702A0;

int swe_second_set_champion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		sub_4AFCE0_add_history_entry(_this, table_teams[0].club, table_teams[1].club, table_teams[2].club, 0);
	}

	return 0;
}

void __declspec(naked) swe_second_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_second_set_champion
		add esp, 0x4
		ret 0
	}
}

void swe_second_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = NoTiebreaker;
	comp_data->f82 = 2;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 3;

	comp_data->promotes_to = SWE_FIRST_9CF();
	BYTE selected = get_country(NATION_SWEDEN_9CF())->NationLeagueSelected;
	if ((selected & 4) == 0) {
		comp_data->relegates_to = -1;
	}
	else {
		comp_data->relegates_to = SWE_THIRD_9CF();
	}

	comp_data->f217 = 0x2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) swe_second_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_second_subs
		add esp, 0x4
		ret
	}
}

DWORD swe_second_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = 16;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		if (stage_idx == -1) *stage_name_id = North;
		else *stage_name_id = South;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 30), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 6), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 13), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 20), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 23), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 27), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 4), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 11), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 14), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 18), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 25), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 6), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 13), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 20), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 27), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 3), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 10), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 4, 2, 4, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) swe_second_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call swe_second_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void swe_second_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = SWE_SECOND_SOUTH_9CF();
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
	create_league_stage_data(pStage, _this, 16, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void swe_second_reputation_setup(BYTE* _this) {
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

void __declspec(naked) swe_second_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_second_reputation_setup
		add esp, 0x4
		ret
	}
}

char swe_second_update(BYTE* _this) {
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
			data->stages[i] = 0;
		}
	}
	data->year++;
	data->current_stage = -1;
	swe_second_subs(_this);
	AddTeamsGroupLeague(_this, SWE_SECOND_NORTH_9CF());
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		swe_second_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) swe_second_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_second_update
		add esp, 0x4
		ret
	}
}

void swe_second_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = swe_second_vtable;
	data->year = year;
	data->rules = RulesSwedenLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 2;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	swe_second_subs(_this);
	AddTeamsGroupLeague(_this, SWE_SECOND_NORTH_9CF());
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		swe_second_setup_groups(_this, i);
	}
	swe_second_reputation_setup(_this);
}

void swe_second_playoffs_under(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	int j = 0;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == BottomPlayoff) {
				*((DWORD*)(&pTeams[j * 2])) = (DWORD)tls.club;
				j++;
			}
		}
	}

	vector<cm3_clubs*> playoff_clubs;
	comp_stats* swe_third_data = (comp_stats*)get_loaded_league(SWE_THIRD_9CF());
	if (swe_third_data) // league is loaded
	{
		for (char al = 5; al < 7; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(swe_third_data->stages[al]);
			}
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.league_fate == TopPlayoff) {
					playoff_clubs.push_back(tls.club);
				}
			}
		}
	}
	else { // league is not loaded
		vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SWE_THIRD_9CF());
		sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
		// Promoted clubs
		int max_to_check = (available_clubs.size() > 12 ? 12 : available_clubs.size());
		for (int i = 0; i < 6; i++)
		{
			int availableIdx = rand() % (max_to_check - i);
			available_clubs.erase(available_clubs.begin() + availableIdx);
		}
		// Playoff clubs
		max_to_check = (available_clubs.size() > 6 ? 6 : available_clubs.size());
		for (int i = 0; i < 2; i++)
		{
			int availableIdx = rand() % (max_to_check - i);
			cm3_clubs* available = available_clubs[availableIdx];
			playoff_clubs.push_back(available);
			available_clubs.erase(available_clubs.begin() + availableIdx);
		}
	}

	shuffle(playoff_clubs.begin(), playoff_clubs.end(), rng);
	j = 0;
	for (cm3_clubs* c : playoff_clubs) {
		*((DWORD*)(&pTeams[j * 2 + 1])) = (DWORD)c;
		j++;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void swe_second_playoffs_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		BYTE* swe_third = get_loaded_league(SWE_THIRD_9CF());
		if (swe_third) {
			comp_stats* swe_third_data = (comp_stats*)swe_third;
			BYTE* swe_third_a = (BYTE*)swe_third_data->stages[5];
			BYTE* swe_third_b = (BYTE*)swe_third_data->stages[6];
			if (swe_third_a && swe_third_b) {
				DWORD v1 = *(DWORD*)swe_third_a;
				char ret1 = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(swe_third_a, 0, 1);
				DWORD v2 = *(DWORD*)swe_third_b;
				char ret2 = (*(int(__thiscall**)(BYTE*, int, int))(v2 + 0x10))(swe_third_b, 0, 1);
				if (ret1 != 0 || ret2 != 0) {
					(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(swe_third_a);
					(*(void(__thiscall**)(BYTE*))(v2 + 0x94))(swe_third_b);
					if (current == 1) {
						comp_data->current_stage = current;
						swe_second_playoffs_under(_this);
					}
				}
			}
		}
		else {
			if (current == 1) {
				comp_data->current_stage = current;
				swe_second_playoffs_under(_this);
			}
		}
	}
}

void __declspec(naked) swe_second_playoffs_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_second_playoffs_create
		add esp, 0x4
		ret
	}
}

int swe_second_table_indicators(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	cm3_club_comps* swe_first = get_comp(SWE_FIRST_9CF());
	if (stage < 1) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(swe_first), None, Playoff, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 1) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* swe_third = get_comp(SWE_THIRD_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == swe_third) {
			WORD current_round = *(WORD*)(round_data + 0x34);
			comp_stats* swe_third_data = (comp_stats*)get_loaded_league(SWE_THIRD_9CF());
			comp_stats* curr_stage = swe_third_data;
			if (swe_third_data) {
				for (char al = -1; al < 5; al++) {
					if (al >= 0) {
						curr_stage = (comp_stats*)(swe_third_data->stages[al]);
					}
					WORD num_teams = curr_stage->n_teams;
					team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
					for (int i = 0; i < num_teams; i++) {
									if (table[i].club != club) continue;
						switch (fate) {
						case TopPlayoff:
							staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)swe_third, 0x32);
							table[i].league_fate = Promoted;
							*a5 = 1;
							//return 0;
							break;
						case Promoted:
							staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
								*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
							//return 0;
							break;
						default:
							//table[i].league_fate = Eliminated;
							//return 0;
							break;
						}
					}
				}
				for (char al = 5; al < 7; al++) {
					if (al >= 0) {
						curr_stage = (comp_stats*)(swe_third_data->stages[al]);
					}
					WORD num_teams = curr_stage->n_teams;
					team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
					for (int i = 0; i < num_teams; i++) {
									if (table[i].club != club) continue;
						switch (fate) {
						case TopPlayoff:
							//staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)swe_third, 0x32);
							table[i].league_fate = Promoted;
							*a5 = 1;
							return 0;
						case Promoted:
							//staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
							//	*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
							return 0;
						default:
							//table[i].league_fate = Eliminated;
							return 0;
						}
					}
				}
			}
		}
		else {
			WORD num_teams = comp_data->n_teams;
			if (num_teams <= 0) return 0;
			WORD current_round = *(WORD*)(round_data + 0x34);
			comp_stats* curr_stage = comp_data;
			for (char al = -1; al < 1; al++) {
				if (al >= 0) {
					curr_stage = (comp_stats*)(comp_data->stages[al]);
				}
				team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
				for (int i = 0; i < num_teams; i++) {
							if (table[i].club != club) continue;
					switch (fate) {
					case BottomPlayoff:
						staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
						table[i].league_fate = Relegated;
						*a5 = 1;
						return 0;
					case Relegated:
						staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
							*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
						return 0;
					case NoFate:
						table[i].league_fate = Eliminated;
						return 0;
					case TopPlayoff:
						table[i].league_fate = Eliminated;
						return 0;
					default:
						return 0;
					}
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) swe_second_set_table_fate()
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
		call swe_second_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void swe_second_awards(BYTE* _this, DWORD** team_list, WORD* total_teams) {
	*total_teams = 32;
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

void __declspec(naked) swe_second_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call swe_second_awards
		add esp, 0xc
		ret 8
	}
}

void swe_second_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
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
		comp_stats* d3_comp_data = (comp_stats*)get_loaded_league(SWE_THIRD_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == SWE_THIRD_9CF()) {
			if (d3_comp_data) {
				ret = (BYTE*)sub_4A4850((BYTE*)d3_comp_data->f8, club);
				if (!ret) return;
				ret_current = 1 * 6 + 1;
				ret_min = 1 * 6 + 1;
				ret_max = 1 * 6 + 1;
			}
		}
		else {
			ret_current = 12 * 2 + 1;
			ret_min = 12 * 2 + 1;
			ret_max = 12 * 2 + 1;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) swe_second_reputation_calc_c()
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
		call swe_second_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_swe_second()
{
	WriteVTablePtr(swe_second_vtable, VTableEoSUpdate, (DWORD)&swe_second_update_c);
	WriteVTablePtr(swe_second_vtable, VTableFixtures, (DWORD)&swe_second_fixtures_c);
	WriteVTablePtr(swe_second_vtable, VTableReputationSetup, (DWORD)&swe_second_reputation_setup_c);
	WriteVTablePtr(swe_second_vtable, VTableReputationCalc, (DWORD)&swe_second_reputation_calc_c);
	WriteVTablePtr(swe_second_vtable, VTableAwardTeamsSetup, (DWORD)&swe_second_awards_c);
	WriteVTablePtr(swe_second_vtable, VTableSubsRounds, (DWORD)&swe_second_subs_c);
	WriteVTablePtr(swe_second_vtable, VTableTableFates, (DWORD)&swe_second_set_table_fate);
	WriteVTablePtr(swe_second_vtable, VTablePlayoffQual, (DWORD)&swe_second_playoffs_create_c);
	WriteVTablePtr(swe_second_vtable, VTableSetChampion, (DWORD)&swe_second_set_champion_c);
	WriteVTablePtr(swe_second_vtable, VTable21, 0x48ce70);
	WriteVTablePtr(swe_second_vtable, VTable9, 0x48ceb0);
	WriteVTablePtr(swe_second_vtable, VTable10, 0x48cea0);
}