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

DWORD* world_cup_quals_caf_vtable = (DWORD*)0x970AD0;

void world_cup_quals_caf_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = world_cup_quals_caf_vtable;
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
	sub_682300(_this);
}

void world_cup_quals_caf_free(BYTE* _this, BYTE a2) {
	world_cup_quals_caf_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) world_cup_quals_caf_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_caf_free
		add esp, 0x8
		ret 4
	}
}

void world_cup_quals_caf_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f67 = 2;
	comp_data->f196 = 10;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_4 = GoalsForAwayTiebreaker;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	comp_data->promotions = num_hosts == 0;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	*((WORD*)(_this + 0xA7)) = -1;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) world_cup_quals_caf_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_caf_subs
		add esp, 0x4
		ret
	}
}

DWORD world_cup_quals_caf_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	if (stage_idx < 8 + (num_hosts == 1)) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 6;
		*num_rounds = 10;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 14), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 6), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 11), year, Tuesday, Afternoon);
		//AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Thursday, Afternoon);
		//AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 19), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 20), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 25), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 9, 23), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 9, 26), year, Sunday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 9, 29), year, Wednesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 10, 3), year, Sunday, Afternoon);

		return (DWORD)pMem;
	}
	// playoff
	else if (stage_idx == 9 && num_hosts == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 2;
		*stage_name_id = SecondRound;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 2, 10, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 2, 11, 13), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, FirstStage, 0, FixedTeamOrderInCup | Penalties | ExtraTime, NoTiebreak, 10, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 2, 11, 14), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 2, 11, 16), year, Sunday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, SecondStage, 0, Penalties | ExtraTime, NoTiebreak, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) world_cup_quals_caf_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_caf_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char world_cup_quals_caf_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	*((WORD*)(_this + 0xA7)) = -1;
	data->f76 = 0;
	sub_687970(_this, 0);
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
	if (data->year < *current_year) data->year += 4;
	data->current_stage = -1;
	data->num_stages = 10;
	world_cup_quals_caf_subs(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) world_cup_quals_caf_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_caf_update
		add esp, 0x4
		ret
	}
}

void world_cup_quals_caf_reputation_setup(BYTE* _this) {
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

		WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
		WORD num_groups = 9 + (num_hosts == 1);

		for (int i = 0; i < num_groups; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 1);
		}
		for (int i = num_groups; i < num_groups * 2; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], num_groups + 1);
		}
		for (int i = num_groups * 2; i < num_groups * 3; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], num_groups * 2 + 1);
		}
		for (int i = num_groups * 3; i < num_groups * 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], num_groups * 3 + 1);
		}
		for (int i = num_groups * 4; i < num_groups * 5; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], num_groups * 4 + 1);
		}
		for (WORD i = num_groups * 5; i < comp_data->special_nteams_seedings; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], num_groups * 5 + 1);
		}
		for (WORD i = 0; i < comp_data->special_nteams_seedings; i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) world_cup_quals_caf_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_caf_reputation_setup
		add esp, 0x4
		ret
	}
}

void world_cup_quals_caf_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;

	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	WORD num_groups = 9 + (num_hosts == 1);

	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < num_groups - 1) {
		ret_current = 1 + num_groups * (current - 1);
		if (min < 2) ret_min = 1;
		else ret_min = 1 + num_groups * (min - 1);
		if (max < 2) ret_max = 1;
		else if (max < 3 && num_hosts == 0) ret_max = num_groups * 2 - 1;
		else ret_max = 1 + num_groups * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == num_groups - 1) {
		if (num_hosts == 0) {
			if (current < 5) ret_current = num_groups + 1;
			else ret_current = num_groups + 5;
			if (min < 5) ret_min = num_groups + 1;
			else ret_min = num_groups + 5;
			if (max < 9) ret_max = num_groups + 4;
			else ret_max = num_groups + 5;
		}
		else {
			if (current < 7 + num_hosts == 1) ret_current = 1;
			else ret_current = num_groups - 3;
			if (min < 7 + num_hosts == 1) ret_min = 1;
			else ret_min = num_groups - 3;
			if (max < 7 + num_hosts == 1) ret_max = 1;
			else ret_max = num_groups - 3;
		}
	}
	else if (stage == num_groups - 1) {
		ret_current = current + num_groups;
		ret_min = min + num_groups;
		ret_max = max + num_groups;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) world_cup_quals_caf_reputation_calc_c()
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
		call world_cup_quals_caf_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void world_cup_quals_caf_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	vector<cm3_clubs*> countries = get_national_teams_of_continent_fifa_members(AFRICA_9CF());
	sort(countries.begin(), countries.end(), compareNationRanking);

	DWORD host1_id, host2_id;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), &host1_id, &host2_id);
	if (num_hosts == 2) data->num_stages--;
	WORD total_teams_in_comp = (WORD)countries.size() - num_hosts;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	WORD num_groups = 9 + (num_hosts == 1);
	shuffle(countries.begin(), countries.begin() + num_groups, rng);
	shuffle(countries.begin() + num_groups, countries.begin() + num_groups * 2, rng);
	shuffle(countries.begin() + num_groups * 2, countries.begin() + num_groups * 3, rng);
	shuffle(countries.begin() + num_groups * 3, countries.begin() + num_groups * 4, rng);
	shuffle(countries.begin() + num_groups * 4, countries.begin() + num_groups * 5, rng);
	shuffle(countries.begin() + num_groups * 5, countries.end(), rng);

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	for (BYTE i = 0, j = 0; i < countries.size() && j < total_teams_in_comp; i++) {
		if (countries[i]->ClubNation->NationID == host1_id || countries[i]->ClubNation->NationID == host2_id) continue;
		teams[j].club = countries[i];
		teams[j].seeding = 6;
		teams[j].f6 = 0;
		j++;
	}
}

void world_cup_quals_caf_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 6;
	BYTE* pMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;

	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	WORD num_groups = 9 + (num_hosts == 1);

	BYTE teamsAdded = 0;
	add_team_call(_this, teamsAdded++, qualifiers[0].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[num_groups].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[num_groups * 2].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[num_groups * 3].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[num_groups * 4].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[num_groups * 5].club, 0, 0);
	sub_684230(_this);
}

void world_cup_quals_caf_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	WORD num_groups = 9 + (num_hosts == 1);
	WORD num_teams = 5 + ((num_groups * 5 + idx + 1) < data->special_nteams_seedings);

	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	BYTE teamsAdded = 0;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + num_groups].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + num_groups * 2].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + num_groups * 3].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + num_groups * 4].club;
	if (num_teams > 5) *((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + num_groups * 5].club;

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, num_teams, pTeams, data->n_rounds, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void world_cup_quals_caf_best_placed_update(BYTE* _this) {
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	WORD num_groups = 9 + (num_hosts == 1);
	comp_stats* data = (comp_stats*)_this;
	char stage_num = num_groups - 1;

	WORD start_date[4];
	WORD end_date[4];
	DWORD tmp1[2];
	DWORD tmp2[2];
	sub_54A110((BYTE*)start_date);
	sub_54A110((BYTE*)end_date);

	WORD year = data->year;
	BYTE* ba = (BYTE*)data->fixtures_table;
	BYTE* cm_date = new BYTE[8];
	sub_549EF0(cm_date, *(WORD*)(ba), year + *(WORD*)(ba + 2));
	sub_417C10((BYTE*)start_date, tmp1, cm_date);
	WORD a9 = *(WORD*)(_this + 0xA9);
	cm_date = new BYTE[8];
	sub_549EF0(cm_date, *(WORD*)(ba + a9 * fixture_dates_sz - fixture_dates_sz),
		year + *(WORD*)(ba + a9 * fixture_dates_sz - fixture_dates_sz + 2));
	sub_54C770(cm_date, (BYTE*)tmp1, 1);
	sub_417C10((BYTE*)end_date, tmp2, (BYTE*)tmp1);

	WORD team_idx = 0 + (num_hosts == 0);
	WORD teams_to_check = 5 + (num_hosts == 0);
	comp_stats* curr_stage = data;
	for (char al = -1; al < num_groups - 1; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		sub_6827D0((BYTE*)curr_stage, 0);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls_place = table_teams[team_idx];
		cm3_clubs* tls_club = tls_place.club;
		DWORD* pMem = (DWORD*)cm0102_malloc(4 * teams_to_check);
		for (WORD i = 0; i < teams_to_check; i++) {
			*((DWORD*)(&pMem[i])) = table_teams[i].club->ClubID;
		}
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		WORD n = data->n_teams; // always assume 6 teams
		sub_88C6D0(pStage, teams_to_check, pMem, -1, -1, start_date, end_date, data->competition_db->ClubCompID, data->pts_for_win, data->pts_for_draw, &data->tiebreaker_1, 9 * (n * (n - 1)), data->f16);
		comp_stats* stage_data = (comp_stats*)pStage;
		table_teams = (team_league_stats*)stage_data->team_league_table;
		WORD chk = 0;
		for (; chk < teams_to_check; chk++) {
			if (table_teams[chk].club == tls_club) break;
		}
		if (chk < teams_to_check) {
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

void world_cup_quals_caf_setup_best_placed(BYTE* _this) {
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	WORD num_groups = 9 + (num_hosts == 1);

	char stage_num = num_groups - 1;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 4, 0, 0 };

	if (num_hosts > 0)
	{
		prom_rel[0] = 7 + (num_hosts == 1);
		prom_rel[1] = 2;
	}

	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };
	create_league_stage_data(pStage, _this, num_groups, 0, 0, (DWORD)(data->competition_db), 0, 0,
		data->pts_for_win, data->pts_for_draw, data->f196, &tiebreaks[0], &prom_rel[0],
		year, stage_num, BestPlacedTeams, 0, 1, 0, 0x28, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	data->current_stage = stage_num;
	world_cup_quals_caf_best_placed_update(_this);
}

void world_cup_quals_caf_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = world_cup_quals_caf_vtable;
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = WORLD_CUP_CONMEBOL_QUALIFYING_9CF();
	data->relegates_to = WORLD_CUP_UEFA_QUALIFYING_9CF();
	data->rules = RulesInternational;
	data->f82 = 3;
	data->year = year - 1;
	while (data->year % 4 != 3) data->year++;
	data->f81 = 0xf;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->f217 = 0x28;
	data->current_stage = -1;
	data->num_stages = 10;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	world_cup_quals_caf_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void world_cup_quals_caf_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 26, July, data->year, -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
		if (!data->f69 && a3) {
			WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
			sub_775070((BYTE*)*b74318, get_continent(AFRICA_9CF()), 0);
			data->f69 = 1;
			world_cup_quals_caf_all_teams(_this);
			world_cup_quals_caf_setup_first_group(_this);
			sub_6835C0(_this);
			sub_6827D0(_this, 0);
			for (BYTE i = 0; i < 8 + (num_hosts == 1); i++) {
				world_cup_quals_caf_setup_groups(_this, i);
			}
			world_cup_quals_caf_setup_best_placed(_this);
			world_cup_quals_caf_reputation_setup(_this);
		}
	}
	else if ((*(WORD*)(current_date) > date_day && *(WORD*)(current_date + 2) == date_year) || *(WORD*)(current_date + 2) > date_year) {
		char ret = sub_5AE6D0((BYTE*)current_date, data->competition_db->ClubCompID);
		if (ret) world_cup_quals_caf_best_placed_update(_this);
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) world_cup_quals_caf_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_caf_init2
		add esp, 0xc
		ret 8
	}
}

int world_cup_quals_caf_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	WORD num_groups = 9 + (num_hosts == 1);
	if (stage < num_groups - 1) {
		switch (fate) {
		case Qualified1:
			if (num_hosts == 0) qualify_team_for_international_comp(club, FIFA_WORLD_CUP_9CF());
			return 0;
		case TopPlayoff:
			//staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(get_comp(WORLD_CUP_PLAYOFFS_9CF())), None, None, 0x1E);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == num_groups - 1) {
		comp_stats* stage_data = comp_data;
		switch (fate) {
		case Qualified1:
			qualify_team_for_international_comp(club, FIFA_WORLD_CUP_9CF());
			for (char al = -1; al < num_groups - 1; al++) {
				if (al >= 0) stage_data = (comp_stats*)(comp_data->stages[al]);
				team_league_stats* table_teams = (team_league_stats*)(stage_data->team_league_table);
				if (table_teams[0].club == club) {
					stage_data->promotions = 1;
					stage_data->prom_playoff = 0;
					table_teams[0].league_fate = Qualified1;
					break;
				}
			}
			return 0;
		case TopPlayoff:
			if (num_hosts == 0)
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SecondRound, 0x1E);
			else
				add_team_to_world_cup_playoffs(club);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			for (char al = -1; al < num_groups - 1; al++) {
				if (al >= 0) stage_data = (comp_stats*)(comp_data->stages[al]);
				team_league_stats* table_teams = (team_league_stats*)(stage_data->team_league_table);
				if (table_teams[1].club == club) {
					stage_data->prom_playoff = 0;
					table_teams[1].league_fate = Eliminated;
					break;
				}
			}
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == num_groups) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			add_team_to_world_cup_playoffs(club);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) world_cup_quals_caf_table_fates_c()
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
		call world_cup_quals_caf_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

int world_cup_quals_caf_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	// This condition breaks aftr the World Cup resets
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	if (stage_name_idx == BestPlacedTeams) {
		if (fate == Qualified1)
		{
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, 0xAD4D6C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, 0xAD4B78, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == TopPlayoff) {
			if (num_hosts > 0) {
				if (show_body_text) {
					sub_66F4E0(0xDE1F64, (DWORD)&qualified_wc_playoff_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					return 1;
				}
				else {
					sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					return 1;
				}
			}
			else
			{
				if (show_body_text) {
					sub_66F4E0(0xDE1F64, 0x98AC50, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
						&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
					return 1;
				}
				else {
					sub_66F4E0(0xDE1F64, 0x98AC50, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
						&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
					return 1;
				}
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_name_idx == SecondRound) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
	}
	else if (stage_id < 9) {
		if (fate == Qualified1)
		{
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, 0xAD4D6C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, 0xAD4B78, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == TopPlayoff) {
			//sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			//sub_4AE660(ret_str_ptr, 0xDE1F64);
			//sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			return 1;
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	return 0;
}

void __declspec(naked) world_cup_quals_caf_stage_news_c()
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
		call world_cup_quals_caf_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void world_cup_quals_caf_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if ((main_stage_id >= 0x41f && main_stage_id <= 0x42e) || main_stage_id == 0x3fc) { // First Round
		if (fate == Qualified1) {
			sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else if (fate == TopPlayoff) {
			sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, 0x99B800);
			return;
		}
	}
	if (main_stage_id == BestPlacedTeams) {
		sub_66F4E0(dest_ptr, 0x9A7C04);
		return;
	}
	if (main_stage_id == SecondRound && sub_stage_id == SecondStage)
	{
		if (fate == 1)
		{
			sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) world_cup_quals_caf_landmarks_c()
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
		call world_cup_quals_caf_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

WORD world_cup_quals_caf_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);

	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	WORD cutoff1 = 10 - num_hosts + 1;
	WORD cutoff2 = cutoff1 + 1 + (num_hosts > 0);
	if (val < cutoff1) return -3;
	else return -5;
}

void __declspec(naked) world_cup_quals_caf_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_caf_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE world_cup_quals_caf_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	WORD cutoff1 = 10 - num_hosts + 1;
	WORD cutoff2 = cutoff1 + 1 + (num_hosts > 0);
	if (al < cutoff1)
	{
		if (bl < cutoff1) return 1;
		else return (bl < cutoff2) - 1;
	}
	else if (al < cutoff2)
	{
		if (bl < cutoff1) return 1;
		else return (bl < cutoff2) - 1;
	}
	else return (bl < cutoff2) - 1;
}

void __declspec(naked) world_cup_quals_caf_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_caf_vtable30
		add esp, 0x8
		ret 4
	}
}

void world_cup_quals_caf_final_stage_setup(BYTE* _this) {
	char stage_num = 9;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = (comp_stats*)(comp_data->stages[stage_num - 1]);
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 4; al++) clubs.push_back(table_teams[al].club);

	BYTE team_order[4] = { 0,2,3,1 };
	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
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

void world_cup_quals_caf_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), AFRICA_9CF(), 0, 0);
	if (num_hosts == 0) {
		if (current < max - 1) {
			current++;
			comp_data->current_stage = current;
			if (current == 9) {
				world_cup_quals_caf_final_stage_setup(_this);
			}
		}
	}
}

void __declspec(naked) world_cup_quals_caf_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_caf_stages_create
		add esp, 0x4
		ret
	}
}

void setup_world_cup_quals_caf() {
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableInitFree, (DWORD)&world_cup_quals_caf_free_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableEoSUpdate, (DWORD)&world_cup_quals_caf_update_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableLeagueSplit, (DWORD)&world_cup_quals_caf_init2_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableTableFates, (DWORD)&world_cup_quals_caf_table_fates_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableFixtures, (DWORD)&world_cup_quals_caf_fixture_caller);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableStageNews, (DWORD)&world_cup_quals_caf_stage_news_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable29, (DWORD)&world_cup_quals_caf_vtable29_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable30, (DWORD)&world_cup_quals_caf_vtable30_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableClubLandmarks, (DWORD)&world_cup_quals_caf_landmarks_c);

	WriteVTablePtr(world_cup_quals_caf_vtable, VTableLoadCompInfo, 0x48CEB0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableSaveCompInfo, 0x48CEA0);

	WriteVTablePtr(world_cup_quals_caf_vtable, VTableSubsRounds, (DWORD)&world_cup_quals_caf_subs_c);

	WriteVTablePtr(world_cup_quals_caf_vtable, VTablePostMatchUpdate, 0x685d30);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable5, 0x689ad0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable7, 0x687b10);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable8, 0x6891c0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTablePlayoffQual, (DWORD)&world_cup_quals_caf_stages_create_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable14, 0x583470);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable17, 0x686670);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable22, 0x68a3e0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableReputationSetup, (DWORD)&world_cup_quals_caf_reputation_setup_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableReputationCalc, (DWORD)&world_cup_quals_caf_reputation_calc_c);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable33, 0x68abd0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable34, 0x68ac40);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable37, 0x68aad0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable38, 0x684cd0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable39, 0x684790);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable40, 0x6847b0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableAwardTeamsSetup, 0x687a20);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTableUpdateLastDivision, 0x68aa30);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable43, 0x4011e0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTable44, 0x4011f0);
	WriteVTablePtr(world_cup_quals_caf_vtable, VTablePromRelUpdate, 0x689c20);
}