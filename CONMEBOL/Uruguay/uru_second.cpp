#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

vtable* uru_second_vtable = new vtable((BYTE*)0x96CAF4, 0xB4);

void uru_second_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(uru_second_vtable->vtable_ptr);
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

void uru_second_free(BYTE* _this, BYTE a2) {
	uru_second_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) uru_second_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call uru_second_free
		add esp, 0x8
		ret 4
	}
}

char* uru_second_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* playoff_bytes = (BYTE*)comp_data->stages[3];
	comp_stats* playoff_data = (comp_stats*)playoff_bytes;
	comp_stats* league_data = (comp_stats*)comp_data->stages[2];
	cm3_clubs* po_win = 0;
	teams_seeded* teams = (teams_seeded*)playoff_data->teams_list;
	for (WORD i = 0; i < playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) po_win = teams[i].club;
	}
	team_league_stats* table = (team_league_stats*)(league_data->team_league_table);
	cm3_clubs* first = table[0].club;
	cm3_clubs* second = table[1].club;
	cm3_clubs* third = table[2].club;
	return sub_4AFCE0_add_history_entry(_this, first, second, third, po_win);
}

void __declspec(naked) uru_second_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_second_set_champion
		add esp, 0x4
		ret 0
	}
}

int uru_second_last_positions(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* league_data = (BYTE*)data->stages[2];
	DWORD v1 = *(DWORD*)league_data;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(league_data);
}

void __declspec(naked) uru_second_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_second_last_positions
		add esp, 0x4
		ret
	}
}

int uru_second_vtable2(BYTE* _this, BYTE* round_data, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	sub_685D30(_this, round_data, a3);

	char curr_stage = *(char*)(round_data + 0x42);
	if (curr_stage < 1)
	{
		DWORD* f8 = comp_data->f8;
		comp_data->f8 = 0;
		*(BYTE*)(round_data + 0x42) = 2;
		sub_685D30(_this, round_data, a3);
		*(BYTE*)(round_data + 0x42) = curr_stage;
		comp_data->f8 = f8;
	}

	return 1;
}

void __declspec(naked) uru_second_vtable2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_second_vtable2
		add esp, 0xc
		ret 0x8
	}
}

void uru_second_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = URU_FIRST_9CF();
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) uru_second_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_second_subs
		add esp, 0x4
		ret
	}
}

int uru_second_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	WORD numberOfLeagueTeams = CountNumberOfTeamsInComp(CompID);
	comp_data->teams2 = (DWORD*)cm0102_malloc(numberOfLeagueTeams * 4);
	comp_data->n_teams2 = numberOfLeagueTeams;
	vector<cm3_clubs*> clubs = find_clubs_of_comp(CompID);
	shuffle(clubs.begin(), clubs.end(), rng);
	for (DWORD i = 0; i < clubs.size(); i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)clubs[i];
	}

	comp_data->n_teams = 7; // number of teams per group in this case
	comp_data->team_league_table = (DWORD*)cm0102_malloc(comp_data->n_teams * league_team_list_sz);
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

void uru_second_setup_playoff_1(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = stage_num;
}

void uru_second_setup_groups(BYTE* _this) {
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
		cm3_clubs* club = (cm3_clubs*)all_teams[data->n_teams * (idx + 1) + i];
		*((DWORD*)(&pTeams[i])) = (DWORD)club;
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

	uru_second_setup_playoff_1(_this);
}

void uru_second_setup_league(BYTE* _this) {
	BYTE idx = 2;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams2 * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < data->n_teams2; i++)
	{
		*((DWORD*)(&pTeams[i])) = all_teams[i];
	}
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 2, 3, 0, 2 };
	short f217 = 3;
	create_league_stage_data(pStage, _this, (short)data->n_teams2, pTeams, 2, (DWORD)(data->competition_db), pFixtures, 32,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 1, 0, f217, -1, 0, 2);
	*((WORD*)(pStage + 0xA7)) = 32; // total number of games each team will play
	*((DWORD*)(pStage + 0xA3)) = 0;
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

DWORD uru_second_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = ((comp_stats*)_this);
	WORD year = data->year;
	if (stage_idx < 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		*num_rounds = 7;
		*stage_name_id = AperturaGroupsAtoB + stage_idx + 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 29), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 5), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 19), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		*num_rounds = 1;
		*stage_name_id = Apertura;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 20), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 26), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 8, FixedTeamOrderInCup | Penalties | ExtraTime, NoTiebreak, 5, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		*num_rounds = 26;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 10), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 3) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		*num_rounds = 2;
		*stage_name_id = PromotionPlayoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, FixedTeamOrderInCup | NoAwayGoals, HigherSeedingTiebreak | NoAwayGoals, 5, 4, 2, 4, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Final, 1, NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 0, 2, 1, 0, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) uru_second_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_second_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int uru_second_table_fates(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 1) {
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), Apertura, Final, 0x1E);
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = (comp_stats*)comp_data->stages[2];
		num_teams = curr_stage->n_teams;
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), PromotionPlayoff, None, 0x1E);
				//table[i].league_fate = TopPlayoff;
				*a5 = 1;
				return 0;
			case Promoted:
				return 0;
			case BottomPlayoff:
				return 0;
			default:
				return 0;
			}
		}
	}
	else if (stage == 2) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), PromotionPlayoff, None, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), RelegationPlayoff, None, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 3) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = (comp_stats*)comp_data->stages[2];
		num_teams = curr_stage->n_teams;
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x32);
				table[i].league_fate = Promoted;
				*a5 = 1;
				return 0;
			case Promoted:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
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

void __declspec(naked) uru_second_table_fates_c()
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
		call uru_second_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

char uru_second_update(BYTE* _this) {
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
	uru_second_subs(_this);
	uru_second_add_teams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("uru_second_tv_money"), 0);
	sub_6835C0(_this);
	uru_second_setup_groups(_this);
	uru_second_setup_league(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) uru_second_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_second_update
		add esp, 0x4
		ret
	}
}

void uru_second_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		DWORD* all_teams = comp_data->teams2;
		vector<cm3_clubs*> clubs;
		for (DWORD i = 0; i < comp_data->n_teams2; i++) clubs.push_back((cm3_clubs*)all_teams[i]);
		sort(clubs.begin(), clubs.end(), compareClubRep);
		for (size_t i = 0; i < clubs.size(); i++) {
			cm3_clubs* c = clubs[i];
			sub_4A2540((BYTE*)comp_data->f8, c, (char)i + 1);
		}
	}
}

void __declspec(naked) uru_second_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_second_reputation_setup
		add esp, 0x4
		ret
	}
}

void uru_second_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 1) {
		ret_current = 1 + 2 * (current - 1);
		ret_min = 1 + 2 * (min - 1);
		if (max < 2) ret_max = 2;
		else ret_max = 1 + 2 * (max - 1);
	}
	else if (stage == 1) {
		ret_current = 2 + current;
		ret_min = 2 + min;
		ret_max = 2 + max;
	}
	else if (stage == 2) {
		// do nothing
	}
	else if (stage == 3) {
		ret_current = 2 + current;
		ret_min = 2 + min;
		ret_max = 2 + max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) uru_second_reputation_calc_c()
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
		call uru_second_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void uru_second_playoff_1_teams(BYTE* _this) {
	char stage_num = 1;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	comp_stats* playoff = (comp_stats*)data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Qualified1 || tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
				break;
			}
		}
	}

	for (char i = 0; i < playoff_teams; i++) {
		teams[i].club = clubs[i];
		teams[i].seeding = i + 1;
	}
}

char uru_second_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		comp_stats* playoff_1 = (comp_stats*)comp_data->stages[1];
		teams_seeded* playoff_1_teams = (teams_seeded*)playoff_1->teams_list;
		if (!playoff_1_teams[0].club) {
			comp_stats* curr_stage = comp_data;
			bool is_finished = true;
			for (char al = -1; al < 1; al++) {
				if (al >= 0) {
					curr_stage = (comp_stats*)(comp_data->stages[al]);
				}
				WORD total_teams = curr_stage->n_teams;
				team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
				for (int i = 0; i < total_teams; i++) {
					team_league_stats tls = table_teams[i];
					if (tls.games < 6) {
						is_finished = false;
						break;
					}
				}
			}
			if (is_finished) {
				uru_second_playoff_1_teams(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) uru_second_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_second_table_split
		add esp, 0xc
		ret 8
	}
}

void uru_second_playoffs_prom(BYTE* _this) {
	char stage_num = 3;
	DWORD v1 = *(DWORD*)_this;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* league_data = (comp_stats*)comp_data->stages[2];
	BYTE playoff_teams = 4;
	WORD total_teams = league_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	BYTE team_order[4] = { 0,2,3,1 };
	BYTE seeds[4] = { 0 };

	// 1. try to get Opening Final winner into playoffs
	BYTE* playoff_bytes = (BYTE*)comp_data->stages[1];
	comp_stats* playoff_data = (comp_stats*)playoff_bytes;
	cm3_clubs* po_win = 0;
	teams_seeded* teams = (teams_seeded*)playoff_data->teams_list;
	for (WORD i = 0; i < playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) po_win = teams[i].club;
	}

	team_league_stats* table_teams = (team_league_stats*)(league_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.club == po_win)
		{
			if (tls.league_fate == NoFate || tls.league_fate == Eliminated) {
				tls.league_fate = TopPlayoff;
			}
			break;
		}
	}

	// 2. count how many teams are in the playoffs already
	int n_quals = 0;
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			n_quals++;
		}
	}

	// 3. while number is different from 4 (number of needed teams):
	for (int i = 0; i < total_teams && n_quals < playoff_teams; i++) {
		team_league_stats tls = table_teams[i];
		// 2.1. get team not in playoffs yet
		if (tls.league_fate == NoFate) {
			// 2.2. set table fate
			table_teams[i].league_fate = TopPlayoff;
			n_quals++;
			league_data->prom_playoff++;
			// 2.3. call 0x40
			(*(int(__thiscall**)(BYTE*, BYTE*, int, int, int, int))(v1 + 0x40))(_this, (BYTE*)table_teams[i].club, 1, league_data->f68, 0, 0);
		}
	}

	vector<cm3_clubs*> clubs;
	for (char i = league_data->promotions, j = 0; i < total_teams && j < playoff_teams; i++) {
		if (table_teams[i].league_fate == TopPlayoff) {
			clubs.push_back(table_teams[i].club);
			j++;
		}
	}
	for (char i = 0; i < playoff_teams; i++) {
		seeds[team_order[i]] = i;
		*((DWORD*)(&pTeams[team_order[i]])) = (DWORD)clubs[i];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, &seeds[0]);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void uru_second_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 3) {
			uru_second_playoffs_prom(_this);
		}
	}
}

void __declspec(naked) uru_second_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_second_playoffs_c
		add esp, 0x4
		ret
	}
}

void uru_second_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(uru_second_vtable->vtable_ptr);
	uru_second_vtable->SetPointer(VTableEoSUpdate, (DWORD)&uru_second_update_c);
	uru_second_vtable->SetPointer(VTableSubsRounds, (DWORD)&uru_second_subs_c);
	uru_second_vtable->SetPointer(VTableFixtures, (DWORD)&uru_second_fixtures_c);
	uru_second_vtable->SetPointer(VTableInitFree, (DWORD)&uru_second_free_c);
	uru_second_vtable->SetPointer(VTableTableFates, (DWORD)&uru_second_table_fates_c);
	uru_second_vtable->SetPointer(VTableReputationCalc, (DWORD)&uru_second_reputation_calc_c);
	uru_second_vtable->SetPointer(VTableReputationSetup, (DWORD)&uru_second_reputation_setup_c);
	uru_second_vtable->SetPointer(VTableLeagueSplit, (DWORD)&uru_second_table_split_c);
	uru_second_vtable->SetPointer(VTablePlayoffQual, (DWORD)&uru_second_playoffs_create);
	uru_second_vtable->SetPointer(VTablePostMatchUpdate, (DWORD)&uru_second_vtable2_c);
	uru_second_vtable->SetPointer(VTableUpdateLastDivision, (DWORD)&uru_second_last_positions_c);
	uru_second_vtable->SetPointer(VTableSetChampion, (DWORD)&uru_second_set_champion_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) uru_second_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	if (configFile.GetBool("showPlayoffWinnerInHistory", true)) uru_second_vtable->SetPointer(VTableShowHostsInHistory, 0x404480);
	data->year = year;
	data->rules = RulesUruguay;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 4;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	uru_second_subs(_this);
	uru_second_add_teams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("uru_second_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	uru_second_setup_groups(_this);
	uru_second_setup_league(_this);
	sub_6827D0(_this, 0);
	league_reputation_setup_generic_68A850(_this);
}

void setup_uru_second()
{

}