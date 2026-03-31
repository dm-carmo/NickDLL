#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* hol_second_vtable = (DWORD*)0x96B86C;

char* hol_second_set_champion(BYTE* _this) {
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

void __declspec(naked) hol_second_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call hol_second_set_champion
		add esp, 0x4
		ret 0
	}
}

void hol_second_block_promotion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
		if (ret_club && !is_main_club) {
			table_teams[i].league_fate = CantBePromoted;
		}
	}
}

void hol_second_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 2;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = HOL_FIRST_9CF();
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

void __declspec(naked) hol_second_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call hol_second_subs
		add esp, 0x4
		ret
	}
}

DWORD hol_second_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 8), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 15), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 22), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 29), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 12), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 16), year, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 19), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 26), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 30), year, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 3), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 17), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 21), year, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 24), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 31), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 7), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 21), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 25), year, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 28), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 5), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 12), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 19), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 13), year, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 16), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 23), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 30), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 6), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 13), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 20), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 27), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 6), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 13), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 17), year, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 20), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 3), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 7), year, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 10), year, Friday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 17), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 24), year, Friday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = PromotionPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 28), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 4, 2, 4, 0, 0, 2, 4);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 5), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 4, 2, 2, 4, 0, 2, 4);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 12), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 2, 1, 0, 0, 0, 2, 4);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) hol_second_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call hol_second_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void hol_second_points_deductions(BYTE* _this, WORD current_year)
{
	if (current_year > 2025) return;
	cm3_clubs* vitesse = find_club("Vitesse Arnhem");
	if (vitesse) {
		comp_stats* data = (comp_stats*)_this;
		WORD total_teams = data->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats* tls = &table_teams[i];
			if (tls->club == vitesse) {
				tls->points = -12;
				tls->points_away = -12;
				return;
			}
		}
	}
}

void hol_second_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = hol_second_vtable;
	data->year = year;
	data->rules = RulesHolland;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_RED_1_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 5;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	hol_second_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, 1903220, 0);
	hol_second_block_promotion(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
	hol_second_points_deductions(_this, year);
}

void __fastcall hol_second_create_periods(BYTE* _this, char stage_idx) {
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(comp_data->n_teams * 4);
	BYTE prom_rel[4] = { 0, 1, 0, 0 };

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)table_teams[i].club;
	}

	WORD stage_name_id = None;
	if (stage_idx >= 0 && stage_idx < 4) stage_name_id = Periods1to4 + stage_idx;
	WORD num_rounds = 10;
	if (stage_idx >= 2 && stage_idx < 4) num_rounds = 9;

	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, comp_data->n_teams, pTeams, 1, (DWORD)(comp_data->competition_db), 0, 0,
		comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), &prom_rel[0],
		comp_data->year, stage_idx, stage_name_id, 0, 1, 0, 0x22, num_rounds, 0, 2);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_idx])) = (DWORD)pStage;

	comp_stats* period_data = (comp_stats*)pStage;
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate != NoFate) {
			team_league_stats* period_table = (team_league_stats*)(period_data->team_league_table);
			for (WORD j = 0; j < comp_data->n_teams; j++) {
				team_league_stats period_tls = period_table[j];
				if (tls.club == period_tls.club) {
					period_table[j].league_fate = Eliminated;
				}
			}
		}
	}

	comp_data->current_stage = stage_idx;
}

int hol_second_vtable2(BYTE* _this, BYTE* round_data, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	sub_685D30(_this, round_data, a3);
	BYTE curr_stage = *(BYTE*)(round_data + 0x42);
	if (curr_stage != (BYTE)-1) return 1;
	WORD n_rounds = *(BYTE*)(round_data + 0x34);
	if (n_rounds < 10) *(BYTE*)(round_data + 0x42) = 0;
	else if (n_rounds < 20) *(BYTE*)(round_data + 0x42) = 1;
	else if (n_rounds < 29) *(BYTE*)(round_data + 0x42) = 2;
	else *(BYTE*)(round_data + 0x42) = 3;
	while (comp_data->current_stage < *(BYTE*)(round_data + 0x42)) {
		hol_second_create_periods(_this, (BYTE)comp_data->current_stage + 1); //5f6ad0
	}
	curr_stage = *(BYTE*)(round_data + 0x42);
	DWORD* stage_list = comp_data->stages;
	DWORD* f8 = comp_data->f8;
	comp_data->f8 = 0;
	BYTE* stage = (BYTE*)stage_list[curr_stage];
	DWORD v1 = *(DWORD*)stage;
	(*(int(__thiscall**)(BYTE*, BYTE*, int))(v1 + 0x4))(stage, round_data, a3);
	comp_data->f8 = f8;
	*(BYTE*)(round_data + 0x42) = (BYTE)-1;
	return 1;
}

void __declspec(naked) hol_second_vtable2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call hol_second_vtable2
		add esp, 0xc
		ret 0x8
	}
}

char hol_second_update(BYTE* _this) {
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
	hol_second_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, 1903220, 0);
	hol_second_block_promotion(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) hol_second_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call hol_second_update
		add esp, 0x4
		ret
	}
}

void hol_second_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 4) {
		ret_current = 2 + current;
		ret_min = 2 + min;
		ret_max = 2 + max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) hol_second_reputation_calc_c()
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
		call hol_second_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void hol_second_playoff_prom(BYTE* _this) {
	char stage_num = 4;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 6;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	BYTE team_order[6] = { 4,5,0,2,3,1 };
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
			hol_second_reputation_calc(_this, (BYTE*)table_teams[i].club, comp_data->f68, 3, 3, 8);
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
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void hol_second_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		if (current == 4) {
			comp_data->current_stage = current;
			hol_second_playoff_prom(_this);
		}
	}
}

void __declspec(naked) hol_second_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call hol_second_playoffs_c
		add esp, 0x4
		ret
	}
}

int hol_second_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 4) {
		cm3_club_comps* hol_first = get_comp(HOL_FIRST_9CF());
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)hol_first, None, Playoff, 0xF);
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

void __declspec(naked) hol_second_set_table_fate()
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
		call hol_second_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void setup_hol_second()
{
	WriteVTablePtr(hol_second_vtable, VTableSubsRounds, (DWORD)&hol_second_subs_c);
	WriteVTablePtr(hol_second_vtable, VTablePostMatchUpdate, (DWORD)&hol_second_vtable2_c);
	WriteVTablePtr(hol_second_vtable, VTableEoSUpdate, (DWORD)&hol_second_update_c);
	WriteVTablePtr(hol_second_vtable, VTableFixtures, (DWORD)&hol_second_fixtures_c);
	WriteVTablePtr(hol_second_vtable, VTableReputationCalc, (DWORD)&hol_second_reputation_calc_c);
	WriteVTablePtr(hol_second_vtable, VTablePlayoffQual, (DWORD)&hol_second_playoffs_create);
	WriteVTablePtr(hol_second_vtable, VTableTableFates, (DWORD)&hol_second_set_table_fate);
	WriteVTablePtr(hol_second_vtable, VTableSetChampion, (DWORD)&hol_second_set_champion_c);
	WriteVTablePtr(hol_second_vtable, VTableStageNews, 0x48c6d0);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(hol_second_vtable, VTable21, 0x4110b0);
}
