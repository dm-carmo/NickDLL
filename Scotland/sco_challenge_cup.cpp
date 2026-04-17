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

vtable* sco_challenge_cup_vtable = new vtable((BYTE*)0x96C264, 0xB4);

void sco_challenge_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(sco_challenge_cup_vtable->vtable_ptr);
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

void sco_challenge_cup_free(BYTE* _this, BYTE a2) {
	sco_challenge_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) sco_challenge_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call sco_challenge_cup_free
		add esp, 0x8
		ret 4
	}
}

int sco_challenge_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[4];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) sco_challenge_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_challenge_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

void sco_challenge_cup_subs(BYTE* _this)
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

	comp_data->promotions = 4;
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

void __declspec(naked) sco_challenge_cup_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_challenge_cup_subs
		add esp, 0x4
		ret
	}
}

DWORD sco_challenge_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 4) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 5;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 26), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 23), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 11), year, Tuesday, Evening);

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
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
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 9), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 32, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("sco_chal_cup_r2_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 10), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 6), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("sco_chal_cup_r3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 7), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 27), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 8, 4, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("sco_chal_cup_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 24), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("sco_chal_cup_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 25), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday, Afternoon, FACupSemiFinals);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("sco_chal_cup_final_win"), prizeMoneyFile.GetInt("sco_chal_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) sco_challenge_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_challenge_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void sco_challenge_cup_reputation_setup(BYTE* _this) {
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
		for (int i = 32; i < 35; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 35; i < 40; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 36);
		}
	}
}

void __declspec(naked) sco_challenge_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_challenge_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void sco_challenge_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 4) {
		ret_current = 1 + 5 * (current - 1);
		if (min < 5) ret_min = 1;
		else ret_min = 1 + 5 * (min - 1);
		if (max < 5) ret_max = 17;
		else ret_max = 1 + 5 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 4) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) sco_challenge_cup_reputation_calc_c()
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
		call sco_challenge_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int sco_challenge_cup_all_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD total_teams = 40;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(4 * total_teams);

	comp_data->n_teams2 = total_teams;
	comp_data->teams2 = (DWORD*)pMem;

	DWORD* teams = comp_data->teams2;

	BYTE selected = get_country(NATION_SCOTLAND_9CF())->NationLeagueSelected;
	// Highland
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(SCO_HIGHLAND_9CF());
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	cm3_clubs* celtic_b = find_club("Glasgow Celtic B");
	cm3_clubs* hearts_b = find_club("Heart of Midlothian FC B");
	auto find_club = find(division_clubs.begin(), division_clubs.end(), celtic_b);
	if (find_club != division_clubs.end()) division_clubs.erase(find_club);
	find_club = find(division_clubs.begin(), division_clubs.end(), hearts_b);
	if (find_club != division_clubs.end()) division_clubs.erase(find_club);
	for (int i = 0; i < 5; i++)
	{
		vec.push_back(division_clubs[i]);
	}
	// Lowland
	division_clubs = find_clubs_of_comp(SCO_LOWLAND_9CF());
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	find_club = find(division_clubs.begin(), division_clubs.end(), celtic_b);
	if (find_club != division_clubs.end()) division_clubs.erase(find_club);
	find_club = find(division_clubs.begin(), division_clubs.end(), hearts_b);
	if (find_club != division_clubs.end()) division_clubs.erase(find_club);
	for (int i = 0; i < 5; i++)
	{
		vec.push_back(division_clubs[i]);
	}
	// League Two
	division_clubs = find_clubs_of_comp(SCO_LEAGUE_2_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// League One
	division_clubs = find_clubs_of_comp(SCO_LEAGUE_1_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Championship
	division_clubs = find_clubs_of_comp(SCO_CHAMP_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	shuffle(vec.begin(), vec.begin() + 5, rng);
	shuffle(vec.begin() + 5, vec.begin() + 10, rng);
	shuffle(vec.begin() + 10, vec.begin() + 15, rng);
	shuffle(vec.begin() + 15, vec.begin() + 20, rng);
	shuffle(vec.begin() + 20, vec.begin() + 25, rng);
	shuffle(vec.begin() + 25, vec.begin() + 30, rng);
	for (DWORD i = 0; i < 5; i++)
	{
		teams[i * 6] = (DWORD)vec[i];
		teams[i * 6 + 1] = (DWORD)vec[i + 5];
		teams[i * 6 + 2] = (DWORD)vec[i + 10];
		teams[i * 6 + 3] = (DWORD)vec[i + 15];
		teams[i * 6 + 4] = (DWORD)vec[i + 20];
		teams[i * 6 + 5] = (DWORD)vec[i + 25];
	}
	for (DWORD i = 30; i < 40; i++)
	{
		teams[i] = (DWORD)vec[i];
	}

	return 1;
}

void sco_challenge_cup_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 6;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	DWORD* teams = data->teams2;
	BYTE teamsAdded = 0;
	for (WORD i = 0; i < total_teams; i++)
		add_team_call(_this, teamsAdded++, (cm3_clubs*)teams[i], 0, 0);
	sub_684230(_this);
}

void sco_challenge_cup_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 6;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(total_teams * 4);

	DWORD* teams = data->teams2;
	BYTE teamsAdded = 0;
	for (WORD i = 0; i < total_teams; i++)
		*((DWORD*)(&pTeams[teamsAdded++])) = teams[i + 6 * (idx + 1)];

	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, total_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

char sco_challenge_cup_update(BYTE* _this) {
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
	sco_challenge_cup_all_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sco_challenge_cup_subs(_this);
	sco_challenge_cup_setup_first_group(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	for (BYTE i = 0; i < 4; i++) {
		sco_challenge_cup_setup_groups(_this, i);
	}
	return 1;
}

void __declspec(naked) sco_challenge_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_challenge_cup_update
		add esp, 0x4
		ret
	}
}

int sco_challenge_cup_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 4) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SecondRound, 0x1E);
			return 0;
		default:
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

void __declspec(naked) sco_challenge_cup_set_table_fate()
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
		call sco_challenge_cup_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void sco_challenge_cup_final_stage_setup(BYTE* _this) {
	char stage_num = 4;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 32;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;

	for (char al = -1; al < 4; al++) {
		if (al > -1) curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
		clubs.push_back(table_teams[2].club);
		clubs.push_back(table_teams[3].club);
	}

	// get best fifth placeds
	vector<team_league_stats> sort_fifths;
	curr_stage = comp_data;
	for (char al = -1; al < 4; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls = table_teams[curr_stage->promotions];
		sort_fifths.push_back(tls);
	}
	sort(sort_fifths.begin(), sort_fifths.end(), sortTLS);
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (int i = 0; i < 2; i++) {
		team_league_stats second = sort_fifths[i];
		clubs.push_back(second.club);
		curr_stage = comp_data;
		for (char al = -1; al < 4; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			team_league_stats tls = table_teams[curr_stage->promotions];
			if (tls.club == second.club) {
				table_teams[curr_stage->promotions].league_fate = Qualified1;
				curr_stage->promotions++;
				staff_history_qualified_86BDD0(staff_hist_ptr, tls.club, (DWORD)(comp_data->competition_db), None, SecondRound, 0x1E);
			}
		}
	}

	for (WORD j = 0; j < 22; j++) {
		*((DWORD*)(&pTeams[j])) = (DWORD)clubs[j];
	}

	DWORD* teams = comp_data->teams2;
	for (WORD j = 0; j < 10; j++) {
		*((DWORD*)(&pTeams[22 + j])) = teams[30 + j];
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

	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	curr_stage = comp_data;
	for (char al = -1; al < 4; al++) {
		if (al > -1) curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < 6; i++) {
			team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[i];
			if (t.league_fate != Qualified1) {
				staff_history_knocked_out_86C000(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
				int ret = sub_5A0590(ae2a38_ptr, (BYTE*)t.club);
				AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("sco_chal_cup_groups_prize_eliminated"));
				AddMoneyFromComp(_this, (BYTE*)t.club, prizeMoneyFile.GetInt("sco_chal_cup_groups_prize_eliminated"), 0, -1, GroupStage, 0, -2);
			}
		}
	}
}

void sco_challenge_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 4) {
			sco_challenge_cup_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) sco_challenge_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_challenge_cup_stages_create
		add esp, 0x4
		ret
	}
}

int sco_challenge_cup_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 4) {
		if (fate == Qualified1) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_rd2_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_rd2_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
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

	return 0;
}

void __declspec(naked) sco_challenge_cup_stage_news_c()
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
		call sco_challenge_cup_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void sco_challenge_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->year = year;
	data->comp_vtable = (DWORD*)(sco_challenge_cup_vtable->vtable_ptr);
	sco_challenge_cup_vtable->SetPointer(VTableInitFree, (DWORD)&sco_challenge_cup_free_c);
	sco_challenge_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&sco_challenge_cup_update_c);
	sco_challenge_cup_vtable->SetPointer(VTablePlayoffQual, (DWORD)&sco_challenge_cup_stages_create_c);
	sco_challenge_cup_vtable->SetPointer(VTableSetChampion, (DWORD)&sco_challenge_cup_set_champion_c);
	sco_challenge_cup_vtable->SetPointer(VTableClubLandmarks, 0x48cab0);
	sco_challenge_cup_vtable->SetPointer(VTableFixtures, (DWORD)&sco_challenge_cup_fixture_caller);
	sco_challenge_cup_vtable->SetPointer(VTableTableFates, (DWORD)&sco_challenge_cup_set_table_fate);
	sco_challenge_cup_vtable->SetPointer(VTableStageNews, (DWORD)&sco_challenge_cup_stage_news_c);
	sco_challenge_cup_vtable->SetPointer(VTableReputationSetup, (DWORD)&sco_challenge_cup_reputation_setup_c);
	sco_challenge_cup_vtable->SetPointer(VTableReputationCalc, (DWORD)&sco_challenge_cup_reputation_calc_c);
	sco_challenge_cup_vtable->SetPointer(VTableSubsRounds, (DWORD)&sco_challenge_cup_subs_c);
	sco_challenge_cup_vtable->SetPointer(VTableLeagueSplit, 0x6847c0);
	data->rules = RulesScotlandCup;
	data->f81 = 0xc;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 5;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	sco_challenge_cup_all_teams(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sco_challenge_cup_reputation_setup(_this);
	sco_challenge_cup_subs(_this);
	sco_challenge_cup_setup_first_group(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	for (BYTE i = 0; i < 4; i++) {
		sco_challenge_cup_setup_groups(_this, i);
	}
}

void setup_sco_challenge_cup() {
}