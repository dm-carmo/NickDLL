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

DWORD* african_nations_vtable = (DWORD*)0x967270;
DWORD afcon_table_start_offset = 0x401000;

int african_nations_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* final_bytes = (BYTE*)comp_data->stages[6];
	BYTE* third_playoff_bytes = (BYTE*)comp_data->stages[7];
	comp_stats* final_data = (comp_stats*)final_bytes;
	comp_stats* third_playoff_data = (comp_stats*)third_playoff_bytes;
	cm3_clubs* first = 0;
	cm3_clubs* second = 0;
	cm3_clubs* third = 0;
	teams_seeded* teams = (teams_seeded*)third_playoff_data->teams_list;
	for (WORD i = 0; i < third_playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) third = teams[i].club;
	}
	teams = (teams_seeded*)final_data->teams_list;
	for (WORD i = 0; i < final_data->n_teams; i++) {
		if (teams[i].f6 == 1) first = teams[i].club;
		else if (teams[i].f6 == 2) second = teams[i].club;
	}
	DWORD host1_id = -1, host2_id = -1;
	char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, comp_data->competition_db->ClubCompID, comp_data->year, &host1_id, &host2_id, 1);
	sub_4AFCE0_add_history_entry(_this, first, second, third, num_hosts > 0 ? get_national_team(host1_id) : 0);

	sub_775420((BYTE*)*b74318, comp_data->competition_db);
	return 0;
}

void __declspec(naked) african_nations_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call african_nations_set_champion
		add esp, 0x4
		ret 0
	}
}

void african_nations_subs(BYTE* _this)
{
	comp_stats* data = (comp_stats*)_this;

	data->f67 = 2;
	data->n_rounds = 1;
	data->pts_for_win = 3;
	data->pts_for_draw = 1;
	data->f196 = 10;
	data->tiebreaker_1 = CurrentPositionTiebreaker;
	data->tiebreaker_2 = GoalDifferenceTiebreaker;
	data->tiebreaker_3 = GoalsForTiebreaker;
	data->tiebreaker_4 = NoTiebreaker;

	data->promotions = 2;
	data->prom_playoff = 0;
	data->rele_playoff = 0;
	data->relegations = 0;

	data->n_games = 1000;
	data->max_bench = 7;
	data->max_subs = 3;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 13, April, data->year, -1);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = 0;

	DWORD v1 = *(DWORD*)_this;
	data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) african_nations_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call african_nations_subs
		add esp, 0x4
		ret
	}
}

DWORD african_nations_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 5) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixture(pMem, 0, Date(year, 6, 22), year, Tuesday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 0, 2);
		AddFixture(pMem, 1, Date(year, 6, 26), year, Saturday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 1, 2);
		AddFixture(pMem, 2, Date(year, 6, 29), year, Tuesday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 2, 2);
		if (stage_idx == -1) {
			AddFixtureTV(pMem, 0, 0, 3, Sunday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 1, 0, 3, Friday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 1, 1, 3, Friday, Evening, NationalStadium);
			AddFixtureTV(pMem, 2, 0, 3, Monday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 1, 3, Monday, Afternoon, LargestStadium1);
		}
		else if (stage_idx == 0) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Evening, LargestStadium2);
			AddFixtureTV(pMem, 1, 0, 3, Friday, Morning, LargestStadium3);
			AddFixtureTV(pMem, 1, 1, 3, Friday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 0, 3, Monday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 1, 3, Monday, Afternoon, LargestStadium3);
		}
		else if (stage_idx == 1) {
			AddFixtureTV(pMem, 0, 0, 3, Tuesday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 0, 1, 3, Tuesday, Evening, LargestStadium7);
			AddFixtureTV(pMem, 1, 0, 3, Saturday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Saturday, Evening, LargestStadium5);
			AddFixtureTV(pMem, 2, 0, 3, Tuesday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 2, 1, 3, Tuesday, Afternoon, LargestStadium7);
		}
		else if (stage_idx == 2) {
			AddFixtureTV(pMem, 0, 0, 3, Tuesday, Morning, LargestStadium8);
			AddFixtureTV(pMem, 0, 1, 3, Tuesday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 1, 0, 3, Saturday, Morning, LargestStadium7);
			AddFixtureTV(pMem, 1, 1, 3, Saturday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 2, 0, 3, Tuesday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 2, 1, 3, Tuesday, Afternoon, LargestStadium8);
		}
		else if (stage_idx == 3) {
			AddFixtureTV(pMem, 0, 0, 3, Wednesday, Morning, LargestStadium4);
			AddFixtureTV(pMem, 0, 1, 3, Wednesday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 1, 0, 3, Sunday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 1, 1, 3, Sunday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 0, 3, Wednesday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 1, 3, Wednesday, Afternoon, LargestStadium4);
		}
		else if (stage_idx == 4) {
			AddFixtureTV(pMem, 0, 0, 3, Wednesday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 0, 1, 3, Wednesday, Evening, LargestStadium2);
			AddFixtureTV(pMem, 1, 0, 3, Sunday, Morning, LargestStadium2);
			AddFixtureTV(pMem, 1, 1, 3, Sunday, Evening, LargestStadium3);
			AddFixtureTV(pMem, 2, 0, 3, Wednesday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 2, 1, 3, Wednesday, Afternoon, LargestStadium2);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 6) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 1), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 5), year, Monday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium5);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Afternoon, LargestStadium6);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Afternoon, LargestStadium5);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Afternoon, LargestStadium8);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 16, 8, 16, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 7), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 9), year, Friday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Friday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Friday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 8, 4, 0, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 11), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 14), year, Wednesday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Wednesday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Wednesday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 18), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 7) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = ThirdPlacePlayoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 14), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 17), year, Saturday, Afternoon, LargestStadium4);
		FillFixtureDetails(pMem, fixture_id++, None, 0, Penalties | ExtraTime, NoTiebreak, 10, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) african_nations_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void african_nations_reputation_setup(BYTE* _this) {
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
		for (int i = 16; i < 18; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 18; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19);
		}
		for (WORD i = 0; i < comp_data->special_nteams_seedings; i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) african_nations_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call african_nations_reputation_setup
		add esp, 0x4
		ret
	}
}

void african_nations_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 5) {
		ret_current = 1 + 6 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 6 * (min - 1);
		if (max < 3) ret_max = 9;
		else ret_max = 1 + 6 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 5) {
		if (current < 5) ret_current = 9;
		else ret_current = 17;
		if (min < 5) ret_min = 1;
		else ret_min = 17;
		if (max < 5) ret_max = 9;
		else ret_max = 17;
	}
	else if (stage == 6) {
		// do nothing
	}
	else if (stage == 7) {
		ret_current = current + 2;
		ret_min = min + 2;
		ret_max = max + 2;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) african_nations_reputation_calc_c()
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
		call african_nations_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void african_nations_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* tMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)tMem;

	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < total_teams; i++) {
		add_team_call(_this, teamsAdded++, teamList[i * 6].club, 0, 0);
	}
	sub_684230(_this);
}

void african_nations_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < data->n_teams; i++) {
		*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)teamList[i * 6 + (idx + 1)].club;
	}

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, data->n_teams, pTeams, data->n_rounds, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, idx, stage_name_id, data->f81, 4, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void african_nations_best_placed_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	char stage_num = 5;

	WORD start_date[4];
	WORD end_date[4];
	DWORD tmp1[2];
	DWORD tmp2[2];
	sub_54A110((BYTE*)start_date);
	sub_54A110((BYTE*)end_date);

	WORD year = data->year;
	BYTE* ba = (BYTE*)data->fixtures_table;
	BYTE* cm_date = new BYTE[8];
	sub_549EF0(cm_date, *(WORD*)(ba)-3, year + *(WORD*)(ba + 2));
	sub_417C10((BYTE*)start_date, tmp1, cm_date);
	WORD a9 = *(WORD*)(_this + 0xA9);
	sub_549EF0(cm_date, *(WORD*)(ba + a9 * fixture_dates_sz - fixture_dates_sz),
		year + *(WORD*)(ba + a9 * fixture_dates_sz - fixture_dates_sz + 2));
	sub_54C770(cm_date, (BYTE*)tmp1, 1);
	sub_417C10((BYTE*)end_date, tmp2, (BYTE*)tmp1);
	comp_stats* curr_stage = data;
	for (char al = -1; al < 5; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		sub_6827D0((BYTE*)curr_stage, 0);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls_third = table_teams[2];
		cm3_clubs* third_club = tls_third.club;
		DWORD* pMem = (DWORD*)cm0102_malloc(4 * curr_stage->n_teams);
		for (WORD i = 0; i < curr_stage->n_teams; i++) {
			*((DWORD*)(&pMem[i])) = table_teams[i].club->ClubID;
		}
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		comp_stats* stage_data = (comp_stats*)pStage;
		WORD n = curr_stage->n_teams;
		sub_88C6D0(pStage, n, pMem, -1, -1, start_date, end_date, data->competition_db->ClubCompID, data->pts_for_win, data->pts_for_draw, &data->tiebreaker_1, 9 * (n * (n - 1)), data->f16);
		table_teams = (team_league_stats*)stage_data->team_league_table;
		WORD chk = 0;
		for (; chk < stage_data->n_teams; chk++) {
			if (table_teams[chk].club == third_club) break;
		}
		if (chk < stage_data->n_teams) {
			comp_stats* best_placed_stage = (comp_stats*)(data->stages[stage_num]);
			team_league_stats* best_placed_table = (team_league_stats*)(best_placed_stage->team_league_table);
			memcpy(&best_placed_table[al + 1], &table_teams[chk], league_team_list_sz);
			best_placed_table[al + 1].position_history = 0;
			best_placed_table[al + 1].f4 = 0;
		}
		DWORD v1 = *(DWORD*)pStage;
		(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)pStage, 1);
		sub_9452CA_free((BYTE*)(pMem));
	}
	sub_6827D0((BYTE*)data->stages[stage_num], 0);
}

void african_nations_setup_best_placed(BYTE* _this) {
	char stage_num = 5;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 4, 0, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };
	create_league_stage_data(pStage, _this, 6, 0, 0, (DWORD)(data->competition_db), 0, 0,
		data->pts_for_win, data->pts_for_draw, data->f196, &tiebreaks[0], &prom_rel[0],
		year, stage_num, BestPlacedTeams, 0, 1, 0, 0x28, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	data->current_stage = stage_num;
	african_nations_best_placed_update(_this);
}

void african_nations_seeded_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	data->special_nteams_seedings = 0;
	WORD count = data->special_nteams_seedings;
	WORD year = data->year;
	DWORD host1_id = -1, host2_id = -1;
	char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
	if (num_hosts > 0) {
		teamList[count].club = get_national_team(host1_id);
		teamList[count].seeding = 1;
		count++;
	}
	if (num_hosts > 1) {
		teamList[count].club = get_national_team(host2_id);
		teamList[count].seeding = 1;
		count++;
	}
	for (WORD i = count; i < 24; i++)
	{
		teamList[i].club = 0;
		teamList[i].seeding = 6;
	}
	//if (year == 2025) {
	//	teamList[count++].club = get_national_team(NATION_MOROCCO_9CF());
	//	teamList[count++].club = get_national_team(NATION_MALI_9CF());
	//	teamList[count++].club = get_national_team(NATION_COMOROS_9CF());
	//	teamList[count++].club = get_national_team(NATION_ZAMBIA_9CF());
	//	teamList[count++].club = get_national_team(NATION_EGYPT_9CF());
	//	teamList[count++].club = get_national_team(NATION_SOUTH_AFRICA_9CF());
	//	teamList[count++].club = get_national_team(NATION_ANGOLA_9CF());
	//	teamList[count++].club = get_national_team(NATION_ZIMBABWE_9CF());
	//	teamList[count++].club = get_national_team(NATION_NIGERIA_9CF());
	//	teamList[count++].club = get_national_team(NATION_TUNISIA_9CF());
	//	teamList[count++].club = get_national_team(NATION_TANZANIA_9CF());
	//	teamList[count++].club = get_national_team(NATION_UGANDA_9CF());
	//	teamList[count++].club = get_national_team(NATION_SENEGAL_9CF());
	//	teamList[count++].club = get_national_team(NATION_DR_CONGO_9CF());
	//	teamList[count++].club = get_national_team(NATION_BENIN_9CF());
	//	teamList[count++].club = get_national_team(NATION_BOTSWANA_9CF());
	//	teamList[count++].club = get_national_team(NATION_ALGERIA_9CF());
	//	teamList[count++].club = get_national_team(NATION_BURKINA_FASO_9CF());
	//	teamList[count++].club = get_national_team(NATION_SUDAN_9CF());
	//	teamList[count++].club = get_national_team(NATION_EQUATORIAL_GUINEA_9CF());
	//	teamList[count++].club = get_national_team(NATION_IVORY_COAST_9CF());
	//	teamList[count++].club = get_national_team(NATION_CAMEROON_9CF());
	//	teamList[count++].club = get_national_team(NATION_MOZAMBIQUE_9CF());
	//	teamList[count++].club = get_national_team(NATION_GABON_9CF());
	//}
	if (year == 2027) {
		vector<cm3_clubs*> clubs;
		// add the 3 real-life hosts
		clubs.push_back(get_national_team(NATION_UGANDA_9CF()));
		clubs.push_back(get_national_team(NATION_TANZANIA_9CF()));
		clubs.push_back(get_national_team(NATION_KENYA_9CF()));
		// simulate the groups in some way
		vector<cm3_clubs*> group_teams;
		group_teams.push_back(get_national_team(NATION_MOROCCO_9CF()));
		group_teams.push_back(get_national_team(NATION_GABON_9CF()));
		group_teams.push_back(get_national_team(NATION_NIGER_9CF()));
		group_teams.push_back(get_national_team(NATION_LESOTHO_9CF()));
		vector<cm3_clubs*> quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_EGYPT_9CF()));
		group_teams.push_back(get_national_team(NATION_ANGOLA_9CF()));
		group_teams.push_back(get_national_team(NATION_MALAWI_9CF()));
		group_teams.push_back(get_national_team(NATION_SOUTH_SUDAN_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_IVORY_COAST_9CF()));
		group_teams.push_back(get_national_team(NATION_GHANA_9CF()));
		group_teams.push_back(get_national_team(NATION_GAMBIA_9CF()));
		group_teams.push_back(get_national_team(NATION_SOMALIA_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_SOUTH_AFRICA_9CF()));
		group_teams.push_back(get_national_team(NATION_GUINEA_9CF()));
		group_teams.push_back(get_national_team(NATION_ERITREA_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 1);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_DR_CONGO_9CF()));
		group_teams.push_back(get_national_team(NATION_EQUATORIAL_GUINEA_9CF()));
		group_teams.push_back(get_national_team(NATION_SIERRA_LEONE_9CF()));
		group_teams.push_back(get_national_team(NATION_ZIMBABWE_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_BURKINA_FASO_9CF()));
		group_teams.push_back(get_national_team(NATION_BENIN_9CF()));
		group_teams.push_back(get_national_team(NATION_MAURITANIA_9CF()));
		group_teams.push_back(get_national_team(NATION_CENTRAL_AFRICA_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_CAMEROON_9CF()));
		group_teams.push_back(get_national_team(NATION_COMOROS_9CF()));
		group_teams.push_back(get_national_team(NATION_NAMIBIA_9CF()));
		group_teams.push_back(get_national_team(NATION_CONGO_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_TUNISIA_9CF()));
		group_teams.push_back(get_national_team(NATION_LIBYA_9CF()));
		group_teams.push_back(get_national_team(NATION_BOTSWANA_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 1);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_ALGERIA_9CF()));
		group_teams.push_back(get_national_team(NATION_ZAMBIA_9CF()));
		group_teams.push_back(get_national_team(NATION_TOGO_9CF()));
		group_teams.push_back(get_national_team(NATION_BURUNDI_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_SENEGAL_9CF()));
		group_teams.push_back(get_national_team(NATION_MOZAMBIQUE_9CF()));
		group_teams.push_back(get_national_team(NATION_SUDAN_9CF()));
		group_teams.push_back(get_national_team(NATION_ETHIOPIA_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_MALI_9CF()));
		group_teams.push_back(get_national_team(NATION_CAPE_VERDE_9CF()));
		group_teams.push_back(get_national_team(NATION_RWANDA_9CF()));
		group_teams.push_back(get_national_team(NATION_LIBERIA_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 2);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		group_teams.clear();
		group_teams.push_back(get_national_team(NATION_NIGERIA_9CF()));
		group_teams.push_back(get_national_team(NATION_MADAGASCAR_9CF()));
		group_teams.push_back(get_national_team(NATION_GUINEA_BISSAU_9CF()));
		quals = get_random_weighted_national_teams(group_teams, 1);
		for (cm3_clubs* c : quals) clubs.push_back(c);
		sort(clubs.begin() + 3, clubs.end(), compareNationRanking);
		for (; count < 24; count++)
		{
			teamList[count].club = clubs[count];
		}
	}
	data->special_nteams_seedings = count;
}

char african_nations_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* afcon_quals = get_loaded_league(AFRICAN_CUP_OF_NATIONS_QUALIFYING_9CF());

	DWORD v1 = *(DWORD*)afcon_quals;
	if (data->year != 2027) (*(int(__thiscall**)(BYTE*))(v1 + 0x8))(afcon_quals);

	sub_687970(_this, 0);
	data->n_teams = 0;
	data->f69 = 0;
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
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
	if (data->year == 2027) data->year++;
	else data->year += 4;
	data->f68 = -1;
	data->current_stage = -1;
	data->f75 = 1;
	african_nations_seeded_teams(_this);
	african_nations_subs(_this);
	data->team_league_table = 0;
	return 1;
}

void __declspec(naked) african_nations_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call african_nations_update
		add esp, 0x4
		ret
	}
}

#pragma warning(push)
#pragma warning(disable:6385)
void african_nations_final_stage_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;

	char stage_num = 6;

	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 5; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
		staff_history_failed_qual_86C1D0(staff_hist_ptr, table_teams[3].club, (DWORD)(data->competition_db), GroupStage, 0x1E);
		sub_775000((BYTE*)*b74318, table_teams[3].club->ClubNation);
	}
	comp_stats* best_placed_stage = (comp_stats*)(data->stages[5]);
	team_league_stats* best_placed_table = (team_league_stats*)(best_placed_stage->team_league_table);
	char best_third_letters[5] = { 0,0,0,0,0, };
	char letter_idx = 0;
	curr_stage = data;
	for (char al = -1; al < 5; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		cm3_clubs* third = table_teams[2].club;
		for (WORD i = 0; i < best_placed_stage->promotions; i++) {
			if (best_placed_table[i].club == third) {
				best_third_letters[letter_idx++] = 65 + al + 1;
				clubs.push_back(third);
				table_teams[2].league_fate = Qualified1;
				curr_stage->promotions++;
				break;
			}
		}
	}
	for (WORD i = 4; i < best_placed_stage->n_teams; i++)
	{
		staff_history_failed_qual_86C1D0(staff_hist_ptr, best_placed_table[i].club, (DWORD)(data->competition_db), GroupStage, 0x1E);
		sub_775000((BYTE*)*b74318, best_placed_table[i].club->ClubNation);
	}

	char key[5] = { '\0' };
	char indexes[5] = { '\0' };
	for (int i = 0; i < 15; i++) {
		strncpy_s(key, (char*)(afcon_table_start_offset + 8 * i), 4);
		if (strcmp(key, best_third_letters) == 0) {
			strncpy_s(indexes, (char*)(afcon_table_start_offset + 8 * i + 4), 4);
			break;
		}
	}

	BYTE table_order[4] = { 11,5,15,3 };
	BYTE team_order[16] = { 10,0,4,8,14,1,2,13,12,7,6,9 };
	for (char i = 0; i < 4; i++) team_order[i + 12] = table_order[indexes[i] - 1];
	for (WORD j = 0; j < playoff_teams; j++) {
		BYTE order = team_order[j];
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 4, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	data->current_stage = (long)stage_num;
}
#pragma warning(pop)

void african_nations_third_place_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	char stage_num = 7;

	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 4, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	data->current_stage = (long)stage_num;
}

void african_nations_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 6) {
			african_nations_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) african_nations_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call african_nations_stages_create
		add esp, 0x4
		ret
	}
}

void african_nations_setup1(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	WORD n = data->special_nteams_seedings;
	vector<cm3_clubs*> qualified_teams;
	for (WORD i = 0; i < n; i++) qualified_teams.push_back(teamList[i].club);
	if (data->year != 2025) {
		data->f75 = 0;
		if (n < 24) {
			string msg = "Not enough teams in AFCON: needed 24 but only had " + to_string(n);
			vector<cm3_clubs*> nat_teams = get_national_teams_of_continent_fifa_members(AFRICA_9CF());
			sort(nat_teams.begin(), nat_teams.end(), compareNationRanking);
			for (WORD i = 0; n < 24 && i < nat_teams.size(); i++) {
				cm3_clubs* c = nat_teams[i];
				if (!vector_contains_element(qualified_teams, c)) {
					teamList[n++].club = c;
					qualified_teams.push_back(c);
				}
			}
			data->special_nteams_seedings = 24;
			create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
		}
		if (n < 24) {
			string msg = "Something went wrong... only have " + to_string(n) + " teams for the AFCON!";
			create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
		}
		WORD year = data->year;
		DWORD host1_id = -1, host2_id = -1;
		char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
		cm3_clubs* host1, * host2;
		if (num_hosts < 1) host1 = 0;
		else host1 = get_national_team(host1_id);
		if (num_hosts < 2) host2 = 0;
		else host2 = get_national_team(host2_id);
		WORD bl = 0;
		for (WORD i = 0; i < n; i++) {
			if (qualified_teams[i] == host1) {
				cm3_clubs* c1 = qualified_teams[0];
				qualified_teams[0] = qualified_teams[i];
				qualified_teams[i] = c1;
				if (bl < 1) bl = 1;
			}
			if (qualified_teams[i] == host2) {
				cm3_clubs* c1 = qualified_teams[1];
				qualified_teams[1] = qualified_teams[i];
				qualified_teams[i] = c1;
				if (bl < 2) bl = 2;
			}
		}
		if (host1 == host2) bl = 1;
		sort(qualified_teams.begin() + bl, qualified_teams.end(), compareNationRanking);
		for (WORD i = 0; i < n; i++) {
			cm3_clubs* c = qualified_teams[i];
			teamList[i].club = c;
			if (i < 6) teamList[i].seeding = 3;
			else if (i < 12) teamList[i].seeding = 10;
			else if (i < 18) teamList[i].seeding = 11;
			else teamList[i].seeding = 12;
		}
	}
}

void african_nations_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	if (year == 2025) {
		vector<cm3_clubs*> clubs;
		clubs.push_back(get_national_team(NATION_MOROCCO_9CF()));
		clubs.push_back(get_national_team(NATION_EGYPT_9CF()));
		clubs.push_back(get_national_team(NATION_NIGERIA_9CF()));
		clubs.push_back(get_national_team(NATION_SENEGAL_9CF()));
		clubs.push_back(get_national_team(NATION_ALGERIA_9CF()));
		clubs.push_back(get_national_team(NATION_IVORY_COAST_9CF()));
		clubs.push_back(get_national_team(NATION_MALI_9CF()));
		clubs.push_back(get_national_team(NATION_SOUTH_AFRICA_9CF()));
		clubs.push_back(get_national_team(NATION_TUNISIA_9CF()));
		clubs.push_back(get_national_team(NATION_DR_CONGO_9CF()));
		clubs.push_back(get_national_team(NATION_BURKINA_FASO_9CF()));
		clubs.push_back(get_national_team(NATION_CAMEROON_9CF()));
		clubs.push_back(get_national_team(NATION_COMOROS_9CF()));
		clubs.push_back(get_national_team(NATION_ANGOLA_9CF()));
		clubs.push_back(get_national_team(NATION_TANZANIA_9CF()));
		clubs.push_back(get_national_team(NATION_BENIN_9CF()));
		clubs.push_back(get_national_team(NATION_SUDAN_9CF()));
		clubs.push_back(get_national_team(NATION_MOZAMBIQUE_9CF()));
		clubs.push_back(get_national_team(NATION_ZAMBIA_9CF()));
		clubs.push_back(get_national_team(NATION_ZIMBABWE_9CF()));
		clubs.push_back(get_national_team(NATION_UGANDA_9CF()));
		clubs.push_back(get_national_team(NATION_BOTSWANA_9CF()));
		clubs.push_back(get_national_team(NATION_EQUATORIAL_GUINEA_9CF()));
		clubs.push_back(get_national_team(NATION_GABON_9CF()));

		for (BYTE i = 0; i < 24; i++) {
			teamList[i].club = clubs[i];
			teamList[i].seeding = 6;
		}
		teamList[0].seeding = 1;
		data->special_nteams_seedings = 24;
	}
	else
	{
		DWORD host1_id = -1, host2_id = -1;
		char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < 24; i++) clubs.push_back(teamList[i].club);
		shuffle(clubs.begin() + num_hosts, clubs.begin() + 6, rng);
		shuffle(clubs.begin() + 6, clubs.begin() + 12, rng);
		shuffle(clubs.begin() + 12, clubs.begin() + 18, rng);
		shuffle(clubs.begin() + 18, clubs.end(), rng);
		for (int i = 0; i < 24; i++) teamList[i].club = clubs[i];
	}
}

void african_nations_setup2(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	african_nations_all_teams(_this);
	african_nations_setup_first_group(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	data->f69 = 1;
	for (BYTE i = 0; i < 5; i++) african_nations_setup_groups(_this, i);
	african_nations_setup_best_placed(_this);
	african_nations_reputation_setup(_this);
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);
}

void african_nations_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	WORD day2 = *(WORD*)(_this + 0xB6);
	short year2 = *(short*)(_this + 0xB8);
	if (day2 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year2) {
		if (a3) {
			african_nations_setup1(_this);
			african_nations_setup2(_this);
		}
	}
	else if (*(WORD*)(current_date) > day2 || *(WORD*)(current_date + 2) > data->year + year2) {
		char ret = sub_5AE6D0((BYTE*)current_date, data->competition_db->ClubCompID);
		if (ret) african_nations_best_placed_update(_this);
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) african_nations_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_init2
		add esp, 0xc
		ret 8
	}
}

void african_nations_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = african_nations_vtable;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f75 = 1;
	data->rules = RulesInternational;
	data->year = year + 1;
	if (data->year == 2027);
	else while (data->year % 4 != 0) data->year++;
	data->f81 = 0xf;
	data->special_nteams_seedings = 0;
	data->f56 = 24;
	BYTE* pMem = (BYTE*)cm0102_malloc(24 * 6);
	data->special_teams_seedings = (DWORD*)pMem;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f217 = 0x28;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 8;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	african_nations_seeded_teams(_this);
	african_nations_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	if (data->year == year) data->special_nteams_seedings = 24;
	else data->f69 = 0;
	data->team_league_table = 0;
	data->n_teams = 0;
}

int african_nations_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 5) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		default:
			//staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), GroupStage, 0x1E);
			return 0;
		}
	}
	else if (stage == 5) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), GroupStage, 0x1E);
			return 0;
		}
	}
	else if (stage == 6) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		char c;
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			*a5 = 4;
			break;
		case Promoted:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			break;
		default:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			WORD round_name = *(WORD*)(rounds + playoff_dates_sz * current_round + 7);
			if (round_name == SemiFinal) {
				if (comp_data->current_stage < comp_data->num_stages - 1) african_nations_third_place_setup(_this);
				comp_stats* stage = (comp_stats*)comp_data->stages[comp_data->current_stage];
				teams_seeded* teams = (teams_seeded*)stage->teams_list;
				if (!teams[0].club) teams[0].club = club;
				else if (!teams[1].club) teams[1].club = club;
			}
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 7) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		char c;
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_third_place_86B710(staff_hist_ptr, club, round_data, a7);
			*a5 = 4;
			break;
		case Promoted:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			break;
		default:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) african_nations_table_fates_c()
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
		call african_nations_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

WORD african_nations_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	if (val == 1) return -1;
	else if (val == 2) return Final;
	else if (val < 5) return SemiFinal;
	else if (val < 9) return QuarterFinal;
	else if (val < 16) return RoundOf16;
	else
	{
		short ret = (val > 16) - 1;
		return (ret & 0x18) - 4;
	}
}

void __declspec(naked) african_nations_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE african_nations_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	if (al < 3) {
		if (bl < 3) return 1;
		else if (bl < 5) return 0;
		else if (bl < 9) return -1;
		else return (bl < 17) - 3;
	}
	else if (al < 5) {
		if (bl < 3) return 2;
		else if (bl < 5) return 1;
		else if (bl < 9) return 0;
		else return (bl < 17) - 2;
	}
	else if (al < 9) {
		if (bl < 3) return 3;
		else if (bl < 5) return 2;
		else if (bl < 9) return 1;
		else if (bl < 17) return 0;
		else return (bl < 25) - 1;
	}
	else if (al < 17) {
		if (bl < 3) return 3;
		else if (bl < 5) return 2;
		else if (bl < 9) return 1;
		else if (bl < 17) return 0;
		else return -1;
	}
	else {
		if (bl < 5) return 3;
		else if (bl < 9) return 2;
		else if (bl < 17) return 1;
		else return 0;
	}
}

void __declspec(naked) african_nations_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_vtable30
		add esp, 0x8
		ret 4
	}
}

int african_nations_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 5) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 5) {
		if (fate == Qualified1) {
			sub_66F4E0(0xDE1F64, (DWORD)&qualified_best3rd_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
				&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
		//else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 6) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 7)
	{
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0x987264, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case BottomPlayoff:
				sub_66F4E0(0xDE1F64, 0x987200, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0x98713C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			}
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
	}
	return 0;
}

void __declspec(naked) african_nations_stage_news_c()
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
		call african_nations_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void african_nations_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if (main_stage_id == BestPlacedTeams) {
		sub_66F4E0(dest_ptr, 0x99B800);
		return;
	}
	if (main_stage_id == None)
	{
		if (sub_stage_id == SemiFinal)
		{
			if (fate == 1) return sub_48CAB0(_this, dest_ptr, a2, None, Final, 0, club);
			else if (fate == 2) return sub_48CAB0(_this, dest_ptr, a2, ThirdPlacePlayoff, None, 0, club);
		}
		else if (sub_stage_id == Final)
		{
			if (fate == 1 || fate == 2) return sub_48CAB0(_this, dest_ptr, a2, None, None, fate, club);
		}
		return sub_48CAB0(_this, dest_ptr, a2, None, sub_stage_id, fate, club);
	}
	else if (main_stage_id == ThirdPlacePlayoff && sub_stage_id == None)
	{
		if (fate == 1) return sub_48CAB0(_this, dest_ptr, a2, None, None, 3, club);
		else return sub_48CAB0(_this, dest_ptr, a2, None, SemiFinal, -1, club);
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) african_nations_landmarks_c()
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
		call african_nations_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

void setup_african_nations() {
	WriteVTablePtr(african_nations_vtable, VTableSubsRounds, (DWORD)&african_nations_subs_c);
	WriteVTablePtr(african_nations_vtable, VTableLeagueSplit, (DWORD)&african_nations_init2_c);
	WriteVTablePtr(african_nations_vtable, VTableEoSUpdate, (DWORD)&african_nations_update_c);
	WriteVTablePtr(african_nations_vtable, VTableReputationCalc, (DWORD)&african_nations_reputation_calc_c);
	WriteVTablePtr(african_nations_vtable, VTableReputationSetup, (DWORD)&african_nations_reputation_setup_c);
	WriteVTablePtr(african_nations_vtable, VTableSetChampion, (DWORD)&african_nations_set_champion_c);
	WriteVTablePtr(african_nations_vtable, VTableFixtures, (DWORD)&african_nations_fixture_caller);
	WriteVTablePtr(african_nations_vtable, VTablePlayoffQual, (DWORD)&african_nations_stages_create_c);
	WriteVTablePtr(african_nations_vtable, VTableTableFates, (DWORD)&african_nations_table_fates_c);
	WriteVTablePtr(african_nations_vtable, VTableStageNews, (DWORD)&african_nations_stage_news_c);
	WriteVTablePtr(african_nations_vtable, VTable29, (DWORD)&african_nations_vtable29_c);
	WriteVTablePtr(african_nations_vtable, VTable30, (DWORD)&african_nations_vtable30_c);
	WriteVTablePtr(african_nations_vtable, VTableClubLandmarks, (DWORD)&african_nations_landmarks_c);
	WriteVTablePtr(african_nations_vtable, VTableShowHostsInHistory, 0x404480);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(african_nations_vtable, VTableShowThirdInHistory, 0x4110b0);

	// third placed teams table
	map<char*, char*> table = {
		{"ABCD", "CDAB"},
		{"ABCE", "CABE"},
		{"ABCF", "CABF"},
		{"ABDE", "DABE"},
		{"ABDF", "DABF"},
		{"ABEF", "EABF"},
		{"ACDE", "CDAE"},
		{"ACDF", "CDAF"},
		{"ACEF", "CAFE"},
		{"ADEF", "DAFE"},
		{"BCDE", "CDBE"},
		{"BCDF", "CDBF"},
		{"BCEF", "ECBF"},
		{"BDEF", "EDBF"},
		{"CDEF", "CDFE"},
	};
	DWORD off = afcon_table_start_offset;
	for (auto const& x : table)
	{
		for (int i = 0; i < 4; i++) WriteBytes(off++, 1, x.first[i]);
		for (int i = 0; i < 4; i++) WriteBytes(off++, 1, strchr(x.second, x.first[i]) - x.second + 1);
	}
}