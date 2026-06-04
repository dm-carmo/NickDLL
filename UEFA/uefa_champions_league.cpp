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

// Possible idea for later: add the two spots for the countries with the highest coefficient
DWORD* uefa_champions_league_vtable = (DWORD*)0x96A1D0;

void uefa_champions_league_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = uefa_champions_league_vtable;
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

void uefa_champions_league_free(BYTE* _this, BYTE a2) {
	uefa_champions_league_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) uefa_champions_league_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call uefa_champions_league_free
		add esp, 0x8
		ret 4
	}
}

int uefa_champions_league_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[6];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) uefa_champions_league_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_champions_league_set_champion
		add esp, 0x4
		ret 0
	}
}

DWORD uefa_champions_league_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = ChampionsPath;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 9), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstQualifyingPhase, 4, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 28, 14, 28, 0, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_qr1_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 23), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondQualifyingPhase, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 24, 12, 10, 28, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_qr2_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 21), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdQualifyingPhase, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 12, 6, 0, 0, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_qr3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 20), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 10, 5, 4, 38, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_po_lose"));

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = LeaguePath;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 23), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondQualifyingPhase, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 4, 2, 4, 0, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_qr2_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 21), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdQualifyingPhase, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 8, 4, 6, 4, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_qr3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 20), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 4, 2, 0, 0, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_po_lose"));

		return (DWORD)pMem;
	}
	else if (stage_idx < 5) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		WORD numberOfLeagueTeams = 9;
		*num_rounds = 9;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 2;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx < 3)
		{
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 17), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 23), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 1), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 22), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 4), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 26), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 9), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 20), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 28), year, Wednesday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 16), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 24), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 30), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 21), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 5), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 25), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 10), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 21), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 28), year, Wednesday, Evening);
		}

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 5) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 30), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 18), year, Wednesday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, KnockoutPlayoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 16, 8, 16, 0, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_ko_lose"));

		return (DWORD)pMem;
	}
	else if (stage_idx == 6) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 27), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 11), year, Wednesday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 16, 8, 16, 0, 0, 2, 7, prizeMoneyFile.GetInt("uefa_ucl_r16_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 18), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 8), year, Wednesday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 8, 4, 0, 0, 0, 2, 7, prizeMoneyFile.GetInt("uefa_ucl_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 29), year, Wednesday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 4, 2, 0, 0, 0, 2, 7, prizeMoneyFile.GetInt("uefa_ucl_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 7), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 30), year, Saturday, Evening, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_final_win"), prizeMoneyFile.GetInt("uefa_ucl_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) uefa_champions_league_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uefa_champions_league_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void uefa_champions_league_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 81;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	DWORD teams_r2 = 0;
	DWORD teams_r3 = 0;
	DWORD teams_r4 = 0;
	DWORD teams_r5 = 0;
	DWORD teams_r6 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == UEFA_CHAMPIONS_LEAGUE_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			if (seed == 1 && teams_r1 < 29) {
				teams[teams_r1].club = club;
				teams[teams_r1].f5 = 7;
				teams[teams_r1].f6 = 0;
				teams_r1++;
			}
			else if (seed == 2 && teams_r2 < 4) {
				teams[teams_r2 + 29].club = club;
				teams[teams_r2 + 29].f5 = 8;
				teams[teams_r2 + 29].f6 = 0;
				teams_r2++;
			}
			else if (seed == 3 && teams_r3 < 6) {
				teams[teams_r3 + 33].club = club;
				teams[teams_r3 + 33].f5 = 6;
				teams[teams_r3 + 33].f6 = 0;
				teams_r3++;
			}
			else if (seed == 4 && teams_r4 < 4) {
				teams[teams_r4 + 39].club = club;
				teams[teams_r4 + 39].f5 = 9;
				teams[teams_r4 + 39].f6 = 0;
				teams_r4++;
			}
			else if (seed == 5 && teams_r5 < 10) {
				teams[teams_r5 + 43].club = club;
				teams[teams_r5 + 43].f5 = 13;
				teams[teams_r5 + 43].f6 = 0;
				teams_r5++;
			}
			else if (seed == 6 && teams_r6 < 28) {
				teams[teams_r6 + 53].club = club;
				teams[teams_r6 + 53].f5 = 0;
				teams[teams_r6 + 53].f6 = 0;
				teams_r6++;
			}
		}
	}
}

void uefa_champions_league_champs_path_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 42;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	WORD count = 0;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 0 || seed == 8 || seed == 13) {
			teams[total_teams - count - 1].club = qualifiers[i].club;
			if (seed == 8) {
				teams[total_teams - count - 1].f5 = 2;
			}
			else if (seed == 13) {
				teams[total_teams - count - 1].f5 = 1;
			}
			else {
				teams[total_teams - count - 1].f5 = 0;
			}
			teams[total_teams - count - 1].f6 = 0;
			count++;
		}
	}
}

void uefa_champions_league_league_path_setup(BYTE* _this) {
	char stage_num = 0;

	comp_stats* data = (comp_stats*)_this;
	BYTE playoff_teams = 10;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	DWORD count = 0;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 6) {
			*((DWORD*)(&pTeams[playoff_teams - count - 1])) = (DWORD)qualifiers[i].club;
			count++;
		}
	}
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 9) {
			*((DWORD*)(&pTeams[playoff_teams - count - 1])) = (DWORD)qualifiers[i].club;
			count++;
		}
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	data->current_stage = (long)stage_num;
}

void uefa_champions_league_reputation_setup(BYTE* _this) {
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
		for (int i = 16; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 24; i < 28; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
		for (int i = 28; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 29);
		}
		for (int i = 32; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 36; i < 43; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 37);
		}
		for (int i = 43; i < 53; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 44);
		}
		for (int i = 53; i < 67; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 54);
		}
		for (int i = 67; i < 81; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 68);
		}
	}
}

void __declspec(naked) uefa_champions_league_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_champions_league_reputation_setup
		add esp, 0x4
		ret
	}
}

map<char, char> ucl_main_mappings = {
	{1,33},
	{6,37},
	{11,44},
	{17,54},
	{29,68},
};
map<char, char> ucl_leag_mappings = {
	{1,33},
	{3,37},
	{5,44},
	{9,54},
};

void uefa_champions_league_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = ucl_main_mappings[current];
		if (ret_min != 1) ret_min = ucl_main_mappings[min];
		ret_max = ucl_main_mappings[max];
	}
	else if (stage == 0) {
		ret_current = ucl_leag_mappings[current];
		if (ret_min != 1) ret_min = ucl_leag_mappings[min];
		ret_max = ucl_leag_mappings[max];
	}
	else if (stage < 5) {
		ret_current = 1 + 4 * (current - 1);
		if (min < 7) ret_min = 1;
		else ret_min = 1 + 4 * (min - 1);
		if (max < 3) ret_max = 9;
		else if (max < 7) ret_max = 17;
		else ret_max = 1 + 4 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 5) {
		if (current != 1) ret_current = 17;
		if (min != 1) ret_min = 17;
		if (max == 1) ret_max = 9;
		else ret_max = 17;
	}
	else if (stage == 6) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) uefa_champions_league_reputation_calc_c()
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
		call uefa_champions_league_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

// prize money for group stage win/draw and coefficient updates
int ucl_money_after_match(BYTE* _this, BYTE* a2, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	char al, bl, cl;
	cm3_clubs* club_check = 0;
	al = *(char*)(a2 + 0x47);
	char win_coef = 4;
	char draw_coef = 2;
	bl = *(char*)(a2 + 0x42);
	if (bl < 1) {
		win_coef = 2;
		draw_coef = 1;
	}
	if (al == -1) {
		al = *(char*)(a2 + 0x43);
		cl = *(char*)(a2 + 0x44);
	}
	else cl = *(char*)(a2 + 0x48);
	if (al == cl) {
		cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
		UpdateCountryCoefficient(club1, draw_coef);
		cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
		UpdateCountryCoefficient(club2, draw_coef);
	}
	else if (al > cl) {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
		UpdateCountryCoefficient(club_check, win_coef);
	}
	else {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
		UpdateCountryCoefficient(club_check, win_coef);
	}
	// group stage indexes
	if (bl > 0 && bl < 5) {
		if (club_check) {
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club_check);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uefa_ucl_groups_win"));
			AddMoneyFromComp(_this, (BYTE*)club_check, prizeMoneyFile.GetInt("uefa_ucl_groups_win"), 0, -1, 0, a2, -2);
		}
		else {
			cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club1);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uefa_ucl_groups_draw"));
			cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
			ret = sub_5A0590(ae2a38_ptr, (BYTE*)club2);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uefa_ucl_groups_draw"));
			AddMoneyFromComp(_this, (BYTE*)club1, prizeMoneyFile.GetInt("uefa_ucl_groups_draw"), 0, -1, 0, a2, -2);
			AddMoneyFromComp(_this, (BYTE*)club2, prizeMoneyFile.GetInt("uefa_ucl_groups_draw"), 0, -1, 0, a2, -2);
		}
	}
	return sub_51A150(_this, a2, a3);
}

void __declspec(naked) ucl_money_after_match_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ucl_money_after_match
		add esp, 0xc
		ret 8
	}
}

// Get teams to send squad registration news
int ucl_register_squad(BYTE* _this, DWORD* a2, char a3) {
	comp_stats* data = (comp_stats*)_this;
	if (a3 == 1) {
		BYTE* pMem = (BYTE*)sub_944CF1_operator_new(data->special_nteams_seedings * 4);
		teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
		int count = 0;
		for (WORD i = 0; i < data->special_nteams_seedings; i++) {
			teams_seeded t = teams[i];
			if (t.club->ClubEuroFlag == data->competition_db->ClubCompID && t.f5 != 7 && t.f5 != 8) {
				*(DWORD*)(pMem + 4 * count) = (DWORD)t.club;
				count++;
			}
		}
		*a2 = (DWORD)pMem;
		return count;
	}
	if (a3 == 2) {
		BYTE* pMem = (BYTE*)sub_944CF1_operator_new(data->special_nteams_seedings * 4);
		teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
		int count = 0;
		for (WORD i = 0; i < data->special_nteams_seedings; i++) {
			teams_seeded t = teams[i];
			if (t.club->ClubEuroFlag == data->competition_db->ClubCompID) {
				*(DWORD*)(pMem + 4 * count) = (DWORD)t.club;
				count++;
			}
		}
		*a2 = (DWORD)pMem;
		return count;
	}
	if (a3 == 3) {
		BYTE* pMem = (BYTE*)sub_944CF1_operator_new(data->special_nteams_seedings * 4);
		teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
		int count = 0;
		for (WORD i = 0; i < data->special_nteams_seedings; i++) {
			teams_seeded t = teams[i];
			if (t.club->ClubEuroFlag == data->competition_db->ClubCompID) {
				*(DWORD*)(pMem + 4 * count) = (DWORD)t.club;
				count++;
			}
		}
		*a2 = (DWORD)pMem;
		return count;
	}

	return sub_48E1C0(_this, a2, 0);
}

void __declspec(naked) ucl_register_squad_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ucl_register_squad
		add esp, 0xc
		ret 8
	}
}

char uefa_champions_league_update(BYTE* _this) {
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
	sub_9035A0((BYTE*)*uefa_seeding_list, 0);
	uefa_champions_league_all_teams(_this);
	uefa_champions_league_champs_path_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	uefa_champions_league_league_path_setup(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) uefa_champions_league_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_champions_league_update
		add esp, 0x4
		ret
	}
}

void uefa_champions_league_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = uefa_champions_league_vtable;
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesEurope;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 7;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	sub_9035A0((BYTE*)*uefa_seeding_list, 0);
	uefa_champions_league_all_teams(_this);
	uefa_champions_league_champs_path_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	uefa_champions_league_league_path_setup(_this);
	uefa_champions_league_reputation_setup(_this);
}

void uefa_champions_league_group_stage_setup(BYTE* _this) {
	char stage_num = 1;
	DWORD v1 = *(DWORD*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 4, 0, 0 };
	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, GamesWonTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < comp_data->special_nteams_seedings; i++) {
		if (teams[i].club->ClubEuroFlag == comp_data->competition_db->ClubCompID)
			clubs.push_back(teams[i].club);
	}
	if (clubs.size() != 36)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(comp_data->competition_db->ClubCompName, msg.c_str(), true);
	}

	sort(clubs.begin(), clubs.end(), compareClubSeeding);
	shuffle(clubs.begin(), clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.begin() + 16, rng);
	shuffle(clubs.begin() + 16, clubs.begin() + 20, rng);
	shuffle(clubs.begin() + 20, clubs.begin() + 24, rng);
	shuffle(clubs.begin() + 24, clubs.begin() + 28, rng);
	shuffle(clubs.begin() + 28, clubs.begin() + 32, rng);
	shuffle(clubs.begin() + 32, clubs.end(), rng);

	WORD group_teams = 9;
	for (int i = 0; i < 4; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 4 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uefa_ucl_groups_qualify"));
			AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("uefa_ucl_groups_qualify"), 0, -1, GroupStage, 0, -2);
			UpdateCountryCoefficient(club, 6);
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 1, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void uefa_champions_league_playoff_stage_setup(BYTE* _this) {
	char stage_num = 5;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	for (char al = 1; al < 5; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		int idx1 = 0;
		if (al == 2) idx1 = 2;
		else if (al == 3) idx1 = 3;
		else if (al == 4) idx1 = 1;
		int idx2 = 1;
		if (al == 2) idx2 = 3;
		else if (al == 3) idx2 = 2;
		else if (al == 4) idx2 = 0;
		*((DWORD*)(&pTeams[idx1 * 4])) = (DWORD)table_teams[2].club;
		UpdateCountryCoefficient(table_teams[2].club, 4);
		*((DWORD*)(&pTeams[idx2 * 4 + 1])) = (DWORD)table_teams[5].club;
		UpdateCountryCoefficient(table_teams[5].club, 1);
		*((DWORD*)(&pTeams[idx2 * 4 + 2])) = (DWORD)table_teams[4].club;
		UpdateCountryCoefficient(table_teams[4].club, 2);
		*((DWORD*)(&pTeams[idx1 * 4 + 3])) = (DWORD)table_teams[3].club;
		UpdateCountryCoefficient(table_teams[3].club, 3);
	}

	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	for (int i = 0; i < 16; i++)
	{
		cm3_clubs* club = (cm3_clubs*)*((DWORD*)(&pTeams[i]));
		if (club)
		{
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uefa_ucl_ko_qualify"));
			AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("uefa_ucl_ko_qualify"), 0, -1, KnockoutPlayoff, 0, -2);
		}
	}

	// for each team in pteams:
	// call 7e9180(AE28F0_ptr + 4 * comp->rules, team)

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (char al = 1; al < 5; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[6];
		t.club->ClubEuroFlag = -1;

		t = ((team_league_stats*)(curr_stage->team_league_table))[7];
		t.club->ClubEuroFlag = -1;

		t = ((team_league_stats*)(curr_stage->team_league_table))[8];
		t.club->ClubEuroFlag = -1;
	}
}

void uefa_champions_league_final_stage_setup(BYTE* _this) {
	char stage_num = 6;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	// fill in teams with 0 to avoid odd crashes
	for (DWORD i = 0; i < playoff_teams; i++)
	{
		*((DWORD*)(&pTeams[i])) = 0;
	}

	comp_stats* curr_stage = comp_data;

	for (char al = 1; al < 5; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		int idx1 = 0;
		if (al == 2) idx1 = 5;
		else if (al == 3) idx1 = 4;
		else if (al == 4) idx1 = 1;
		*((DWORD*)(&pTeams[idx1 * 2 + 1])) = (DWORD)table_teams[0].club;
		UpdateCountryCoefficient(table_teams[0].club, 6);
		UpdateCountryCoefficient(table_teams[0].club, 3);
		*((DWORD*)(&pTeams[idx1 * 2 + 4 + 1])) = (DWORD)table_teams[1].club;
		UpdateCountryCoefficient(table_teams[1].club, 5);
		UpdateCountryCoefficient(table_teams[1].club, 3);
	}

	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	for (int i = 0; i < 16; i++)
	{
		cm3_clubs* club = (cm3_clubs*)*((DWORD*)(&pTeams[i]));
		if (club)
		{
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uefa_ucl_r16_qualify2"));
			AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("uefa_ucl_r16_qualify2"), 0, -1, RoundOf16, 0, -2);
		}
	}

	char playoff_idx = 0;
	comp_stats* stage5_data = (comp_stats*)comp_data->stages[5];
	for (WORD j = 0; j < stage5_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)stage5_data->teams_list)[j];
		if (t.f6 == 1) {
			*((DWORD*)(&pTeams[playoff_idx])) = (DWORD)t.club;
			UpdateCountryCoefficient(t.club, 3);
			playoff_idx += 2;
		}
	}

	// for each team in pteams:
	// call 7e9180(AE28F0_ptr + 4 * comp->rules, team)

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void uefa_champions_league_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 1) {
			uefa_champions_league_group_stage_setup(_this);
		}
		else if (current == 5) {
			uefa_champions_league_playoff_stage_setup(_this);
		}
		else if (current == 6) {
			uefa_champions_league_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) uefa_champions_league_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_champions_league_stages_create
		add esp, 0x4
		ret
	}
}

int uefa_champions_league_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* uel_bytes = get_loaded_league(UEFA_EUROPA_LEAGUE_9CF());
	comp_stats* uel_data = (comp_stats*)uel_bytes;
	DWORD v2 = *(DWORD*)uel_bytes;
	BYTE* uecl_bytes = get_loaded_league(UEFA_CONFERENCE_LEAGUE_9CF());
	comp_stats* uecl_data = (comp_stats*)uecl_bytes;
	DWORD v3 = *(DWORD*)uecl_bytes;
	if (stage == -1 || stage == 0) {
		BYTE* rounds = comp_data->rounds_list;
		if (stage != -1) rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
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
			WORD round_idx = *(WORD*)(rounds + playoff_dates_sz * current_round + 9);
			// Second Qualifying Round (league only) + Third Qualifying Round (champions only) to Europa League qualifiers
			if ((round_idx == 0 && stage == 0) || (round_idx == 2 && stage == -1)) {
				club->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
				teams_seeded* qualifiers = (teams_seeded*)uel_data->special_teams_seedings;
				WORD insert_idx = uel_data->special_nteams_seedings;
				qualifiers[insert_idx].club = club;
				qualifiers[insert_idx].f5 = 5;
				qualifiers[insert_idx].f6 = 0;
				uel_data->special_nteams_seedings++;

				teams_seeded* teams = (teams_seeded*)uel_data->teams_list;
				insert_idx = 0;
				while (teams[insert_idx].club) insert_idx++;
				teams[insert_idx].club = club;
				teams[insert_idx].f5 = 2;
				teams[insert_idx].f6 = 0;

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uel_data->competition_db), MainPath,
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0x1E);
				(*(int(__thiscall**)(BYTE*))(v2 + 0x5C))(uel_bytes);
			}
			// Second Qualifying Round (champions only) to Europa League qualifiers
			else if (round_idx == 1 && stage == -1) {
				club->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
				teams_seeded* qualifiers = (teams_seeded*)uel_data->special_teams_seedings;
				WORD insert_idx = uel_data->special_nteams_seedings;
				qualifiers[insert_idx].club = club;
				qualifiers[insert_idx].f5 = 5;
				qualifiers[insert_idx].f6 = 0;
				uel_data->special_nteams_seedings++;

				comp_stats* stage0_data = (comp_stats*)uel_data->stages[0];
				teams_seeded* teams = (teams_seeded*)stage0_data->teams_list;
				insert_idx = 0;
				while (teams[insert_idx].club) insert_idx++;
				teams[insert_idx].club = club;
				teams[insert_idx].f5 = 2;
				teams[insert_idx].f6 = 0;

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uel_data->competition_db), ChampionsPath, ThirdQualifyingPhase, 0x1E);
				(*(int(__thiscall**)(BYTE*))(v2 + 0x5C))(uel_bytes);
			}
			// Playoff (all) to Europa League groups (handled in Europa League)
			else if (round_idx + stage == 2) {
				club->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uel_data->competition_db), None, GroupStage, 0x1E);
			}
			// Third Qualifying Round (league only) to Europa League groups
			else if (round_idx == 1 && stage == 0) {
				club->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
				teams_seeded* qualifiers = (teams_seeded*)uel_data->special_teams_seedings;
				WORD insert_idx = uel_data->special_nteams_seedings;
				qualifiers[insert_idx].club = club;
				qualifiers[insert_idx].f5 = 5;
				qualifiers[insert_idx].f6 = 0;
				uel_data->special_nteams_seedings++;

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uel_data->competition_db), None, GroupStage, 0x1E);
				(*(int(__thiscall**)(BYTE*))(v2 + 0x5C))(uel_bytes);
			}
			// First Qualifying Round (champions only) to Conference League qualifiers
			else if (round_idx == 0 && stage == -1) {
				club->ClubEuroFlag = UEFA_CONFERENCE_LEAGUE_9CF();
				teams_seeded* qualifiers = (teams_seeded*)uecl_data->special_teams_seedings;
				WORD insert_idx = uecl_data->special_nteams_seedings;
				qualifiers[insert_idx].club = club;
				qualifiers[insert_idx].f5 = 5;
				qualifiers[insert_idx].f6 = 0;
				uecl_data->special_nteams_seedings++;

				comp_stats* stage0_data = (comp_stats*)uecl_data->stages[0];
				teams_seeded* teams = (teams_seeded*)stage0_data->teams_list;
				insert_idx = 0;
				while (teams[insert_idx].club) insert_idx++;
				teams[insert_idx].club = club;
				teams[insert_idx].f5 = 2;
				teams[insert_idx].f6 = 0;

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uecl_data->competition_db), ChampionsPath, SecondQualifyingPhase, 0x1E);
				(*(int(__thiscall**)(BYTE*))(v3 + 0x5C))(uecl_bytes);
			}
			else club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage < 5) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, KnockoutPlayoff, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 5) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
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
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 6) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			UpdateCountryCoefficient(club, 3);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) uefa_champions_league_set_table_fate()
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
		call uefa_champions_league_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

char ucl_team_selection(BYTE* _this, BYTE* club_list, int club_count) {
	uefa_seedings* list = (uefa_seedings*)_this;
	// Last winner of Champions League
	cm3_club_comps* ucl = get_comp(UEFA_CHAMPIONS_LEAGUE_9CF());
	cm3_clubs* ucl_winner = get_last_comp_winner(ucl);
	ucl_winner->ClubEuroFlag = UEFA_CHAMPIONS_LEAGUE_9CF();
	ucl_winner->ClubEuroSeeding = 1;
	for (int i = 0; i < 55; i++) {
		uefa_seedings* u = &list[i];
		if (u->nation == ucl_winner->ClubNation) {
			u->num_teams_in_comps += 2;
			break;
		}
	}

	// Last winner of Europa League
	cm3_club_comps* uel = get_comp(UEFA_EUROPA_LEAGUE_9CF());
	cm3_clubs* uel_winner = get_last_comp_winner(uel);
	uel_winner->ClubEuroFlag = UEFA_CHAMPIONS_LEAGUE_9CF();
	uel_winner->ClubEuroSeeding = 1;
	for (int i = 0; i < 55; i++) {
		uefa_seedings* u = &list[i];
		if (u->nation == uel_winner->ClubNation) {
			u->num_teams_in_comps += 2;
			break;
		}
	}

	// Remaining teams
	// League, Playoff, 3QR, 2QR, 1QR
	BYTE quals_1[5] = { 4,0,0,0,0 }; // 1 to 4
	BYTE quals_2[5] = { 3,0,1,0,0 }; // 5
	BYTE quals_3[5] = { 2,0,1,0,0 }; // 6
	BYTE quals_4[5] = { 2,0,0,0,0 }; // 7
	BYTE quals_5[5] = { 1,0,1,0,0 }; // 8 to 11
	BYTE quals_6[5] = { 0,1,0,1,0 }; // 12 to 15
	BYTE quals_7[5] = { 0,0,0,1,0 }; // 16 to 25
	BYTE quals_8[5] = { 0,0,0,0,1 }; // 26 to 53
	BYTE quals_9[5] = { 0,0,0,0,0 }; // rest

	char i;
	WORD effective_count = 0;
	for (i = 0; i < 55; i++) {
		uefa_seedings* u = &list[i];
		cm3_nations* euro_country = get_country(u->id);
		if (euro_country->NationID == NATION_LIECHTENSTEIN_9CF()) continue;
		if (euro_country->NationID == NATION_RUSSIA_9CF()) continue;
		BYTE* quals;
		if (effective_count < 4) quals = quals_1;
		else if (effective_count < 5) quals = quals_2;
		else if (effective_count < 6) quals = quals_3;
		else if (effective_count < 7) quals = quals_4;
		else if (effective_count < 11) quals = quals_5;
		else if (effective_count < 15) quals = quals_6;
		else if (effective_count < 25) quals = quals_7;
		else if (effective_count < 53) quals = quals_8;
		else quals = quals_9;

		BYTE count = 0;
		BYTE curr_seeding = 0;
		for (int x = 0; x < 5; x++) {
			count += quals[x];
			curr_seeding = x + 1;
			if (quals[x] > 0) break;
		}

		BYTE j = 0;
		if (filesystem::exists("Data/euro.cfg") && *current_year == (WORD)START_YEAR) {
			ifstream in("Data/euro.cfg", ios_base::in);
			string name;
			char nation[LONG_TXT_LENGTH];
			int required = -1;
			while (std::getline(in, name))
			{
				if (name.size() == 0) {
					if (required == -1) continue;
					else break;
				}
				if (name[0] == '*') {
					strcpy_s(nation, name.substr(1).c_str());
					if (_strcmpi(nation, euro_country->NationName) == 0)
					{
						required = u->ucl_spots;
						//dprintf("[UCL] Getting clubs from euro.cfg: %s - max %d\n", nation, required);
					}
					else {
						required = -1;
					}
					continue;
				}
				if (_strcmpi(nation, euro_country->NationName) != 0) continue;
				if (j >= required) continue;
				cm3_clubs* euro_club = find_club(name.c_str());
				if (!euro_club || !euro_club->ClubNation || euro_club->ClubNation != euro_country) {
					//dprintf("Club %s not found, skipping\n", name.c_str());
				}
				else if (euro_club->ClubEuroFlag != -1) {
					//dprintf("Club %s is already in an European competition, skipping\n", (euro_club->ClubName));
				}
				else {
					//dprintf("Setting club %s to Champions League\n", (euro_club->ClubName));
					euro_club->ClubEuroFlag = UEFA_CHAMPIONS_LEAGUE_9CF();
					if (j >= count) {
						for (int x = curr_seeding; x < 5; x++) {
							count += quals[x];
							curr_seeding = x + 1;
							if (quals[x] > 0) break;
						}
						if (curr_seeding > 5) break;
					}
					euro_club->ClubEuroSeeding = curr_seeding == 5 ? 6 : effective_count >= 15 && curr_seeding == 4 ? 5 : curr_seeding;
					u->num_teams_in_comps += 2;
					j++;
				}
			}
		}

		//if (j < u->ucl_spots) dprintf("[UCL] Getting clubs from database - best\n");
		vector<cm3_clubs*> clubs;
		bool playable = euro_country->NationLeagueSelected;
		//dprintf("[UCL] Getting clubs from nation: %s\n", euro_country->NationName);
		//dprintf("[UCL] playable: %d\n", euro_country->NationLeagueSelected);
		if (playable) {
			// playable
			clubs = find_clubs_of_country_for_euro_playable(u->id);
			sort(clubs.begin(), clubs.end(), compareClubLastDivPos);
		}
		else {
			// not playable
			clubs = find_clubs_of_country_for_euro(u->id);
			sort(clubs.begin(), clubs.end(), compareClubRep);
		}
		size_t max_count = u->ucl_spots + 2 - j;
		if (max_count > clubs.size()) max_count = clubs.size();
		for (; j < u->ucl_spots; j++) {
			int idx = 0;
			if (!playable) idx = rand() % max_count;
			cm3_clubs* euro_club = clubs[idx];
			//dprintf("Setting club %s to Champions League, idx=%d\n", (euro_club->ClubName), j);
			euro_club->ClubEuroFlag = UEFA_CHAMPIONS_LEAGUE_9CF();
			if (j >= count) {
				for (int x = curr_seeding; x < 5; x++) {
					count += quals[x];
					curr_seeding = x + 1;
					if (quals[x] > 0) break;
				}
				if (curr_seeding > 5) break;
			}
			euro_club->ClubEuroSeeding = curr_seeding == 5 ? 6 : effective_count >= 15 && curr_seeding == 4 ? 5 : curr_seeding;
			u->num_teams_in_comps += 2;
			clubs.erase(clubs.begin() + idx);
			max_count--;
		}
		effective_count++;
	}
	return i;
}

void __declspec(naked) ucl_team_selection_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ucl_team_selection
		add esp, 0xc
		ret 8
	}
}

void uefa_set_team_counts(BYTE* _this) {
	uefa_seedings* list = (uefa_seedings*)_this;
	WORD effective_count = 0;
	for (char i = 0; i < 55; i++) {
		uefa_seedings* u = &list[i];

		if (u->nation->NationID == NATION_LIECHTENSTEIN_9CF())
		{
			u->ucl_spots = 0;
			u->uel_spots = 0;
			u->uecl_spots = 1;
			continue;
		}
		if (u->nation->NationID == NATION_RUSSIA_9CF())
		{
			u->ucl_spots = 0;
			u->uel_spots = 0;
			u->uecl_spots = 0;
			continue;
		}

		if (effective_count < 5) u->ucl_spots = 4;
		else if (effective_count < 6) u->ucl_spots = 3;
		else if (effective_count < 15) u->ucl_spots = 2;
		else if (effective_count < 53) u->ucl_spots = 1;
		else u->ucl_spots = 0;

		if (effective_count < 12) u->uel_spots = 2;
		else if (effective_count < 32) u->uel_spots = 1;
		else u->uel_spots = 0;

		if (effective_count < 12) u->uecl_spots = 1;
		else if (effective_count < 32) u->uecl_spots = 2;
		else if (effective_count < 47) u->uecl_spots = 3;
		else if (effective_count < 53) u->uecl_spots = 2;
		else u->uecl_spots = 0;

		effective_count++;
	}
}

void __declspec(naked) uefa_set_team_counts_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_set_team_counts
		add esp, 0x4
		ret
	}
}

int ucl_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1 || stage_id == 0)
	{
		WORD substage_id = sub_4B0870(*(WORD*)(round_data + 0x30));
		if (substage_id == FirstQualifyingPhase) {
			if (show_body_text) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
			if (fate != -1) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
			else {
				comp_data = get_comp(UEFA_CONFERENCE_LEAGUE_9CF());
				sub_66F4E0(0xDE1F64, (DWORD)&drop_down_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (substage_id == SecondQualifyingPhase) {
			if (show_body_text) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
			if (fate != -1) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
			else {
				comp_data = get_comp(UEFA_EUROPA_LEAGUE_9CF());
				sub_66F4E0(0xDE1F64, (DWORD)&drop_down_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (substage_id == ThirdQualifyingPhase) {
			if (show_body_text) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
			if (fate != -1) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
			else {
				comp_data = get_comp(UEFA_EUROPA_LEAGUE_9CF());
				if (stage_id == 0) {
					sub_66F4E0(0xDE1F64, (DWORD)&drop_down_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
						&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				}
				else {
					sub_66F4E0(0xDE1F64, (DWORD)&drop_down_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
						&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				}
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (substage_id == Playoff)
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
			else {
				comp_data = get_comp(UEFA_EUROPA_LEAGUE_9CF());
				sub_66F4E0(0xDE1F64, (DWORD)&drop_down_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
	}
	else if (stage_id < 5) {
		if (fate == Qualified1) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_r16_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_r16_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == TopPlayoff) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_knockout_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_knockout_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 5) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 6) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) ucl_stage_news_c()
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
		call ucl_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void setup_uefa_champions_league() {
	WriteVTablePtr(uefa_champions_league_vtable, VTableInitFree, (DWORD)&uefa_champions_league_free_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTablePostMatchUpdate, (DWORD)&ucl_money_after_match_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableEoSUpdate, (DWORD)&uefa_champions_league_update_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTablePlayoffQual, (DWORD)&uefa_champions_league_stages_create_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableSetChampion, (DWORD)&uefa_champions_league_set_champion_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableClubLandmarks, 0x48cab0); // review? -> 586fa0
	WriteVTablePtr(uefa_champions_league_vtable, VTableFixtures, (DWORD)&uefa_champions_league_fixture_caller);
	WriteVTablePtr(uefa_champions_league_vtable, VTableTableFates, (DWORD)&uefa_champions_league_set_table_fate);
	WriteVTablePtr(uefa_champions_league_vtable, VTableStageNews, (DWORD)&ucl_stage_news_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTable23, (DWORD)&ucl_register_squad_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableReputationSetup, (DWORD)&uefa_champions_league_reputation_setup_c);
	WriteVTablePtr(uefa_champions_league_vtable, VTableReputationCalc, (DWORD)&uefa_champions_league_reputation_calc_c);

	PatchFunction(0x904210, (DWORD)&ucl_team_selection_c);
	PatchFunction(0x903CC0, (DWORD)&uefa_set_team_counts_c);

	// weird hardcoded stuff with fixtures?
	WriteBytes(0x68a03f, 1, 0xeb);
}