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
// Credits to tafo for the initial research on how to have a realistic league phase
// https://julienguyon.github.io/UEFA-league-phase-draw/ => an algorithm tu perform the draw, haven't implemented it
DWORD* uefa_champions_league_vtable = (DWORD*)0x96A1D0;

void uefa_champions_league_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = uefa_champions_league_vtable;
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
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[3];
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

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

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

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

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
	else if (stage_idx == 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		*num_rounds = 15;
		*stage_name_id = LeagueStage;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 9), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 10), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 14), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 15), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 21), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 22), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 4), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 5), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 25), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 26), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 9), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 10), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 20), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 21), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 28), year, Wednesday, Evening);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 30), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 18), year, Wednesday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, KnockoutPlayoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 16, 8, 16, 0, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_ko_lose"));

		return (DWORD)pMem;
	}
	else if (stage_idx == 3) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

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
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 6, 6), year, Saturday, Evening, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("uefa_ucl_final_win"), prizeMoneyFile.GetInt("uefa_ucl_final_lose"));

		return (DWORD)pMem;
	}
	else if (stage_idx == -2 || stage_idx == -3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		*num_rounds = 8;
		*stage_name_id = LeagueStage;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx == -2)
		{
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 10), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 15), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 22), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 4), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 26), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 9), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 20), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 28), year, Wednesday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 9), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 14), year, Tuesday, Evening);
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
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
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
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

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
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

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
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
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
		for (int i = 24; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], i + 1);
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
	else if (stage == 1) {
		ret_current = current;
		if (min < 25) ret_min = 1;
		else ret_min = min;
		ret_max = max;
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 2) {
		if (current != 1) ret_current = 17;
		if (min != 1) ret_min = 17;
		if (max == 1) ret_max = 9;
		else ret_max = 17;
	}
	else if (stage == 3) {
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
	if (bl == 1) {
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
		BYTE* pMem = (BYTE*)cm0102_new(data->special_nteams_seedings * 4);
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
		BYTE* pMem = (BYTE*)cm0102_new(data->special_nteams_seedings * 4);
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
		BYTE* pMem = (BYTE*)cm0102_new(data->special_nteams_seedings * 4);
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
	data->num_stages = 4;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	sub_9035A0((BYTE*)*uefa_seeding_list, 0);
	uefa_champions_league_all_teams(_this);
	uefa_champions_league_champs_path_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
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

	char prom_rel[4] = { 8, 16, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, GamesWonTiebreaker };

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

	sort(clubs.begin(), clubs.end(), compareClubRep);

	WORD group_teams = 36;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures_1 = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, -2, &num_rounds, &stage_name_id, 0);
	BYTE* pFixtures_2 = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, -3, &num_rounds, &stage_name_id, 0);
	DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

	for (int j = 0; j < group_teams; j++) {
		cm3_clubs* club = clubs[j];
		*((DWORD*)(&pTeams[j])) = (DWORD)club;
		int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
		AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uefa_ucl_groups_qualify"));
		AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("uefa_ucl_groups_qualify"), 0, -1, LeagueStage, 0, -2);
		UpdateCountryCoefficient(club, 6);
	}

	WORD year = comp_data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, group_teams, pTeams, 0, (DWORD)(comp_data->competition_db), 0, num_rounds,
		3, 1, 8, &tiebreaks[0], &prom_rel[0], year, stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);

	*((DWORD*)(pStage + 0xA7)) = num_rounds;
	comp_stats* stage_data = (comp_stats*)pStage;
	char matchups[36][8] = {
		{17, -9, -19, 35, -11, 1, -32, 25},
		{30, -21, 2, -16, 26, -1, 13, -33},
		{-10, 31, -2, 12, -26, 21, -36, 3},
		{4, -14, 28, -35, 9, -23, 24, -3},
		{-4, 10, -22, 5, -30, 33, -13, 18},
		{15, -27, 32, -5, 20, -29, 6, -12},
		{-20, 7, -15, 23, -28, 16, -6, 29},
		{22, -7, 11, -25, 8, -31, 34, -18},
		{-34, 0, -17, 19, -8, 14, -24, 27},
		{2, -35, 20, -18, -4, 31, -22, 10},
		{11, -5, 26, -23, 0, -33, 30, -10},
		{-11, 35, -8, 25, -19, 12, -30, 5},
		{18, -28, 13, -3, 34, -12, 4, -21},
		{-24, 3, -13, 29, -34, 19, -2, 14},
		{32, -25, 6, -29, 15, -9, 22, -14},
		{-6, 16, -32, 1, -15, 23, -26, 33},
		{28, -16, 8, -31, 24, -7, 17, -27},
		{-1, 21, -20, 9, -36, 27, -17, 7},
		{-13, 19, 0, -28, 11, -27, 32, -5},
		{6, -19, 17, -9, 30, -14, 20, -35},
		{-32, 1, -10, 21, -6, 29, -20, 12},
		{34, -18, 4, -21, 22, -3, 9, -29},
		{-8, 33, -36, 10, -22, 3, -15, 23},
		{13, -31, 24, -7, 28, -16, 8, -23},
		{-30, 14, -24, 7, -17, 25, -4, 35},
		{26, -33, 27, -12, 2, -25, 15, -1},
		{-26, 5, -11, 31, -2, 18, -34, 16},
		{-36, 12, -26, 18, 6, -18, 28, -9},
		{-17, 29, -4, 14, -24, 5, -28, 21},
		{24, -29, 30, -14, 4, -21, 11, -7},
		{-2, 23, -30, 16, -20, 7, -11, 31},
		{20, -3, 15, -27, 32, -10, 0, -31},
		{-15, 25, -6, 33, -32, 10, -19, 1},
		{8, -23, 34, -33, 13, -5, 26, -16},
		{-22, 9, -34, 3, -13, 35, -8, 19},
		{27, -12, 22, -1, 17, -35, 2, -25},
	};

	map<cm3_nations*, int> pot_nations;
	for (size_t t = 0; t < group_teams; t++) {
		cm3_clubs* club = clubs[t];
		if (pot_nations.find(club->ClubNation) == pot_nations.end()) {
			pot_nations[club->ClubNation] = 1;
		}
		else {
			pot_nations[club->ClubNation] = pot_nations[club->ClubNation] + 1;
		}
	}

	int n_tries = 0;
	for (BYTE t = 0; t < group_teams; t++) {
		cm3_clubs* club = clubs[t];
		map<cm3_nations*, int> counts;
		for (BYTE m = 0; m < num_rounds; m++) {
			char idx = matchups[t][m];
			if (idx < 0) idx = abs(idx) - 1;
			cm3_clubs* opp = clubs[idx];
			bool multiple = false;
			if (n_tries > 511)
			{
				//if (n_tries == 512 && m == 0) dprintf("[UCL] Tried to make draw without teams from the same country facing each other, but failed.\n");
				multiple = pot_nations[club->ClubNation] > 3;
			}
			if (n_tries > 1023)
			{
				//if (n_tries == 1024 && m == 0) dprintf("[UCL] Tried to make draw without teams from the same country facing each other, but failed.\n");
				multiple = pot_nations[club->ClubNation] > 2;
			}

			if (!multiple)
			{
				if (opp->ClubNation == club->ClubNation) {
					shuffle(clubs.begin(), clubs.begin() + 9, rng);
					if (idx > 8) shuffle(clubs.begin() + 9, clubs.begin() + 18, rng);
					if (idx > 17) shuffle(clubs.begin() + 18, clubs.begin() + 27, rng);
					if (idx > 26) shuffle(clubs.begin() + 27, clubs.end(), rng);
					t = -1;
					n_tries++;
					break;
				}
			}
			if (counts.find(opp->ClubNation) != counts.end()) {
				int count = counts[opp->ClubNation];
				if (count > 1 + multiple || (opp->ClubNation == club->ClubNation && count == 1)) {
					shuffle(clubs.begin(), clubs.begin() + 9, rng);
					if (idx > 8) shuffle(clubs.begin() + 9, clubs.begin() + 18, rng);
					if (idx > 17) shuffle(clubs.begin() + 18, clubs.begin() + 27, rng);
					if (idx > 26) shuffle(clubs.begin() + 27, clubs.end(), rng);
					t = -1;
					n_tries++;
					break;
				}
				else counts[opp->ClubNation] = count + 1;
			}
			else counts[opp->ClubNation] = 1;
		}
	}

	for (BYTE m = 0; m < num_rounds; m++) {
		BYTE* pFixtures = pFixtures_1;
		BYTE* ptr_last = (BYTE*)(pFixtures + fixture_dates_sz * 7);
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
		match->f56_0xab = stage_data->f171;
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
			if (t % 2 == 1) pFixtures = pFixtures_2;
			else pFixtures = pFixtures_1;
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

	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	sub_684230(pStage);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures_1);
	sub_9452CA_free(pFixtures_2);
	comp_data->current_stage = stage_num;
}

void uefa_champions_league_playoff_stage_setup(BYTE* _this) {
	char stage_num = 2;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	vector<cm3_clubs*> clubs;

	comp_stats* curr_stage = (comp_stats*)(comp_data->stages[1]);
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);

	for (WORD i = 0; i < curr_stage->n_teams; i++) {
		if (table_teams[i].league_fate == TopPlayoff) {
			cm3_clubs* club = table_teams[i].club;
			clubs.push_back(club);
			UpdateCountryCoefficient(club, (char)(0.5 * (24 - i + 1)));
		}
	}
	shuffle(clubs.begin(), clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.end(), rng);
	for (int i = 0; i < 8; i++)
	{
		*((DWORD*)(&pTeams[i * 2])) = (DWORD)clubs[i];
		*((DWORD*)(&pTeams[i * 2 + 1])) = (DWORD)clubs[i + 8];
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
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void uefa_champions_league_final_stage_setup(BYTE* _this) {
	char stage_num = 3;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	vector<cm3_clubs*> clubs;

	comp_stats* curr_stage = (comp_stats*)(comp_data->stages[1]);
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);

	for (WORD i = 0; i < curr_stage->n_teams; i++) {
		if (table_teams[i].league_fate == Qualified1) {
			cm3_clubs* club = table_teams[i].club;
			clubs.push_back(club);
			UpdateCountryCoefficient(club, (char)(0.5 * (24 - i + 1)));
		}
	}
	shuffle(clubs.begin(), clubs.end(), rng);
	for (int i = 0; i < 8; i++)
		*((DWORD*)(&pTeams[i * 2 + 1])) = (DWORD)clubs[i];

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
	comp_stats* stage2_data = (comp_stats*)comp_data->stages[2];
	for (WORD j = 0; j < stage2_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)stage2_data->teams_list)[j];
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
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
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
		else if (current == 2) {
			uefa_champions_league_playoff_stage_setup(_this);
		}
		else if (current == 3) {
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueStage, 0x1E);
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
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uel_data->competition_db), None, LeagueStage, 0x1E);
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

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uel_data->competition_db), None, LeagueStage, 0x1E);
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
	else if (stage == 1) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, KnockoutPlayoff, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueStage, 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 2) {
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
	else if (stage == 3) {
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
			cm3_nations* nation_ptr;
			int required = -1;
			while (std::getline(in, name))
			{
				if (name.size() == 0) {
					if (required == -1) continue;
					else break;
				}
				if (name[0] == '*') {
					strcpy_s(nation, name.substr(1).c_str());
					nation_ptr = find_country(nation);
					if (euro_country == nation_ptr)
					{
						required = u->ucl_spots;
						//dprintf("[UCL] Getting clubs from euro.cfg: %s - max %d\n", nation, required);
					}
					else {
						required = -1;
					}
					continue;
				}
				if (euro_country != nation_ptr) continue;
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
					sub_66F4E0(0xDE1F64, (DWORD)&drop_down_lge_stage_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
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
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_lge_stage_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				comp_data = get_comp(UEFA_EUROPA_LEAGUE_9CF());
				sub_66F4E0(0xDE1F64, (DWORD)&drop_down_lge_stage_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
	}
	else if (stage_id == 1) {
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
	else if (stage_id == 2) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 3) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

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
}