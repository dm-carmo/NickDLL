#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

vtable* mex_second_vtable = new vtable((BYTE*)0x969798, 0xB4);

void mex_second_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(mex_second_vtable->vtable_ptr);
	sub_687970(_this, 0);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
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
	if (data->stages) {
		sub_9452CA_free((BYTE*)(data->stages));
		data->stages = 0;
	}
	if (data->f8) {
		sub_49F450((BYTE*)(data->f8));
		sub_944C94_free((BYTE*)(data->f8));
	}
	sub_682300(_this);
}

void mex_second_free(BYTE* _this, BYTE a2) {
	mex_second_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) mex_second_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call mex_second_free
		add esp, 0x8
		ret 4
	}
}

int mex_second_set_champion(BYTE* _this) {
	return 0;
}

void __declspec(naked) mex_second_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call mex_second_set_champion
		add esp, 0x4
		ret 0
	}
}

int mex_second_last_positions(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	vector<cm3_clubs*> clubs;

	comp_stats* open_playoff = (comp_stats*)data->stages[1];
	teams_seeded* open_teams = (teams_seeded*)open_playoff->teams_list;
	for (WORD i = 0; i < open_playoff->n_teams; i++) {
		if (open_teams[i].f6 == 1 && !vector_contains_element(clubs, open_teams[i].club))
		{
			clubs.push_back(open_teams[i].club);
			break;
		}
	}

	comp_stats* close_playoff = (comp_stats*)data->stages[2];
	teams_seeded* close_teams = (teams_seeded*)close_playoff->teams_list;
	for (WORD i = 0; i < close_playoff->n_teams; i++) {
		if (close_teams[i].f6 == 1 && !vector_contains_element(clubs, close_teams[i].club))
		{
			clubs.push_back(close_teams[i].club);
			break;
		}
	}

	comp_stats* aggregate = (comp_stats*)data->stages[3];
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);
	bool checked_order = (clubs.size() == 1); // if only 1 club, no need to check the Apertura/Clausura winners' order
	for (WORD i = 0; i < aggregate->n_teams; i++)
	{
		if (!vector_contains_element(clubs, table_teams[i].club)) clubs.push_back(table_teams[i].club);
		else if (!checked_order)
		{
			// if Clausura winner is behind, swap them with Apertura winner
			if (table_teams[i].club == clubs[1]) iter_swap(clubs.begin(), clubs.begin() + 1);
			checked_order = true;
		}
	}

	if (clubs.size() != aggregate->n_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
	}

	for (size_t i = 0; i < clubs.size(); i++) {
		clubs[i]->ClubLastDivision = data->competition_db;
		clubs[i]->ClubLastPosition = (char)i + 1;
	}
	return 1;
}

void __declspec(naked) mex_second_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call mex_second_last_positions
		add esp, 0x4
		ret
	}
}

void mex_second_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = GoalsForAwayTiebreaker;
	comp_data->tiebreaker_4 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 8;
	comp_data->rele_playoff = 8;
	comp_data->relegations = 0;

	comp_data->promotes_to = MEX_FIRST_9CF();
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) mex_second_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call mex_second_subs
		add esp, 0x4
		ret
	}
}

int mex_second_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	// Count the number of teams first, as the code really expects us to know up front
	vector<cm3_clubs*> d1_clubs = find_clubs_of_comp(CompID);
	comp_data->teams2 = (DWORD*)cm0102_malloc(d1_clubs.size() * 4);
	comp_data->n_teams = (WORD)d1_clubs.size();

	for (WORD i = 0; i < comp_data->n_teams; i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)d1_clubs[i];
	}

	comp_data->team_league_table = (DWORD*)cm0102_malloc(comp_data->n_teams * league_team_list_sz);
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

int mex_second_vtable2(BYTE* _this, BYTE* round_data, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	sub_685D30(_this, round_data, a3);

	char curr_stage = *(char*)(round_data + 0x42);
	if (curr_stage < 1)
	{
		DWORD* f8 = comp_data->f8;
		comp_data->f8 = 0;
		*(BYTE*)(round_data + 0x42) = 3;
		sub_685D30(_this, round_data, a3);
		*(BYTE*)(round_data + 0x42) = curr_stage;
		comp_data->f8 = f8;
	}

	return 1;
}

void __declspec(naked) mex_second_vtable2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call mex_second_vtable2
		add esp, 0xc
		ret 0x8
	}
}

DWORD mex_second_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = Apertura;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
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
		AddFixture(pMem, fixture_id, Date(year, 9, 6), year, Saturday);
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
		AddFixture(pMem, fixture_id, Date(year, 10, 11), year, Saturday);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 1), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = Clausura;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 19), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AperturaPlayoffs;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 8, FixedTeamOrderInCup, HigherSeedingTiebreak, 5, 8, 4, 8, 0, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 12), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 8, FixedTeamOrderInCup, HigherSeedingTiebreak, 5, 4, 2, 0, 0, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Final, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 5, 2, 1, 0, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = ClausuraPlayoffs;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 20), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 23), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 8, FixedTeamOrderInCup, HigherSeedingTiebreak, 5, 8, 4, 8, 0, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 27), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 30), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 8, FixedTeamOrderInCup, HigherSeedingTiebreak, 5, 4, 2, 0, 0, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 4), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Final, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 5, 2, 1, 0, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) mex_second_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call mex_second_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void mex_second_setup_close(BYTE* _this) {
	BYTE idx = 0;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < data->n_teams; i++)
	{
		*((DWORD*)(&pTeams[i])) = all_teams[i];
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, data->n_teams, pTeams, data->n_rounds, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void mex_second_open_playoff(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void mex_second_close_playoff(BYTE* _this) {
	char stage_num = 2;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void mex_second_league_table(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE idx = 3;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < data->n_teams; i++)
	{
		*((DWORD*)(&pTeams[i])) = all_teams[i];
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 0, 0, 0 };
	short f217 = 0;
	create_league_stage_data(pStage, _this, (short)data->n_teams, pTeams, 0, (DWORD)(data->competition_db), pFixtures, 30,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 1, 0, f217, -1, 0, data->f225);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

char mex_second_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	sub_687970(_this, 0);
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
	mex_second_subs(_this);
	mex_second_add_teams(_this);
	sub_6835C0(_this);
	mex_second_setup_close(_this);
	mex_second_open_playoff(_this);
	mex_second_close_playoff(_this);
	mex_second_league_table(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) mex_second_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call mex_second_update
		add esp, 0x4
		ret
	}
}

void mex_second_open_playoff_teams(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			clubs.push_back(tls.club);
		}
	}
	BYTE team_order[8] = { 0,4,2,6,7,3,5,1 };

	for (char i = 0; i < playoff_teams; i++) {
		teams[team_order[i]].club = clubs[i];
		teams[team_order[i]].seeding = i + 1;
	}
}

void mex_second_close_playoff_teams(BYTE* _this) {
	char stage_num = 2;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = (comp_stats*)(comp_data->stages[0]);
	WORD total_teams = curr_stage->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			clubs.push_back(tls.club);
		}
	}
	BYTE team_order[8] = { 0,4,2,6,7,3,5,1 };

	for (char i = 0; i < playoff_teams; i++) {
		teams[team_order[i]].club = clubs[i];
		teams[team_order[i]].seeding = i + 1;
	}
}

int mex_second_table_fates(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		WORD num_teams = comp_data->n_teams;
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), AperturaPlayoffs, QuarterFinal, 0x1E);
			return 0;
		case BottomPlayoff:
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				table[i].league_fate = Eliminated;
			}
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 0) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[stage]);
		WORD num_teams = comp_data->n_teams;
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), ClausuraPlayoffs, QuarterFinal, 0x1E);
			return 0;
		case BottomPlayoff:
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				table[i].league_fate = Eliminated;
			}
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
		BYTE* stage_data = (BYTE*)comp_data->stages[stage];
		BYTE* rounds = ((comp_stats*)(stage_data))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			DWORD v1 = *(DWORD*)stage_data;
			switch (fate) {
			case TopPlayoff:
				staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
				table[i].league_fate = Champions;
				*a5 = 1;
				(*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data);
				return 0;
			case Promoted:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
				return 0;
			case BottomPlayoff:
				staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
				table[i].league_fate = Eliminated;
				return 0;
			default:
				staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
				table[i].league_fate = Eliminated;
				return 0;
			}
		}
	}
	else if (stage == 2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* stage_data = (BYTE*)comp_data->stages[stage];
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[0]);
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			DWORD v1 = *(DWORD*)stage_data;
			switch (fate) {
			case TopPlayoff:
				staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
				table[i].league_fate = Champions;
				*a5 = 1;
				(*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data);
				return 0;
			case Promoted:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
				return 0;
			case BottomPlayoff:
				staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
				table[i].league_fate = Eliminated;
				return 0;
			default:
				staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
				table[i].league_fate = Eliminated;
				return 0;
			}
		}
	}
	return 0;
}

void __declspec(naked) mex_second_table_fates_c()
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
		call mex_second_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void mex_second_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 1) {
		if (min < 9) ret_min = 1;
		if (max < 9) ret_max = 9;
		if (ret_current > ret_max) ret_current = ret_max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) mex_second_reputation_calc_c()
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
		call mex_second_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char mex_second_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		comp_stats* open_playoff = (comp_stats*)comp_data->stages[1];
		teams_seeded* open_teams = (teams_seeded*)open_playoff->teams_list;
		if (!open_teams[0].club) {
			bool is_finished = true;
			WORD total_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 15) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				mex_second_open_playoff_teams(_this);
			}
		}
		comp_stats* close_playoff = (comp_stats*)comp_data->stages[2];
		teams_seeded* close_teams = (teams_seeded*)close_playoff->teams_list;
		if (!close_teams[0].club) {
			comp_stats* curr_stage = (comp_stats*)(comp_data->stages[0]);
			bool is_finished = true;
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 15) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				mex_second_close_playoff_teams(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) mex_second_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call mex_second_table_split
		add esp, 0xc
		ret 8
	}
}

void mex_second_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(mex_second_vtable->vtable_ptr);
	mex_second_vtable->SetPointer(VTableSubsRounds, (DWORD)&mex_second_subs_c);
	mex_second_vtable->SetPointer(VTableInitFree, (DWORD)&mex_second_free_c);
	mex_second_vtable->SetPointer(VTableEoSUpdate, (DWORD)&mex_second_update_c);
	mex_second_vtable->SetPointer(VTableFixtures, (DWORD)&mex_second_fixtures_c);
	mex_second_vtable->SetPointer(VTableSetChampion, (DWORD)&mex_second_set_champion_c);
	mex_second_vtable->SetPointer(VTablePostMatchUpdate, (DWORD)&mex_second_vtable2_c);
	mex_second_vtable->SetPointer(VTableUpdateLastDivision, (DWORD)&mex_second_last_positions_c);
	mex_second_vtable->SetPointer(VTableLeagueSplit, (DWORD)&mex_second_table_split_c);
	mex_second_vtable->SetPointer(VTableReputationCalc, (DWORD)&mex_second_reputation_calc_c);
	mex_second_vtable->SetPointer(VTableTableFates, (DWORD)&mex_second_table_fates_c);
	//if (configFile.GetBool("showThirdPlaceInHistory", true)) mex_second_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesMexico;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 10000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 4;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	mex_second_subs(_this);
	mex_second_add_teams(_this);
	sub_6835C0(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	mex_second_setup_close(_this);
	mex_second_open_playoff(_this);
	mex_second_close_playoff(_this);
	mex_second_league_table(_this);
	sub_6827D0(_this, 0);
	league_reputation_setup_generic_68A850(_this);
}

void setup_mex_second()
{
}