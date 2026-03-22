#include <windows.h>
#include <filesystem>
#include <fstream>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

using namespace std;

vtable* eng_league_trophy_vtable = new vtable((BYTE*)0x96C264, 0xB4);

void eng_league_trophy_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(eng_league_trophy_vtable->vtable_ptr);
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

void eng_league_trophy_free(BYTE* _this, BYTE a2) {
	eng_league_trophy_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) eng_league_trophy_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call eng_league_trophy_free
		add esp, 0x8
		ret 4
	}
}

// prize money for group stage win/draw
int league_trophy_money_after_match(BYTE* _this, BYTE* a2, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	char al, bl, cl;
	cm3_clubs* club_check = 0;
	al = *(char*)(a2 + 0x47);
	bl = *(char*)(a2 + 0x42);
	if (al == -1) {
		al = *(char*)(a2 + 0x43);
		cl = *(char*)(a2 + 0x44);
	}
	else cl = *(char*)(a2 + 0x48);
	if (al > cl) {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
	}
	else if (al < cl) {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
	}
	// group stage indexes
	if (bl < 15) {
		if (club_check) {
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club_check);
			AddToClubIncome((BYTE*)ret, 20000);
			AddMoneyFromComp(_this, (BYTE*)club_check, 20000, 0, -1, 0, a2, -2);
		}
		else {
			cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club1);
			AddToClubIncome((BYTE*)ret, 10000);
			cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
			ret = sub_5A0590(ae2a38_ptr, (BYTE*)club2);
			AddToClubIncome((BYTE*)ret, 10000);
			AddMoneyFromComp(_this, (BYTE*)club1, 10000, 0, -1, 0, a2, -2);
			AddMoneyFromComp(_this, (BYTE*)club2, 10000, 0, -1, 0, a2, -2);
		}
	}
	return sub_685D30(_this, a2, a3);
}

void __declspec(naked) league_trophy_money_after_match_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call league_trophy_money_after_match
		add esp, 0xc
		ret 8
	}
}

int eng_league_trophy_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[15];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) eng_league_trophy_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_trophy_set_champion
		add esp, 0x4
		ret 0
	}
}

void eng_league_trophy_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 4;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->f82 = 3;

	comp_data->promotions = 2;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x28;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) eng_league_trophy_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_trophy_subs
		add esp, 0x4
		ret
	}
}

DWORD eng_league_trophy_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 15) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 2), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 7), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 11), year, Tuesday, Evening);

		return (DWORD)pMem;
	}
	else if (stage_idx == 15) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 5;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));
		for (int i = 0; i < playoff_dates_sz * (*num_rounds); i++) pMem[i] = 0;

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 12), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 2), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, TenthRound, 0, FixedTeamOrderInCup2 + PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 32, 16, 32, 0, 0, 1, 0, 0, 20000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 13), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, EleventhRound, 0, FixedTeamOrderInCup2 + PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 0, 40000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 14), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 10), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 + PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 8, 4, 0, 0, 0, 1, 0, 0, 50000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 11), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 3), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 + PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 0, 50000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 4), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 12), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 50000, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) eng_league_trophy_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_league_trophy_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void eng_league_trophy_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		DWORD* all_teams = comp_data->teams2;
		vector<cm3_clubs*> clubs;
		for (DWORD i = 0; i < comp_data->n_teams2; i++)
		{
			clubs.push_back((cm3_clubs*)all_teams[i]);
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
		for (int i = 16; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 32; i < 48; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 48; i < 64; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 49);
		}
	}
}

void __declspec(naked) eng_league_trophy_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_trophy_reputation_setup
		add esp, 0x4
		ret
	}
}

void eng_league_trophy_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 15) {
		ret_current = 1 + 16 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 16 * (min - 1);
		if (max < 3) ret_max = 17;
		else ret_max = 1 + 16 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 15) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) eng_league_trophy_reputation_calc_c()
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
		call eng_league_trophy_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int eng_league_trophy_all_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD total_teams = 64;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(4 * total_teams);

	comp_data->n_teams2 = total_teams;
	comp_data->teams2 = (DWORD*)pMem;

	DWORD* teams = comp_data->teams2;
	vector<cm3_clubs*> division_clubs;
	size_t i = 0;
	// use academy teams as per real life, if setting is set to TRUE
	if (configFile.GetBool("useEnglandAcademyTeams"))
	{
		vector<cm3_clubs*> division_clubs = find_clubs_of_comp(ENG_ACADEMY_9CF());
		shuffle(division_clubs.begin(), division_clubs.end(), rng);
		for (; i < 16 && i < division_clubs.size(); i++)
		{
			vec.push_back(division_clubs[i]);
		}
	}
	// use National League teams otherwise, or as backup if there aren't enough academy teams
	division_clubs = find_clubs_of_comp(ENG_CONFERENCE_9CF());
	BYTE selected = get_country(NATION_ENGLAND_9CF())->NationLeagueSelected;
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (int j = 0; i < 16 && j < 16; i++, j++)
	{
		vec.push_back(division_clubs[i]);
	}
	// League Two
	division_clubs = find_clubs_of_comp(ENG_LEAGUE_2_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// League One
	division_clubs = find_clubs_of_comp(ENG_LEAGUE_1_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	sort(vec.begin(), vec.begin() + 16, compareClubLatitude);
	shuffle(vec.begin(), vec.begin() + 8, rng);
	shuffle(vec.begin() + 8, vec.begin() + 16, rng);
	sort(vec.begin() + 16, vec.end(), compareClubLatitude);
	shuffle(vec.begin() + 16, vec.begin() + 40, rng);
	shuffle(vec.begin() + 40, vec.end(), rng);
	for (DWORD i = 0; i < 16; i++)
	{
		teams[i * 4] = (DWORD)vec[i];
	}
	for (DWORD i = 0; i < 16; i++)
	{
		teams[i * 4 + 1] = (DWORD)vec[i * 3 + 16];
		teams[i * 4 + 2] = (DWORD)vec[i * 3 + 17];
		teams[i * 4 + 3] = (DWORD)vec[i * 3 + 18];
	}

	return 1;
}

void eng_league_trophy_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	DWORD* teams = data->teams2;
	BYTE teamsAdded = 0;
	for (WORD i = 0; i < total_teams; i++)
		add_team_call(_this, teamsAdded++, (cm3_clubs*)teams[i], 0, 0);
	SetupTVMoney(_this, 20000, 0);
	sub_684230(_this);
}

void eng_league_trophy_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(total_teams * 4);

	DWORD* teams = data->teams2;
	BYTE teamsAdded = 0;
	for (WORD i = 0; i < total_teams; i++)
		*((DWORD*)(&pTeams[teamsAdded++])) = teams[i + 4 * (idx + 1)];

	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, total_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	SetupTVMoney(pStage, 20000, 0);
	sub_684230(pStage);
	data->current_stage = idx;
}

char eng_league_trophy_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	sub_687970(_this, ebx);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	if (data->teams2) sub_9452CA_free(data->teams2);
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
	eng_league_trophy_all_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	eng_league_trophy_subs(_this);
	eng_league_trophy_setup_first_group(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	for (BYTE i = 0; i < 15; i++) {
		eng_league_trophy_setup_groups(_this, i);
	}
	return 1;
}

void __declspec(naked) eng_league_trophy_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_trophy_update
		add esp, 0x4
		ret
	}
}

int eng_league_trophy_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 15) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, TenthRound, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 15) {
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

void __declspec(naked) eng_league_trophy_set_table_fate()
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
		call eng_league_trophy_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void eng_league_trophy_final_stage_setup(BYTE* _this) {
	char stage_num = 15;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 32;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs_1;
	vector<cm3_clubs*> clubs_2;
	for (char al = -1; al < 15; al++) {
		if (al > -1) curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs_1.push_back(table_teams[0].club);
		clubs_2.push_back(table_teams[1].club);
	}

	shuffle(clubs_1.begin(), clubs_1.begin() + 8, rng);
	shuffle(clubs_1.begin() + 8, clubs_1.end(), rng);
	shuffle(clubs_2.begin(), clubs_2.begin() + 8, rng);
	shuffle(clubs_2.begin() + 8, clubs_2.end(), rng);

	for (WORD j = 0; j < 16; j++) {
		*((DWORD*)(&pTeams[j * 2])) = (DWORD)clubs_1[j];
	}
	for (WORD j = 0; j < 16; j++) {
		*((DWORD*)(&pTeams[j * 2 + 1])) = (DWORD)clubs_2[j];
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
	comp_data->current_stage = (long)stage_num;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_51C410(new_stage, 0);

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	curr_stage = comp_data;
	for (char al = -1; al < 15; al++) {
		if (al > -1) curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[2];
		staff_history_knocked_out_86C000(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);

		t = ((team_league_stats*)(curr_stage->team_league_table))[3];
		staff_history_knocked_out_86C000(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
	}
}

void eng_league_trophy_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 15) {
			eng_league_trophy_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) eng_league_trophy_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_trophy_stages_create
		add esp, 0x4
		ret
	}
}

int eng_league_trophy_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 15) {
		if (fate == Qualified1) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_r32_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_r32_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 15) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) eng_league_trophy_stage_news_c()
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
		call eng_league_trophy_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void eng_league_trophy_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->year = year;
	data->comp_vtable = (DWORD*)(eng_league_trophy_vtable->vtable_ptr);
	eng_league_trophy_vtable->SetPointer(VTableInitFree, (DWORD)&eng_league_trophy_free_c);
	eng_league_trophy_vtable->SetPointer(VTableEoSUpdate, (DWORD)&eng_league_trophy_update_c);
	eng_league_trophy_vtable->SetPointer(VTablePlayoffQual, (DWORD)&eng_league_trophy_stages_create_c);
	eng_league_trophy_vtable->SetPointer(VTableSetChampion, (DWORD)&eng_league_trophy_set_champion_c);
	eng_league_trophy_vtable->SetPointer(VTableClubLandmarks, 0x48cab0);
	eng_league_trophy_vtable->SetPointer(VTableFixtures, (DWORD)&eng_league_trophy_fixture_caller);
	eng_league_trophy_vtable->SetPointer(VTableTableFates, (DWORD)&eng_league_trophy_set_table_fate);
	eng_league_trophy_vtable->SetPointer(VTableStageNews, (DWORD)&eng_league_trophy_stage_news_c);
	eng_league_trophy_vtable->SetPointer(VTableReputationSetup, (DWORD)&eng_league_trophy_reputation_setup_c);
	eng_league_trophy_vtable->SetPointer(VTableReputationCalc, (DWORD)&eng_league_trophy_reputation_calc_c);
	eng_league_trophy_vtable->SetPointer(VTableSubsRounds, (DWORD)&eng_league_trophy_subs_c);
	eng_league_trophy_vtable->SetPointer(VTableLeagueSplit, 0x6847c0);
	eng_league_trophy_vtable->SetPointer(VTablePostMatchUpdate, (DWORD)&league_trophy_money_after_match_c);
	data->rules = 0x9;
	data->f81 = 0xc;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_GREEN_3_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 16;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	eng_league_trophy_all_teams(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	eng_league_trophy_reputation_setup(_this);
	eng_league_trophy_subs(_this);
	eng_league_trophy_setup_first_group(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	for (BYTE i = 0; i < 15; i++) {
		eng_league_trophy_setup_groups(_this, i);
	}
}

void setup_eng_league_trophy() {
}