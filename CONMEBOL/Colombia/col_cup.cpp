#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include "Helpers\9cf_constants.h"

vtable* col_cup_vtable = new vtable((BYTE*)0x96C8B8, 0xA0);

void col_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(col_cup_vtable->vtable_ptr);
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

void col_cup_free(BYTE* _this, BYTE a2) {
	col_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) col_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call col_cup_free
		add esp, 0x8
		ret 4
	}
}

int col_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[4];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) col_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call col_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

int col_cup_all_teams(BYTE* _this) {
	vector<cm3_clubs*> vec_qual;
	vector<cm3_clubs*> vec_r1;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 36;
	comp_data->special_nteams_seedings = total_teams;
	//comp_data->f56 = total_teams;

	if (comp_data->special_teams_seedings) sub_9452CA_free(comp_data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);
	comp_data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;

	// D1 Open
	comp_stats* col_first = (comp_stats*)get_loaded_league(COL_FIRST_9CF());
	WORD n_teams = col_first->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(col_first->team_league_table);
	for (int i = 0; i < n_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (i < 8) vec_r1.push_back(tls.club);
		else vec_qual.push_back(tls.club);
	}

	// D2 Open
	comp_stats* col_second = (comp_stats*)get_loaded_league(COL_SECOND_9CF());
	n_teams = col_second->n_teams;
	table_teams = (team_league_stats*)(col_second->team_league_table);
	for (int i = 0; i < n_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (i < 8) vec_r1.push_back(tls.club);
		else vec_qual.push_back(tls.club);
	}

	DWORD i = 0;
	for (DWORD j = 0; j < vec_r1.size() && i < total_teams; i++, j++)
	{
		teams[i].club = vec_r1[j];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}
	for (DWORD j = 0; j < 12 && i < total_teams; i++, j++)
	{
		teams[i].club = vec_qual[j];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}
	for (DWORD j = 0; j < 8 && i < total_teams; i++, j++)
	{
		teams[i].club = vec_qual[12 + (8 - j - 1)];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void col_cup_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 16;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	if (data->teams_list) sub_9452CA_free(data->teams_list);
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
	}

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	BYTE team_order[16] = { 8,6,10,4,12,2,14,0,1,15,3,13,5,11,7,9 };

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	for (WORD i = 0; i < total_teams; i++) {
		teams[team_order[i]].club = qualifiers[i].club;
		teams[team_order[i]].seeding = (i < 8);
		teams[team_order[i]].f6 = 0;
	}
}

void col_cup_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 5;
	DWORD* pTeams = (DWORD*)cm0102_malloc(total_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	WORD start = 16;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_teams; i++) {
		cm3_clubs* c = qualifiers[start + idx + i * 4].club;
		*((DWORD*)(&pTeams[i])) = (DWORD)c;
	}

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 2, 0, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };
	create_league_stage_data(pStage, _this, total_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		3, 1, 2, &tiebreaks[0], &prom_rel[0], year, idx, stage_name_id, data->f81, 1, 0, 0x28, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

char col_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	//if (data->teams_list) {
	//	sub_9452CA_free(data->teams_list);
	//	data->teams_list = 0;
	//}
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
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) col_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call col_cup_update
		add esp, 0x4
		ret
	}
}

DWORD col_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 27), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 31), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QualifyingRound, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | NoAwayGoals, 4, 16, 8, 16, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	else if (stage_idx < 4) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 5;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 7), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 14), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 21), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 24), year, Saturday);

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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 8), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 2), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 1, FixedTeamOrderInCup | Penalties, NoTiebreak, 4, 16, 8, 16, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 3), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 15), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, Penalties, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 6), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 17), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 1, Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("col_cup_final_win"), prizeMoneyFile.GetInt("col_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) col_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call col_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void col_cup_reputation_setup(BYTE* _this) {
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
		sort(clubs.begin(), clubs.end(), compareClubRep);

		sub_4A2540((BYTE*)comp_data->f8, clubs[0], 1);
		sub_4A2540((BYTE*)comp_data->f8, clubs[1], 2);
		for (int i = 2; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 3);
		}
		for (int i = 4; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 8; i < 16; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 16; i < 28; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 28; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 29);
		}
		for (int i = 32; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		comp_data->special_nteams_seedings = 0;
		sub_9452CA_free(comp_data->special_teams_seedings);
		comp_data->special_teams_seedings = 0;
	}
}

void __declspec(naked) col_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call col_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void col_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		// do nothing ?
	}
	else if (stage < 4) {
		ret_current = 1 + 4 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 4 * (min - 1);
		if (max < 3) ret_max = 9;
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

void __declspec(naked) col_cup_reputation_calc_c()
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
		call col_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int col_cup_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		default:
			//staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 4) {
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

void __declspec(naked) col_cup_table_fates_c()
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
		call col_cup_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void col_cup_final_stage_setup(BYTE* _this) {
	char stage_num = 4;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = comp_data;
	for (char al = 0; al < 4; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
	}
	for (WORD j = 0; j < comp_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)comp_data->teams_list)[j];
		if (t.f6 == 1) clubs.push_back(t.club);
	}
	shuffle(clubs.begin(), clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.end(), rng);

	for (WORD j = 0; j < playoff_teams / 2; j++) {
		*((DWORD*)(&pTeams[j * 2])) = (DWORD)clubs[j];
		*((DWORD*)(&pTeams[j * 2 + 1])) = (DWORD)clubs[j + 8];
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

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (char al = 0; al < 4; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[2];
		staff_history_knocked_out_86C000(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);

		t = ((team_league_stats*)(curr_stage->team_league_table))[3];
		staff_history_knocked_out_86C000(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
	}
}

void col_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 4) {
			col_cup_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) col_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call col_cup_stages_create
		add esp, 0x4
		ret
	}
}

bool col_cup_check_open_finishes(BYTE* _this) {
	comp_stats* col_first = (comp_stats*)get_loaded_league(COL_FIRST_9CF());
	comp_stats* col_second = (comp_stats*)get_loaded_league(COL_SECOND_9CF());

	bool is_finished = true;
	WORD total_teams = col_first->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(col_first->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.games < 19) {
			is_finished = false;
			break;
		}
	}
	if (is_finished) {
		total_teams = col_second->n_teams;
		table_teams = (team_league_stats*)(col_second->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.games < 15) {
				is_finished = false;
				break;
			}
		}
		return is_finished;
	}
	else return false;
}

void col_cup_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if (main_stage_id == QualifyingRound && sub_stage_id == FirstRound && fate == 1)
		sub_48CAB0(_this, dest_ptr, a2, None, RoundOf16, 2, club);
	else sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) col_cup_landmarks_c()
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
		call col_cup_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

int col_cup_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 4) {
		if (fate == Qualified1) {
			if (show_body_text) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
			else {
				sub_66F4E0(0xDE1F64, through_to_next_round_msg, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) col_cup_stage_news_c()
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
		call col_cup_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void col_cup_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 27, April, data->year, Sunday);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (*(WORD*)(current_date) >= date_day && *(WORD*)(current_date + 2) == date_year) {
			if (a3) {
				bool can_start = col_cup_check_open_finishes(_this);
				if (can_start) {
					data->f69 = 1;
					col_cup_all_teams(_this);
					col_cup_qualifier_teams(_this);
					DWORD v1 = *(DWORD*)_this;
					(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
					(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
					for (BYTE i = 0; i < 4; i++) {
						col_cup_setup_groups(_this, i);
					}
					(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
					sub_51C800(_this, 0);
				}
			}
		}
	}
	sub_51F890(_this, current_date, a3);
}

void __declspec(naked) col_cup_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call col_cup_init2
		add esp, 0xc
		ret 8
	}
}

void col_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(col_cup_vtable->vtable_ptr);
	col_cup_vtable->SetPointer(VTableInitFree, (DWORD)&col_cup_free_c);
	col_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&col_cup_update_c);
	col_cup_vtable->SetPointer(VTableFixtures, (DWORD)&col_cup_fixture_caller);
	col_cup_vtable->SetPointer(VTableReputationSetup, (DWORD)&col_cup_reputation_setup_c);
	col_cup_vtable->SetPointer(VTableReputationCalc, (DWORD)&col_cup_reputation_calc_c);
	col_cup_vtable->SetPointer(VTableTableFates, (DWORD)&col_cup_table_fates_c);
	col_cup_vtable->SetPointer(VTablePlayoffQual, (DWORD)&col_cup_stages_create_c);
	col_cup_vtable->SetPointer(VTableSetChampion, (DWORD)&col_cup_set_champion_c);
	col_cup_vtable->SetPointer(VTableLeagueSplit, (DWORD)&col_cup_init2_c);
	col_cup_vtable->SetPointer(VTableStageNews, (DWORD)&col_cup_stage_news_c);
	col_cup_vtable->SetPointer(VTableClubLandmarks, (DWORD)&col_cup_landmarks_c);
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 5;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesColombia;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void setup_col_cup() {

}