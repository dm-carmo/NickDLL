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

DWORD* world_cup_quals_concacaf_vtable = (DWORD*)0x970C24;

void world_cup_quals_concacaf_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = world_cup_quals_concacaf_vtable;
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

void world_cup_quals_concacaf_free(BYTE* _this, BYTE a2) {
	world_cup_quals_concacaf_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) world_cup_quals_concacaf_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_concacaf_free
		add esp, 0x8
		ret 4
	}
}

DWORD world_cup_quals_concacaf_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 1), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 7), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 10, 22 - num_hosts * 2, 11 - num_hosts, 22 - num_hosts * 2, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	else if (stage_idx < 6) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 6;
		*stage_name_id = SecondRoundAlphabeticGroup + stage_idx;
		if (stage_idx == 5) *stage_name_id = SecondRoundGroupF;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 12), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 17), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 16), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 21), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 26), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	else if (stage_idx < 9) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 6;
		*stage_name_id = ThirdRoundAlphabeticGroup + stage_idx - 6;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 6), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 11), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 9, 4), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 9, 9), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 10, 9), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 10, 14), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	else if (stage_idx == 10) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 2, 10, 15), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 2, 11, 13), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 10, 2 + 2 * (num_hosts == 1), 1 + (num_hosts == 1), 2 + 2 * (num_hosts == 1), 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) world_cup_quals_concacaf_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_concacaf_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char world_cup_quals_concacaf_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
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
	data->num_stages = 11;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	if (data->year < *current_year) data->year += 4;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) world_cup_quals_concacaf_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_concacaf_update
		add esp, 0x4
		ret
	}
}

void world_cup_quals_concacaf_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	vector<cm3_clubs*> countries = get_national_teams_of_continent(NORTH_AMERICA_9CF());
	sort(countries.begin(), countries.end(), compareNationRanking);

	DWORD host1_id, host2_id;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), &host1_id, &host2_id);
	if (num_hosts == 2) data->num_stages--;
	WORD total_teams_in_comp = (WORD)countries.size() - num_hosts;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	for (WORD i = 0, j = 0; i < countries.size() && j < total_teams_in_comp; i++) {
		if (countries[i]->ClubNation->NationID == host1_id || countries[i]->ClubNation->NationID == host2_id) continue;
		teams[j].club = countries[i];
		if (j < 13 + num_hosts) teams[j].f5 = 10;
		else teams[j].f5 = 11;
		teams[j].f6 = 0;
		j++;
	}
}

void world_cup_quals_concacaf_qualifier_teams(BYTE* _this) {
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 22 - 2 * num_hosts;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

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

	WORD year = data->year;
	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	for (WORD i = 0; i < total_teams; i++) {
		cm3_clubs* club = qualifiers[13 + num_hosts + i].club;
		teams[i].club = club;
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
}

void world_cup_quals_concacaf_reputation_setup(BYTE* _this) {
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

		for (DWORD i = 0; i < 3; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 1);
		}
		for (DWORD i = 3; i < 6; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 4);
		}
		for (DWORD i = 6; i < 9; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 7);
		}
		for (DWORD i = 9; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 10);
		}
		for (DWORD i = 12; i < 18; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (DWORD i = 18; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19);
		}
		for (DWORD i = 24; i < clubs.size(); i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
		for (WORD i = 0; i < clubs.size(); i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) world_cup_quals_concacaf_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_concacaf_reputation_setup
		add esp, 0x4
		ret
	}
}

void world_cup_quals_concacaf_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = 13 + num_hosts + current;
		if (ret_min != 1) ret_min = 13 + num_hosts + min;
		ret_max = 13 + num_hosts + max;
	}
	else if (stage < 6) {
		ret_current = 1 + 6 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 6 * (min - 1);
		if (max < 3) ret_max = 10;
		else ret_max = 1 + 6 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage < 9) {
		ret_current = 1 + 3 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 3 * (min - 1);
		if (max < 3) ret_max = max;
		else ret_max = 1 + 3 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 9) {
		ret_current = 4 + current;
		ret_min = 4 + min;
		ret_max = 4 + max;
	}
	else if (stage == 10) {
		ret_current = current + 7;
		ret_min = min + 7;
		ret_max = max + 7;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) world_cup_quals_concacaf_reputation_calc_c()
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
		call world_cup_quals_concacaf_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void world_cup_quals_concacaf_best_placed_update(BYTE* _this) {
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);

	comp_stats* data = (comp_stats*)_this;
	BYTE* first_group_bytes = (BYTE*)data->stages[6];
	comp_stats* first_group_data = (comp_stats*)first_group_bytes;
	char stage_num = 9;

	WORD start_date[4];
	WORD end_date[4];
	DWORD tmp1[2];
	DWORD tmp2[2];
	sub_54A110((BYTE*)start_date);
	sub_54A110((BYTE*)end_date);

	WORD year = data->year;
	BYTE* ba = (BYTE*)first_group_data->fixtures_table;
	BYTE* cm_date = new BYTE[8];
	sub_549EF0(cm_date, *(WORD*)(ba), year + *(WORD*)(ba + 2));
	sub_417C10((BYTE*)start_date, tmp1, cm_date);
	WORD a9 = *(WORD*)(first_group_bytes + 0xA9);
	cm_date = new BYTE[8];
	sub_549EF0(cm_date, *(WORD*)(ba + a9 * fixture_dates_sz - fixture_dates_sz),
		year + *(WORD*)(ba + a9 * fixture_dates_sz - fixture_dates_sz + 2));
	sub_54C770(cm_date, (BYTE*)tmp1, 1);
	sub_417C10((BYTE*)end_date, tmp2, (BYTE*)tmp1);

	WORD team_idx = 1 + (num_hosts == 0);
	for (char al = 6; al < 9; al++) {
		comp_stats* curr_stage = (comp_stats*)(data->stages[al]);
		WORD num_teams = curr_stage->n_teams;
		sub_6827D0((BYTE*)curr_stage, 0);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls_place = table_teams[team_idx];
		cm3_clubs* tls_club = tls_place.club;
		DWORD* pMem = (DWORD*)sub_944E46_malloc(4 * num_teams);
		for (WORD i = 0; i < num_teams; i++) {
			*((DWORD*)(&pMem[i])) = table_teams[i].club->ClubID;
		}
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		sub_88C6D0(pStage, num_teams, pMem, -1, -1, start_date, end_date, data->competition_db->ClubCompID, 3, 1, (BYTE*)(first_group_bytes + 0xC5), 9 * (num_teams * (num_teams - 1)), data->f16);
		comp_stats* stage_data = (comp_stats*)pStage;
		table_teams = (team_league_stats*)stage_data->team_league_table;
		WORD chk = 0;
		for (; chk < num_teams; chk++) {
			if (table_teams[chk].club == tls_club) break;
		}
		if (chk < num_teams) {
			comp_stats* best_placed_stage = (comp_stats*)(data->stages[stage_num]);
			team_league_stats* best_placed_table = (team_league_stats*)(best_placed_stage->team_league_table);
			memcpy(&best_placed_table[al - 6], &table_teams[chk], league_team_list_sz);
			best_placed_table[al - 6].position_history = 0;
			best_placed_table[al - 6].f4 = 0;
		}
		DWORD v1 = *(DWORD*)pStage;
		(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)pStage, 1);
		sub_9452CA_free((BYTE*)(pMem));
	}
	sub_6827D0((BYTE*)data->stages[stage_num], 0);
}

void world_cup_quals_concacaf_setup_best_placed(BYTE* _this) {
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);
	char stage_num = 9;

	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	BYTE prom_rel[4] = { 0, 2, 0, 0 };

	if (num_hosts == 1)
	{
		prom_rel[0] = 2;
		prom_rel[1] = 1;
	}
	else if (num_hosts == 2)
	{
		prom_rel[0] = 1;
		prom_rel[1] = 0;
		prom_rel[2] = 2;
	}

	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };
	create_league_stage_data(pStage, _this, 3, 0, 0, (DWORD)(data->competition_db), 0, 0, 3, 1, 10, &tiebreaks[0], &prom_rel[0],
		year, stage_num, BestPlacedTeams, 0, 1, 0, 0x28, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	data->current_stage = stage_num;
	world_cup_quals_concacaf_best_placed_update(_this);
}

void world_cup_quals_concacaf_second_stage_setup(BYTE* _this) {
	char stage_num = 0;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 0, 0, 0 };
	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, CurrentPositionTiebreaker, GoalsForAwayTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (int i = 0; i < 13 + num_hosts; i++) clubs.push_back(teams[i].club);
	teams = (teams_seeded*)comp_data->teams_list;
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		if (teams[i].f6 == 1) clubs.push_back(teams[i].club);
	}

	sort(clubs.begin(), clubs.end(), compareNationRanking);
	shuffle(clubs.begin(), clubs.begin() + 6, rng);
	shuffle(clubs.begin() + 6, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.begin() + 18, rng);
	shuffle(clubs.begin() + 18, clubs.end(), rng);

	DWORD v1 = *(DWORD*)_this;
	WORD group_teams = 4;
	for (int i = 0; i < 6; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 6 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 10, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void world_cup_quals_concacaf_third_stage_setup(BYTE* _this) {
	char stage_num = 6;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 1, 0, 0 };
	if (num_hosts > 0) prom_rel[0] = 1;
	if (num_hosts == 1) prom_rel[1] = 2;
	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, CurrentPositionTiebreaker, GoalsForAwayTiebreaker };

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 6; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Qualified1) {
				clubs.push_back(tls.club);
			}
		}
	}

	sort(clubs.begin(), clubs.end(), compareNationRanking);
	shuffle(clubs.begin(), clubs.begin() + 3, rng);
	shuffle(clubs.begin() + 3, clubs.begin() + 6, rng);
	shuffle(clubs.begin() + 6, clubs.begin() + 9, rng);
	shuffle(clubs.begin() + 9, clubs.end(), rng);

	DWORD v1 = *(DWORD*)_this;
	WORD group_teams = 4;
	for (int i = 0; i < 3; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 3 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 10, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
	world_cup_quals_concacaf_setup_best_placed(_this);
}

void world_cup_quals_concacaf_final_stage_setup(BYTE* _this) {
	char stage_num = 10;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2 + 2 * (num_hosts == 1);
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<cm3_clubs*> clubs;
	for (char al = 6; al < 9; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
		}
	}

	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[j])) = (DWORD)clubs[j];
	}

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

void world_cup_quals_concacaf_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			world_cup_quals_concacaf_second_stage_setup(_this);
		}
		else if (current == 6) {
			world_cup_quals_concacaf_third_stage_setup(_this);
		}
		else if (current == 10) {
			world_cup_quals_concacaf_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) world_cup_quals_concacaf_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_concacaf_stages_create
		add esp, 0x4
		ret
	}
}

void world_cup_quals_concacaf_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = world_cup_quals_concacaf_vtable;
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = WORLD_CUP_AFC_QUALIFYING_9CF();
	data->rules = RulesInternational;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->year = year;
	while (data->year % 4 != 3) data->year++;
	data->f81 = 0xf;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 11;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;

	data->n_teams = 22;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * data->n_teams);
	data->teams_list = (DWORD*)pMem;

	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* ebx = 0;
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void world_cup_quals_concacaf_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 26, July, data->year, -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
		if (!data->f69 && a3) {
			sub_775070((BYTE*)*b74318, get_continent(NORTH_AMERICA_9CF()), 0);
			data->f69 = 1;
			world_cup_quals_concacaf_all_teams(_this);
			world_cup_quals_concacaf_qualifier_teams(_this);
			DWORD v1 = *(DWORD*)_this;
			(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
			(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
			(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
			sub_51C800(_this, 0);
		}
	}
	else if ((*(WORD*)(current_date) > date_day && *(WORD*)(current_date + 2) == date_year) || *(WORD*)(current_date + 2) > date_year) {
		char ret = sub_5AE6D0((BYTE*)current_date, data->competition_db->ClubCompID);
		if (ret && data->current_stage >= 6) world_cup_quals_concacaf_best_placed_update(_this);
	}
	sub_51F890(_this, current_date, a3);
}

void __declspec(naked) world_cup_quals_concacaf_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_concacaf_init2
		add esp, 0xc
		ret 8
	}
}

int world_cup_quals_concacaf_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* world_cup_bytes = get_loaded_league(FIFA_WORLD_CUP_9CF());
	comp_stats* world_cup_data = (comp_stats*)world_cup_bytes;
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SecondRound, 0x1E);
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
	else if (stage < 6) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, ThirdRound, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SecondRound, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage < 9) {
		switch (fate) {
		case Qualified1:
			add_team_to_world_cup(club);
			return 0;
		case TopPlayoff:
			if (num_hosts < 2) staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, FourthRound, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, ThirdRound, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 9) {
		switch (fate) {
		case Qualified1:
			add_team_to_world_cup(club);
			for (char al = 6; al < 9; al++) {
				comp_stats* stage_data = (comp_stats*)(comp_data->stages[al]);
				team_league_stats* table_teams = (team_league_stats*)(stage_data->team_league_table);
				if (table_teams[1].club == club) {
					stage_data->promotions++;
					stage_data->prom_playoff--;
					table_teams[1].league_fate = Qualified1;
					break;
				}
			}
			return 0;
		case TopPlayoff:
			if (num_hosts == 0)
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, FourthRound, 0x1E);
			else if (num_hosts == 2)
				add_team_to_world_cup_playoffs(club);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			for (char al = 6; al < 9; al++) {
				comp_stats* stage_data = (comp_stats*)(comp_data->stages[al]);
				team_league_stats* table_teams = (team_league_stats*)(stage_data->team_league_table);
				if (table_teams[2].club == club) {
					stage_data->prom_playoff = 0;
					table_teams[2].league_fate = Eliminated;
					break;
				}
			}
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 10) {
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
		case BottomPlayoff:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			break;
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

void __declspec(naked) world_cup_quals_concacaf_set_table_fate()
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
		call world_cup_quals_concacaf_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int world_cup_quals_concacaf_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);
	if (stage_id == -1) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0x98AC50, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			}
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 0;
		}
	}
	else if (stage_id < 6) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 9) {
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
		else if (fate == TopPlayoff)
		{
			if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
			else {
				if (num_hosts < 2)
				{
					sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					return 1;
				}
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 9) {
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
			if (num_hosts == 0)
			{
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			else if (num_hosts == 2)
			{
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 10) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			case BottomPlayoff:
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
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

void __declspec(naked) world_cup_quals_concacaf_stage_news_c()
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
		call world_cup_quals_concacaf_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void world_cup_quals_concacaf_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	WORD num_hosts = get_world_cup_hosts_in_continent(_this, NORTH_AMERICA_9CF(), 0, 0);
	if ((main_stage_id >= 0x407 && main_stage_id <= 0x40B) || main_stage_id == SecondRoundGroupF) { // Second Round
		if (fate != Qualified1) {
			sub_66F4E0(dest_ptr, 0x9A7B94);
			return;
		}
	}
	if ((main_stage_id >= 0x40c && main_stage_id <= 0x40e) || main_stage_id == BestPlacedTeams) { // Third Round
		if (fate == Qualified1) {
			sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else if (fate == TopPlayoff) {
			if (num_hosts < 2) sub_66F4E0(dest_ptr, 0x9A7AA0);
			else sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, 0x9A7B10);
			return;
		}
	}
	if (sub_stage_id == FourthRound)
	{
		if (fate == 1) {
			sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) world_cup_quals_concacaf_landmarks_c()
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
		call world_cup_quals_concacaf_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

void setup_world_cup_quals_concacaf() {
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableInitFree, (DWORD)&world_cup_quals_concacaf_free_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableEoSUpdate, (DWORD)&world_cup_quals_concacaf_update_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableLeagueSplit, (DWORD)&world_cup_quals_concacaf_init2_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTable10, 0x48CEA0);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTablePlayoffQual, (DWORD)&world_cup_quals_concacaf_stages_create_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableClubLandmarks, (DWORD)&world_cup_quals_concacaf_landmarks_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableFixtures, (DWORD)&world_cup_quals_concacaf_fixture_caller);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableStageNews, (DWORD)&world_cup_quals_concacaf_stage_news_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableTableFates, (DWORD)&world_cup_quals_concacaf_set_table_fate);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableReputationSetup, (DWORD)&world_cup_quals_concacaf_reputation_setup_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTableReputationCalc, (DWORD)&world_cup_quals_concacaf_reputation_calc_c);
	//WriteVTablePtr(world_cup_quals_concacaf_vtable, VTable29, (DWORD)&world_cup_quals_concacaf_vtable29_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTable29, 0x911b80);
	//WriteVTablePtr(world_cup_quals_concacaf_vtable, VTable30, (DWORD)&world_cup_quals_concacaf_vtable30_c);
	WriteVTablePtr(world_cup_quals_concacaf_vtable, VTable30, 0x920260);
}