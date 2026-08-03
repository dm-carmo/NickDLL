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
	DWORD x = 0;
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
	DWORD y = -1;
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
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[4];
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
		FillFixtureDetails(pMem, fixture_id++, FirstPreliminaryRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 14), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 20), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondPreliminaryRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 24, 12, 22, 4, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx < 4) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		WORD numberOfLeagueTeams = 5;
		*num_rounds = 5;
		*stage_name_id = NumericGroupStage + stage_idx - 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 17), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 24), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 29), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 3), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 17), year, Wednesday, Evening);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 18), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 7), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 8, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 8), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 15), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 4, 8, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, NoTiebreak_2, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0);

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
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 34;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(GRE_SECOND_9CF());
	int d2_count = 0;
	// D2 - 20 teams
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) {
			vec.push_back(club);
			d2_count++;
		}
	}
	// extra lower if needed
	division_clubs = find_clubs_of_comp(GRE_LOWER_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	while (d2_count < 20)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* lower_club = division_clubs[availableIdx];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)lower_club, &is_main_club, 1);
		if (!ret_club || is_main_club) {
			vec.push_back(lower_club);
			d2_count++;
		}
		division_clubs.erase(division_clubs.begin() + availableIdx);
	}
	// D1
	division_clubs = find_clubs_of_comp(GRE_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

extern "C" _declspec(naked) void gre_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call gre_cup_teams
		add esp, 0x4
		ret
	}
}

char gre_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
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
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 1, 2, 0, 0 };
	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GamesWonTiebreaker, NoTiebreaker };

	vector<cm3_clubs*> clubs;
	for (WORD i = 0; i < 26; i++) {
		teams_seeded t = ((teams_seeded*)comp_data->teams_list)[i];
		if (t.f6 == 1) {
			clubs.push_back(t.club);
		}
	}
	for (WORD i = 26; i < comp_data->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)comp_data->teams_list)[i];
		clubs.push_back(t.club);
	}

	sort(clubs.begin(), clubs.end(), compareClubRep);
	shuffle(clubs.begin(), clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.begin() + 16, rng);
	shuffle(clubs.begin() + 16, clubs.end(), rng);

	WORD group_teams = 5;
	for (int i = 0; i < 4; i++) {
		DWORD v1 = *(DWORD*)_this;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i, &num_rounds, &stage_name_id, 0);
		comp_stats* data = (comp_stats*)_this;
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			*((DWORD*)(&pTeams[j])) = (DWORD)clubs[i + 4 * j];
		}

		WORD year = data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
			3, 1, 2, &tiebreaks[0], &prom_rel[0], year, i, stage_name_id, data->f81, 1, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = data->stages;
		*((DWORD*)(&stages_arr[i])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		data->current_stage = i;
	}
}

void gre_cup_final_stage_setup(BYTE* _this) {
	char stage_num = 4;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 12;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	for (char al = 0; al < 4; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		*((DWORD*)(&pTeams[al * 2])) = (DWORD)table_teams[1].club;
		*((DWORD*)(&pTeams[al * 2 + 1])) = (DWORD)table_teams[2].club;
		*((DWORD*)(&pTeams[al + 8])) = (DWORD)table_teams[0].club;
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
		else if (current == 4) {
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

int gre_cup_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0x1E);
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
	else if (stage < 4) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 4) {
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

void __declspec(naked) gre_cup_set_table_fate()
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
		call gre_cup_set_fates
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
		for (int i = 12; i < 20; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (int i = 20; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 21);
		}
		for (int i = 32; i < 34; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
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
	{13,21},
	{25,33},
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
	else if (stage < 4) {
		ret_current = 1 + 4 * (current - 1);
		if (min < 2) ret_min = 1;
		else ret_min = 1 + 4 * (min - 1);
		if (max < 2) ret_max = 5;
		else if (max < 4) ret_max = 9;
		else ret_max = 1 + 4 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 4) {
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
			sub_66F4E0(0xDE1F64, (DWORD)&qualified_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
				&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
		else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 4) {
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
	else if (stage_id == 4) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 5) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

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
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesGreece;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 5;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	gre_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
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
	WriteVTablePtr(gre_cup_vtable, VTableTableFates, (DWORD)&gre_cup_set_table_fate);
	WriteVTablePtr(gre_cup_vtable, VTableStageNews, (DWORD)&gre_cup_stage_news_c);
	WriteVTablePtr(gre_cup_vtable, VTableReputationSetup, (DWORD)&gre_cup_reputation_setup_c);
	WriteVTablePtr(gre_cup_vtable, VTableReputationCalc, (DWORD)&gre_cup_reputation_calc_c);
	WriteVTablePtr(gre_cup_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(gre_cup_vtable, VTablePostMatchUpdate, 0x51A150);
	WriteVTablePtr(gre_cup_vtable, VTable5, 0x521E00);
	WriteVTablePtr(gre_cup_vtable, VTableLeagueSplit, 0x51F890);
	WriteVTablePtr(gre_cup_vtable, VTable7, 0x51FC00);
	WriteVTablePtr(gre_cup_vtable, VTable8, 0x5210F0);
	WriteVTablePtr(gre_cup_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(gre_cup_vtable, VTable10, 0x48CEA0);
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
