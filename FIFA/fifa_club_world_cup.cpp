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

vtable* fifa_club_world_cup_vtable = new vtable((BYTE*)0x968BF4, 0xB4);

void fifa_club_world_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(fifa_club_world_cup_vtable->vtable_ptr);
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

void fifa_club_world_cup_free(BYTE* _this, BYTE a2) {
	fifa_club_world_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) fifa_club_world_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_club_world_cup_free
		add esp, 0x8
		ret 4
	}
}

int fifa_club_world_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[7];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) fifa_club_world_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_club_world_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

void fifa_club_world_cup_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 8;
	comp_data->comp_type = CLUB_INTERNATIONAL;
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

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 3, January, comp_data->year, -1);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) fifa_club_world_cup_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_club_world_cup_subs
		add esp, 0x4
		ret
	}
}

// prize money for group stage win/draw
int cwc_money_after_match(BYTE* _this, BYTE* a2, int a3) {
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
	if (bl < 7) {
		if (club_check) {
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club_check);
			AddToClubIncome((BYTE*)ret, 1485442);
			AddMoneyFromComp(_this, (BYTE*)club_check, 1485442, 0, -1, 0, a2, -2);
		}
		else {
			cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club1);
			AddToClubIncome((BYTE*)ret, 742721);
			cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
			ret = sub_5A0590(ae2a38_ptr, (BYTE*)club2);
			AddToClubIncome((BYTE*)ret, 742721);
			AddMoneyFromComp(_this, (BYTE*)club1, 742721, 0, -1, 0, a2, -2);
			AddMoneyFromComp(_this, (BYTE*)club2, 742721, 0, -1, 0, a2, -2);
		}
	}
	return sub_685D30(_this, a2, a3);
}

void __declspec(naked) cwc_money_after_match_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call cwc_money_after_match
		add esp, 0xc
		ret 8
	}
}

DWORD fifa_club_world_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 7) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx < 1) {
			AddFixture(pMem, fixture_id, Date(year, 6, 15), year, Sunday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Sunday, Morning, LargestStadium2);
			AddFixtureTV(pMem, fixture_id, 1, 1, Sunday, Evening, LargestStadium1);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 19), year, Thursday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Thursday, Morning, LargestStadium2);
			AddFixtureTV(pMem, fixture_id, 1, 1, Thursday, Evening, LargestStadium1);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 23), year, Monday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Monday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, fixture_id, 1, 1, Monday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, fixture_id++, 2);
		}
		else if (stage_idx < 3) {
			AddFixture(pMem, fixture_id, Date(year, 6, 16), year, Monday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Monday, Morning, LargestStadium4);
			AddFixtureTV(pMem, fixture_id, 1, 1, Monday, Evening, LargestStadium3);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 20), year, Friday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Friday, Morning, LargestStadium4);
			AddFixtureTV(pMem, fixture_id, 1, 1, Friday, Evening, LargestStadium3);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 24), year, Tuesday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Tuesday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, fixture_id, 1, 1, Tuesday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, fixture_id++, 2);
		}
		else if (stage_idx < 5) {
			AddFixture(pMem, fixture_id, Date(year, 6, 17), year, Tuesday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Tuesday, Morning, LargestStadium6);
			AddFixtureTV(pMem, fixture_id, 1, 1, Tuesday, Evening, LargestStadium5);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 21), year, Saturday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Saturday, Morning, LargestStadium6);
			AddFixtureTV(pMem, fixture_id, 1, 1, Saturday, Evening, LargestStadium5);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 25), year, Wednesday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Wednesday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, fixture_id, 1, 1, Wednesday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, fixture_id++, 2);
		}
		else {
			AddFixture(pMem, fixture_id, Date(year, 6, 18), year, Wednesday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Wednesday, Morning, LargestStadium8);
			AddFixtureTV(pMem, fixture_id, 1, 1, Wednesday, Evening, LargestStadium7);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 22), year, Sunday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Sunday, Morning, LargestStadium8);
			AddFixtureTV(pMem, fixture_id, 1, 1, Sunday, Evening, LargestStadium7);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 26), year, Thursday, Afternoon, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 1, Thursday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, fixture_id, 1, 1, Thursday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, fixture_id++, 2);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 7) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 27), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 28), year, Saturday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Tuesday, Afternoon, LargestStadium7);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Monday, Afternoon, LargestStadium9);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon, LargestStadium4);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Tuesday, Morning, LargestStadium8);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Monday, Morning, LargestStadium6);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Sunday, Morning, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Saturday, Morning, LargestStadium2);
		FillFixtureDetails(pMem, fixture_id++, EleventhRound, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 23, 16, 8, 16, 0, 0, 1, 0, 5570408);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 2), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 4), year, Friday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Friday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Saturday, Morning, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Friday, Morning, LargestStadium5);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 23, 8, 4, 0, 0, 0, 1, 0, 9748213);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 6), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 8), year, Tuesday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Wednesday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Tuesday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 23, 4, 2, 0, 0, 0, 1, 0, 15597141);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 10), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 13), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 23, 2, 1, 0, 0, 0, 1, 0, 0, 29708840, 22281630);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) fifa_club_world_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_club_world_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void fifa_club_world_cup_reputation_setup(BYTE* _this) {
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
		for (int i = 24; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
	}
}

void __declspec(naked) fifa_club_world_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_club_world_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void fifa_club_world_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 7) {
		ret_current = 1 + 8 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 8 * (min - 1);
		if (max < 3) ret_max = 9;
		else ret_max = 1 + 8 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 7) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) fifa_club_world_cup_reputation_calc_c()
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
		call fifa_club_world_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

static char(__thiscall* get_host_ids_5FA730)(BYTE* _this, long comp_id, WORD year, DWORD* host1_ptr, DWORD* host2_ptr, int a6) =
(char(__thiscall*)(BYTE * _this, long comp_id, WORD year, DWORD * host1_ptr, DWORD * host2_ptr, int a6))(0x5FA730);
void fifa_club_world_cup_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	WORD total_teams_in_comp = 32;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	// Get teams for Club World Cup
	// AFC (4)
	// - last 4 winners of ACL Elite, get runner-ups as backup
	vector<cm3_clubs*> afc_clubs;
	for (int i = 0; i < 4; i++) {
		cm3_clubs* winner = get_last_comp_winner_by_year(get_comp(AFC_CHAMPIONS_LEAGUE_ELITE_9CF()), year - i - 1);
		if (winner && !vector_contains_club(afc_clubs, winner)) afc_clubs.push_back(winner);
	}
	for (int i = 0; i < 4 && afc_clubs.size() < 4; i++) {
		cm3_clubs* runner_up = get_last_comp_runner_up_by_year(get_comp(AFC_CHAMPIONS_LEAGUE_ELITE_9CF()), year - i - 1);
		if (runner_up && !vector_contains_club(afc_clubs, runner_up)) afc_clubs.push_back(runner_up);
	}
	vector<cm3_clubs*> high_rep_clubs = find_clubs_of_continent(ASIA_9CF());
	sort(high_rep_clubs.begin(), high_rep_clubs.end(), compareClubRep);
	int backup_count = 0;
	while (afc_clubs.size() < 4)
	{
		cm3_clubs* backup = high_rep_clubs[backup_count++];
		if (!vector_contains_club(afc_clubs, backup)) afc_clubs.push_back(backup);
	}
	// CAF (4)
	// - last 4 winners of CAF CL, get runner-ups as backup
	vector<cm3_clubs*> caf_clubs;
	for (int i = 0; i < 4; i++) {
		cm3_clubs* winner = get_last_comp_winner_by_year(get_comp(CAF_CHAMPIONS_LEAGUE_9CF()), year - i - 1);
		if (winner && !vector_contains_club(caf_clubs, winner)) caf_clubs.push_back(winner);
	}
	for (int i = 0; i < 4 && caf_clubs.size() < 4; i++) {
		cm3_clubs* runner_up = get_last_comp_runner_up_by_year(get_comp(CAF_CHAMPIONS_LEAGUE_9CF()), year - i - 1);
		if (runner_up && !vector_contains_club(caf_clubs, runner_up)) caf_clubs.push_back(runner_up);
	}
	high_rep_clubs = find_clubs_of_continent(AFRICA_9CF());
	sort(high_rep_clubs.begin(), high_rep_clubs.end(), compareClubRep);
	backup_count = 0;
	while (caf_clubs.size() < 4)
	{
		cm3_clubs* backup = high_rep_clubs[backup_count++];
		if (!vector_contains_club(caf_clubs, backup)) caf_clubs.push_back(backup);
	}
	// CONCACAF (4)
	// - last 4 winners of CONCACAF CL, get runner-ups as backup
	vector<cm3_clubs*> concacaf_clubs;
	for (int i = 0; i < 4; i++) {
		cm3_clubs* winner = get_last_comp_winner_by_year(get_comp(CONCACAF_CHAMPIONS_CUP_9CF()), year - i - 1);
		if (winner && !vector_contains_club(concacaf_clubs, winner)) concacaf_clubs.push_back(winner);
	}
	for (int i = 0; i < 4 && concacaf_clubs.size() < 4; i++) {
		cm3_clubs* runner_up = get_last_comp_runner_up_by_year(get_comp(CONCACAF_CHAMPIONS_CUP_9CF()), year - i - 1);
		if (runner_up && !vector_contains_club(concacaf_clubs, runner_up)) concacaf_clubs.push_back(runner_up);
	}
	high_rep_clubs = find_clubs_of_continent(NORTH_AMERICA_9CF());
	sort(high_rep_clubs.begin(), high_rep_clubs.end(), compareClubRep);
	backup_count = 0;
	while (concacaf_clubs.size() < 4)
	{
		cm3_clubs* backup = high_rep_clubs[backup_count++];
		if (!vector_contains_club(concacaf_clubs, backup)) concacaf_clubs.push_back(backup);
	}
	// CONMEBOL (6)
	// - last 4 winners of Libertadores, get runner-ups as backup
	vector<cm3_clubs*> conmebol_clubs;
	for (int i = 0; i < 4; i++) {
		cm3_clubs* winner = get_last_comp_winner_by_year(get_comp(COPA_LIBERTADORES_9CF()), year - i - 1);
		if (winner && !vector_contains_club(conmebol_clubs, winner)) conmebol_clubs.push_back(winner);
	}
	for (int i = 0; i < 4 && conmebol_clubs.size() < 6; i++) {
		cm3_clubs* runner_up = get_last_comp_runner_up_by_year(get_comp(COPA_LIBERTADORES_9CF()), year - i - 1);
		if (runner_up && !vector_contains_club(conmebol_clubs, runner_up)) conmebol_clubs.push_back(runner_up);
	}
	high_rep_clubs = find_clubs_of_continent(SOUTH_AMERICA_9CF());
	sort(high_rep_clubs.begin(), high_rep_clubs.end(), compareClubRep);
	backup_count = 0;
	while (conmebol_clubs.size() < 6)
	{
		cm3_clubs* backup = high_rep_clubs[backup_count++];
		if (!vector_contains_club(conmebol_clubs, backup)) conmebol_clubs.push_back(backup);
	}
	// OFC (1)
	// - last winner of OFC CL
	cm3_clubs* ofc_club = 0;
	for (int i = 0; i < 4 && !ofc_club; i++) {
		ofc_club = get_last_comp_winner_by_year(get_comp(OFC_CHAMPIONS_LEAGUE_9CF()), year - i - 1);
	}
	// UEFA (12)
	// - last 4 winners of UCL, last 4 winners of UEL, get UCL runner-ups as backup
	vector<cm3_clubs*> uefa_clubs;
	for (int i = 0; i < 4; i++) {
		cm3_clubs* winner = get_last_comp_winner_by_year(get_comp(UEFA_CHAMPIONS_LEAGUE_9CF()), year - i - 1);
		if (winner && !vector_contains_club(uefa_clubs, winner)) uefa_clubs.push_back(winner);
	}
	for (int i = 0; i < 4; i++) {
		cm3_clubs* winner = get_last_comp_winner_by_year(get_comp(UEFA_EUROPA_LEAGUE_9CF()), year - i - 1);
		if (winner && !vector_contains_club(uefa_clubs, winner)) uefa_clubs.push_back(winner);
	}
	for (int i = 0; i < 4 && uefa_clubs.size() < 12; i++) {
		cm3_clubs* runner_up = get_last_comp_runner_up_by_year(get_comp(UEFA_CHAMPIONS_LEAGUE_9CF()), year - i - 1);
		if (runner_up && !vector_contains_club(uefa_clubs, runner_up)) uefa_clubs.push_back(runner_up);
	}
	high_rep_clubs = find_clubs_of_continent(EUROPE_9CF());
	sort(high_rep_clubs.begin(), high_rep_clubs.end(), compareClubRep);
	backup_count = 0;
	while (uefa_clubs.size() < 12)
	{
		cm3_clubs* backup = high_rep_clubs[backup_count++];
		if (!vector_contains_club(uefa_clubs, backup)) uefa_clubs.push_back(backup);
	}
	// Host (1)
	cm3_clubs* host_club = 0;
	DWORD host1_id, host2_id;
	get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
	cm3_nations* host;
	if (host1_id == (DWORD)-1) host = get_country(NATION_QATAR_9CF());
	else host = host = get_country(host1_id);
	high_rep_clubs = find_clubs_of_country(host->NationID);
	if (host->NationLeagueSelected) {
		// playable
		sort(high_rep_clubs.begin(), high_rep_clubs.end(), compareClubLastDivPos);
	}
	else {
		// not playable
		sort(high_rep_clubs.begin(), high_rep_clubs.end(), compareClubRep);
	}
	for (size_t i = 0; i < high_rep_clubs.size() && !host_club; i++) {
		cm3_clubs* club = high_rep_clubs[i];
		if (!vector_contains_club(afc_clubs, club) && !vector_contains_club(caf_clubs, club) && !vector_contains_club(concacaf_clubs, club) &&
			!vector_contains_club(conmebol_clubs, club) && !vector_contains_club(uefa_clubs, club) && ofc_club != club)
			host_club = club;
	}

	sort(uefa_clubs.begin(), uefa_clubs.end(), compareClubRep);
	shuffle(uefa_clubs.begin(), uefa_clubs.begin() + 4, rng);
	shuffle(uefa_clubs.begin() + 4, uefa_clubs.end(), rng);
	sort(conmebol_clubs.begin(), conmebol_clubs.end(), compareClubRep);
	shuffle(conmebol_clubs.begin(), conmebol_clubs.begin() + 4, rng);
	shuffle(conmebol_clubs.begin() + 4, conmebol_clubs.end(), rng);
	sort(concacaf_clubs.begin(), concacaf_clubs.end(), compareClubRep);
	shuffle(concacaf_clubs.begin(), concacaf_clubs.begin() + 2, rng);
	shuffle(concacaf_clubs.begin() + 2, concacaf_clubs.end(), rng);
	sort(afc_clubs.begin(), afc_clubs.end(), compareClubRep);
	shuffle(afc_clubs.begin(), afc_clubs.begin() + 2, rng);
	shuffle(afc_clubs.begin() + 2, afc_clubs.end(), rng);
	sort(caf_clubs.begin(), caf_clubs.end(), compareClubRep);
	shuffle(caf_clubs.begin(), caf_clubs.begin() + 2, rng);
	shuffle(caf_clubs.begin() + 2, caf_clubs.end(), rng);

	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	// Pot 1: The four top-ranked teams from both UEFA and CONMEBOL
	for (int i = 0; i < 4; i++) {
		teams[i].club = uefa_clubs[i];
		teams[i].f5 = 10;
		teams[i].f6 = 0;
		int ret = sub_5A0590(ae2a38_ptr, (BYTE*)uefa_clubs[i]);
		AddToClubIncome((BYTE*)ret, 11296786);
		AddMoneyFromComp(_this, (BYTE*)uefa_clubs[i], 11296786, 0, -1, GroupStage, 0, -2);

		teams[i + 4].club = conmebol_clubs[i];
		teams[i + 4].f5 = 10;
		teams[i + 4].f6 = 0;
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)conmebol_clubs[i]);
		AddToClubIncome((BYTE*)ret, 11296786);
		AddMoneyFromComp(_this, (BYTE*)conmebol_clubs[i], 11296786, 0, -1, GroupStage, 0, -2);
	}
	// Pot 2: The remaining eight teams from UEFA
	for (int i = 0; i < 8; i++) {
		teams[i + 8].club = uefa_clubs[i + 4];
		teams[i + 8].f5 = 11;
		teams[i + 8].f6 = 0;
		int ret = sub_5A0590(ae2a38_ptr, (BYTE*)uefa_clubs[i + 4]);
		AddToClubIncome((BYTE*)ret, 11296786);
		AddMoneyFromComp(_this, (BYTE*)uefa_clubs[i + 4], 11296786, 0, -1, GroupStage, 0, -2);
	}
	// Pot 3: The two top-ranked teams from each of AFC, CAF and CONCACAF, and the remaining two teams from CONMEBOL
	for (int i = 0; i < 2; i++) {
		teams[i + 16].club = afc_clubs[i];
		teams[i + 16].f5 = 12;
		teams[i + 16].f6 = 0;
		int ret = sub_5A0590(ae2a38_ptr, (BYTE*)afc_clubs[i]);
		AddToClubIncome((BYTE*)ret, 7092986);
		AddMoneyFromComp(_this, (BYTE*)afc_clubs[i], 7092986, 0, -1, GroupStage, 0, -2);

		teams[i + 18].club = caf_clubs[i];
		teams[i + 18].f5 = 12;
		teams[i + 18].f6 = 0;
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)caf_clubs[i]);
		AddToClubIncome((BYTE*)ret, 7092986);
		AddMoneyFromComp(_this, (BYTE*)caf_clubs[i], 7092986, 0, -1, GroupStage, 0, -2);

		teams[i + 20].club = concacaf_clubs[i];
		teams[i + 20].f5 = 12;
		teams[i + 20].f6 = 0;
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)concacaf_clubs[i]);
		AddToClubIncome((BYTE*)ret, 7092986);
		AddMoneyFromComp(_this, (BYTE*)concacaf_clubs[i], 7092986, 0, -1, GroupStage, 0, -2);

		teams[i + 22].club = conmebol_clubs[i + 4];
		teams[i + 22].f5 = 12;
		teams[i + 22].f6 = 0;
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)conmebol_clubs[i + 4]);
		AddToClubIncome((BYTE*)ret, 11296786);
		AddMoneyFromComp(_this, (BYTE*)conmebol_clubs[i + 4], 11296786, 0, -1, GroupStage, 0, -2);
	}
	// Pot 4: The remaining teams from AFC, CAF, CONCACAF, OFC and host country
	for (int i = 0; i < 2; i++) {
		teams[i + 24].club = afc_clubs[i + 2];
		teams[i + 24].f5 = 13;
		teams[i + 24].f6 = 0;
		int ret = sub_5A0590(ae2a38_ptr, (BYTE*)afc_clubs[i + 2]);
		AddToClubIncome((BYTE*)ret, 7092986);
		AddMoneyFromComp(_this, (BYTE*)afc_clubs[i + 2], 7092986, 0, -1, GroupStage, 0, -2);

		teams[i + 26].club = caf_clubs[i + 2];
		teams[i + 26].f5 = 13;
		teams[i + 26].f6 = 0;
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)caf_clubs[i + 2]);
		AddToClubIncome((BYTE*)ret, 7092986);
		AddMoneyFromComp(_this, (BYTE*)caf_clubs[i + 2], 7092986, 0, -1, GroupStage, 0, -2);

		teams[i + 28].club = concacaf_clubs[i + 2];
		teams[i + 28].f5 = 13;
		teams[i + 28].f6 = 0;
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)concacaf_clubs[i + 2]);
		AddToClubIncome((BYTE*)ret, 7092986);
		AddMoneyFromComp(_this, (BYTE*)concacaf_clubs[i + 2], 7092986, 0, -1, GroupStage, 0, -2);
	}

	teams[30].club = ofc_club;
	teams[30].f5 = 13;
	teams[30].f6 = 0;
	int ret = sub_5A0590(ae2a38_ptr, (BYTE*)ofc_club);
	AddToClubIncome((BYTE*)ret, 2658941);
	AddMoneyFromComp(_this, (BYTE*)ofc_club, 2658941, 0, -1, GroupStage, 0, -2);

	teams[31].club = host_club;
	teams[31].f5 = 13;
	teams[31].f6 = 0;
	if (host_club)
	{
		int prize = 0;
		if (host_club->ClubNation->NationContinent->ContinentID == EUROPE_9CF() ||
			host_club->ClubNation->NationContinent->ContinentID == SOUTH_AMERICA_9CF()) {
			prize = 11296786;
		}
		else if (host_club->ClubNation->NationContinent->ContinentID == NORTH_AMERICA_9CF() ||
			host_club->ClubNation->NationContinent->ContinentID == ASIA_9CF() ||
			host_club->ClubNation->NationContinent->ContinentID == AFRICA_9CF()) {
			prize = 7092986;
		}
		else if (host_club->ClubNation->NationContinent->ContinentID == OCEANIA_9CF()) {
			prize = 2658941;
		}
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)ofc_club);
		AddToClubIncome((BYTE*)ret, prize);
		AddMoneyFromComp(_this, (BYTE*)ofc_club, prize, 0, -1, GroupStage, 0, -2);
	}
}

void fifa_club_world_cup_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;

	BYTE teamsAdded = 0;
	add_team_call(_this, teamsAdded++, qualifiers[0].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[8].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[16].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[24].club, 0, 0);
	sub_684230(_this);
}

void fifa_club_world_cup_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	BYTE teamsAdded = 0;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[1 + idx].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[9 + idx].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[17 + idx].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[25 + idx].club;

	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, 4, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

char fifa_club_world_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	sub_687970(_this, ebx);
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
	data->year += 4;
	data->current_stage = -1;
	fifa_club_world_cup_subs(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) fifa_club_world_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_club_world_cup_update
		add esp, 0x4
		ret
	}
}

int fifa_club_world_cup_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 7) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, EleventhRound, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 7) {
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

void __declspec(naked) fifa_club_world_cup_set_table_fate()
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
		call fifa_club_world_cup_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void fifa_club_world_cup_final_stage_setup(BYTE* _this) {
	char stage_num = 7;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 7; al++) {
		if (al > -1) curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
	}

	BYTE team_order[16] = { 0,8,2,10,4,12,6,14,15,7,13,5,11,3,9,1 };
	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
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

void fifa_club_world_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 7) {
			fifa_club_world_cup_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) fifa_club_world_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_club_world_cup_stages_create
		add esp, 0x4
		ret
	}
}

void fifa_club_world_cup_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 3, January, data->year, -1);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year) {
			if (!a3) {
				fifa_club_world_cup_all_teams(_this);
				fifa_club_world_cup_setup_first_group(_this);
				sub_6827D0(_this, 0);
				sub_6835C0(_this);
				for (BYTE i = 0; i < 7; i++) {
					fifa_club_world_cup_setup_groups(_this, i);
				}
				fifa_club_world_cup_reputation_setup(_this);
				data->f69 = 1;
			}
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) fifa_club_world_cup_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_club_world_cup_init2
		add esp, 0xc
		ret 8
	}
}

int cwc_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 7) {
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
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 7) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) cwc_stage_news_c()
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
		call cwc_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void fifa_club_world_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	WORD start_year = year;
	while ((start_year - 2025) % 4 != 0) {
		start_year++;
	}
	data->year = start_year;
	data->comp_vtable = (DWORD*)(fifa_club_world_cup_vtable->vtable_ptr);
	fifa_club_world_cup_vtable->SetPointer(VTableInitFree, (DWORD)&fifa_club_world_cup_free_c);
	fifa_club_world_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&fifa_club_world_cup_update_c);
	fifa_club_world_cup_vtable->SetPointer(VTablePlayoffQual, (DWORD)&fifa_club_world_cup_stages_create_c);
	fifa_club_world_cup_vtable->SetPointer(VTableSetChampion, (DWORD)&fifa_club_world_cup_set_champion_c);
	fifa_club_world_cup_vtable->SetPointer(VTableClubLandmarks, 0x48cab0);
	fifa_club_world_cup_vtable->SetPointer(VTableFixtures, (DWORD)&fifa_club_world_cup_fixture_caller);
	fifa_club_world_cup_vtable->SetPointer(VTableTableFates, (DWORD)&fifa_club_world_cup_set_table_fate);
	fifa_club_world_cup_vtable->SetPointer(VTableStageNews, (DWORD)&cwc_stage_news_c);
	fifa_club_world_cup_vtable->SetPointer(VTableReputationSetup, (DWORD)&fifa_club_world_cup_reputation_setup_c);
	fifa_club_world_cup_vtable->SetPointer(VTableReputationCalc, (DWORD)&fifa_club_world_cup_reputation_calc_c);
	fifa_club_world_cup_vtable->SetPointer(VTableSubsRounds, (DWORD)&fifa_club_world_cup_subs_c);
	fifa_club_world_cup_vtable->SetPointer(VTablePostMatchUpdate, (DWORD)&cwc_money_after_match_c);
	fifa_club_world_cup_vtable->SetPointer(VTableLeagueSplit, (DWORD)&fifa_club_world_cup_init2_c);
	data->rules = RulesInternational;
	data->f81 = 0xf;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_BLACK_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_GOLD_9CF());
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 8;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	fifa_club_world_cup_subs(_this);
	BYTE* ebx = 0;
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void __declspec(naked) fifa_cwc_hosts_adjustment()
{
	__asm
	{
		add eax, 0x22
		add ecx, 0x4
		dec edx
		push 0x5fa458
		ret
	}
}

void setup_fifa_club_world_cup() {
	WriteDWORD(0x5fa424 + 1, 2025);
	PatchFunction(0x5fa453, (DWORD)&fifa_cwc_hosts_adjustment);
}