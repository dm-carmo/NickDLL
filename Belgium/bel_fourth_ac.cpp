#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* bel_fourth_ac_vtable = new vtable((BYTE*)0x96B86C, 0xB4);

char* bel_fourth_ac_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* playoff_bytes = (BYTE*)comp_data->stages[4];
	comp_stats* playoff_data = (comp_stats*)playoff_bytes;
	cm3_clubs* third = 0;
	teams_seeded* teams = (teams_seeded*)playoff_data->teams_list;
	for (WORD i = 0; i < playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) third = teams[i].club;
	}
	team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
	cm3_clubs* first = table[0].club;
	cm3_clubs* second = table[1].club;
	return sub_4AFCE0_add_history_entry(_this, first, second, third, 0);
}

void __declspec(naked) bel_fourth_ac_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bel_fourth_ac_set_champion
		add esp, 0x4
		ret 0
	}
}

void bel_fourth_ac_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(bel_fourth_ac_vtable->vtable_ptr);
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

void bel_fourth_ac_free(BYTE* _this, BYTE a2) {
	bel_fourth_ac_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) bel_fourth_ac_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call bel_fourth_ac_free
		add esp, 0x8
		ret 4
	}
}

void bel_fourth_ac_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GamesWonTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->tiebreaker_4 = GoalsForAwayTiebreaker;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 3;

	comp_data->promotes_to = BEL_FOURTH_VV_9CF();
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	*(BYTE*)(_this + 0xEE) = 0;
	*(BYTE*)(_this + 0xEF) = 0;
	*(BYTE*)(_this + 0xF0) = 0;
	*(BYTE*)(_this + 0xF1) = 0;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) bel_fourth_ac_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bel_fourth_ac_subs
		add esp, 0x4
		ret
	}
}

DWORD bel_fourth_ac_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
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
		AddFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
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
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 21), year, Wednesday, Evening);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 4), year, Wednesday, Evening);
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
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 28), year, Saturday);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = PromotionPlayoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 11), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 17), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) bel_fourth_ac_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call bel_fourth_ac_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void block_reserve_promotion_bel_fourth_ac(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
		if (ret_club && !is_main_club) {
			if (ret_club->ClubDivision->ClubCompID != BEL_FIRST_9CF() || ret_club->ClubDivision->ClubCompID != BEL_SECOND_9CF())
				table_teams[i].league_fate = CantBePromoted;
		}
	}
}

char bel_fourth_ac_update(BYTE* _this) {
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
	bel_fourth_ac_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	block_reserve_promotion_bel_fourth_ac(_this);
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) bel_fourth_ac_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bel_fourth_ac_update
		add esp, 0x4
		ret
	}
}

void bel_fourth_ac_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 4) {
		ret_current = 1 + current;
		ret_min = 1 + min;
		ret_max = 1 + max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) bel_fourth_ac_reputation_calc_c()
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
		call bel_fourth_ac_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void bel_fourth_ac_playoff_prom(BYTE* _this) {
	char stage_num = 4;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	BYTE team_order[4] = { 0,2,3,1 };
	DWORD v1 = *(DWORD*)_this;

	// 1. count how many teams are in the playoffs already
	int n_quals = 0;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			n_quals++;
		}
	}

	// 2. while number is different from 6 (number of needed teams):
	for (int i = 0; i < total_teams && n_quals < playoff_teams; i++) {
		team_league_stats tls = table_teams[i];
		// 2.1. get team not in playoffs yet
		if (tls.league_fate == NoFate) {
			// 2.2. set table fate
			table_teams[i].league_fate = TopPlayoff;
			n_quals++;
			// 2.3. call 0x40
			(*(int(__thiscall**)(BYTE*, BYTE*, int, int, int, int))(v1 + 0x40))(_this, (BYTE*)table_teams[i].club, 1, comp_data->f68, 0, 0);
			// 2.4. call reputation calc (not needed?)
			bel_fourth_ac_reputation_calc(_this, (BYTE*)table_teams[i].club, comp_data->f68, 3, 3, 8);
		}
	}

	for (int i = 0, j = 0; i < total_teams && j < playoff_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[team_order[j++]])) = (DWORD)tls.club;
		}
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void bel_fourth_ac_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		if (current == 4) {
			comp_data->current_stage = current;
			bel_fourth_ac_playoff_prom(_this);
		}
	}
}

void __declspec(naked) bel_fourth_ac_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bel_fourth_ac_playoffs_c
		add esp, 0x4
		ret
	}
}

int bel_fourth_ac_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 4) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
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
	else if (stage == -1) {
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
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage < 4) {
		if (fate == TopPlayoff) staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, PromotionPlayoff, 0x1E);
	}
	return 0;
}

void __declspec(naked) bel_fourth_ac_set_table_fate()
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
		call bel_fourth_ac_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void bel_fourth_ac_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(bel_fourth_ac_vtable->vtable_ptr);
	bel_fourth_ac_vtable->SetPointer(VTableInitFree, (DWORD)&bel_fourth_ac_free_c);
	bel_fourth_ac_vtable->SetPointer(VTableEoSUpdate, (DWORD)&bel_fourth_ac_update_c);
	bel_fourth_ac_vtable->SetPointer(VTableFixtures, (DWORD)&bel_fourth_ac_fixtures_c);
	bel_fourth_ac_vtable->SetPointer(VTableSubsRounds, (DWORD)&bel_fourth_ac_subs_c);
	bel_fourth_ac_vtable->SetPointer(VTableTableFates, (DWORD)&bel_fourth_ac_set_table_fate);
	bel_fourth_ac_vtable->SetPointer(VTableReputationCalc, (DWORD)&bel_fourth_ac_reputation_calc_c);
	bel_fourth_ac_vtable->SetPointer(VTablePlayoffQual, (DWORD)&bel_fourth_ac_playoffs_create);
	bel_fourth_ac_vtable->SetPointer(VTableSetChampion, (DWORD)&bel_fourth_ac_set_champion_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) bel_fourth_ac_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesBelgiumLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 5;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	bel_fourth_ac_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	block_reserve_promotion_bel_fourth_ac(_this);
	league_reputation_setup_generic_68A850(_this);
}

void setup_bel_fourth_ac()
{
}
