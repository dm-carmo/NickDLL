#include <windows.h>
#include <map>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

using namespace std;

DWORD* gre_cup_vtable = (DWORD*)0x96B4B4;

void gre_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = gre_cup_vtable;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
	}
	if ((DWORD*)data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
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
	sub_518690(_this);
}

void gre_cup_free(BYTE* _this, BYTE a2) {
	gre_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) gre_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call gre_cup_free
		add esp, 0x8
		ret 4
	}
}

int gre_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[2];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) gre_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

DWORD gre_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 13), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstPreliminaryRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 6, 3, 6, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 14), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 20), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondPreliminaryRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 22, 11, 19, 6, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		*num_rounds = 4;
		*stage_name_id = LeagueStage;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 3), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 10), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 29), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 3), year, Wednesday, Evening);

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

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 18), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 24), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 1, FixedTeamOrderInCup | Penalties | ExtraTime, NoTiebreak, 6, 8, 4, 8, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 15), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, FixedTeamOrderInCup | Penalties | ExtraTime, NoTiebreak, 6, 8, 4, 8, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 6, 4, 2, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 30), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) gre_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gre_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int gre_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	vector<cm3_clubs*> vec_uefa;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 30;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	vector<cm3_clubs*> division_clubs = find_clubs_of_country(NATION_GREECE_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		if (club->ClubEuroFlag != -1 && club->ClubDivision &&
			(club->ClubDivision->ClubCompID == GRE_FIRST_9CF() || club->ClubDivision->ClubCompID == GRE_SECOND_9CF()))
		{
			vec_uefa.push_back(club);
		}
	}

	division_clubs = find_clubs_of_comp(GRE_SECOND_9CF());
	int d2_count = 0;
	// D2 - 16 teams
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if ((!ret_club || is_main_club) && !vector_contains_element(vec_uefa, club)) {
			vec.push_back(club);
			d2_count++;
		}
	}
	// extra lower if needed
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(GRE_LOWER_9CF(), NATION_GREECE_9CF());
	for (size_t i = 0; i < lower_clubs.size(); i++) {
		cm3_clubs* c = lower_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if ((ret_club && !is_main_club) || vector_contains_element(vec_uefa, c))
		{
			lower_clubs.erase(lower_clubs.begin() + i);
			i--;
		}
	}
	division_clubs = get_random_weighted_clubs(lower_clubs, 16 - d2_count, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	sort(vec.begin(), vec.end(), compareClubLastDivPosInv);
	// D1
	division_clubs = find_clubs_of_comp(GRE_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_element(vec_uefa, club)) vec.push_back(club);
	}

	for (cm3_clubs* club : vec_uefa)
	{
		vec.push_back(club);
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

char gre_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_nteams_seedings = 0;
		data->special_teams_seedings = 0;
	}
	if (data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
		data->rounds_list = 0;
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
				data->f173[i] = 0;
			}
		}
		sub_9452CA_free(data->f173);
		data->f173 = 0;
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
	data->current_stage = -1;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	gre_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) gre_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_cup_update
		add esp, 0x4
		ret
	}
}

void gre_cup_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* comp_data = (comp_stats*)_this;

	char prom_rel[4] = { 4, 8, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GamesWonTiebreaker, NoTiebreaker };

	vector<cm3_clubs*> clubs;
	for (WORD i = 0; i < 25; i++) {
		teams_seeded t = ((teams_seeded*)comp_data->teams_list)[i];
		if (t.f6 == 1) {
			clubs.push_back(t.club);
		}
	}
	for (WORD i = 25; i < comp_data->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)comp_data->teams_list)[i];
		clubs.push_back(t.club);
	}
	if (clubs.size() != 16)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(comp_data->competition_db->ClubCompName, msg.c_str(), true);
	}

	sort(clubs.begin(), clubs.end(), compareClubRep);

	WORD group_teams = 16;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

	for (int j = 0; j < group_teams; j++) {
		*((DWORD*)(&pTeams[j])) = (DWORD)clubs[j];
	}

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, group_teams, pTeams, 0, (DWORD)(data->competition_db), 0, num_rounds,
		3, 1, 2, &tiebreaks[0], &prom_rel[0], year, stage_num, stage_name_id, data->f81, 1, 0, 0x28, -1, 0, 2);

	*((WORD*)(pStage + 0xA7)) = num_rounds;
	comp_stats* stage_data = (comp_stats*)pStage;
	char matchups[16][4] = {
		{6,-15,11,-4},
		{5,13,-10,-3},
		{-8,12,-11,1},
		{-5,15,-9,0},
		{3,-11,14,-6},
		{-2,-10,12,4},
		{-1,8,-16,7},
		{2,-12,13,-7},
		{-15,-7,3,9},
		{-16,5,1,-9},
		{-13,4,2,-12},
		{-14,7,-1,10},
		{10,-3,-6,15},
		{11,-2,-8,14},
		{8,0,-5,-14},
		{9,-4,6,-13},
	};
	shuffle(clubs.begin(), clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.end(), rng);


	for (BYTE m = 0; m < num_rounds; m++) {
		BYTE* ptr_last = (BYTE*)(pFixtures + fixture_dates_sz * 3);
		match_data* match = new match_data();
		match->comp_id = comp_data->competition_db->ClubCompID;
		match->f8 = -1;
		match->comp = comp_data->competition_db;
		match->end_year = year + *(WORD*)(ptr_last + 2);
		match->end_day = *(WORD*)(ptr_last);
		match->current_year = year;
		match->sub_stage_id = 0;
		match->main_stage_id = stage_name_id;
		match->f54_0xdb = stage_data->f219;
		match->tiebreaks = stage_data->f171;
		match->f58_0xc4 = stage_data->f196;
		match->f59 = -1;
		match->f61 = 0;
		match->f62 = 0;
		match->f64 = 1;
		match->f65 = 1;
		match->stage_number = stage_num;
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
		for (char t = 0; t < group_teams; t++) {
			char p1 = t;
			char p2 = matchups[t][m];
			if (p2 < 0) {
				p1 = abs(p2) - 1;
				p2 = t;
			}
			pair<char, char> match = make_pair(p1, p2);
			if (find(matchup_pairs.begin(), matchup_pairs.end(), match) == matchup_pairs.end())
				matchup_pairs.push_back(match);
		}

		for (int t = 0; t < group_teams / 2; t++) {
			cm3_clubs* home = clubs[matchup_pairs[t].first];
			cm3_clubs* away = clubs[matchup_pairs[t].second];
			BYTE* ptr = (BYTE*)(pFixtures + fixture_dates_sz * m);
			match->home_team_id = home->ClubID;
			match->away_team_id = away->ClubID;
			match->home_team = home;
			match->away_team = away;
			match->fixture_year = year + *(WORD*)(ptr + 2);
			match->fixture_day = *(WORD*)(ptr);
			match->fixture_number = m;
			match->f63 = *(BYTE*)(ptr + 4);

			sub_85C260((BYTE*)*(DWORD*)0xDD7EF4, *(DWORD*)(ptr + 0x3D), (BYTE*)match, comp_data->f36);
			sub_5AA680((BYTE*)*(DWORD*)0xAE2A58, (BYTE*)match, 1);
		}
	}

	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	sub_684230(pStage);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = stage_num;
}

void gre_cup_playoff_stage_setup(BYTE* _this) {
	char stage_num = 1;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	vector<cm3_clubs*> clubs;

	comp_stats* curr_stage = (comp_stats*)(comp_data->stages[0]);
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);

	for (WORD i = 0; i < curr_stage->n_teams; i++) {
		if (table_teams[i].league_fate == TopPlayoff) {
			cm3_clubs* club = table_teams[i].club;
			clubs.push_back(club);
		}
	}
	shuffle(clubs.begin(), clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.end(), rng);
	for (int i = 0; i < 4; i++)
	{
		*((DWORD*)(&pTeams[i * 2])) = (DWORD)clubs[i];
		*((DWORD*)(&pTeams[i * 2 + 1])) = (DWORD)clubs[i + 4];
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

void gre_cup_final_stage_setup(BYTE* _this) {
	char stage_num = 2;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	vector<cm3_clubs*> clubs;

	comp_stats* curr_stage = (comp_stats*)(comp_data->stages[0]);
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);

	for (WORD i = 0; i < curr_stage->n_teams; i++) {
		if (table_teams[i].league_fate == Qualified1) {
			cm3_clubs* club = table_teams[i].club;
			clubs.push_back(club);
		}
	}
	shuffle(clubs.begin(), clubs.end(), rng);
	for (int i = 0; i < 4; i++)
		*((DWORD*)(&pTeams[i * 2 + 1])) = (DWORD)clubs[i];

	char playoff_idx = 0;
	comp_stats* stage1_data = (comp_stats*)comp_data->stages[1];
	for (WORD j = 0; j < stage1_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)stage1_data->teams_list)[j];
		if (t.f6 == 1) {
			*((DWORD*)(&pTeams[playoff_idx])) = (DWORD)t.club;
			playoff_idx += 2;
		}
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
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

void gre_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			gre_cup_group_stage_setup(_this);
		}
		else if (current == 1) {
			gre_cup_playoff_stage_setup(_this);
		}
		else if (current == 2) {
			gre_cup_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) gre_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_cup_stages_create
		add esp, 0x4
		ret
	}
}

int gre_cup_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueStage, 0x1E);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			return 0;
		}
	}
	else if (stage == 0) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueStage, 0xF);
			return 0;
		}
	}
	else if (stage == 1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
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

void __declspec(naked) gre_cup_table_fates_c()
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
		call gre_cup_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void gre_cup_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		teams_seeded* all_teams = (teams_seeded*)comp_data->teams_list;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < comp_data->n_teams; i++)
		{
			clubs.push_back(all_teams[i].club);
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
		for (int i = 8; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 12; i < 16; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], i + 1);
		}
		for (int i = 16; i < 27; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 27; i < 30; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 28);
		}
	}
}

void __declspec(naked) gre_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

map<char, char> gre_cup_mappings = {
	{1,13},
	{12,17},
	{24,28},
};

void gre_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = gre_cup_mappings[current];
		if (ret_min != 1) ret_min = gre_cup_mappings[min];
		ret_max = gre_cup_mappings[max];
	}
	else if (stage == 0) {
		ret_current = current;
		if (min < 13) ret_min = 1;
		else ret_min = min;
		ret_max = max;
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 1) {
		if (current != 1) ret_current = 9;
		if (min != 1) ret_min = 9;
		if (max == 1) ret_max = 5;
		else ret_max = 9;
	}
	else if (stage == 2) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) gre_cup_reputation_calc_c()
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
		call gre_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int gre_cup_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1)
	{
		if (show_body_text) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
		if (fate == 1) {
			sub_66F4E0(0xDE1F64, (DWORD)&qualified_lge_stage_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
				&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
		else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 0) {
		if (fate == Qualified1) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_qtr_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_qtr_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == TopPlayoff) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_playoff_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_playoff_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 1) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 2) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) gre_cup_stage_news_c()
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
		call gre_cup_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void gre_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = gre_cup_vtable;
	data->year = year;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesGreece;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 3;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	gre_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	gre_cup_reputation_setup(_this);
}

void setup_gre_cup()
{
	WriteVTablePtr(gre_cup_vtable, VTableFixtures, (DWORD)&gre_cup_fixture_caller);
	WriteVTablePtr(gre_cup_vtable, VTableInitFree, (DWORD)&gre_cup_free_c);
	WriteVTablePtr(gre_cup_vtable, VTableEoSUpdate, (DWORD)&gre_cup_update_c);
	WriteVTablePtr(gre_cup_vtable, VTablePlayoffQual, (DWORD)&gre_cup_stages_create_c);
	WriteVTablePtr(gre_cup_vtable, VTableSetChampion, (DWORD)&gre_cup_set_champion_c);
	WriteVTablePtr(gre_cup_vtable, VTableTableFates, (DWORD)&gre_cup_table_fates_c);
	WriteVTablePtr(gre_cup_vtable, VTableStageNews, (DWORD)&gre_cup_stage_news_c);
	WriteVTablePtr(gre_cup_vtable, VTableReputationSetup, (DWORD)&gre_cup_reputation_setup_c);
	WriteVTablePtr(gre_cup_vtable, VTableReputationCalc, (DWORD)&gre_cup_reputation_calc_c);
	WriteVTablePtr(gre_cup_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(gre_cup_vtable, VTablePostMatchUpdate, 0x51A150);
	WriteVTablePtr(gre_cup_vtable, VTable5, 0x521E00);
	WriteVTablePtr(gre_cup_vtable, VTableLeagueSplit, 0x51F890);
	WriteVTablePtr(gre_cup_vtable, VTable7, 0x51FC00);
	WriteVTablePtr(gre_cup_vtable, VTable8, 0x5210F0);
	WriteVTablePtr(gre_cup_vtable, VTableLoadCompInfo, 0x48CEB0);
	WriteVTablePtr(gre_cup_vtable, VTableSaveCompInfo, 0x48CEA0);
	WriteVTablePtr(gre_cup_vtable, VTable17, 0x519690);
	WriteVTablePtr(gre_cup_vtable, VTable22, 0x5221F0);
	WriteVTablePtr(gre_cup_vtable, VTable32, 0x48F2D0);
	WriteVTablePtr(gre_cup_vtable, VTable33, 0x522910);
	WriteVTablePtr(gre_cup_vtable, VTable34, 0x522C50);
	WriteVTablePtr(gre_cup_vtable, VTable37, 0x522360);
	WriteVTablePtr(gre_cup_vtable, VTable38, 0x518790);
	WriteVTablePtr(gre_cup_vtable, VTable39, 0x51C020);
	WriteVTablePtr(gre_cup_vtable, VTable40, 0x51F2F0);
}
