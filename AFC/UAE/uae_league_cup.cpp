#include <windows.h>
#include <filesystem>
#include <fstream>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

using namespace std;

vtable* uae_league_cup_vtable = new vtable((BYTE*)0x96C264, 0xB4);

void uae_league_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(uae_league_cup_vtable->vtable_ptr);
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

void uae_league_cup_free(BYTE* _this, BYTE a2) {
	uae_league_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) uae_league_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call uae_league_cup_free
		add esp, 0x8
		ret 4
	}
}

int uae_league_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[0];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) uae_league_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uae_league_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

void uae_league_cup_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	*((WORD*)(_this + 0xA7)) = 3;
	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 4;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	//comp_data->f82 = 3;

	comp_data->promotions = 8;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x28;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	//comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);
	comp_data->fixtures_table = (DWORD*)cm0102_malloc(fixture_dates_sz);
	BYTE* fixtures = (BYTE*)comp_data->fixtures_table;
	*((WORD*)(fixtures)) = *(WORD*)current_date;
	*((WORD*)(fixtures + 2)) = (*current_year) - comp_data->year;
	*((BYTE*)(fixtures + 4)) = 0;
	*((WORD*)(_this + 0xA9)) = 1;
	*((BYTE*)(_this + 0xDD)) = 0;

	return;
}

void __declspec(naked) uae_league_cup_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uae_league_cup_subs
		add esp, 0x4
		ret
	}
}

DWORD uae_league_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = LeagueStage;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 19), year, Saturday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 8), year, Thursday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 11), year, Sunday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 22), year, Thursday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 17), year, Thursday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 7), year, Thursday);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 8), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 19), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup | Penalties, NoTiebreak, 4, 8, 4, 8, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 20), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 25), year, Thursday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup | Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 26), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 29), year, Monday, Evening, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup | Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) uae_league_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uae_league_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void uae_league_cup_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		vector<cm3_clubs*> clubs;
		WORD total_teams = comp_data->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
		for (WORD i = 0; i < total_teams; i++) {
			clubs.push_back(table_teams[i].club);
		}
		sort(clubs.begin(), clubs.end(), compareClubRep);

		sub_4A2540((BYTE*)comp_data->f8, clubs[0], 1);
		sub_4A2540((BYTE*)comp_data->f8, clubs[1], 2);
		for (int i = 2; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 3);
		}
		for (int i = 4; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 8; i < 14; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (WORD i = 14; i < total_teams; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 15);
		}
	}
}

void __declspec(naked) uae_league_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uae_league_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void uae_league_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = current;
		if (min < 15) ret_min = 1;
		else ret_min = min;
		if (max < 15) ret_max = 9;
		else ret_max = max;
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 0) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) uae_league_cup_reputation_calc_c()
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
		call uae_league_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int uae_league_cup_all_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 14;
	BYTE* pMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	WORD year = data->year;
	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	// D1
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(UAE_PREMIER_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (WORD i = 0; i < total_teams; i++)
		add_team_call(_this, (BYTE)i, vec[i], 0, 0);

	return 1;
}

void uae_league_cup_setup_league_stage(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	WORD total_teams = data->n_teams;

	WORD year = data->year;
	team_league_stats* table = (team_league_stats*)data->team_league_table;

	char matchups[6][14] = {
		{11,9,13,2,7,8,3,1,6,14,12,10,4,5},
		{14,13,8,12,10,5,1,7,3,11,2,6,9,4},
		{1,11,2,14,9,3,6,13,7,10,5,12,8,4},
		{12,7,11,2,3,6,4,10,14,8,13,1,5,9},
		{2,5,11,14,4,7,13,9,10,3,6,12,1,8},
		{7,2,12,4,10,6,14,3,5,11,9,1,8,13},
	};

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, -1, &num_rounds, &stage_name_id, 0);
	data->n_games = stage_name_id;
	*((WORD*)(_this + 0xA7)) = num_rounds;

	for (BYTE m = 0; m < 6; m++) {
		BYTE* ptr_last = (BYTE*)(pFixtures + fixture_dates_sz * 5);
		match_data* match = new match_data();
		match->comp_id = data->competition_db->ClubCompID;
		match->f8 = -1;
		match->comp = data->competition_db;
		match->end_year = year + *(WORD*)(ptr_last + 2);
		match->end_day = *(WORD*)(ptr_last);
		match->current_year = year;
		match->sub_stage_id = 0;
		match->main_stage_id = stage_name_id;
		match->f54_0xdb = data->f219;
		match->tiebreaks = data->f171;
		match->f58_0xc4 = data->f196;
		match->f59 = -1;
		match->f61 = 0;
		match->f62 = 0;
		match->f64 = 1;
		match->f65 = 1;
		match->stage_number = -1;
		match->goals_home2 = -1;
		match->goals_away2 = -1;
		match->f69 = -1;
		match->f70 = -1;
		match->goals_home1 = -1;
		match->goals_away1 = -1;
		match->f73 = -1;
		match->f74 = -1;
		match->f75 = -1;
		match->f76 = -1;
		match->subs = 0x59; // force 9/5 subs

		vector<pair<char, char>> matchup_pairs;
		for (char t = 0; t < 7; t++) {
			char p1 = matchups[m][t * 2] - 1;
			char p2 = matchups[m][t * 2 + 1] - 1;
			cm3_clubs* home = table[p1].club;
			cm3_clubs* away = table[p2].club;
			BYTE* ptr = (BYTE*)(pFixtures + fixture_dates_sz * m);
			match->home_team_id = home->ClubID;
			match->away_team_id = away->ClubID;
			match->home_team = home;
			match->away_team = away;
			match->fixture_year = year + *(WORD*)(ptr + 2);
			match->fixture_day = *(WORD*)(ptr);
			match->fixture_number = m;
			match->f63 = *(BYTE*)(ptr + 4);

			sub_85C260((BYTE*)*(DWORD*)0xDD7EF4, *(DWORD*)(ptr + 0x3D), (BYTE*)match, data->f36);
			sub_5AA680((BYTE*)*(DWORD*)0xAE2A58, (BYTE*)match, 1);
		}
	}

	sub_9452CA_free(pFixtures);
	sub_684230(_this);
}

char uae_league_cup_update(BYTE* _this) {
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
	uae_league_cup_all_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	uae_league_cup_subs(_this);
	uae_league_cup_setup_league_stage(_this);
	//sub_6835C0(_this); -> done in function above instead
	sub_6827D0(_this, 0);
	return 1;
}

void __declspec(naked) uae_league_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uae_league_cup_update
		add esp, 0x4
		ret
	}
}

int uae_league_cup_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueStage, 0xF);
			return 0;
		}
	}
	else if (stage == 0) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
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
	return 0;
}

void __declspec(naked) uae_league_cup_table_fates_c()
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
		call uae_league_cup_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void uae_league_cup_final_stage_setup(BYTE* _this) {
	char stage_num = 0;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	BYTE team_order[8] = { 0,4,6,2,3,7,5,1 };

	vector<cm3_clubs*> clubs;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);

	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)table_teams[j].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	comp_data->current_stage = (long)stage_num;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_51C410(new_stage, 0);
}

void uae_league_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			uae_league_cup_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) uae_league_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uae_league_cup_stages_create
		add esp, 0x4
		ret
	}
}

int uae_league_cup_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 0) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) uae_league_cup_stage_news_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x28]
		push dword ptr[eax + 0x24]
		push dword ptr[eax + 0x20]
		push dword ptr[eax + 0x1c]
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uae_league_cup_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void uae_league_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->year = year;
	data->comp_vtable = (DWORD*)(uae_league_cup_vtable->vtable_ptr);
	uae_league_cup_vtable->SetPointer(VTableInitFree, (DWORD)&uae_league_cup_free_c);
	uae_league_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&uae_league_cup_update_c);
	uae_league_cup_vtable->SetPointer(VTablePlayoffQual, (DWORD)&uae_league_cup_stages_create_c);
	uae_league_cup_vtable->SetPointer(VTableSetChampion, (DWORD)&uae_league_cup_set_champion_c);
	uae_league_cup_vtable->SetPointer(VTableClubLandmarks, 0x48cab0);
	uae_league_cup_vtable->SetPointer(VTableFixtures, (DWORD)&uae_league_cup_fixture_caller);
	uae_league_cup_vtable->SetPointer(VTableTableFates, (DWORD)&uae_league_cup_table_fates_c);
	uae_league_cup_vtable->SetPointer(VTableStageNews, (DWORD)&uae_league_cup_stage_news_c);
	uae_league_cup_vtable->SetPointer(VTableReputationSetup, (DWORD)&uae_league_cup_reputation_setup_c);
	uae_league_cup_vtable->SetPointer(VTableReputationCalc, (DWORD)&uae_league_cup_reputation_calc_c);
	uae_league_cup_vtable->SetPointer(VTableSubsRounds, (DWORD)&uae_league_cup_subs_c);
	uae_league_cup_vtable->SetPointer(VTableLeagueSplit, 0x6847c0);
	data->rules = RulesUAE;
	data->f81 = 0xc;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	uae_league_cup_all_teams(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	uae_league_cup_reputation_setup(_this);
	uae_league_cup_subs(_this);
	uae_league_cup_setup_league_stage(_this);
	//sub_6835C0(_this); -> done in function above instead
	sub_6827D0(_this, 0);
}

void setup_uae_league_cup() {
}