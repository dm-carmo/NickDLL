#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* aus_league_vtable = (DWORD*)0x967768;

int aus_league_last_positions(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* finals_bytes = (BYTE*)comp_data->stages[0];
	comp_stats* finals_data = (comp_stats*)finals_bytes;
	vector<cm3_clubs*> done;
	teams_seeded* teams = (teams_seeded*)finals_data->teams_list;
	for (WORD i = 0; i < finals_data->n_teams; i++) {
		if (teams[i].f6 != -1)
		{
			teams[i].club->ClubLastDivision = comp_data->competition_db;
			teams[i].club->ClubLastPosition = teams[i].f6;
			done.push_back(teams[i].club);
		}
	}
	char curr_pos = 3;
	team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		if (vector_contains_element(done, table[i].club)) continue;
		table[i].club->ClubLastDivision = comp_data->competition_db;
		table[i].club->ClubLastPosition = curr_pos++;
	}
	return 1;
}

void __declspec(naked) aus_league_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call aus_league_last_positions
		add esp, 0x4
		ret
	}
}

void aus_league_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);
}

void __declspec(naked) aus_league_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call aus_league_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void aus_league_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	*((WORD*)(_this + 0xA7)) = 26;
	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = GamesWonTiebreaker;
	comp_data->tiebreaker_4 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 6;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->f217 = 0x2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -3, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) aus_league_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call aus_league_subs
		add esp, 0x4
		ret
	}
}

void aus_league_setup_extra_games(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	vector<cm3_clubs*> teams;
	team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);
	for (WORD i = 0; i < data->n_teams; i++) teams.push_back(table_teams[i].club);
	shuffle(teams.begin(), teams.end(), rng);

	char matchups[4][12] = {
		{ 1,2, 3,4,  5,6, 7,8,  9,10, 12,11, },
		{ 1,3, 2,4,  5,7, 6,8,  11,9, 10,12, },
		{ 7,1, 8,2,  9,3, 4,10, 11,5, 6,12,  },
		{ 8,1, 12,5, 3,6, 10,7,  2,9,  4,11 },
	};

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, -2, &num_rounds, &stage_name_id, 0);

	for (BYTE m = 0; m < 4; m++) {
		BYTE* ptr_last = (BYTE*)(pFixtures + fixture_dates_sz * 3);
		match_data* match = new match_data();
		match->comp_id = data->competition_db->ClubCompID;
		match->f8 = -1;
		match->comp = data->competition_db;
		match->end_year = data->year + *(WORD*)(ptr_last + 2);
		match->end_day = *(WORD*)(ptr_last);
		match->current_year = data->year;
		match->sub_stage_id = 0;
		match->main_stage_id = stage_name_id;
		match->f54_0xdb = data->f219;
		match->f56_0xab = data->f171;
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
		for (char t = 0; t < 6; t++) {
			char p1 = matchups[m][t * 2];
			char p2 = matchups[m][t * 2 + 1];
			cm3_clubs* home = (cm3_clubs*)teams[p1 - 1];
			cm3_clubs* away = (cm3_clubs*)teams[p2 - 1];
			BYTE* ptr = (BYTE*)(pFixtures + fixture_dates_sz * m);
			match->home_team_id = home->ClubID;
			match->away_team_id = away->ClubID;
			match->home_team = home;
			match->away_team = away;
			match->fixture_year = data->year + *(WORD*)(ptr + 2);
			match->fixture_day = *(WORD*)(ptr);
			match->fixture_number = m + 22;
			match->f63 = *(BYTE*)(ptr + 4);

			sub_85C260((BYTE*)*(DWORD*)0xDD7EF4, *(DWORD*)(ptr + 0x3D), (BYTE*)match, data->f36);
			sub_5AA680((BYTE*)*(DWORD*)0xAE2A58, (BYTE*)match, 1);
		}
	}

	sub_9452CA_free(pFixtures);
	//sub_684230(_this);

	data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);
}

char* aus_league_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* finals_bytes = (BYTE*)comp_data->stages[0];
	comp_stats* finals_data = (comp_stats*)finals_bytes;
	cm3_clubs* first = 0;
	cm3_clubs* second = 0;
	teams_seeded* teams = (teams_seeded*)finals_data->teams_list;
	for (WORD i = 0; i < finals_data->n_teams; i++) {
		if (teams[i].f6 == 1) first = teams[i].club;
		else if (teams[i].f6 == 2) second = teams[i].club;
	}
	team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
	cm3_clubs* third = table[0].club;
	return sub_4AFCE0_add_history_entry(_this, first, second, third, 0);
}

void __declspec(naked) aus_league_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call aus_league_set_champion
		add esp, 0x4
		ret 0
	}
}

char aus_league_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	aus_league_prom_rel_update(_this, 1);

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
	aus_league_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("aus_league_tv_money"), 0);
	sub_6835C0(_this);
	aus_league_setup_extra_games(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) aus_league_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call aus_league_update
		add esp, 0x4
		ret
	}
}

void aus_league_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = aus_league_vtable;
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

void aus_league_free(BYTE* _this, BYTE a2) {
	aus_league_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) aus_league_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call aus_league_free
		add esp, 0x8
		ret 4
	}
}

DWORD aus_league_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	// base games
	if (stage_idx == -3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1 + numberOfLeagueTeams % 2) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	// extra games
	else if (stage_idx == -2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1 + numberOfLeagueTeams % 2) * data->n_rounds + 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		// extra game?
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		// extra game?
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		// extra game?
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		// extra game?
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, EliminationFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 4, 2, 2, 4, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 17), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 23), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, GrandFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 0, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) aus_league_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call aus_league_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void aus_league_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = aus_league_vtable;
	data->year = year;
	data->rules = RulesAustralia;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	aus_league_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("aus_league_tv_money"), 0);
	sub_6835C0(_this);
	aus_league_setup_extra_games(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void aus_league_playoff_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = comp_data->prom_playoff;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	BYTE team_order[6] = { 4,5,2,0,1,3 };

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (char i = comp_data->promotions, j = 0; i < total_teams && j < playoff_teams; i++) {
		*((DWORD*)(&pTeams[team_order[j++]])) = (DWORD)table_teams[i].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num * 4])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void aus_league_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			aus_league_playoff_under(_this);
		}
	}
}

void __declspec(naked) aus_league_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call aus_league_playoffs_c
		add esp, 0x4
		ret
	}
}

int aus_league_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
				table[i].league_fate = Champions;
				*a5 = 1;
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
	else {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
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
	return 0;
}

void __declspec(naked) aus_league_set_table_fate()
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
		call aus_league_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void aus_league_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) aus_league_reputation_calc_c()
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
		call aus_league_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_aus_league()
{
	WriteVTablePtr(aus_league_vtable, VTableSubsRounds, (DWORD)&aus_league_subs_c);
	WriteVTablePtr(aus_league_vtable, VTableEoSUpdate, (DWORD)&aus_league_update_c);
	WriteVTablePtr(aus_league_vtable, VTableFixtures, (DWORD)&aus_league_fixtures_c);
	WriteVTablePtr(aus_league_vtable, VTablePlayoffQual, (DWORD)&aus_league_playoffs_create);
	WriteVTablePtr(aus_league_vtable, VTableTableFates, (DWORD)&aus_league_set_table_fate);
	WriteVTablePtr(aus_league_vtable, VTableStageNews, 0x48c6d0);
	WriteVTablePtr(aus_league_vtable, VTable32, 0x48F2D0);
	WriteVTablePtr(aus_league_vtable, VTableSetChampion, (DWORD)&aus_league_set_champion_c);
	WriteVTablePtr(aus_league_vtable, VTablePromRelUpdate, (DWORD)&aus_league_prom_rel_update_c);
	WriteVTablePtr(aus_league_vtable, VTableUpdateLastDivision, (DWORD)&aus_league_last_positions_c);
}
