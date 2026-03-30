#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

DWORD* gre_second_vtable = (DWORD*)0x96B61C;

char* gre_second_set_champion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	if (data->year == 2025)
	{
		BYTE* stage_data_for_history = (BYTE*)data->stages[1];
		DWORD v1 = *(DWORD*)stage_data_for_history;
		return (*(char*(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
	}
	else return sub_684640(_this);
}

void __declspec(naked) gre_second_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_second_set_champion
		add esp, 0x4
		ret 0
	}
}

void gre_second_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = gre_second_vtable;
	DWORD x = 0;
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
	DWORD y = -1;
	sub_682300(_this);
}

void gre_second_free(BYTE* _this, BYTE a2) {
	gre_second_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) gre_second_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call gre_second_free
		add esp, 0x8
		ret 4
	}
}

void gre_second_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->year == 2025) comp_data->n_rounds = 3;
	else comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->f82 = 2;
	if (comp_data->year == 2025) comp_data->promotions = 1;
	else comp_data->promotions = 2;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	if (comp_data->year == 2025) comp_data->relegations = 4;
	else comp_data->relegations = 3;

	comp_data->promotes_to = GRE_FIRST_9CF();
	comp_data->relegates_to = -1;

	if (comp_data->year == 2025) comp_data->f217 = 0x2;
	else comp_data->f217 = 0x3;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) gre_second_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_second_subs
		add esp, 0x4
		ret
	}
}

DWORD gre_second_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (year == 2025)
	{
		if (stage_idx < 1) {
			if (a5)
				*a5 = 1;
			BYTE* pMem = NULL;
			DWORD CompID = data->competition_db->ClubCompID;
			BYTE numberOfLeagueTeams = 10;
			*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
			*stage_name_id = NorthernSouthernSection + stage_idx;

			pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

			int fixture_id = 0;
			int tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 11), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 12, 21), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 22), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 15), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 22), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);

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
			AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 27), year, Monday);
			AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
			FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 2, 0, 0, 1, 0);

			return (DWORD)pMem;
		}
	}
	else {
		if (stage_idx < 0) {
			if (a5)
				*a5 = 1;
			BYTE* pMem = NULL;
			DWORD CompID = data->competition_db->ClubCompID;
			BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
			*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
			*stage_name_id = None;

			pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

			int fixture_id = 0;
			int tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 11), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 12, 21), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 22), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 15), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 22), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);

			check_number_of_fixtures(_this, fixture_id, *num_rounds);

			return (DWORD)pMem;
		}
	}
	return 0;
}

void __declspec(naked) gre_second_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gre_second_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void gre_second_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = GRE_SECOND_SOUTH_9CF();
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
	create_league_stage_data(pStage, _this, 10, pTeams, 3, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void gre_second_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->year == 2025) {
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
	else reputation_setup_generic_68A850(_this);
}

void __declspec(naked) gre_second_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_second_reputation_setup
		add esp, 0x4
		ret
	}
}

void block_reserve_promotion_gre_second(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	if (comp_data->year == 2025)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
				if (ret_club && !is_main_club) {
					table_teams[i].league_fate = CantBePromoted;
				}
			}
		}
	}
	else {
		WORD total_teams = comp_data->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
			if (ret_club && !is_main_club) {
				table_teams[i].league_fate = CantBePromoted;
			}
		}
	}
}

char gre_second_update(BYTE* _this) {
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
	data->num_stages = 0;
	if (data->stages) {
		sub_9452CA_free(data->stages);
		data->stages = 0;
	}
	*((DWORD*)(_this + 0xA7)) = -1;
	gre_second_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	block_reserve_promotion_gre_second(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) gre_second_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_second_update
		add esp, 0x4
		ret
	}
}

int gre_second_table_indicators(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 1) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, PromotionPlayoff, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RelegationPlayoff, 0x1E);
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
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
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
				case TopPlayoff:
					staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					if(table[i].league_fate != CantBePromoted) table[i].league_fate = Champions;
					*a5 = 1;
					return 0;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				case BottomPlayoff:
					staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
					return 0;
				default:
					staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
					return 0;
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) gre_second_set_table_fate()
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
		call gre_second_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void gre_second_awards(BYTE* _this, DWORD** team_list, WORD* total_teams) {
	comp_stats* comp_data = (comp_stats*)_this;
	if (comp_data->year == 2025)
	{
		*total_teams = 20;
		DWORD* pMem = (DWORD*)sub_944E46_malloc(4 * (*total_teams));
		*team_list = pMem;

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
	else {
		*total_teams = 16;
		DWORD* pMem = (DWORD*)sub_944E46_malloc(4 * (*total_teams));
		*team_list = pMem;

		WORD idx = 0;
		for (WORD num = 0; num < comp_data->n_teams; num++) {
			cm3_clubs* club = ((team_league_stats*)comp_data->team_league_table)[num].club;
			pMem[idx++] = (DWORD)club;
		}
	}
}

void __declspec(naked) gre_second_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gre_second_awards
		add esp, 0xc
		ret 8
	}
}

void gre_second_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (comp_data->year == 2025)
	{
		if (stage < 1) {
			ret_current = 1 + 2 * (current - 1);
			ret_min = 1 + 2 * (min - 1);
			ret_max = 1 + 2 * (max - 1);
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) gre_second_reputation_calc_c()
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
		call gre_second_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void gre_second_playoffs_champ(BYTE* _this) {
	char stage_num = 1;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		*((DWORD*)(&pTeams[al + 1])) = (DWORD)table_teams[0].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void gre_second_playoffs_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	if (comp_data->year == 2025)
	{
		long current = comp_data->current_stage;
		long max = comp_data->num_stages;
		if (current < max - 1) {
			current++;
			if (current == 1) {
				comp_data->current_stage = current;
				gre_second_playoffs_champ(_this);
			}
		}
	}
}

void __declspec(naked) gre_second_playoffs_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_second_playoffs_create
		add esp, 0x4
		ret
	}
}

void gre_second_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = gre_second_vtable;
	data->year = year;
	data->rules = RulesGreece;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = 0;
	comp->ClubCompForegroundColour = 0;
	data->min_stadium_capacity = 500;
	data->min_stadium_seats = 500;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 2;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	gre_second_subs(_this);
	AddTeamsGroupLeague(_this, GRE_SECOND_NORTH_9CF());
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		gre_second_setup_groups(_this, i);
	}
	block_reserve_promotion_gre_second(_this);
	gre_second_reputation_setup(_this);
}

void setup_gre_second()
{
	WriteVTablePtr(gre_second_vtable, VTableInitFree, (DWORD)&gre_second_free_c);
	WriteVTablePtr(gre_second_vtable, VTableEoSUpdate, (DWORD)&gre_second_update_c);
	WriteVTablePtr(gre_second_vtable, VTableFixtures, (DWORD)&gre_second_fixtures_c);
	WriteVTablePtr(gre_second_vtable, VTableReputationSetup, (DWORD)&gre_second_reputation_setup_c);
	WriteVTablePtr(gre_second_vtable, VTableReputationCalc, (DWORD)&gre_second_reputation_calc_c);
	WriteVTablePtr(gre_second_vtable, VTableAwardTeamsSetup, (DWORD)&gre_second_awards_c);
	WriteVTablePtr(gre_second_vtable, VTableSubsRounds, (DWORD)&gre_second_subs_c);
	WriteVTablePtr(gre_second_vtable, VTableTableFates, (DWORD)&gre_second_set_table_fate);
	WriteVTablePtr(gre_second_vtable, VTableSetChampion, (DWORD)&gre_second_set_champion_c);
	WriteVTablePtr(gre_second_vtable, VTablePlayoffQual, (DWORD)&gre_second_playoffs_create_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(gre_second_vtable, VTable21, 0x4110b0);
}