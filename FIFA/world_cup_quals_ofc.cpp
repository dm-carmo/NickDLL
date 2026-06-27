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

DWORD* world_cup_quals_ofc_vtable = (DWORD*)0x970D78;

void world_cup_quals_ofc_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = world_cup_quals_ofc_vtable;
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

void world_cup_quals_ofc_free(BYTE* _this, BYTE a2) {
	world_cup_quals_ofc_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) world_cup_quals_ofc_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_ofc_free
		add esp, 0x8
		ret 4
	}
}

DWORD world_cup_quals_ofc_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 2;
		*stage_name_id = FirstRound;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		DWORD host1_id, host2_id;
		WORD num_to_exclude = get_world_cup_hosts_in_continent(_this, OCEANIA_9CF(), &host1_id, &host2_id);
		WORD num_teams = 4 - num_to_exclude;
		WORD r1_teams = num_teams - num_teams % 2;
		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 1), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 6), year, Friday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, r1_teams, r1_teams / 2, r1_teams, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 7), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 9), year, Monday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, num_teams - r1_teams, r1_teams == num_teams ? 0 : r1_teams, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 3;
		*stage_name_id = SecondRoundNumericGroup + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx == 0) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 10), year, Thursday, Afternoon);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 14), year, Thursday, Afternoon);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 17), year, Saturday, Afternoon);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 11), year, Friday, Afternoon);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 15), year, Friday, Afternoon);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 18), year, Sunday, Afternoon);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 2;
		*stage_name_id = ThirdRound;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 19), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Friday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 10, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 22), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 24), year, Monday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) world_cup_quals_ofc_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_ofc_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char world_cup_quals_ofc_update(BYTE* _this) {
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

void __declspec(naked) world_cup_quals_ofc_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_ofc_update
		add esp, 0x4
		ret
	}
}

void world_cup_quals_ofc_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	//*(WORD*)(_this + 0xA7) = -1;

	vector<cm3_clubs*> ofc_countries = get_national_teams_of_continent(OCEANIA_9CF());
	sort(ofc_countries.begin(), ofc_countries.end(), compareNationRanking);

	DWORD host1_id, host2_id;
	WORD num_to_exclude = get_world_cup_hosts_in_continent(_this, OCEANIA_9CF(), &host1_id, &host2_id);
	WORD total_teams_in_comp = (WORD)ofc_countries.size() - num_to_exclude;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	for (size_t i = 0, j = 0; i < ofc_countries.size() && j < total_teams_in_comp; i++) {
		if (ofc_countries[i]->ClubNation->NationID == host1_id || ofc_countries[i]->ClubNation->NationID == host2_id) continue;
		teams[j].club = ofc_countries[i];
		if (j < 2) teams[j].f5 = 3;
		else if (j < 6) teams[j].f5 = 10;
		else if (j < 7) teams[j].f5 = 11;
		else teams[j].f5 = 12;
		teams[j].f6 = 0;
		j++;
	}
}

void world_cup_quals_ofc_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = data->special_nteams_seedings - 7;
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
		cm3_clubs* club = qualifiers[data->special_nteams_seedings - i - 1].club;
		teams[i].club = club;
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
}

void world_cup_quals_ofc_reputation_setup(BYTE* _this) {
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
		for (DWORD i = 2; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 3);
		}
		for (DWORD i = 4; i < 6; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (DWORD i = 6; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 7);
		}
		for (DWORD i = 8; i < 10 && i < clubs.size(); i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (DWORD i = 10; i < 12 && i < clubs.size(); i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 11);
		}
		for (WORD i = 0; i < clubs.size(); i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) world_cup_quals_ofc_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_ofc_reputation_setup
		add esp, 0x4
		ret
	}
}

void world_cup_quals_ofc_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = 7 + current;
		if (ret_min != 1) ret_min = 7 + min;
		ret_max = 7 + max;
	}
	else if (stage < 2) {
		ret_current = 1 + 2 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 2 * (min - 1);
		if (max < 3) ret_max = 17;
		else ret_max = 1 + 2 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 2) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) world_cup_quals_ofc_reputation_calc_c()
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
		call world_cup_quals_ofc_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void world_cup_quals_ofc_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 5;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	teams_seeded* all_teams = (teams_seeded*)data->special_teams_seedings;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < total_teams; i++) {
		add_team_call(_this, teamsAdded++, all_teams[i * 2].club, 0, 0);
	}
	sub_684230(_this);
}

void world_cup_quals_ofc_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	for (BYTE i = 0; i < 5; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)teams[i * 2 + (idx + 1)].club;
	}

	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, 5, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void world_cup_quals_ofc_group_stage_setup(BYTE* _this) {
	char stage_num = 0;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 0, 0, 0 };
	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, CurrentPositionTiebreaker, GoalsForAwayTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < 7; i++) clubs.push_back(teams[i].club);
	teams = (teams_seeded*)comp_data->teams_list;
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		if (teams[i].f6 == 1)
		{
			clubs.push_back(teams[i].club);
			break;
		}
	}

	shuffle(clubs.begin(), clubs.begin() + 2, rng);
	shuffle(clubs.begin() + 2, clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 6, rng);
	shuffle(clubs.begin() + 6, clubs.end(), rng);

	DWORD v1 = *(DWORD*)_this;
	WORD group_teams = 4;
	for (int i = 0; i < 2; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 2 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 1, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 10, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void world_cup_quals_ofc_final_stage_setup(BYTE* _this) {
	char stage_num = 2;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 2; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
	}

	BYTE team_order[4] = { 0,2,3,1 };
	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
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

void world_cup_quals_ofc_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			world_cup_quals_ofc_group_stage_setup(_this);
		}
		else if (current == 2) {
			world_cup_quals_ofc_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) world_cup_quals_ofc_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_ofc_stages_create
		add esp, 0x4
		ret
	}
}

void world_cup_quals_ofc_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = world_cup_quals_ofc_vtable;
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	//data->promotes_to = AFC QUALIFIERS;
	data->promotes_to = -1;
	//data->relegates_to = CONMEBOL QUALIFIERS;
	data->relegates_to = -1;
	data->rules = RulesInternational;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->year = year;
	while (data->year % 4 != 0) data->year++;
	data->f81 = 0xf;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 3;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;

	data->n_teams = 4;
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

void world_cup_quals_ofc_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 26, July, data->year, -1);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
			if (a3) {
				sub_775070((BYTE*)*b74318, get_continent(OCEANIA_9CF()), 0);
				data->f69 = 1;
				world_cup_quals_ofc_all_teams(_this);
				world_cup_quals_ofc_qualifier_teams(_this);
				DWORD v1 = *(DWORD*)_this;
				(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
				(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
				(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
				sub_51C800(_this, 0);
			}
		}
	}
	sub_51F890(_this, current_date, a3);
}

void __declspec(naked) world_cup_quals_ofc_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_ofc_init2
		add esp, 0xc
		ret 8
	}
}

int world_cup_quals_ofc_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
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
	else if (stage < 2) {
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
	else if (stage == 2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		BYTE* world_cup_bytes = get_loaded_league(FIFA_WORLD_CUP_9CF());
		comp_stats* world_cup_data = (comp_stats*)world_cup_bytes;
		teams_seeded* qualifiers = (teams_seeded*)world_cup_data->special_teams_seedings;
		WORD insert_idx = world_cup_data->special_nteams_seedings;
		switch (fate) {
		case TopPlayoff:
			qualifiers[insert_idx].club = club;
			qualifiers[insert_idx].f5 = 6;
			qualifiers[insert_idx].f6 = 0;
			world_cup_data->special_nteams_seedings++;
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)world_cup_data->competition_db, None, None, 0x64);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		case BottomPlayoff:
			// intercontinental playoffs
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)world_cup_data->competition_db, None, QualifyingRound, 0x64);
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

void __declspec(naked) world_cup_quals_ofc_set_table_fate()
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
		call world_cup_quals_ofc_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int world_cup_quals_ofc_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
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
	else if (stage_id < 2) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 2) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0xAD4B78, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
				// case Relegated: intercontinental playoffs 0xAD4BE0
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

void __declspec(naked) world_cup_quals_ofc_stage_news_c()
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
		call world_cup_quals_ofc_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void setup_world_cup_quals_ofc() {
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableInitFree, (DWORD)&world_cup_quals_ofc_free_c);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableEoSUpdate, (DWORD)&world_cup_quals_ofc_update_c);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableLeagueSplit, (DWORD)&world_cup_quals_ofc_init2_c);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTablePlayoffQual, (DWORD)&world_cup_quals_ofc_stages_create_c);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableTableFates, (DWORD)&world_cup_quals_ofc_set_table_fate);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableReputationSetup, (DWORD)&world_cup_quals_ofc_reputation_setup_c);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableReputationCalc, (DWORD)&world_cup_quals_ofc_reputation_calc_c);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableFixtures, (DWORD)&world_cup_quals_ofc_fixture_caller);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableStageNews, (DWORD)&world_cup_quals_ofc_stage_news_c);
	//WriteVTablePtr(world_cup_quals_ofc_vtable, VTable29, (DWORD)&world_cup_quals_ofc_vtable29_c);
	//WriteVTablePtr(world_cup_quals_ofc_vtable, VTable30, (DWORD)&world_cup_quals_ofc_vtable30_c);
	//WriteVTablePtr(world_cup_quals_ofc_vtable, VTableClubLandmarks, (DWORD)&world_cup_quals_ofc_48CAB0_c);

	WriteVTablePtr(world_cup_quals_ofc_vtable, VTablePostMatchUpdate, 0x51A150);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable5, 0x521E00);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable7, 0x51FC00);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable8, 0x5210F0);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable10, 0x48CEA0);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable17, 0x519690);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable22, 0x5221F0);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable33, 0x522910);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable34, 0x522C50);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable37, 0x522360);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable38, 0x518790);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable39, 0x51C020);
	WriteVTablePtr(world_cup_quals_ofc_vtable, VTable40, 0x51F2F0);
	//WriteVTablePtr(world_cup_quals_ofc_vtable, VTableSetChampion, 0x519A90);
}