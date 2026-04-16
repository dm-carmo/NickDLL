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

DWORD* uefa_europa_league_vtable = (DWORD*)0x970790;

void uefa_europa_league_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = uefa_europa_league_vtable;
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

void uefa_europa_league_free(BYTE* _this, BYTE a2) {
	uefa_europa_league_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) uefa_europa_league_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call uefa_europa_league_free
		add esp, 0x8
		ret 4
	}
}

int uefa_europa_league_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[6];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) uefa_europa_league_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_europa_league_set_champion
		add esp, 0x4
		ret 0
	}
}

DWORD uefa_europa_league_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = MainPath;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 10), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstQualifyingPhase, 4, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 12, 6, 12, 0, 0, 2, 7, 0, 0, 151489);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 24), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondQualifyingPhase, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 18, 9, 12, 12, 0, 2, 7, 0, 0, 151489);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 21), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 7), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdQualifyingPhase, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 14, 7, 5, 24, 0, 2, 7, 0, 0, 151489);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 21), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 4, FixedTeamOrderInCup3 + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 24, 12, 17, 29, 0, 2, 7, 0, 0, 151489);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = ChampionsPath;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 21), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 7), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdQualifyingPhase, 4, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 12, 6, 12, 0, 0, 2, 7, 0, 0, 151489);

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
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 18), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 25), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 2), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 23), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 6), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 27), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 11), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 22), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 29), year, Thursday, Evening);

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
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 19), year, Thursday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, KnockoutPlayoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 16, 8, 16, 0, 0, 2, 7, 259695);

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
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 12), year, Thursday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 16, 8, 16, 0, 0, 2, 7, 1514888);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 19), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 9), year, Thursday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 8, 4, 0, 0, 0, 2, 7, 2164125);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 17), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 30), year, Thursday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 4, 2, 0, 0, 0, 2, 7, 3635730);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 8), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 20), year, Wednesday, Evening, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, 11253450, 6059550);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) uefa_europa_league_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uefa_europa_league_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void uefa_europa_league_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 76;
	data->special_nteams_seedings = 45;
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
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == UEFA_EUROPA_LEAGUE_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			if (seed == 1 && teams_r1 < 13) {
				teams[teams_r1].club = club;
				teams[teams_r1].f5 = 7;
				teams[teams_r1].f6 = 0;
				teams_r1++;
			}
			else if (seed == 2 && teams_r2 < 5) {
				teams[teams_r2 + 13].club = club;
				teams[teams_r2 + 13].f5 = 8;
				teams[teams_r2 + 13].f6 = 0;
				teams_r2++;
			}
			else if (seed == 3 && teams_r3 < 3) {
				teams[teams_r3 + 18].club = club;
				teams[teams_r3 + 18].f5 = 6;
				teams[teams_r3 + 18].f6 = 0;
				teams_r3++;
			}
			else if (seed == 4 && teams_r4 < 12) {
				teams[teams_r4 + 21].club = club;
				teams[teams_r4 + 21].f5 = 13;
				teams[teams_r4 + 21].f6 = 0;
				teams_r4++;
			}
			else if (seed == 5 && teams_r5 < 12) {
				teams[teams_r5 + 33].club = club;
				teams[teams_r5 + 33].f5 = 0;
				teams[teams_r5 + 33].f6 = 0;
				teams_r5++;
			}
		}
	}
}

void uefa_europa_league_main_path_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 46;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	// fill in teams with 0 to avoid odd crashes
	for (DWORD i = 0; i < total_teams; i++)
	{
		teams[i].club = 0;
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	WORD count = 0;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 0) {
			teams[count].club = qualifiers[i].club;
			teams[count].f5 = 0;
			teams[count].f6 = 0;
			count++;
		}
	}
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 13) {
			teams[count].club = qualifiers[i].club;
			teams[count].f5 = 1;
			teams[count].f6 = 0;
			count++;
		}
	}
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 6) {
			teams[count].club = qualifiers[i].club;
			teams[count].f5 = 2;
			teams[count].f6 = 0;
			count++;
		}
	}
	count += 2;
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 8) {
			teams[count].club = qualifiers[i].club;
			teams[count].f5 = 3;
			teams[count].f6 = 0;
			count++;
		}
	}
	count += 6;
}

void uefa_europa_league_champions_path_setup(BYTE* _this) {
	char stage_num = 0;

	comp_stats* data = (comp_stats*)_this;
	BYTE playoff_teams = 12;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	// teams are added somewhere else, fill in teams with 0 to avoid odd crashes
	for (int i = 0; i < playoff_teams; i++) *((DWORD*)(&pTeams[i])) = 0;

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

void uefa_europa_league_reputation_setup(BYTE* _this) {
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
		for (int i = 36; i < 48; i++) {
			if (i >= comp_data->special_nteams_seedings) return;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 37);
		}
		for (int i = 48; i < 61; i++) {
			if (i >= comp_data->special_nteams_seedings) return;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 49);
		}
		for (int i = 61; i < 70; i++) {
			if (i >= comp_data->special_nteams_seedings) return;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 62);
		}
		for (int i = 70; i < 76; i++) {
			if (i >= comp_data->special_nteams_seedings) return;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 71);
		}
	}
}

void __declspec(naked) uefa_europa_league_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_europa_league_reputation_setup
		add esp, 0x4
		ret
	}
}

map<char, char> uel_main_mappings = {
	{1,33},
	{13,37},
	{25,49},
	{32,62},
	{41,71},
};
map<char, char> uel_cham_mappings = {
	{1,37},
	{7,49},
};

void uefa_europa_league_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = uel_main_mappings[current];
		if (ret_min != 1) ret_min = uel_main_mappings[min];
		ret_max = uel_main_mappings[max];
	}
	else if (stage == 0) {
		ret_current = uel_cham_mappings[current];
		if (ret_min != 1) ret_min = uel_cham_mappings[min];
		ret_max = uel_cham_mappings[max];
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

void __declspec(naked) uefa_europa_league_reputation_calc_c()
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
		call uefa_europa_league_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

// prize money for group stage win/draw and coefficient updates
int uel_money_after_match(BYTE* _this, BYTE* a2, int a3) {
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
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club1->ClubNation), draw_coef);
		cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club2->ClubNation), draw_coef);
	}
	else if (al > cl) {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club_check->ClubNation), win_coef);
	}
	else {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club_check->ClubNation), win_coef);
	}
	// group stage indexes
	if (bl > 0 && bl < 5) {
		if (club_check) {
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club_check);
			AddToClubIncome((BYTE*)ret, 389543);
			AddMoneyFromComp(_this, (BYTE*)club_check, 389543, 0, -1, 0, a2, -2);
		}
		else {
			cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club1);
			AddToClubIncome((BYTE*)ret, 129848);
			cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
			ret = sub_5A0590(ae2a38_ptr, (BYTE*)club2);
			AddToClubIncome((BYTE*)ret, 129848);
			AddMoneyFromComp(_this, (BYTE*)club1, 129848, 0, -1, 0, a2, -2);
			AddMoneyFromComp(_this, (BYTE*)club2, 129848, 0, -1, 0, a2, -2);
		}
	}
	return sub_51A150(_this, a2, a3);
}

void __declspec(naked) uel_money_after_match_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uel_money_after_match
		add esp, 0xc
		ret 8
	}
}

// Get teams to send squad registration news
int uel_register_squad(BYTE* _this, DWORD* a2, char a3) {
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

void __declspec(naked) uel_register_squad_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uel_register_squad
		add esp, 0xc
		ret 8
	}
}

char uefa_europa_league_update(BYTE* _this) {
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
	uefa_europa_league_all_teams(_this);
	uefa_europa_league_main_path_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	uefa_europa_league_champions_path_setup(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) uefa_europa_league_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_europa_league_update
		add esp, 0x4
		ret
	}
}

void uefa_europa_league_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = uefa_europa_league_vtable;
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesEurope;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_ORANGE_2_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_BLACK_9CF());
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 7;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	sub_9035A0((BYTE*)*uefa_seeding_list, 0);
	uefa_europa_league_all_teams(_this);
	uefa_europa_league_main_path_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	uefa_europa_league_champions_path_setup(_this);
	uefa_europa_league_reputation_setup(_this);
}

void uefa_europa_league_group_stage_setup(BYTE* _this) {
	char stage_num = 1;
	DWORD v1 = *(DWORD*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 4, 0, 0 };
	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, GamesWonTiebreaker };
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;

	comp_stats* ucl_data = (comp_stats*)get_loaded_league(UEFA_CHAMPIONS_LEAGUE_9CF());
	comp_stats* stage0_data = (comp_stats*)ucl_data->stages[0];
	for (WORD j = 0; j < stage0_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)stage0_data->teams_list)[j];
		if (t.f6 == 2) {
			WORD insert_idx = comp_data->special_nteams_seedings;
			teams[insert_idx].club = t.club;
			teams[insert_idx].f5 = 5;
			teams[insert_idx].f6 = 0;
			comp_data->special_nteams_seedings++;
		}
	}
	for (WORD j = 0; j < ucl_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)ucl_data->teams_list)[j];
		if (t.f6 == 2) {
			WORD insert_idx = comp_data->special_nteams_seedings;
			teams[insert_idx].club = t.club;
			teams[insert_idx].f5 = 5;
			teams[insert_idx].f6 = 0;
			comp_data->special_nteams_seedings++;
		}
	}

	vector<cm3_clubs*> clubs;
	for (DWORD i = 0; i < comp_data->special_nteams_seedings; i++) {
		if (teams[i].club->ClubEuroFlag == comp_data->competition_db->ClubCompID)
			clubs.push_back(teams[i].club);
	}
	if (clubs.size() != 36)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(comp_data->competition_db->ClubCompName, msg.c_str(), true);
	}

	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

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
			AddToClubIncome((BYTE*)ret, 3730952);
			AddMoneyFromComp(_this, (BYTE*)club, 3730952, 0, -1, GroupStage, 0, -2);
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

void uefa_europa_league_playoff_stage_setup(BYTE* _this) {
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
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(table_teams[2].club->ClubNation), 8);
		*((DWORD*)(&pTeams[idx2 * 4 + 1])) = (DWORD)table_teams[5].club;
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(table_teams[5].club->ClubNation), 2);
		*((DWORD*)(&pTeams[idx2 * 4 + 2])) = (DWORD)table_teams[4].club;
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(table_teams[4].club->ClubNation), 4);
		*((DWORD*)(&pTeams[idx1 * 4 + 3])) = (DWORD)table_teams[3].club;
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(table_teams[3].club->ClubNation), 6);
	}

	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	for (int i = 0; i < 16; i++)
	{
		cm3_clubs* club = (cm3_clubs*)*((DWORD*)(&pTeams[i]));
		if (club)
		{
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, 259695);
			AddMoneyFromComp(_this, (BYTE*)club, 259695, 0, -1, KnockoutPlayoff, 0, -2);
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

void uefa_europa_league_final_stage_setup(BYTE* _this) {
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
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(table_teams[0].club->ClubNation), 12);
		*((DWORD*)(&pTeams[idx1 * 2 + 4 + 1])) = (DWORD)table_teams[1].club;
		sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(table_teams[1].club->ClubNation), 10);
	}

	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	for (int i = 0; i < 16; i++)
	{
		cm3_clubs* club = (cm3_clubs*)*((DWORD*)(&pTeams[i]));
		if (club)
		{
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, 519390);
			AddMoneyFromComp(_this, (BYTE*)club, 519390, 0, -1, RoundOf16, 0, -2);
			sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club->ClubNation), 2);
		}
	}

	char playoff_idx = 0;
	comp_stats* stage5_data = (comp_stats*)comp_data->stages[5];
	for (WORD j = 0; j < stage5_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)stage5_data->teams_list)[j];
		if (t.f6 == 1) {
			*((DWORD*)(&pTeams[playoff_idx])) = (DWORD)t.club;
			sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(t.club->ClubNation), 2);
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

void uefa_europa_league_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 1) {
			uefa_europa_league_group_stage_setup(_this);
		}
		else if (current == 5) {
			uefa_europa_league_playoff_stage_setup(_this);
		}
		else if (current == 6) {
			uefa_europa_league_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) uefa_europa_league_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uefa_europa_league_stages_create
		add esp, 0x4
		ret
	}
}

int uefa_europa_league_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* uecl_bytes = get_loaded_league(UEFA_CONFERENCE_LEAGUE_9CF());
	comp_stats* uecl_data = (comp_stats*)uecl_bytes;
	DWORD v3 = *(DWORD*)uecl_bytes;
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
			WORD round_idx = *(WORD*)(rounds + playoff_dates_sz * current_round + 9);
			// First Qualifying Round + Second Qualifying Round + Third Qualifying Round (league only) to Conference League qualifiers
			if (stage == -1 && (round_idx < 3)) {
				club->ClubEuroFlag = UEFA_CONFERENCE_LEAGUE_9CF();
				teams_seeded* qualifiers = (teams_seeded*)uecl_data->special_teams_seedings;
				WORD insert_idx = uecl_data->special_nteams_seedings;
				qualifiers[insert_idx].club = club;
				qualifiers[insert_idx].f5 = 4;
				qualifiers[insert_idx].f6 = 0;
				uecl_data->special_nteams_seedings++;

				teams_seeded* teams = (teams_seeded*)uecl_data->teams_list;
				insert_idx = 0;
				while (teams[insert_idx].club) insert_idx++;
				teams[insert_idx].club = club;
				teams[insert_idx].f5 = 2;
				teams[insert_idx].f6 = 0;

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uecl_data->competition_db), ChampionsPath,
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0x1E);
				(*(int(__thiscall**)(BYTE*))(v3 + 0x5C))(uecl_bytes);
			}
			// Playoff to Conference League groups (handled in Conference League)
			else if (stage == -1 && round_idx == 3) {
				club->ClubEuroFlag = UEFA_CONFERENCE_LEAGUE_9CF();
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uecl_data->competition_db), None, GroupStage, 0x1E);
			}
			else club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 0) {
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
		WORD insert_idx = 0;
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), MainPath, Playoff, 0x1E);
			while (teams[insert_idx].club) insert_idx++;
			teams[insert_idx].club = club;
			teams[insert_idx].f5 = 2;
			teams[insert_idx].f6 = 0;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			WORD round_idx = *(WORD*)(rounds + playoff_dates_sz * current_round + 9);
			// Third Qualifying Round (champions only) to Conference League qualifiers
			if (round_idx == 0 && stage == 0) {
				club->ClubEuroFlag = UEFA_CONFERENCE_LEAGUE_9CF();
				teams_seeded* qualifiers = (teams_seeded*)uecl_data->special_teams_seedings;
				WORD insert_idx = uecl_data->special_nteams_seedings;
				qualifiers[insert_idx].club = club;
				qualifiers[insert_idx].f5 = 4;
				qualifiers[insert_idx].f6 = 0;
				uecl_data->special_nteams_seedings++;

				comp_stats* stage0_data = (comp_stats*)uecl_data->stages[0];
				teams_seeded* teams = (teams_seeded*)stage0_data->teams_list;
				insert_idx = 0;
				while (teams[insert_idx].club) insert_idx++;
				teams[insert_idx].club = club;
				teams[insert_idx].f5 = 2;
				teams[insert_idx].f6 = 0;

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(uecl_data->competition_db), ChampionsPath, Playoff, 0x1E);
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
			sub_9058B0((BYTE*)*uefa_seeding_list, (BYTE*)(club->ClubNation), 2);
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

void __declspec(naked) uefa_europa_league_set_table_fate()
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
		call uefa_europa_league_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

char uel_team_selection(BYTE* _this, BYTE* club_list, int club_count) {
	uefa_seedings* list = (uefa_seedings*)_this;
	bool extra_team = false;
	// Last winner of Conference League
	cm3_club_comps* uecl = get_comp(UEFA_CONFERENCE_LEAGUE_9CF());
	cm3_clubs* uecl_winner = get_last_comp_winner(uecl);
	if (uecl_winner->ClubEuroFlag != -1) extra_team = true;
	else {
		uecl_winner->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
		uecl_winner->ClubEuroSeeding = 1;
		for (int i = 0; i < 55; i++) {
			uefa_seedings* u = &list[i];
			if (u->nation == uecl_winner->ClubNation) {
				u->num_teams_in_comps += 2;
				break;
			}
		}
	}

	// Remaining teams
	// League, Playoff, 3QR, 2QR, 1QR
	BYTE quals_1[5] = { 2,0,0,0,0 }; // 1 to 5
	BYTE quals_x[5] = { 2,0,0,1,0 }; // special case
	BYTE quals_2[5] = { 1,0,0,1,0 }; // 6 to 7
	BYTE quals_3[5] = { 0,1,0,1,0 }; // 8 to 12
	BYTE quals_4[5] = { 0,0,1,0,0 }; // 13 to 15
	BYTE quals_5[5] = { 0,0,0,1,0 }; // 16 to 20
	BYTE quals_6[5] = { 0,0,0,0,1 }; // 21 to 32
	BYTE quals_7[5] = { 0,0,0,0,0 }; // rest
	char i;
	WORD effective_count = 0;
	for (i = 0; i < 55; i++) {
		uefa_seedings* u = &list[i];
		cm3_nations* euro_country = get_country(u->id);
		if (euro_country->NationID == NATION_LIECHTENSTEIN_9CF()) continue;
		if (euro_country->NationID == NATION_RUSSIA_9CF()) continue;

		BYTE* quals;
		if (effective_count < 5) quals = quals_1;
		else if (effective_count < 7) quals = quals_2;
		else if (effective_count < 12) quals = quals_3;
		else if (effective_count < 15) quals = quals_4;
		else if (effective_count < 20) quals = quals_5;
		else if (effective_count < 32) quals = quals_6;
		else quals = quals_7;

		if (extra_team && effective_count == 5)
		{
			quals = quals_x;
			u->uel_spots++;
		}

		BYTE count = 0;
		BYTE curr_seeding = 0;
		for (int x = 0; x < 5; x++) {
			count += quals[x];
			curr_seeding = x + 1;
			if (quals[x] > 0) break;
		}

		BYTE j = 0;
		if (filesystem::exists("Data/euro.cfg") && *current_year == (WORD)2025) {
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
						required = u->uel_spots;
						//dprintf("[UEL] Getting clubs from euro.cfg: %s - max %d\n", nation, required);
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
					//dprintf("Setting club %s to Europa League\n", (euro_club->ClubName));
					euro_club->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
					if (j >= count) {
						for (int x = curr_seeding; x < 5; x++) {
							count += quals[x];
							curr_seeding = x + 1;
							if (quals[x] > 0) break;
						}
						if (curr_seeding > 5) break;
					}
					euro_club->ClubEuroSeeding = curr_seeding;
					u->num_teams_in_comps += 2;
					j++;
				}
			}
		}
		else
		{
			// Get cup winners if country is playable, only from second season onwards
			if (effective_count < 32 && euro_country->NationLeagueSelected) {
				DWORD max_playables = pnd_count;
				for (DWORD i = 0; i < max_playables; i++) {
					playable_nation_data playable = pnd_list[i];
					if (playable.nation == euro_country && playable.main_cup) {
						cm3_clubs* cup_winner = get_last_comp_winner(playable.main_cup);
						if (cup_winner && cup_winner->ClubNation == euro_country && cup_winner->ClubEuroFlag == -1) {
							cup_winner->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
							if (j >= count) {
								for (int x = curr_seeding; x < 5; x++) {
									count += quals[x];
									curr_seeding = x + 1;
									if (quals[x] > 0) break;
								}
								if (curr_seeding > 5) break;
							}
							cup_winner->ClubEuroSeeding = curr_seeding;
							u->num_teams_in_comps += 2;
							j++;
						}
						else if(configFile.GetBool("cupRunnerUpsInUEFA", false)) {
							cm3_clubs* cup_loser = get_last_comp_runner_up(playable.main_cup);
							if (cup_loser && cup_loser->ClubNation == euro_country && cup_loser->ClubEuroFlag == -1) {
								cup_loser->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
								if (j >= count) {
									for (int x = curr_seeding; x < 5; x++) {
										count += quals[x];
										curr_seeding = x + 1;
										if (quals[x] > 0) break;
									}
									if (curr_seeding > 5) break;
								}
								cup_loser->ClubEuroSeeding = curr_seeding;
								u->num_teams_in_comps += 2;
								j++;
							}
						}
					}
				}
			}
		}

		//if (j < u->uel_spots) dprintf("[UEL] Getting clubs from database - best\n");
		vector<cm3_clubs*> clubs;
		bool playable = euro_country->NationLeagueSelected;
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
		size_t max_count = u->uel_spots + 2 - j;
		if (max_count > clubs.size()) max_count = clubs.size();
		for (; j < u->uel_spots; j++) {
			int idx = 0;
			if (!playable) idx = rand() % max_count;
			cm3_clubs* euro_club = clubs[idx];
			//dprintf("Setting club %s to Europa League\n", (euro_club->ClubName));
			euro_club->ClubEuroFlag = UEFA_EUROPA_LEAGUE_9CF();
			if (j >= count) {
				for (int x = curr_seeding; x < 5; x++) {
					count += quals[x];
					curr_seeding = x + 1;
					if (quals[x] > 0) break;
				}
				if (curr_seeding > 5) break;
			}
			euro_club->ClubEuroSeeding = curr_seeding;
			u->num_teams_in_comps += 2;
			clubs.erase(clubs.begin() + idx);
			max_count--;
		}
		effective_count++;
	}
	return i;
}

void __declspec(naked) uel_team_selection_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uel_team_selection
		add esp, 0xc
		ret 8
	}
}

static void(__thiscall* sub_48CAB0)(BYTE* _this, char* a1, int a2, __int16 a3, __int16 a4, char a5, int a6) =
(void(__thiscall*)(BYTE * _this, char* a1, int a2, __int16 a3, __int16 a4, char a5, int a6))(0x48CAB0);
void uel_48CAB0(BYTE* _this, char* a1, int a2, __int16 a3, __int16 a4, char a5, int a6) {
	// Shows the right text in club's Competitions history if they win in the Champions Third Qualifying Round then lose in the Playoff
	if (a3 == ChampionsPath && a4 == ThirdQualifyingPhase && a5 == 1)
		sub_48CAB0(_this, a1, a2, MainPath, Playoff, 2, a6);
	else sub_48CAB0(_this, a1, a2, a3, a4, a5, a6);
}

void __declspec(naked) uel_48CAB0_c()
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
		call uel_48CAB0
		add esp, 0x1c
		ret 0x18
	}
}

int uel_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1)
	{
		WORD substage_id = sub_4B0870(*(WORD*)(round_data + 0x30));
		if (substage_id == FirstQualifyingPhase || substage_id == SecondQualifyingPhase || substage_id == ThirdQualifyingPhase) {
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
				comp_data = get_comp(UEFA_CONFERENCE_LEAGUE_9CF());
				sub_66F4E0(0xDE1F64, (DWORD)&drop_down_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
	}
	else if (stage_id == 0)
	{
		WORD substage_id = sub_4B0870(*(WORD*)(round_data + 0x30));
		if (substage_id == ThirdQualifyingPhase) {
			if (show_body_text) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
			if (fate == 1) {
				sub_66F4E0(0xDE1F64, (DWORD)&uel_playoff_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
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

void __declspec(naked) uel_stage_news_c()
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
		call uel_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void setup_uefa_europa_league() {
	WriteVTablePtr(uefa_europa_league_vtable, VTableInitFree, (DWORD)&uefa_europa_league_free_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTablePostMatchUpdate, (DWORD)&uel_money_after_match_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTableEoSUpdate, (DWORD)&uefa_europa_league_update_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(uefa_europa_league_vtable, VTable10, 0x48CEA0);
	WriteVTablePtr(uefa_europa_league_vtable, VTablePlayoffQual, (DWORD)&uefa_europa_league_stages_create_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTableSetChampion, (DWORD)&uefa_europa_league_set_champion_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTableClubLandmarks, (DWORD)&uel_48CAB0_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(uefa_europa_league_vtable, VTableFixtures, (DWORD)&uefa_europa_league_fixture_caller);
	WriteVTablePtr(uefa_europa_league_vtable, VTableTableFates, (DWORD)&uefa_europa_league_set_table_fate);
	WriteVTablePtr(uefa_europa_league_vtable, VTableStageNews, (DWORD)&uel_stage_news_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTable23, (DWORD)&uel_register_squad_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTableReputationSetup, (DWORD)&uefa_europa_league_reputation_setup_c);
	WriteVTablePtr(uefa_europa_league_vtable, VTableReputationCalc, (DWORD)&uefa_europa_league_reputation_calc_c);

	PatchFunction(0x904580, (DWORD)&uel_team_selection_c);
}