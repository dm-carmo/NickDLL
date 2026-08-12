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

DWORD* world_cup_quals_uefa_vtable = (DWORD*)0x970CC4;

void world_cup_quals_uefa_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = world_cup_quals_uefa_vtable;
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

void world_cup_quals_uefa_free(BYTE* _this, BYTE a2) {
	world_cup_quals_uefa_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) world_cup_quals_uefa_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_uefa_free
		add esp, 0x8
		ret 4
	}
}

void world_cup_quals_uefa_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f67 = 2;
	comp_data->f196 = 10;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_4 = GoalsForAwayTiebreaker;
	comp_data->promotions = 2;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	*((DWORD*)(_this + 0xA7)) = -1;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) world_cup_quals_uefa_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_uefa_subs
		add esp, 0x4
		ret
	}
}

DWORD world_cup_quals_uefa_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);
	if (stage_idx < 8) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 6;
		*num_rounds = 5;
		if (stage_idx < 5) *stage_name_id = LeagueA1to6 + stage_idx + 1;
		else *stage_name_id = LeagueB1to4 + stage_idx - 5;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 4), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 9), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 9), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 14), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 16), year, Thursday, Afternoon);
		//AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 21), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	// playoff
	else if (stage_idx == 9) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 2 - (num_hosts == 1);
		*stage_name_id = Playoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		WORD total_teams = 10;
		if (num_hosts == 1) total_teams = 6;
		else if (num_hosts == 2) total_teams = 8;
		WORD teams_r1 = 4 + 2 * num_hosts;
		WORD teams_r2 = total_teams - teams_r1 / 2;

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 22), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 24), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, num_hosts == 1 ? Final : SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 10, teams_r1, teams_r1 / 2, teams_r1, 0, 0, 1 + (num_hosts == 1), 5);

		if (num_hosts != 1) {
			AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 25), year, Friday);
			AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 29), year, Tuesday, Afternoon);
			FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup3 + ExtraTimePenalties_1, NoTiebreak_2, 10, teams_r2, teams_r2 / 2, total_teams - teams_r1, teams_r1 * (total_teams != teams_r1), 0, 1, 0);
		}

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) world_cup_quals_uefa_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_uefa_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char world_cup_quals_uefa_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	*((DWORD*)(_this + 0xA7)) = -1;
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
	world_cup_quals_uefa_subs(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) world_cup_quals_uefa_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_uefa_update
		add esp, 0x4
		ret
	}
}

void world_cup_quals_uefa_reputation_setup(BYTE* _this) {
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

		for (int i = 0; i < 6; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 1);
		}
		for (int i = 6; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 7);
		}
		for (int i = 12; i < 18; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (int i = 18; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19 + 3);
		}
		for (int i = 24; i < 30; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25 + 6);
		}
		for (int i = 30; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 31 + 9);
		}

		for (int i = 36; i < 39; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (int i = 39; i < 42; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19 + 3);
		}
		for (int i = 42; i < 45; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25 + 6);
		}
		for (int i = 45; i < 48; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 31 + 9);
		}
		for (int i = 48; i < 51; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 49);
		}
		for (WORD i = 51; i < comp_data->special_nteams_seedings; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 52);
		}
		for (WORD i = 0; i < comp_data->special_nteams_seedings; i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) world_cup_quals_uefa_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_uefa_reputation_setup
		add esp, 0x4
		ret
	}
}

void world_cup_quals_uefa_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;

	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);

	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 5) {
		ret_current = 1 + 6 * (current - 1);
		if (current > 3) ret_current += 3 * (current - 3);
		ret_min = 1 + 6 * (min - 1);
		if (min > 3) ret_min += 3 * (min - 3);
		ret_max = 1 + 6 * (max - 1);
		if (max > 3) ret_max += 3 * (max - 3);
	}
	else if (stage < 8) {
		ret_current = 6 * (current + 1) + 1 + 3 * (current - 1);
		ret_min = 6 * (min + 1) + 1 + 3 * (min - 1);
		ret_max = 6 * (max + 1) + 1 + 3 * (max - 1);
	}
	else if (stage == 8) {
		char offset = 1;
		if (num_hosts == 1) offset = 3;
		if (num_hosts == 2) offset = 2;
		if (current < offset + 1) ret_current = 12;
		else ret_current = 16 - num_hosts + current;
		if (min < offset + 1) ret_min = 12;
		else ret_min = 16 - num_hosts + min;
		if (max < offset + 1) ret_max = 16 - num_hosts;
		else ret_max = 16 - num_hosts + max;
	}
	else if (stage == 9) {
		ret_current = current + 12;
		ret_min = min + 12;
		ret_max = max + 12;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) world_cup_quals_uefa_reputation_calc_c()
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
		call world_cup_quals_uefa_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void world_cup_quals_uefa_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	vector<cm3_clubs*> countries = get_national_teams_of_continent_fifa_members(EUROPE_9CF());
	sort(countries.begin(), countries.end(), compareNationRanking);

	DWORD host1_id, host2_id;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), &host1_id, &host2_id);
	WORD total_teams_in_comp = (WORD)countries.size() - num_hosts;
	total_teams_in_comp--; // subtract Russia
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	shuffle(countries.begin(), countries.begin() + 6, rng);
	shuffle(countries.begin() + 6, countries.begin() + 12, rng);
	shuffle(countries.begin() + 12, countries.begin() + 18, rng);
	shuffle(countries.begin() + 18, countries.begin() + 24, rng);
	shuffle(countries.begin() + 24, countries.begin() + 30, rng);
	shuffle(countries.begin() + 30, countries.begin() + 36, rng);
	shuffle(countries.begin() + 36, countries.begin() + 39, rng);
	shuffle(countries.begin() + 39, countries.begin() + 42, rng);
	shuffle(countries.begin() + 42, countries.begin() + 45, rng);
	shuffle(countries.begin() + 45, countries.begin() + 48, rng);
	shuffle(countries.begin() + 48, countries.begin() + 51, rng);
	shuffle(countries.begin() + 51, countries.end(), rng);

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	for (BYTE i = 0, j = 0; i < countries.size() && j < total_teams_in_comp; i++) {
		if (countries[i]->ClubNation->NationID == host1_id || countries[i]->ClubNation->NationID == host2_id) continue;
		if (countries[i]->ClubNation->NationID == NATION_RUSSIA_9CF()) continue; // review Russia ban at a later date
		teams[j].club = countries[i];
		if (j < 36) teams[j].f5 = 10;
		else teams[j].f5 = 11;
		teams[j].f6 = 0;
		j++;
	}
}

void world_cup_quals_uefa_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 6;
	BYTE* pMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;

	BYTE teamsAdded = 0;
	add_team_call(_this, teamsAdded++, qualifiers[0].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[6].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[12].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[18].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[24].club, 0, 0);
	add_team_call(_this, teamsAdded++, qualifiers[30].club, 0, 0);
	sub_684230(_this);
}

void world_cup_quals_uefa_setup_groups_a(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD num_teams = 6;

	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	BYTE teamsAdded = 0;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + 6].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + 12].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + 18].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + 24].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[idx + 1 + 30].club;

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, num_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void world_cup_quals_uefa_setup_groups_b(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);
	WORD num_teams = 6;
	WORD rem = data->special_nteams_seedings % 3;
	if (rem > 0) num_teams = 6 - ((idx - 5) >= rem);

	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	BYTE teamsAdded = 0;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[36 + idx - 5].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[36 + idx - 5 + 3].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[36 + idx - 5 + 6].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[36 + idx - 5 + 9].club;
	*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[36 + idx - 5 + 12].club;
	if (num_teams > 5) *((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)qualifiers[36 + idx - 5 + 15].club;

	char prom_rel[4] = { 1, 1, 0, 0 };
	if (num_hosts == 1) prom_rel[0] = 0;
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, num_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void world_cup_quals_uefa_best_placed_update(BYTE* _this) {
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);
	char start = 5;
	if (num_hosts == 1) start = -1;
	char end = 8;
	if (num_hosts == 1) end = 5;
	comp_stats* data = (comp_stats*)_this;
	char stage_num = 8;

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

	WORD team_idx = (num_hosts + 1) % 3;
	WORD teams_to_check = 6;
	if (start != -1) teams_to_check = 6 - (data->special_nteams_seedings % 3 > 0);
	comp_stats* curr_stage = data;
	for (char al = start; al < end; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		sub_6827D0((BYTE*)curr_stage, 0);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls_place = table_teams[team_idx];
		cm3_clubs* tls_club = tls_place.club;
		DWORD* pMem = (DWORD*)cm0102_malloc(4 * teams_to_check);
		for (WORD i = 0; i < curr_stage->n_teams; i++) {
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
			memcpy(&best_placed_table[al - start], &table_teams[chk], league_team_list_sz);
			best_placed_table[al - start].position_history = 0;
			best_placed_table[al - start].f4 = 0;
		}
		DWORD v1 = *(DWORD*)pStage;
		(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)pStage, 1);
		sub_9452CA_free((BYTE*)(pMem));
	}
	sub_6827D0((BYTE*)data->stages[stage_num], 0);
}

void world_cup_quals_uefa_setup_best_placed(BYTE* _this) {
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);
	WORD num_teams = 3;
	if (num_hosts == 1) num_teams = 6;

	char stage_num = 8;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 1, 0, 0 };
	if (num_hosts == 1) prom_rel[1] = 3;
	if (num_hosts == 2) prom_rel[1] = 2;

	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };
	create_league_stage_data(pStage, _this, num_teams, 0, 0, (DWORD)(data->competition_db), 0, 0,
		data->pts_for_win, data->pts_for_draw, data->f196, &tiebreaks[0], &prom_rel[0],
		year, stage_num, BestPlacedTeams, 0, 1, 0, 0x28, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	data->current_stage = stage_num;
	world_cup_quals_uefa_best_placed_update(_this);
}

void world_cup_quals_uefa_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = world_cup_quals_uefa_vtable;
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = WORLD_CUP_CAF_QUALIFYING_9CF();
	data->relegates_to = -1;
	data->rules = RulesInternational;
	data->f82 = 3;
	data->year = year + 1;
	while (data->year % 4 != 1) data->year++;
	data->f81 = 0xf;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->f217 = 0x28;
	data->current_stage = -1;
	data->num_stages = 10;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	world_cup_quals_uefa_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void world_cup_quals_uefa_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 26, July, data->year, -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
		if (!data->f69 && a3) {
			sub_775070((BYTE*)*b74318, get_continent(EUROPE_9CF()), 0);
			data->f69 = 1;
			world_cup_quals_uefa_all_teams(_this);
			world_cup_quals_uefa_setup_first_group(_this);
			sub_6835C0(_this);
			sub_6827D0(_this, 0);
			for (BYTE i = 0; i < 5; i++) {
				world_cup_quals_uefa_setup_groups_a(_this, i);
			}
			for (BYTE i = 0; i < 3; i++) {
				world_cup_quals_uefa_setup_groups_b(_this, i + 5);
			}
			world_cup_quals_uefa_setup_best_placed(_this);
			world_cup_quals_uefa_reputation_setup(_this);
		}
	}
	else if ((*(WORD*)(current_date) > date_day && *(WORD*)(current_date + 2) == date_year) || *(WORD*)(current_date + 2) > date_year) {
		char ret = sub_5AE6D0((BYTE*)current_date, data->competition_db->ClubCompID);
		if (ret) world_cup_quals_uefa_best_placed_update(_this);
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) world_cup_quals_uefa_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_uefa_init2
		add esp, 0xc
		ret 8
	}
}

int world_cup_quals_uefa_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* world_cup_bytes = get_loaded_league(FIFA_WORLD_CUP_9CF());
	comp_stats* world_cup_data = (comp_stats*)world_cup_bytes;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);
	if (stage < 5) {
		switch (fate) {
		case Qualified1:
			add_team_to_world_cup(club);
			return 0;
		case TopPlayoff:
			if (num_hosts != 1) staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), Playoff, None, 0x1E);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage < 8) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), Playoff, None, 0x1E);
			return 0;
		case TopPlayoff:
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 8) {
		comp_stats* stage_data = comp_data;
		char start = 5;
		if (num_hosts == 1) start = -1;
		char end = 8;
		if (num_hosts == 1) end = 5;
		WORD team_idx = (num_hosts + 1) % 3;
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), Playoff, None, 0x1E);
			break;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			for (char al = start; al < end; al++) {
				if (al >= 0) stage_data = (comp_stats*)(comp_data->stages[al]);
				team_league_stats* table_teams = (team_league_stats*)(stage_data->team_league_table);
				if (table_teams[team_idx].club == club) {
					stage_data->prom_playoff = 0;
					table_teams[team_idx].league_fate = Eliminated;
					break;
				}
			}
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 9) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			add_team_to_world_cup(club, num_hosts == 1);
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

void __declspec(naked) world_cup_quals_uefa_set_table_fate()
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
		call world_cup_quals_uefa_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int world_cup_quals_uefa_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);
	if (stage_id < 5) {
		if (fate == Qualified1)
		{
			if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
			else {
				sub_66F4E0(0xDE1F64, 0xAD4B78, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == TopPlayoff) {
			if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
			else if (num_hosts != 1) {
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			else return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 8) {
		if (fate == Qualified1)
		{
			if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
			else {
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == TopPlayoff) {
			//sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			//sub_4AE660(ret_str_ptr, 0xDE1F64);
			//sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			//return 1;
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 8) {
		if (fate == TopPlayoff) {
			if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
			else {
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 9) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0xAD4B78, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
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
	return 0;
}

void __declspec(naked) world_cup_quals_uefa_stage_news_c()
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
		call world_cup_quals_uefa_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void world_cup_quals_uefa_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);
	if (main_stage_id >= 0x475 && main_stage_id <= 0x47a) { // League A
		if (fate == Qualified1) {
			sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else if (fate == TopPlayoff) {
			if (num_hosts != 1) {
				sub_66F4E0(dest_ptr, 0x9a4399);
				return;
			}
		}
		else {
			sub_66F4E0(dest_ptr, (DWORD)&lge_a[0]);
			return;
		}
	}
	if (main_stage_id >= 0x459 && main_stage_id <= 0x45c) { // League B
		if (fate == Qualified1) {
			sub_66F4E0(dest_ptr, 0x9a4399);
			return;
		}
		else if (fate == TopPlayoff) {
		}
		else {
			sub_66F4E0(dest_ptr, (DWORD)&lge_b[0]);
			return;
		}
	}
	if (main_stage_id == BestPlacedTeams) {
		if (fate == TopPlayoff) {
			sub_66F4E0(dest_ptr, 0x9a4399);
			return;
		}
	}
	if (main_stage_id == Playoff)
	{
		if (fate == 1)
		{
			sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) world_cup_quals_uefa_landmarks_c()
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
		call world_cup_quals_uefa_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

WORD world_cup_quals_uefa_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	return (val < 16) - 3;
}

void __declspec(naked) world_cup_quals_uefa_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_uefa_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE world_cup_quals_uefa_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	if (al < 16) return (bl < 16) - 1;
	else return (bl < 16);
}

void __declspec(naked) world_cup_quals_uefa_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_uefa_vtable30
		add esp, 0x8
		ret 4
	}
}

void world_cup_quals_uefa_final_stage_setup(BYTE* _this) {
	char stage_num = 9;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, EUROPE_9CF(), 0, 0);

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 10;
	if (num_hosts == 1) playoff_teams = 6;
	else if (num_hosts == 2) playoff_teams = 8;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 8; al++)
	{
		if (al >= 0) curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
			else if (tls.league_fate == Qualified1 && al > 4) {
				clubs.push_back(tls.club);
			}
		}
	}
	if (clubs.size() != playoff_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size()) + ", should be " + to_string(playoff_teams);
		create_message_box("Error", msg.c_str(), true);
	}

	reverse(clubs.begin(), clubs.end());
	shuffle(clubs.begin(), clubs.begin() + 4 - num_hosts, rng);
	shuffle(clubs.begin() + 4 - num_hosts, clubs.end(), rng);
	BYTE team_order[10] = { 0 };
	if (num_hosts == 0) {
		team_order[0] = 0;
		team_order[1] = 2;
		team_order[2] = 3;
		team_order[3] = 1;
		team_order[4] = 4;
		team_order[5] = 6;
		team_order[6] = 8;
		team_order[7] = 9;
		team_order[8] = 7;
		team_order[9] = 5;
	}
	else if (num_hosts == 1) {
		team_order[0] = 0;
		team_order[1] = 2;
		team_order[2] = 4;
		team_order[3] = 5;
		team_order[4] = 3;
		team_order[5] = 1;
	}
	else if (num_hosts == 2) {
		team_order[0] = 0;
		team_order[1] = 2;
		team_order[2] = 4;
		team_order[3] = 6;
		team_order[4] = 7;
		team_order[5] = 5;
		team_order[6] = 3;
		team_order[7] = 1;
	}

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
	comp_data->current_stage = (long)stage_num;
}

void world_cup_quals_uefa_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 9) {
			world_cup_quals_uefa_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) world_cup_quals_uefa_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_uefa_stages_create
		add esp, 0x4
		ret
	}
}

char* grp_c3_short = "Grp C3";
void __declspec(naked) jmp_shortname_c3()
{
	__asm
	{
		push grp_c3_short
		push ebx
		push call_ret
		push 0x66f4e0
		ret
		call_ret :
		add esp, 0x8
			mov eax, ebx
			pop edi
			pop esi
			pop ebx
			add esp, 0x200
			ret
	}
}

char* grp_c4_short = "Grp C4";
void __declspec(naked) jmp_shortname_c4()
{
	__asm
	{
		push grp_c4_short
		push ebx
		push call_ret
		push 0x66f4e0
		ret
		call_ret :
		add esp, 0x8
			mov eax, ebx
			pop edi
			pop esi
			pop ebx
			add esp, 0x200
			ret
	}
}

void setup_world_cup_quals_uefa() {
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableInitFree, (DWORD)&world_cup_quals_uefa_free_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableEoSUpdate, (DWORD)&world_cup_quals_uefa_update_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableLeagueSplit, (DWORD)&world_cup_quals_uefa_init2_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableTableFates, (DWORD)&world_cup_quals_uefa_set_table_fate);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableFixtures, (DWORD)&world_cup_quals_uefa_fixture_caller);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableStageNews, (DWORD)&world_cup_quals_uefa_stage_news_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTable29, (DWORD)&world_cup_quals_uefa_vtable29_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTable30, (DWORD)&world_cup_quals_uefa_vtable30_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableClubLandmarks, (DWORD)&world_cup_quals_uefa_landmarks_c);

	WriteVTablePtr(world_cup_quals_uefa_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTable10, 0x48CEA0);

	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableSubsRounds, (DWORD)&world_cup_quals_uefa_subs_c);

	WriteVTablePtr(world_cup_quals_uefa_vtable, VTablePostMatchUpdate, 0x685d30); // check?
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTablePlayoffQual, (DWORD)&world_cup_quals_uefa_stages_create_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableReputationSetup, (DWORD)&world_cup_quals_uefa_reputation_setup_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTableReputationCalc, (DWORD)&world_cup_quals_uefa_reputation_calc_c);
	WriteVTablePtr(world_cup_quals_uefa_vtable, VTable38, 0x684cd0); // check?

	WriteDWORD(0x4B5fde + 1, (DWORD)&lge_a[0]);
	WriteDWORD(0x4B5ff8 + 1, (DWORD)&lge_b[0]);
	WriteDWORD(0x4B6438 + 1, (DWORD)&lge_c[0]);
	WriteDWORD(0x4B6452 + 1, (DWORD)&lge_d[0]);
	WriteDWORD(0x4B8ae5 + 1, (DWORD)&lge_a_short[0]);
	WriteDWORD(0x4B8aff + 1, (DWORD)&lge_b_short[0]);
	WriteDWORD(0x4B8f25 + 1, (DWORD)&lge_c_short[0]);
	WriteDWORD(0x4B8f3f + 1, (DWORD)&lge_d_short[0]);

	char* grp_a1 = "Group A1";
	char* grp_a2 = "Group A2";
	char* grp_a3 = "Group A3";
	char* grp_a4 = "Group A4";
	char* grp_a5 = "Group A5";
	char* grp_a6 = "Group A6";
	char* grp_a1_short = "Grp A1";
	char* grp_a2_short = "Grp A2";
	char* grp_a3_short = "Grp A3";
	char* grp_a4_short = "Grp A4";
	char* grp_a5_short = "Grp A5";
	char* grp_a6_short = "Grp A6";
	WriteDWORD(0x4B67e5 + 1, (DWORD)&grp_a1[0]);
	WriteDWORD(0x4B67ff + 1, (DWORD)&grp_a2[0]);
	WriteDWORD(0x4B6819 + 1, (DWORD)&grp_a3[0]);
	WriteDWORD(0x4B6833 + 1, (DWORD)&grp_a4[0]);
	WriteDWORD(0x4B684d + 1, (DWORD)&grp_a5[0]);
	WriteDWORD(0x4B6867 + 1, (DWORD)&grp_a6[0]);
	WriteDWORD(0x4B9337 + 1, (DWORD)&grp_a1_short[0]);
	WriteDWORD(0x4B9351 + 1, (DWORD)&grp_a2_short[0]);
	WriteDWORD(0x4B936b + 1, (DWORD)&grp_a3_short[0]);
	WriteDWORD(0x4B9385 + 1, (DWORD)&grp_a4_short[0]);
	WriteDWORD(0x4B939f + 1, (DWORD)&grp_a5_short[0]);
	WriteDWORD(0x4B93b9 + 1, (DWORD)&grp_a6_short[0]);

	char* grp_b1 = "Group B1";
	char* grp_b2 = "Group B2";
	char* grp_b3 = "Group B3";
	char* grp_b4 = "Group B4";
	char* grp_b1_short = "Grp B1";
	char* grp_b2_short = "Grp B2";
	char* grp_b3_short = "Grp B3";
	char* grp_b4_short = "Grp B4";
	WriteDWORD(0x4B6611 + 1, (DWORD)&grp_b1[0]);
	WriteDWORD(0x4B662b + 1, (DWORD)&grp_b2[0]);
	WriteDWORD(0x4B6645 + 1, (DWORD)&grp_b3[0]);
	WriteDWORD(0x4B665f + 1, (DWORD)&grp_b4[0]);
	WriteDWORD(0x4B90fd + 1, (DWORD)&grp_b1_short[0]);
	WriteDWORD(0x4B911c + 1, (DWORD)&grp_b2_short[0]);
	WriteDWORD(0x4B913b + 1, (DWORD)&grp_b3_short[0]);
	WriteDWORD(0x4B915a + 1, (DWORD)&grp_b4_short[0]);

	char* grp_c1 = "Group C1";
	char* grp_c2 = "Group C2";
	char* grp_c3 = "Group C3";
	char* grp_c4 = "Group C4";
	char* grp_c1_short = "Grp C1";
	char* grp_c2_short = "Grp C2";
	WriteDWORD(0x4B5e4f + 1, (DWORD)&grp_c1[0]);
	WriteDWORD(0x4B5e69 + 1, (DWORD)&grp_c2[0]);
	WriteDWORD(0x4B5e83 + 1, (DWORD)&grp_c3[0]);
	WriteDWORD(0x4B5e9d + 1, (DWORD)&grp_c4[0]);
	WriteDWORD(0x4B899a + 1, (DWORD)&grp_c1_short[0]);
	WriteDWORD(0x4B89a4 + 1, (DWORD)&grp_c2_short[0]);
	WriteDWORD(0x4ba720, (DWORD)&jmp_shortname_c3); // the switch table
	WriteDWORD(0x4ba724, (DWORD)&jmp_shortname_c4); // the switch table

	char* grp_d1 = "Group D1";
	char* grp_d2 = "Group D2";
	char* grp_d1_short = "Grp D1";
	char* grp_d2_short = "Grp D2";
	WriteDWORD(0x4B67b1 + 1, (DWORD)&grp_d1[0]);
	WriteDWORD(0x4B67cb + 1, (DWORD)&grp_d2[0]);
	WriteDWORD(0x4B9303 + 1, (DWORD)&grp_d1_short[0]);
	WriteDWORD(0x4B931d + 1, (DWORD)&grp_d2_short[0]);
}