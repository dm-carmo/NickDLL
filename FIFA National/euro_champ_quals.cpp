#include <windows.h>
#include <filesystem>
#include <fstream>
#include <map>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

using namespace std;

DWORD* euro_champ_quals_vtable = (DWORD*)0x96A0D4;

void euro_champ_quals_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 0;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f67 = 2;
	comp_data->f196 = 10;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_4 = GoalsForAwayTiebreaker;
	comp_data->promotions = 6;
	comp_data->prom_playoff = 2;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 6, December, comp_data->year - 1, Sunday);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = -1;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)cm0102_malloc(fixture_dates_sz);
	BYTE* fixtures = (BYTE*)comp_data->fixtures_table;
	*((WORD*)(fixtures)) = *(WORD*)current_date;
	*((WORD*)(fixtures + 2)) = (*current_year) - comp_data->year;
	*((BYTE*)(fixtures + 4)) = 0;
	*((WORD*)(_this + 0xA9)) = 1;
	*((BYTE*)(_this + 0xDD)) = 0;

	return;
}

void __declspec(naked) euro_champ_quals_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call euro_champ_quals_subs
		add esp, 0x4
		ret
	}
}

DWORD euro_champ_quals_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx < 5) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 6;
		if (stage_idx < 2) *stage_name_id = LeagueA1to4 + stage_idx + 1;
		else *stage_name_id = LeagueB1to4 + stage_idx - 2;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 23), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 26), year, Sunday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 29), year, Wednesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 3), year, Sunday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 11), year, Wednesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 14), year, Saturday, Afternoon);

		return (DWORD)pMem;
	}
	// playoff
	else if (stage_idx == 5) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 15), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 23), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 10, 12, 6, 12, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) euro_champ_quals_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call euro_champ_quals_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char euro_champ_quals_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	*((WORD*)(_this + 0xA7)) = -1;
	data->f76 = 0;
	sub_687970(_this, 0);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_teams_seedings = 0;
		data->special_nteams_seedings = 0;
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
	if (data->year < *current_year) data->year += 4;
	data->current_stage = -1;
	euro_champ_quals_subs(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) euro_champ_quals_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call euro_champ_quals_update
		add esp, 0x4
		ret
	}
}

void euro_champ_quals_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		teams_seeded* all_teams = (teams_seeded*)comp_data->special_teams_seedings;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < comp_data->special_nteams_seedings; i++)
		{
			clubs.push_back(all_teams[i].club);
		}
		sort(clubs.begin(), clubs.end(), compareNationRanking);

		for (int i = 0; i < 6; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 1);
		}
		for (int i = 6; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 7);
		}
		for (int i = 12; i < 18; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (int i = 18; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19 + 3);
		}
		for (int i = 24; i < 30; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25 + 6);
		}
		for (int i = 30; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 31 + 9);
		}

		for (int i = 36; i < 39; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (int i = 39; i < 42; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19 + 3);
		}
		for (int i = 42; i < 45; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25 + 6);
		}
		for (int i = 45; i < 48; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 31 + 9);
		}
		for (int i = 48; i < 51; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 49);
		}
		for (WORD i = 51; i < comp_data->special_nteams_seedings; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 52);
		}
		for (WORD i = 0; i < comp_data->special_nteams_seedings; i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) euro_champ_quals_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call euro_champ_quals_reputation_setup
		add esp, 0x4
		ret
	}
}

void euro_champ_quals_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;

	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 2) {
		ret_current = 1 + 3 * (current - 1);
		if (current > 5) ret_current += 3 * (current - 3);
		ret_min = 1 + 3 * (min - 1);
		if (min > 5) ret_min += 3 * (min - 3);
		ret_max = 1 + 3 * (max - 1);
		if (max > 5) ret_max += 3 * (max - 3);
	}
	else if (stage < 5) {
		ret_current = 3 * (current + 1) + 1 + 3 * (current - 1);
		ret_min = 3 * (min + 1) + 1 + 3 * (min - 1);
		ret_max = 3 * (max + 1) + 1 + 3 * (max - 1);
	}
	else if (stage == 5) {
		ret_current = current + 18;
		ret_min = min + 18;
		ret_max = max + 18;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) euro_champ_quals_reputation_calc_c()
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
		call euro_champ_quals_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void euro_champ_quals_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	vector<cm3_clubs*> countries = get_national_teams_of_continent_fifa_members(EUROPE_9CF());
	sort(countries.begin(), countries.end(), compareNationRanking);

	DWORD host1_id, host2_id;
	get_comp_hosts_in_continent(_this, UEFA_EURO_9CF(), EUROPE_9CF(), &host1_id, &host2_id);
	WORD total_teams_in_comp = (WORD)countries.size();
	total_teams_in_comp--; // subtract Russia
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	for (WORD i = 0; i < total_teams_in_comp; i++) {
		if (countries[i]->ClubNation->NationID == host1_id || countries[i]->ClubNation->NationID == host2_id)
		{
			auto it = countries.begin() + i;
			rotate(countries.begin(), it, it + 1);
		}
	}

	shuffle(countries.begin(), countries.begin() + 3, rng);
	shuffle(countries.begin() + 3, countries.begin() + 6, rng);
	shuffle(countries.begin() + 6, countries.begin() + 9, rng);
	shuffle(countries.begin() + 9, countries.begin() + 12, rng);
	shuffle(countries.begin() + 12, countries.begin() + 15, rng);
	shuffle(countries.begin() + 15, countries.begin() + 18, rng);
	shuffle(countries.begin() + 18, countries.begin() + 21, rng);
	shuffle(countries.begin() + 21, countries.begin() + 24, rng);
	shuffle(countries.begin() + 24, countries.begin() + 27, rng);
	shuffle(countries.begin() + 27, countries.begin() + 30, rng);
	shuffle(countries.begin() + 30, countries.begin() + 33, rng);
	shuffle(countries.begin() + 33, countries.begin() + 36, rng);
	shuffle(countries.begin() + 36, countries.begin() + 39, rng);
	shuffle(countries.begin() + 39, countries.begin() + 42, rng);
	shuffle(countries.begin() + 42, countries.begin() + 45, rng);
	shuffle(countries.begin() + 45, countries.begin() + 48, rng);
	shuffle(countries.begin() + 48, countries.begin() + 51, rng);
	shuffle(countries.begin() + 51, countries.end(), rng);

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	for (BYTE i = 0, j = 0; i < countries.size() && j < total_teams_in_comp; i++) {
		if (countries[i]->ClubNation->NationID == NATION_RUSSIA_9CF()) continue; // review Russia ban at a later date
		teams[j].club = countries[i];
		if (j < 36) teams[j].f5 = 10;
		else teams[j].f5 = 11;
		teams[j].f6 = 0;
		j++;
	}
}

void euro_champ_quals_create_league_a_matchups(BYTE* _this, BYTE* stage, vector<cm3_clubs*> clubs, BYTE idx) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* stage_data = (comp_stats*)stage;
	DWORD v1 = *(DWORD*)_this;

	shuffle(clubs.begin(), clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.end(), rng);

	char matchups[6][12] = {
		{ 7,6,5,9,10,8,11,4,1,3,12,2, },
		{ 6,3,4,2,11,7,8,9,1,5,10,12, },
		{ 2,9,8,1,3,12,6,11,5,10,7,4, },
		{ 9,3,4,10,5,8,2,6,12,7,1,11, },
		{ 4,1,9,12,3,7,2,5,6,8,11,10, },
		{ 7,5,8,4,10,1,9,11,3,2,12,6, },
	};

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	*((WORD*)(stage + 0x3A)) = stage_name_id;
	*((WORD*)(stage + 0xA7)) = num_rounds;

	for (BYTE m = 0; m < 6; m++) {
		BYTE* ptr_last = (BYTE*)(pFixtures + fixture_dates_sz * 5);
		match_data* match = new match_data();
		match->comp_id = data->competition_db->ClubCompID;
		match->f8 = -1;
		match->comp = data->competition_db;
		match->end_year = data->year + *(WORD*)(ptr_last + 2);
		match->end_day = *(WORD*)(ptr_last);
		match->current_year = data->year;
		match->sub_stage_id = 0;
		match->main_stage_id = stage_name_id;
		match->f54_0xdb = stage_data->f219;
		match->f56_0xab = stage_data->f171;
		match->f58_0xc4 = stage_data->f196;
		match->f59 = -1;
		match->f61 = 0;
		match->f62 = 0;
		match->f64 = 1;
		match->f65 = 1;
		match->stage_number = idx;
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
			cm3_clubs* home = clubs[p1 - 1];
			cm3_clubs* away = clubs[p2 - 1];
			BYTE* ptr = (BYTE*)(pFixtures + fixture_dates_sz * m);
			match->home_team_id = home->ClubID;
			match->away_team_id = away->ClubID;
			match->home_team = home;
			match->away_team = away;
			match->fixture_year = data->year + *(WORD*)(ptr + 2);
			match->fixture_day = *(WORD*)(ptr);
			match->fixture_number = m;
			match->f63 = *(BYTE*)(ptr + 4);

			sub_85C260((BYTE*)*(DWORD*)0xDD7EF4, *(DWORD*)(ptr + 0x3D), (BYTE*)match, data->f36);
			sub_5AA680((BYTE*)*(DWORD*)0xAE2A58, (BYTE*)match, 1);
		}
	}
	sub_9452CA_free(pFixtures);
}

void block_hosts_from_qualifying_euro_champ(BYTE* stage, DWORD host1_id, DWORD host2_id) {
	comp_stats* comp_data = (comp_stats*)stage;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		if (table_teams[i].club->ClubNation->NationID == host1_id ||
			table_teams[i].club->ClubNation->NationID == host2_id) {
			table_teams[i].league_fate = CantBePromoted;
			comp_data->promotions--;
		}
	}
}

void euro_champ_quals_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 12;
	BYTE* pMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	WORD year = data->year;
	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;

	vector<cm3_clubs*> clubs;
	for (int i = 0; i < total_teams; i++)
	{
		clubs.push_back(qualifiers[3 * i].club);
		add_team_call(_this, i, qualifiers[3 * i].club, 0, 0);
	}

	euro_champ_quals_create_league_a_matchups(_this, _this, clubs, -1);

	DWORD host1_id, host2_id;
	get_comp_hosts_in_continent(_this, UEFA_EURO_9CF(), EUROPE_9CF(), &host1_id, &host2_id);
	block_hosts_from_qualifying_euro_champ(_this, host1_id, host2_id);

	sub_684230(_this);
}

void euro_champ_quals_setup_groups_a(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD num_teams = 12;

	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	vector<cm3_clubs*> clubs;
	for (int i = 0; i < num_teams; i++)
	{
		clubs.push_back(qualifiers[3 * i + (idx + 1)].club);
		*((DWORD*)(&pTeams[i])) = (DWORD)qualifiers[3 * i + (idx + 1)].club;
	}

	char prom_rel[4] = { 6, 2, 0, 0 };
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, num_teams, pTeams, 0, (DWORD)(data->competition_db), 0, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);

	euro_champ_quals_create_league_a_matchups(_this, pStage, clubs, idx);

	DWORD host1_id, host2_id;
	get_comp_hosts_in_continent(_this, UEFA_EURO_9CF(), EUROPE_9CF(), &host1_id, &host2_id);
	block_hosts_from_qualifying_euro_champ(pStage, host1_id, host2_id);

	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void euro_champ_quals_setup_groups_b(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD num_teams = 6;

	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	vector<cm3_clubs*> clubs;
	for (int i = 0; i < num_teams; i++)
	{
		clubs.push_back(qualifiers[36 + 3 * i + (idx - 2)].club);
		*((DWORD*)(&pTeams[i])) = (DWORD)qualifiers[36 + 3 * i + (idx - 2)].club;
	}

	char prom_rel[4] = { 0, 2, 0, 0 };
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	if (num_teams < 6) {
		create_league_stage_data(pStage, _this, num_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
			data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
			year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);
	}
	else {
		create_league_stage_data(pStage, _this, num_teams, pTeams, 0, (DWORD)(data->competition_db), 0, num_rounds,
			data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
			year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);

		*((WORD*)(pStage + 0xA7)) = num_rounds;
		comp_stats* stage_data = (comp_stats*)pStage;

		char matchups[6][6] = {
			{ 1,2,3,4,5,6, },
			{ 4,2,5,3,1,6, },
			{ 1,5,6,4,3,2, },
			{ 4,1,2,5,6,3, },
			{ 3,1,5,4,2,6, },
			{ 2,1,4,3,6,5, },
		};

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
			match->f56_0xab = data->f171;
			match->f58_0xc4 = data->f196;
			match->f59 = -1;
			match->f61 = 0;
			match->f62 = 0;
			match->f64 = 1;
			match->f65 = 1;
			match->stage_number = idx;
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
			for (char t = 0; t < 3; t++) {
				char p1 = matchups[m][t * 2];
				char p2 = matchups[m][t * 2 + 1];
				if (p1 > num_teams || p2 > num_teams) continue;
				cm3_clubs* home = clubs[p1 - 1];
				cm3_clubs* away = clubs[p2 - 1];
				BYTE* ptr = (BYTE*)(pFixtures + fixture_dates_sz * m);
				match->home_team_id = home->ClubID;
				match->away_team_id = away->ClubID;
				match->home_team = home;
				match->away_team = away;
				match->fixture_year = data->year + *(WORD*)(ptr + 2);
				match->fixture_day = *(WORD*)(ptr);
				match->fixture_number = m;
				match->f63 = *(BYTE*)(ptr + 4);

				sub_85C260((BYTE*)*(DWORD*)0xDD7EF4, *(DWORD*)(ptr + 0x3D), (BYTE*)match, data->f36);
				sub_5AA680((BYTE*)*(DWORD*)0xAE2A58, (BYTE*)match, 1);
			}
		}
	}

	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void euro_champ_quals_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = euro_champ_quals_vtable;
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->rules = RulesInternational;
	data->f82 = 3;
	data->year = year;
	while (data->year % 4 != 3) data->year++;
	data->f81 = 0xf;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->f217 = 0x28;
	data->current_stage = -1;
	data->num_stages = 6;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	euro_champ_quals_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void euro_champ_quals_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	WORD day2 = *(WORD*)(_this + 0xB6);
	short year2 = *(short*)(_this + 0xB8);
	if (day2 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year2) {
		if (!data->f69 && a3) {
			sub_775070((BYTE*)*b74318, get_continent(EUROPE_9CF()), 0);
			data->f69 = 1;
			euro_champ_quals_all_teams(_this);
			euro_champ_quals_setup_first_group(_this);
			sub_6835C0(_this);
			sub_6827D0(_this, 0);
			for (BYTE i = 0; i < 2; i++) {
				euro_champ_quals_setup_groups_a(_this, i);
			}
			for (BYTE i = 0; i < 3; i++) {
				euro_champ_quals_setup_groups_b(_this, i + 2);
			}
			euro_champ_quals_reputation_setup(_this);
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) euro_champ_quals_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call euro_champ_quals_init2
		add esp, 0xc
		ret 8
	}
}

int euro_champ_quals_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 2) {
		switch (fate) {
		case Qualified1:
			qualify_team_for_international_comp(club, UEFA_EURO_9CF());
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage < 5) {
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 5) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			qualify_team_for_international_comp(club, UEFA_EURO_9CF(), false);
			if (a5) *a5 = 3;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) euro_champ_quals_set_table_fate()
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
		call euro_champ_quals_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int euro_champ_quals_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 2) {
		if (fate == Qualified1)
		{
			if (show_body_text) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
			else {
				cm3_club_comps* uefa_euro = get_comp(UEFA_EURO_9CF());
				sub_66F4E0(0xDE1F64, 0x9C470C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, uefa_euro->ClubCompGenderNameShort, uefa_euro->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &uefa_euro->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &uefa_euro->ClubCompNameShort[0], 0x7d0, (DWORD)uefa_euro);
				return 1;
			}
		}
		else if (fate == TopPlayoff) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 5) {
		if (fate == TopPlayoff)
		{
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 5) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			cm3_club_comps* uefa_euro = get_comp(UEFA_EURO_9CF());
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0x9C470C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, uefa_euro->ClubCompGenderNameShort, uefa_euro->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &uefa_euro->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &uefa_euro->ClubCompNameShort[0], 0x7d0, (DWORD)uefa_euro);
				return 1;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			default:
				sub_66F4E0(0xDE1F64, 0x9C46B8, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, uefa_euro->ClubCompGenderNameShort, uefa_euro->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &uefa_euro->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &uefa_euro->ClubCompNameShort[0], 0x7d0, (DWORD)uefa_euro);
				return 1;
			}
		}
	}
	return 0;
}

void __declspec(naked) euro_champ_quals_stage_news_c()
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
		call euro_champ_quals_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void euro_champ_quals_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if (main_stage_id >= 0x475 && main_stage_id <= 0x478) { // League A
		if (fate == Qualified1 || fate == CantBePromoted) {
			sub_66F4E0(dest_ptr, 0x9C48A4, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else if (fate == TopPlayoff) {
			sub_66F4E0(dest_ptr, 0x9a4399);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, (DWORD)&lge_a[0]);
			return;
		}
	}
	if (main_stage_id >= 0x459 && main_stage_id <= 0x45c) { // League B
		if (fate == TopPlayoff) {
			sub_66F4E0(dest_ptr, 0x9a4399);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, (DWORD)&lge_b[0]);
			return;
		}
	}
	if (main_stage_id == Playoff || sub_stage_id == Playoff)
	{
		if (fate == 1)
		{
			sub_66F4E0(dest_ptr, 0x9C48A4, club->ClubGenderName, 0xAD9C64);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) euro_champ_quals_landmarks_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call euro_champ_quals_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

WORD euro_champ_quals_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	return (val < 24) - 3;
}

void __declspec(naked) euro_champ_quals_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call euro_champ_quals_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE euro_champ_quals_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	if (al < 24) return (bl < 24) - 1;
	else return (bl < 24);
}

void __declspec(naked) euro_champ_quals_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call euro_champ_quals_vtable30
		add esp, 0x8
		ret 4
	}
}

void euro_champ_quals_final_stage_setup(BYTE* _this) {
	char stage_num = 5;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 12;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 5; al++)
	{
		if (al >= 0) curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
		}
	}
	if (clubs.size() != playoff_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size()) + ", should be " + to_string(playoff_teams);
		create_message_box("Error", msg.c_str(), true);
	}

	reverse(clubs.begin(), clubs.end());
	shuffle(clubs.begin(), clubs.begin() + 6, rng);
	shuffle(clubs.begin() + 6, clubs.end(), rng);
	BYTE team_order[12] = { 0,2,4,6,8,10,1,3,5,7,9,11 };

	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

void euro_champ_quals_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 5) {
			euro_champ_quals_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) euro_champ_quals_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call euro_champ_quals_stages_create
		add esp, 0x4
		ret
	}
}

void setup_euro_champ_quals() {
	WriteVTablePtr(euro_champ_quals_vtable, VTableEoSUpdate, (DWORD)&euro_champ_quals_update_c);
	WriteVTablePtr(euro_champ_quals_vtable, VTableLeagueSplit, (DWORD)&euro_champ_quals_init2_c);
	WriteVTablePtr(euro_champ_quals_vtable, VTableTableFates, (DWORD)&euro_champ_quals_set_table_fate);
	WriteVTablePtr(euro_champ_quals_vtable, VTableFixtures, (DWORD)&euro_champ_quals_fixture_caller);
	WriteVTablePtr(euro_champ_quals_vtable, VTableStageNews, (DWORD)&euro_champ_quals_stage_news_c);
	WriteVTablePtr(euro_champ_quals_vtable, VTable29, (DWORD)&euro_champ_quals_vtable29_c);
	WriteVTablePtr(euro_champ_quals_vtable, VTable30, (DWORD)&euro_champ_quals_vtable30_c);
	WriteVTablePtr(euro_champ_quals_vtable, VTableClubLandmarks, (DWORD)&euro_champ_quals_landmarks_c);

	WriteVTablePtr(euro_champ_quals_vtable, VTableLoadCompInfo, 0x48CEB0);
	WriteVTablePtr(euro_champ_quals_vtable, VTableSaveCompInfo, 0x48CEA0);

	WriteVTablePtr(euro_champ_quals_vtable, VTableSubsRounds, (DWORD)&euro_champ_quals_subs_c);

	WriteVTablePtr(euro_champ_quals_vtable, VTablePostMatchUpdate, 0x685d30); // check?
	WriteVTablePtr(euro_champ_quals_vtable, VTablePlayoffQual, (DWORD)&euro_champ_quals_stages_create_c);
	WriteVTablePtr(euro_champ_quals_vtable, VTableReputationSetup, (DWORD)&euro_champ_quals_reputation_setup_c);
	WriteVTablePtr(euro_champ_quals_vtable, VTableReputationCalc, (DWORD)&euro_champ_quals_reputation_calc_c);
	WriteVTablePtr(euro_champ_quals_vtable, VTable38, 0x684cd0); // check?
}