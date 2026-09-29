#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

vtable* col_first_vtable = new vtable((BYTE*)0x969798, 0xB4);

void col_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(col_first_vtable->vtable_ptr);
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

void col_first_free(BYTE* _this, BYTE a2) {
	col_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) col_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call col_first_free
		add esp, 0x8
		ret 4
	}
}

void col_first_aggregate_relegation(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	char aggregate_idx = 7;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (year % 4 == 2) aggregate_idx = 5;
	comp_stats* aggregate = (comp_stats*)(data->stages[aggregate_idx]);
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);
	WORD nteams = aggregate->n_teams;
	for (WORD i = nteams; i > nteams - 2; i--) {
		table_teams[i - 1].league_fate = Relegated;
		staff_history_relegated_86A1C0(staff_hist_ptr, table_teams[i - 1].club, (DWORD)(data->competition_db));
	}
}

//
int col_first_set_champion(BYTE* _this) {
	char open_finals_idx = 3;
	char close_finals_idx = 6;
	char aggregate_idx = 7;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (year % 4 == 2)
	{
		open_finals_idx = 1;
		close_finals_idx = 4;
		aggregate_idx = 5;
	}
	cm3_clubs* open_winner = 0;
	cm3_clubs* close_winner = 0;

	// add aggregate champions to history
	comp_stats* aggregate = (comp_stats*)(data->stages[aggregate_idx]);
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);

	// add closing stage winners to history
	BYTE* close_playoff = (BYTE*)data->stages[close_finals_idx];
	comp_stats* close_playoff_data = (comp_stats*)(close_playoff);
	DWORD v1 = *(DWORD*)close_playoff;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x30))(close_playoff);

	teams_seeded* close_teams = (teams_seeded*)close_playoff_data->teams_list;
	for (WORD i = 0; i < close_playoff_data->n_teams; i++) {
		if (close_teams[i].f6 == 1)
		{
			close_winner = close_teams[i].club;
			break;
		}
	}

	// add opening stage winners to history
	BYTE* open_playoff = (BYTE*)data->stages[open_finals_idx];
	comp_stats* open_playoff_data = (comp_stats*)(open_playoff);
	v1 = *(DWORD*)open_playoff;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x30))(open_playoff);

	teams_seeded* open_teams = (teams_seeded*)open_playoff_data->teams_list;
	for (WORD i = 0; i < open_playoff_data->n_teams; i++) {
		if (open_teams[i].f6 == 1)
		{
			open_winner = open_teams[i].club;
			break;
		}
	}

	// set relegated teams
	col_first_aggregate_relegation(_this);

	//// qualify teams for champions trophy
	//comp_stats* champions_cup = (comp_stats*)get_loaded_league(COL_SUPER_CUP_9CF());
	//teams_seeded* teams = (teams_seeded*)champions_cup->teams_list;
	//teams[0].club = open_winner;
	//// if the same team won both opening and closing stage, get the best placed team in the aggregate table
	//if (open_winner == close_winner) {
	//	for (WORD i = 0; i < aggregate->n_teams; i++) {
	//		if (table_teams[i].club != close_winner) {
	//			close_winner = table_teams[i].club;
	//			break;
	//		}
	//	}
	//}
	//teams[1].club = close_winner;

	return 0;
}

void __declspec(naked) col_first_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call col_first_set_champion
		add esp, 0x4
		ret 0
	}
}

int col_first_last_positions(BYTE* _this) {
	char open_finals_idx = 3;
	char close_finals_idx = 6;
	char aggregate_idx = 7;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (year % 4 == 2)
	{
		open_finals_idx = 1;
		close_finals_idx = 4;
		aggregate_idx = 5;
	}
	vector<cm3_clubs*> clubs;

	comp_stats* open_playoff = (comp_stats*)data->stages[open_finals_idx];
	teams_seeded* open_teams = (teams_seeded*)open_playoff->teams_list;
	for (WORD i = 0; i < open_playoff->n_teams; i++) {
		if (open_teams[i].f6 == 1 && !vector_contains_element(clubs, open_teams[i].club))
		{
			clubs.push_back(open_teams[i].club);
			break;
		}
	}

	comp_stats* close_playoff = (comp_stats*)data->stages[close_finals_idx];
	teams_seeded* close_teams = (teams_seeded*)close_playoff->teams_list;
	for (WORD i = 0; i < close_playoff->n_teams; i++) {
		if (close_teams[i].f6 == 1 && !vector_contains_element(clubs, close_teams[i].club))
		{
			clubs.push_back(close_teams[i].club);
			break;
		}
	}

	comp_stats* aggregate = (comp_stats*)data->stages[aggregate_idx];
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);
	for (WORD i = 0; i < aggregate->n_teams; i++)
	{
		if (!vector_contains_element(clubs, table_teams[i].club)) clubs.push_back(table_teams[i].club);
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

void __declspec(naked) col_first_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call col_first_last_positions
		add esp, 0x4
		ret
	}
}

void col_first_subs(BYTE* _this)
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
	comp_data->promotions = 0;
	comp_data->prom_playoff = 8;
	comp_data->rele_playoff = 12;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = COL_SECOND_9CF();

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) col_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call col_first_subs
		add esp, 0x4
		ret
	}
}

int col_first_add_teams(BYTE* _this)
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

int col_first_vtable2(BYTE* _this, BYTE* round_data, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	sub_685D30(_this, round_data, a3);
	char stage_num = 7;
	WORD year = comp_data->year;
	if (year % 4 == 2) stage_num = 5;

	char curr_stage = *(char*)(round_data + 0x42);
	if (curr_stage < stage_num)
	{
		DWORD* f8 = comp_data->f8;
		comp_data->f8 = 0;
		*(BYTE*)(round_data + 0x42) = stage_num;
		sub_685D30(_this, round_data, a3);
		*(BYTE*)(round_data + 0x42) = curr_stage;
		comp_data->f8 = f8;
	}

	return 1;
}

void __declspec(naked) col_first_vtable2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call col_first_vtable2
		add esp, 0xc
		ret 0x8
	}
}

DWORD col_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	char open_playoff_id = 1;
	char open_playoff_id2 = 3;
	char close_playoff_id = 4;
	char close_playoff_id2 = 6;
	if (year % 4 == 2) {
		open_playoff_id2 = -2;
		close_playoff_id = 2;
		close_playoff_id2 = 4;
	}

	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = Apertura;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 1, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 1, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 1, 29), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 12), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 19), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 26), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 23), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 26), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = Clausura;

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
		AddFixture(pMem, fixture_id, Date(year, 8, 6), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
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
		AddFixture(pMem, fixture_id, Date(year, 8, 27), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 12), year, Wednesday, Evening);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == open_playoff_id && year % 4 == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		*num_rounds = 3;
		*stage_name_id = AperturaPlayoffs;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 27), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 3), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | NoAwayGoals, 5, 8, 4, 8, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | NoAwayGoals, 5, 4, 2, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 25), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 1), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | NoAwayGoals, 5, 2, 1, 0, 0, 0, 2, 4, 0, prizeMoneyFile.GetInt("col_first_final_win"));

		return (DWORD)pMem;
	}
	else if (stage_idx < open_playoff_id + 2 && year % 4 != 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		WORD numberOfLeagueTeams = 4;
		*num_rounds = (numberOfLeagueTeams - 1) * 2;
		if (stage_idx == open_playoff_id) *stage_name_id = AperturaSemiGroupA;
		else *stage_name_id = AperturaSemiGroupB;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 14), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 31), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == open_playoff_id2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		*num_rounds = 1;
		*stage_name_id = AperturaFinal;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 1), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 7), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, None, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | NoAwayGoals, 5, 2, 1, 2, 0, 0, 2, 4, 0, prizeMoneyFile.GetInt("col_first_final_win"));

		return (DWORD)pMem;
	}
	else if (stage_idx < close_playoff_id + 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		WORD numberOfLeagueTeams = 4;
		*num_rounds = (numberOfLeagueTeams - 1) * 2;
		if (stage_idx == close_playoff_id) *stage_name_id = ClausuraSemiGroupA;
		else *stage_name_id = ClausuraSemiGroupB;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 26), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 3), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 10), year, Wednesday, Evening);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == close_playoff_id2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		*num_rounds = 1;
		*stage_name_id = ClausuraFinal;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, None, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | NoAwayGoals, 5, 2, 1, 2, 0, 0, 2, 3, 0, prizeMoneyFile.GetInt("col_first_final_win"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) col_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call col_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

DWORD col_first_fixtures_dummy(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	char open_playoff_id = 1;
	char open_playoff_id2 = 3;
	char close_playoff_id = 4;
	char close_playoff_id2 = 6;
	if (year % 4 == 2) {
		open_playoff_id2 = -2;
		close_playoff_id = 2;
		close_playoff_id2 = 4;
	}
	else if (stage_idx < open_playoff_id + 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		*num_rounds = 1;
		if (stage_idx == open_playoff_id) *stage_name_id = AperturaSemiGroupA;
		else *stage_name_id = AperturaSemiGroupB;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 27), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 3), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak, NoTiebreak, 5, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx < close_playoff_id + 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		*num_rounds = 1;
		if (stage_idx == close_playoff_id) *stage_name_id = ClausuraSemiGroupA;
		else *stage_name_id = ClausuraSemiGroupB;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 13), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 19), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak, NoTiebreak, 5, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}

	return 0;
}

//
void col_first_prom_rel_update(BYTE* _this, int a2) {
	BYTE idx = 7;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (year % 4 == 2) idx = 5;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	//BYTE* col_second = get_loaded_league(COL_SECOND_9CF());
	//v1 = *(DWORD*)col_second;
	//(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(col_second);
	//process_promotion_relegation_689C80(_this, (BYTE*)data->stages[idx], col_second, 1, a2, -1, -1);
}

void __declspec(naked) col_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call col_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void col_first_setup_close(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE idx = 0;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
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

void col_first_open_playoff_finals_setup(BYTE* _this) {
	char stage_num = 3;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
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
	comp_data->current_stage = stage_num;
}

void col_first_open_playoff_no_wc_year(BYTE* _this) {
	char stage_num = 1;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE playoff_teams = 2;
	DWORD* stages_arr = data->stages;

	for (int g = 0; g < 2; g++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)col_first_fixtures_dummy(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
		BYTE* pStage = (BYTE*)cm0102_new(0xB2);
		create_cup_stage_data(pStage, _this, playoff_teams, pTeams, num_rounds, (DWORD)data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	col_first_open_playoff_finals_setup(_this);
}

void col_first_open_playoff_wc_year(BYTE* _this) {
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
	comp_data->current_stage = stage_num;
}

void col_first_open_playoff(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	if (comp_data->year % 4 == 2) col_first_open_playoff_wc_year(_this);
	else col_first_open_playoff_no_wc_year(_this);
}

void col_first_close_playoff_finals_setup(BYTE* _this) {
	char stage_num = 6;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	if (year % 4 == 2) stage_num = 4;
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

void col_first_close_playoff(BYTE* _this) {
	char stage_num = 4;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	if (year % 4 == 2) stage_num = 2;
	DWORD v1 = *(DWORD*)_this;
	BYTE playoff_teams = 2;
	DWORD* stages_arr = comp_data->stages;

	for (int g = 0; g < 2; g++) {
		vector<cm3_clubs*> clubs;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)col_first_fixtures_dummy(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
		BYTE* pStage = (BYTE*)cm0102_new(0xB2);
		create_cup_stage_data(pStage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	col_first_close_playoff_finals_setup(_this);
}

void col_first_league_table(BYTE* _this) {
	BYTE idx = 7;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (year % 4 == 2) idx = 5;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < data->n_teams; i++)
	{
		*((DWORD*)(&pTeams[i])) = all_teams[i];
	}
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 0, 0, 0 };
	short f217 = 0;
	create_league_stage_data(pStage, _this, (short)data->n_teams, pTeams, 0, (DWORD)(data->competition_db), pFixtures, 54,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 1, 0, f217, -1, 0, data->f225);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

//
char col_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* col_second = get_loaded_league(COL_SECOND_9CF());

	//// All teams that were in D1 must be professional
	//update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	//update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	//// All teams that were relegated from D2 must be semi-professional
	//// All teams that were not relegated from D2 must be professional
	//update_club_pro_status_68A980(col_second, Professional, Relegated, -3, 1);
	//update_club_pro_status_68A980(col_second, SemiProfessional, -3, Relegated, 0);

	DWORD v1 = *(DWORD*)_this;
	col_first_prom_rel_update(_this, 1);

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
	if (data->year % 4 == 2) data->num_stages = 6;
	else data->num_stages = 8;
	col_first_subs(_this);
	col_first_add_teams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("col_first_tv_money"), 0);
	sub_6835C0(_this);
	col_first_setup_close(_this);
	col_first_open_playoff(_this);
	col_first_close_playoff(_this);
	col_first_league_table(_this);
	sub_6827D0(_this, 0);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	//v1 = *(DWORD*)col_second;
	//(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(col_second);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) col_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call col_first_update
		add esp, 0x4
		ret
	}
}

void col_first_open_playoff_teams_no_wc_year(BYTE* _this) {
	char stage_num = 1;
	DWORD v1 = *(DWORD*)_this;
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE playoff_teams = 4;
	char prom_rel[4] = { 0, 1, 0, 0 };
	vector<cm3_clubs*> clubs;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			clubs.push_back(tls.club);
		}
	}
	shuffle(clubs.begin(), clubs.begin() + 2, rng);
	shuffle(clubs.begin() + 2, clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 6, rng);
	shuffle(clubs.begin() + 6, clubs.end(), rng);

	for (int g = 0; g < 2; g++) {
		comp_stats* stage = (comp_stats*)(comp_data->stages[stage_num]);
		DWORD v2 = *(DWORD*)stage;
		(*(int(__thiscall**)(BYTE*, int a2))(v2))((BYTE*)stage, 1);
		comp_data->stages[stage_num] = 0;

		// Create the new stage
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
		for (size_t i = 0; i < playoff_teams; i++) {
			*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i * 2 + g];
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, &comp_data->tiebreaker_1, &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, comp_data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
}

void col_first_open_playoff_teams_wc_year(BYTE* _this) {
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
		teams[team_order[i]].seeding = 8 - i;
	}
}

void col_first_open_playoff_teams(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	if (comp_data->year % 4 == 2) col_first_open_playoff_teams_wc_year(_this);
	else col_first_open_playoff_teams_no_wc_year(_this);
}

void col_first_close_playoff_teams(BYTE* _this) {
	char stage_num = 4;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	if (year % 4 == 2) stage_num = 2;
	DWORD v1 = *(DWORD*)_this;
	DWORD* stages_arr = comp_data->stages;
	comp_stats* curr_stage = (comp_stats*)comp_data->stages[0];

	BYTE playoff_teams = 4;
	char prom_rel[4] = { 0, 1, 0, 0 };
	vector<cm3_clubs*> clubs;
	WORD total_teams = curr_stage->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			clubs.push_back(tls.club);
		}
	}
	shuffle(clubs.begin(), clubs.begin() + 2, rng);
	shuffle(clubs.begin() + 2, clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 6, rng);
	shuffle(clubs.begin() + 6, clubs.end(), rng);

	for (int g = 0; g < 2; g++) {
		comp_stats* stage = (comp_stats*)(comp_data->stages[stage_num]);
		DWORD v2 = *(DWORD*)stage;
		(*(int(__thiscall**)(BYTE*, int a2))(v2))((BYTE*)stage, 1);
		comp_data->stages[stage_num] = 0;

		// Create the new stage
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
		for (size_t i = 0; i < playoff_teams; i++) {
			*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i * 2 + g];
		}

		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, &comp_data->tiebreaker_1, &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, comp_data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
}

int col_first_table_fates(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	char open_playoff_id = 1;
	char open_playoff_id2 = 3;
	char close_playoff_id = 4;
	char close_playoff_id2 = 6;
	if (year % 4 == 2) {
		open_playoff_id2 = -2;
		close_playoff_id = 2;
		close_playoff_id2 = 4;
	}

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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), AperturaPlayoffs, None, 0x1E);
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), ClausuraPlayoffs, None, 0x1E);
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
	else if (stage == open_playoff_id && year % 4 == 2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
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
	else if (stage < open_playoff_id + 2 && year % 4 != 2) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[stage]);
		WORD num_teams = comp_data->n_teams;
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), AperturaFinal, None, 0x1E);
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == open_playoff_id2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
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
		for (char al = 1; al < 3; al++) {
			comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
			table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
				case Promoted:
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else if (stage < close_playoff_id + 2) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[stage]);
		WORD num_teams = comp_data->n_teams;
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), ClausuraFinal, None, 0x1E);
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == close_playoff_id2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[0]);
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
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
		for (char al = close_playoff_id; al < close_playoff_id + 2; al++) {
			comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
			table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
				case Promoted:
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

void __declspec(naked) col_first_table_fates_c()
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
		call col_first_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void col_first_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	char open_playoff_id = 1;
	char open_playoff_id2 = 3;
	char close_playoff_id = 4;
	char close_playoff_id2 = 6;
	if (year % 4 == 2) {
		open_playoff_id2 = -2;
		close_playoff_id = 2;
		close_playoff_id2 = 4;
	}
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
	else if (stage == open_playoff_id && year % 4 == 2) {
		// do nothing
	}
	else if (stage < open_playoff_id + 2 && year % 4 != 2) {
		if (min < 2) ret_min = 1;
		if (max < 2) ret_max = 2;
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == open_playoff_id2) {
		// do nothing
	}
	else if (stage < close_playoff_id + 2) {
		if (min < 2) ret_min = 1;
		if (max < 2) ret_max = 2;
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == close_playoff_id2) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) col_first_reputation_calc_c()
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
		call col_first_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void col_first_open_final_teams(BYTE* _this) {
	char stage_num = 3;
	comp_stats* data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	for (char al = 1; al < 3; al++) {
		comp_stats* curr_stage = (comp_stats*)(data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Qualified1 || tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
			else {
				WORD num_teams = data->n_teams;
				team_league_stats* open_table = (team_league_stats*)(data->team_league_table);
				for (int i = 0; i < num_teams; i++) {
					if (open_table[i].club != tls.club) continue;
					open_table[i].league_fate = Eliminated;
					break;
				}
			}
		}
	}

	for (char i = 0; i < playoff_teams; i++) {
		teams[i].club = clubs[i];
		teams[i].seeding = i + 1;
	}
}

void col_first_close_final_teams(BYTE* _this) {
	char stage_num = 6;
	char offset = 4;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (year % 4 == 2)
	{
		stage_num = 4;
		offset = 2;
	}
	comp_stats* playoff = (comp_stats*)data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	for (char al = offset; al < offset + 2; al++) {
		comp_stats* curr_stage = (comp_stats*)(data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Qualified1 || tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
			else {
				comp_stats* close_data = (comp_stats*)(data->stages[0]);
				WORD num_teams = close_data->n_teams;
				team_league_stats* close_table = (team_league_stats*)(close_data->team_league_table);
				for (int i = 0; i < num_teams; i++) {
					if (close_table[i].club != tls.club) continue;
					close_table[i].league_fate = Eliminated;
					break;
				}
			}
		}
	}

	for (char i = 0; i < playoff_teams; i++) {
		teams[i].club = clubs[i];
		teams[i].seeding = i + 1;
	}
}

char col_first_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		WORD year = comp_data->year;
		// check if can start Apertura playoffs
		char open_playoff_id = 1;
		char open_playoff_id2 = 3;
		comp_stats* open_playoff = (comp_stats*)comp_data->stages[open_playoff_id];
		bool open_check = false;
		if (*(DWORD*)open_playoff == 0x969468) { // default cup vtable
			teams_seeded* open_teams = (teams_seeded*)open_playoff->teams_list;
			open_check = !open_teams[0].club;
		}
		else {
			team_league_stats* table = (team_league_stats*)(open_playoff->team_league_table);
			if (!table) open_check = false;
			else open_check = !table[0].club;
		}
		if (open_check) {
			bool is_finished = true;
			WORD total_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 19) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				col_first_open_playoff_teams(_this);
			}
		}
		// check if can start Clausura playoffs
		char close_playoff_id = 4;
		char close_playoff_id2 = 6;
		if (year % 4 == 2)
		{
			close_playoff_id = 2;
			close_playoff_id2 = 4;
		}
		comp_stats* close_playoff = (comp_stats*)comp_data->stages[close_playoff_id];
		bool close_check = false;
		if (*(DWORD*)close_playoff == 0x969468) { // default cup vtable
			teams_seeded* close_teams = (teams_seeded*)close_playoff->teams_list;
			close_check = !close_teams[0].club;
		}
		else {
			team_league_stats* table = (team_league_stats*)(close_playoff->team_league_table);
			if (!table) close_check = false;
			else close_check = !table[0].club;
		}
		if (close_check) {
			comp_stats* curr_stage = (comp_stats*)(comp_data->stages[0]);
			bool is_finished = true;
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 19) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				col_first_close_playoff_teams(_this);
			}
		}
		// check if can start Apertura final
		if (year % 4 != 2 && *(DWORD*)open_playoff == 0x96D0F0) { // default league vtable
			comp_stats* open_finals = (comp_stats*)comp_data->stages[open_playoff_id2];
			teams_seeded* open_finals_teams = (teams_seeded*)open_finals->teams_list;
			if (!open_finals_teams[0].club) {
				bool is_finished = true;
				WORD total_teams = open_playoff->n_teams;
				team_league_stats* table_teams = (team_league_stats*)(open_playoff->team_league_table);
				for (int i = 0; i < total_teams; i++) {
					team_league_stats tls = table_teams[i];
					if (tls.games < 6) {
						is_finished = false;
						break;
					}
				}
				if (is_finished)
				{
					comp_stats* open_playoff2 = (comp_stats*)comp_data->stages[open_playoff_id + 1];
					total_teams = open_playoff2->n_teams;
					table_teams = (team_league_stats*)(open_playoff2->team_league_table);
					for (int i = 0; i < total_teams; i++) {
						team_league_stats tls = table_teams[i];
						if (tls.games < 6) {
							is_finished = false;
							break;
						}
					}
					if (is_finished) {
						col_first_open_final_teams(_this);
					}
				}
			}
		}
		// check if can start Clausura final
		if (*(DWORD*)close_playoff == 0x96D0F0) { // default league vtable
			comp_stats* close_finals = (comp_stats*)comp_data->stages[close_playoff_id2];
			teams_seeded* close_finals_teams = (teams_seeded*)close_finals->teams_list;
			if (!close_finals_teams[0].club) {
				bool is_finished = true;
				WORD total_teams = close_playoff->n_teams;
				team_league_stats* table_teams = (team_league_stats*)(close_playoff->team_league_table);
				for (int i = 0; i < total_teams; i++) {
					team_league_stats tls = table_teams[i];
					if (tls.games < 6) {
						is_finished = false;
						break;
					}
				}
				if (is_finished)
				{
					comp_stats* close_playoff2 = (comp_stats*)comp_data->stages[close_playoff_id + 1];
					total_teams = close_playoff2->n_teams;
					table_teams = (team_league_stats*)(close_playoff2->team_league_table);
					for (int i = 0; i < total_teams; i++) {
						team_league_stats tls = table_teams[i];
						if (tls.games < 6) {
							is_finished = false;
							break;
						}
					}
					if (is_finished) {
						col_first_close_final_teams(_this);
					}
				}
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) col_first_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call col_first_table_split
		add esp, 0xc
		ret 8
	}
}

void col_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(col_first_vtable->vtable_ptr);
	col_first_vtable->SetPointer(VTableSubsRounds, (DWORD)&col_first_subs_c);
	col_first_vtable->SetPointer(VTableInitFree, (DWORD)&col_first_free_c);
	col_first_vtable->SetPointer(VTableEoSUpdate, (DWORD)&col_first_update_c);
	col_first_vtable->SetPointer(VTableFixtures, (DWORD)&col_first_fixtures_c);
	col_first_vtable->SetPointer(VTablePromRelUpdate, (DWORD)&col_first_prom_rel_update_c);
	col_first_vtable->SetPointer(VTableSetChampion, (DWORD)&col_first_set_champion_c);
	col_first_vtable->SetPointer(VTablePostMatchUpdate, (DWORD)&col_first_vtable2_c);
	col_first_vtable->SetPointer(VTableUpdateLastDivision, (DWORD)&col_first_last_positions_c);
	col_first_vtable->SetPointer(VTableLeagueSplit, (DWORD)&col_first_table_split_c);
	col_first_vtable->SetPointer(VTableReputationCalc, (DWORD)&col_first_reputation_calc_c);
	col_first_vtable->SetPointer(VTableTableFates, (DWORD)&col_first_table_fates_c);
	//if (configFile.GetBool("showThirdPlaceInHistory", true)) col_first_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesColombia;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	if (year % 4 == 2) data->num_stages = 6;
	else data->num_stages = 8;
	data->stages = (DWORD*)cm0102_malloc(8 * 4);
	col_first_subs(_this);
	col_first_add_teams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("col_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	col_first_setup_close(_this);
	col_first_open_playoff(_this);
	col_first_close_playoff(_this);
	col_first_league_table(_this);
	sub_6827D0(_this, 0);
	league_reputation_setup_generic_68A850(_this);
}

void setup_col_first()
{
	char* open_sa = "Opening Semi-Final Group A";
	char* open_sa_short = "Open Semi Grp A";
	WriteDWORD(0x4B53d8 + 1, (DWORD)&open_sa[0]);
	WriteDWORD(0x4B846f + 1, (DWORD)&open_sa_short[0]);

	char* open_sb = "Opening Semi-Final Group B";
	char* open_sb_short = "Open Semi Grp B";
	WriteDWORD(0x4B53f2 + 1, (DWORD)&open_sb[0]);
	WriteDWORD(0x4B8479 + 1, (DWORD)&open_sb_short[0]);

	char* close_sa = "Closing Semi-Final Group A";
	char* close_sa_short = "Close Semi Grp A";
	WriteDWORD(0x4B540c + 1, (DWORD)&close_sa[0]);
	WriteDWORD(0x4B8483 + 1, (DWORD)&close_sa_short[0]);

	char* close_sb = "Closing Semi-Final Group B";
	char* close_sb_short = "Close Semi Grp B";
	WriteDWORD(0x4B5780 + 1, (DWORD)&close_sb[0]);
	WriteDWORD(0x4B85f1 + 1, (DWORD)&close_sb_short[0]);

	char* open_final = "Opening Final";
	char* open_final_short = "Open Final";
	WriteDWORD(0x4B579a + 1, (DWORD)&open_final[0]);
	WriteDWORD(0x4B8610 + 1, (DWORD)&open_final_short[0]);

	char* close_final = "Closing Final";
	char* close_final_short = "Close Final";
	WriteDWORD(0x4B57ce + 1, (DWORD)&close_final[0]);
	WriteDWORD(0x4B864e + 1, (DWORD)&close_final_short[0]);
}