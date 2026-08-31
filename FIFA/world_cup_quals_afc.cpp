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

DWORD* world_cup_quals_afc_vtable = (DWORD*)0x970B84;

void world_cup_quals_afc_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = world_cup_quals_afc_vtable;
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

void world_cup_quals_afc_free(BYTE* _this, BYTE a2) {
	world_cup_quals_afc_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) world_cup_quals_afc_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_afc_free
		add esp, 0x8
		ret 4
	}
}

int world_cup_quals_afc_vtable2(BYTE* _this, BYTE* round_data, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;

	char curr_stage = *(char*)(round_data + 0x42);
	if (curr_stage == -1)
	{
		DWORD* f8 = comp_data->f8;
		comp_data->f8 = 0;
		*(BYTE*)(round_data + 0x42) = 0;
		sub_685D30(_this, round_data, a3);
		*(BYTE*)(round_data + 0x42) = curr_stage;
		comp_data->f8 = f8;
	}

	return sub_51A150(_this, round_data, a3);
}

void __declspec(naked) world_cup_quals_afc_vtable2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_afc_vtable2
		add esp, 0xc
		ret 0x8
	}
}

DWORD world_cup_quals_afc_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 1), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 28), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 10, 20, 10, 20, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {}
	else if (stage_idx < 10) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 6;
		*stage_name_id = SecondRoundAlphabeticGroup + stage_idx - 1;
		if (stage_idx == 6) *stage_name_id = SecondRoundGroupF;
		if (stage_idx > 6) *stage_name_id = SecondRoundGroupGtoI + stage_idx - 7;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 14), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 26), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 6), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 11), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	else if (stage_idx < 13) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 10;
		*stage_name_id = ThirdRoundAlphabeticGroup + stage_idx - 10;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 9, 23), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 9, 26), year, Sunday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 9, 29), year, Wednesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 10, 3), year, Sunday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 11, 14), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 11, 19), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 20), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 25), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 6, 5), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 6, 10), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	else if (stage_idx < 15) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 3;
		*stage_name_id = FourthRoundAlphabeticGroup + stage_idx - 13;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 10, 1), year, Wednesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 10, 4), year, Saturday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 10, 7), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	else if (stage_idx == 15) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 2, 10, 8), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 2, 11, 6), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 10, 2, 1, 2, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	else if (stage_idx == 16) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 2, 10, 8), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 2, 11, 6), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, SixthRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 10, 2, 1, 2, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) world_cup_quals_afc_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_afc_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char world_cup_quals_afc_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
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
	data->num_stages = 17;
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

void __declspec(naked) world_cup_quals_afc_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_afc_update
		add esp, 0x4
		ret
	}
}

void world_cup_quals_afc_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	vector<cm3_clubs*> afc_countries = get_national_teams_of_continent_fifa_members(ASIA_9CF());
	sort(afc_countries.begin(), afc_countries.end(), compareNationRanking);

	DWORD host1_id, host2_id;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), ASIA_9CF(), &host1_id, &host2_id);
	if (num_hosts != 1) data->num_stages--;
	if (num_hosts == 2) data->num_stages--;
	WORD total_teams_in_comp = (WORD)afc_countries.size();
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	DWORD host3_id, host4_id;
	get_comp_hosts_in_continent(_this, ASIAN_CUP_9CF(), ASIA_9CF(), &host3_id, &host4_id);

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	// hosts 1 + 2 for World Cup, hosts 3 + 4 for Asian Cup
	for (WORD i = 0; i < total_teams_in_comp; i++) {
		if (afc_countries[i]->ClubNation->NationID == host1_id || afc_countries[i]->ClubNation->NationID == host2_id
			|| afc_countries[i]->ClubNation->NationID == host3_id || afc_countries[i]->ClubNation->NationID == host4_id)
		{
			auto it = afc_countries.begin() + i;
			rotate(afc_countries.begin(), it, it + 1);
		}
	}

	for (size_t i = 0, j = 0; i < afc_countries.size() && j < total_teams_in_comp; i++) {
		teams[j].club = afc_countries[i];
		if (j < 26) teams[j].f5 = 10;
		else teams[j].f5 = 11;
		teams[j].f6 = 0;
		j++;
	}
}

void world_cup_quals_afc_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 20;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

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
		cm3_clubs* club = qualifiers[26 + i].club;
		teams[i].club = club;
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	// table to find the "best loser"
	WORD stage_name_id = Playoff;
	BYTE idx = 0;
	DWORD* pTeams = (DWORD*)cm0102_malloc(total_teams * 4);

	for (DWORD i = 0; i < total_teams; i++)
	{
		*((DWORD*)(&pTeams[i])) = (DWORD)teams[i].club;
	}
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 0, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, 0, 0 };
	short f217 = 0;
	create_league_stage_data(pStage, _this, total_teams, pTeams, 0, (DWORD)(data->competition_db), 0, 2,
		3, 1, 10, &tiebreaks[0], &prom_rel[0], year, idx, stage_name_id, 0xf, 2, 0, f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	data->current_stage = idx;
}

void world_cup_quals_afc_reputation_setup(BYTE* _this) {
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
		for (DWORD i = 6; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 7);
		}
		for (DWORD i = 8; i < 10; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (DWORD i = 10; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 11);
		}
		for (DWORD i = 12; i < 15; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (DWORD i = 15; i < 18; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 16);
		}
		for (DWORD i = 18; i < 27; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19);
		}
		for (DWORD i = 27; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 28);
		}
		for (DWORD i = 36; i < clubs.size(); i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 37);
		}
		for (WORD i = 0; i < clubs.size(); i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) world_cup_quals_afc_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_afc_reputation_setup
		add esp, 0x4
		ret
	}
}

void world_cup_quals_afc_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = 26 + current;
		if (ret_min != 1) ret_min = 26 + min;
		ret_max = 26 + max;
	}
	else if (stage == 0) {
		ret_current = 36 + current;
		ret_min = 36 + min;
		ret_max = 36 + max;
	}
	else if (stage < 10) {
		ret_current = 1 + 9 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 9 * (min - 1);
		if (max < 3) ret_max = 10;
		else ret_max = 1 + 9 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage < 13) {
		ret_current = 1 + 3 * (current - 1);
		if (min < 3) ret_min = 1;
		else if (min < 5) ret_min = 7;
		else ret_min = 1 + 3 * (min - 1);
		if (max < 3) ret_max = max;
		else if (max < 5) ret_max = 11;
		else ret_max = 1 + 3 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage < 15) {
		ret_current = 1 + 2 * (current - 1);
		ret_min = 1 + 2 * (min - 1);
		ret_max = 1 + 2 * (max - 1);
	}
	else if (stage == 15) {
		ret_current = current + 6;
		ret_min = min + 6;
		ret_max = max + 6;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) world_cup_quals_afc_reputation_calc_c()
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
		call world_cup_quals_afc_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void qualify_teams_for_asian_cup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	DWORD host3_id, host4_id;
	get_comp_hosts_in_continent(get_loaded_league(ASIAN_CUP_9CF()), ASIAN_CUP_9CF(), ASIA_9CF(), &host3_id, &host4_id);

	for (char al = 1; al < 10; al++) {
		vector<cm3_clubs*> clubs_qual;

		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			cm3_clubs* club = table_teams[i].club;
			if (i < 2)
			{
				if (club->ClubNation->NationID != host3_id && club->ClubNation->NationID != host4_id) clubs_qual.push_back(club);
			}
			else if (club->ClubNation->NationID == host3_id || club->ClubNation->NationID == host4_id) {
				clubs_qual.pop_back();
			}
		}

		for (cm3_clubs* club : clubs_qual) qualify_team_for_international_comp(club, ASIAN_CUP_9CF(), true);
	}
}

void block_hosts_from_qualifying_wc_asia(BYTE* stage, DWORD host1_id, DWORD host2_id) {
	comp_stats* comp_data = (comp_stats*)stage;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		if (table_teams[i].club->ClubNation->NationID == host1_id ||
			table_teams[i].club->ClubNation->NationID == host2_id) {
			table_teams[i].league_fate = CantBePromoted;
		}
	}
}

void world_cup_quals_afc_second_stage_setup(BYTE* _this) {
	char stage_num = 1;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	char prom_rel[4] = { 2, 0, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, CurrentPositionTiebreaker, GoalsForAwayTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < 26; i++) clubs.push_back(teams[i].club);
	teams = (teams_seeded*)comp_data->teams_list;
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		if (teams[i].f6 == 1) clubs.push_back(teams[i].club);
	}

	sort(clubs.begin(), clubs.end(), compareNationRanking);
	shuffle(clubs.begin(), clubs.begin() + 9, rng);
	shuffle(clubs.begin() + 9, clubs.begin() + 18, rng);
	shuffle(clubs.begin() + 18, clubs.begin() + 27, rng);
	shuffle(clubs.begin() + 27, clubs.end(), rng);

	DWORD v1 = *(DWORD*)_this;
	WORD group_teams = 4;
	DWORD host1_id, host2_id;
	get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), ASIA_9CF(), &host1_id, &host2_id);
	for (int i = 0; i < 9; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 9 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 10, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		block_hosts_from_qualifying_wc_asia(pStage, host1_id, host2_id);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void world_cup_quals_afc_third_stage_setup(BYTE* _this) {
	qualify_teams_for_asian_cup(_this);

	char stage_num = 10;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	char prom_rel[4] = { 2, 2, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, CurrentPositionTiebreaker, GoalsForAwayTiebreaker };

	vector<cm3_clubs*> clubs;
	for (char al = 1; al < 10; al++) {
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
	shuffle(clubs.begin() + 9, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.begin() + 15, rng);
	shuffle(clubs.begin() + 15, clubs.end(), rng);

	DWORD v1 = *(DWORD*)_this;
	WORD group_teams = 6;
	for (int i = 0; i < 3; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 3 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
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

void world_cup_quals_afc_fourth_stage_setup(BYTE* _this) {
	char stage_num = 13;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	char prom_rel[4] = { 1, 1, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, CurrentPositionTiebreaker, GoalsForAwayTiebreaker };

	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), ASIA_9CF(), 0, 0);
	if (num_hosts > 1) prom_rel[0] = 0;

	vector<cm3_clubs*> clubs;
	for (char al = 10; al < 13; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
		}
	}

	sort(clubs.begin(), clubs.end(), compareNationRanking);
	shuffle(clubs.begin(), clubs.begin() + 2, rng);
	shuffle(clubs.begin() + 2, clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.end(), rng);

	DWORD v1 = *(DWORD*)_this;
	WORD group_teams = 3;
	for (int i = 0; i < 2; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 2 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
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

void world_cup_quals_afc_final_stage_setup(BYTE* _this) {
	char stage_num = 15;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<cm3_clubs*> clubs;
	for (char al = 13; al < 15; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if ((comp_data->num_stages == 16 && tls.league_fate == TopPlayoff) ||
				(comp_data->num_stages == 17 && tls.league_fate == Qualified1)) {
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
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

void world_cup_quals_afc_extra_stage_setup(BYTE* _this) {
	char stage_num = 16;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<cm3_clubs*> clubs;
	for (char al = 13; al < 15; al++) {
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
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

void world_cup_quals_afc_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 1) {
			world_cup_quals_afc_second_stage_setup(_this);
		}
		else if (current == 10) {
			world_cup_quals_afc_third_stage_setup(_this);
		}
		else if (current == 13) {
			world_cup_quals_afc_fourth_stage_setup(_this);
		}
		else if (current == 15) {
			world_cup_quals_afc_final_stage_setup(_this);
			if (max == 17) world_cup_quals_afc_extra_stage_setup(_this);
		}
	}
}

void __declspec(naked) world_cup_quals_afc_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_afc_stages_create
		add esp, 0x4
		ret
	}
}

void world_cup_quals_afc_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = world_cup_quals_afc_vtable;
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = WORLD_CUP_CONCACAF_QUALIFYING_9CF();
	data->relegates_to = WORLD_CUP_OFC_QUALIFYING_9CF();
	data->rules = RulesInternational;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->year = year - 1;
	while (data->year % 4 != 3) data->year++;
	data->f81 = 0xf;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 17;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);

	data->n_teams = 20;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * data->n_teams);
	data->teams_list = (DWORD*)pMem;

	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void world_cup_quals_afc_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 26, July, data->year, -1);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
			if (a3) {
				sub_775070((BYTE*)*b74318, get_continent(ASIA_9CF()), 0);
				data->f69 = 1;
				world_cup_quals_afc_all_teams(_this);
				world_cup_quals_afc_qualifier_teams(_this);
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

void __declspec(naked) world_cup_quals_afc_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_afc_init2
		add esp, 0xc
		ret 8
	}
}

int world_cup_quals_afc_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), ASIA_9CF(), 0, 0);
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[0]);
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SecondRound, 0x1E);
			for (int i = 0; i < curr_stage->n_teams; i++) {
				if (table[i].club != club) continue;
				table[i].league_fate = Qualified1;
			}
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
	else if (stage == 0) {}
	else if (stage < 10) {
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
	else if (stage < 13) {
		switch (fate) {
		case Qualified1:
			qualify_team_for_international_comp(club, FIFA_WORLD_CUP_9CF());
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, FourthRound, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, ThirdRound, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage < 15) {
		switch (fate) {
		case Qualified1:
			if (num_hosts == 1)
			{
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, FifthRound, 0x1E);
				return 0;
			}
			else
			{
				qualify_team_for_international_comp(club, FIFA_WORLD_CUP_9CF());
				return 0;
			}
		case TopPlayoff:
			if (num_hosts == 1)
			{
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SixthRound, 0x1E);
				return 0;
			}
			else if (num_hosts == 2)
			{
				add_team_to_world_cup_playoffs(club);
				return 0;
			}
			else
			{
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, FifthRound, 0x1E);
				return 0;
			}
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, FourthRound, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 15) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			if (num_hosts == 1)
			{
				qualify_team_for_international_comp(club, FIFA_WORLD_CUP_9CF());
			}
			else {
				add_team_to_world_cup_playoffs(club);
			}
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		case BottomPlayoff:
			if (num_hosts == 1)
			{
				add_team_to_world_cup_playoffs(club);
			}
			else {
				staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
				break;
			}
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 16) {
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

void __declspec(naked) world_cup_quals_afc_set_table_fate()
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
		call world_cup_quals_afc_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int world_cup_quals_afc_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	// This condition breaks aftr the World Cup resets
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), ASIA_9CF(), 0, 0);
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
	else if (stage_id == 0) {}
	else if (stage_id < 10) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 13) {
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
		else if (fate == TopPlayoff) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 15) {
		if (fate == Qualified1)
		{
			if (num_hosts == 0) {
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
			else if (num_hosts == 1) {
				if (show_body_text) {
					sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
						&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
					return 1;
				}
				else {
					sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
						&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
					return 1;
				}
			}
		}
		else if (fate == TopPlayoff)
		{
			if (num_hosts == 2) {
				if (show_body_text) {
					sub_66F4E0(0xDE1F64, (DWORD)&qualified_wc_playoff_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					return 1;
				}
			}
			else {
				sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 15) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				if (num_hosts == 1)
				{
					sub_66F4E0(0xDE1F64, 0xAD4B78, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				}
				else {
					sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				}
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			case BottomPlayoff:
				if (num_hosts == 1)
				{
					sub_66F4E0(0xDE1F64, 0xAD4BE0, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					return 1;
				}
				else {
					sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					return 1;
				}
				return 0;
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
	else if (stage_id == 16) {
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
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
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

void __declspec(naked) world_cup_quals_afc_stage_news_c()
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
		call world_cup_quals_afc_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void world_cup_quals_afc_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	DWORD host1_id, host2_id;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), ASIA_9CF(), &host1_id, &host2_id);
	if (main_stage_id == Playoff) return sub_48CAB0(_this, dest_ptr, a2, None, FirstRound, fate, club);
	if ((main_stage_id >= 0x407 && main_stage_id <= 0x40B) || main_stage_id == SecondRoundGroupF ||
		(main_stage_id >= 0x42f && main_stage_id <= 0x431)) { // Second Round
		if (fate == CantBePromoted) {
			sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, 0x9A7B94);
			return;
		}
	}
	if (main_stage_id >= 0x40c && main_stage_id <= 0x40e) { // Third Round
		if (fate == Qualified1) {
			sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else if (fate != TopPlayoff) {
			sub_66F4E0(dest_ptr, 0x9A7B10);
			return;
		}
	}
	if (main_stage_id >= 0x47e && main_stage_id <= 0x47f) { // Fourth Round
		if (fate == Qualified1) {
			if (num_hosts == 0)
			{
				sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
				return;
			}
		}
		else if (fate != TopPlayoff) {
			sub_66F4E0(dest_ptr, 0x9A7AA0);
			return;
		}
		else if (num_hosts == 2) {
			sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
			return;
		}
	}
	if (sub_stage_id == FifthRound)
	{
		if (num_hosts == 1)
		{
			if (fate == 1) {
				sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
				return;
			}
			else if (fate == 2) {
				sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
				return;
			}
		}
		else if (fate == 1) {
			sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
			return;
		}
	}
	if (sub_stage_id == SixthRound)
	{
		if (fate == 1) {
			sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) world_cup_quals_afc_landmarks_c()
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
		call world_cup_quals_afc_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

WORD world_cup_quals_afc_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);

	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), ASIA_9CF(), 0, 0);
	WORD cutoff1 = 9 - num_hosts + 1;
	WORD cutoff2 = cutoff1 + 1 + (num_hosts > 0);
	if (val < cutoff1) return -3;
	else return -5;
}

void __declspec(naked) world_cup_quals_afc_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_afc_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE world_cup_quals_afc_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), ASIA_9CF(), 0, 0);
	WORD cutoff1 = 9 - num_hosts + 1;
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

void __declspec(naked) world_cup_quals_afc_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_afc_vtable30
		add esp, 0x8
		ret 4
	}
}

char* r2_1_short = "2nd Rnd Grp G";
void __declspec(naked) jmp_shortname_r2g()
{
	__asm
	{
		push r2_1_short
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

void setup_world_cup_quals_afc() {
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableInitFree, (DWORD)&world_cup_quals_afc_free_c);
	//WriteVTablePtr(world_cup_quals_afc_vtable, VTablePostMatchUpdate, 0x51A150);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTablePostMatchUpdate, (DWORD)&world_cup_quals_afc_vtable2_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableEoSUpdate, (DWORD)&world_cup_quals_afc_update_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable4, 0x48ce10);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable5, 0x521E00);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableLeagueSplit, (DWORD)&world_cup_quals_afc_init2_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable7, 0x51FC00);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable8, 0x5210F0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableLoadCompInfo, 0x48CEB0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableSaveCompInfo, 0x48CEA0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTablePlayoffQual, (DWORD)&world_cup_quals_afc_stages_create_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable12, 0x48ce70);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableSetChampion, 0x90fbe0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable14, 0x910f00);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableClubLandmarks, (DWORD)&world_cup_quals_afc_landmarks_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableFixtures, (DWORD)&world_cup_quals_afc_fixture_caller);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable17, 0x519690);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableStageNews, (DWORD)&world_cup_quals_afc_stage_news_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableTableFates, (DWORD)&world_cup_quals_afc_set_table_fate);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable20, 0x48dfa0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableShowThirdInHistory, 0x48e180);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable22, 0x5221F0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable23, 0x48e1c0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableReputationSetup, (DWORD)&world_cup_quals_afc_reputation_setup_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable25, 0x48e360);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable26, 0x5bb550);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableReputationCalc, (DWORD)&world_cup_quals_afc_reputation_calc_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable28, 0x583470);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable29, (DWORD)&world_cup_quals_afc_vtable29_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable30, (DWORD)&world_cup_quals_afc_vtable30_c);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableGetFinalsComp, 0x91e1c0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable32, 0x48f2d0);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable33, 0x522910);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable34, 0x522C50);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableShowHostsInHistory, 0x5dce00);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable37, 0x522360);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable38, 0x518790);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable39, 0x51C020);
	WriteVTablePtr(world_cup_quals_afc_vtable, VTable40, 0x51F2F0);

	char* r3_1 = "Third Round Group A";
	char* r3_1_short = "3rd Rnd Grp A";
	char* r3_2 = "Third Round Group B";
	char* r3_2_short = "3rd Rnd Grp B";
	char* r3_3 = "Third Round Group C";
	char* r3_3_short = "3rd Rnd Grp C";
	WriteDWORD(0x4B5e01 + 1, (DWORD)&r3_1[0]);
	WriteDWORD(0x4B897c + 1, (DWORD)&r3_1_short[0]);
	WriteDWORD(0x4B5e1b + 1, (DWORD)&r3_2[0]);
	WriteDWORD(0x4B8986 + 1, (DWORD)&r3_2_short[0]);
	WriteDWORD(0x4B5e35 + 1, (DWORD)&r3_3[0]);
	WriteDWORD(0x4B8990 + 1, (DWORD)&r3_3_short[0]);

	char* r4_1 = "Fourth Round Group A";
	char* r4_1_short = "4th Rnd Grp A";
	char* r4_2 = "Fourth Round Group B";
	char* r4_2_short = "4th Rnd Grp B";
	WriteDWORD(0x4B68cf + 1, (DWORD)&r4_1[0]);
	WriteDWORD(0x4B9421 + 1, (DWORD)&r4_1_short[0]);
	WriteDWORD(0x4B68e9 + 1, (DWORD)&r4_2[0]);
	WriteDWORD(0x4B7a36 + 1, (DWORD)&r4_2[0]);
	WriteDWORD(0x4B943b + 1, (DWORD)&r4_2_short[0]);

	char* r2_1 = "Second Round Group G";
	char* r2_2 = "Second Round Group H";
	char* r2_2_short = "2nd Rnd Grp H";
	char* r2_3 = "Second Round Group I";
	char* r2_3_short = "2nd Rnd Grp I";
	WriteDWORD(0x4B61c8 + 1, (DWORD)&r2_1[0]);
	WriteDWORD(0x4ba798, (DWORD)&jmp_shortname_r2g); // the switch table
	WriteDWORD(0x4B61e2 + 1, (DWORD)&r2_2[0]);
	WriteDWORD(0x4B8ccf + 1, (DWORD)&r2_2_short[0]);
	WriteDWORD(0x4B61fc + 1, (DWORD)&r2_3[0]);
	WriteDWORD(0x4B8ce9 + 1, (DWORD)&r2_3_short[0]);

	WriteBytes(0x9a6ba7, 1, 'A');
	WriteBytes(0x9a4760, 1, 'A');

	WriteBytes(0x9a6b8f, 1, 'B');
	WriteBytes(0x9a4750, 1, 'B');

	WriteBytes(0x9a6b77, 1, 'C');
	WriteBytes(0x9a4740, 1, 'C');

	WriteBytes(0x9a6b5f, 1, 'D');
	WriteBytes(0x9a4730, 1, 'D');

	WriteBytes(0x9a6b47, 1, 'E');
	WriteBytes(0x9a4720, 1, 'E');

	WriteBytes(0x9a6543, 1, 'F');
	WriteBytes(0x9a4164, 1, 'F');


	WriteBytes(0x9a6c76, 1, 'A');
	WriteBytes(0x9a4800, 1, 'A');

	WriteBytes(0x9a6c62, 1, 'B');
	WriteBytes(0x9a47f0, 1, 'B');

	WriteBytes(0x9a6c4e, 1, 'C');
	WriteBytes(0x9a47e0, 1, 'C');

	WriteBytes(0x9a6c3a, 1, 'D');
	WriteBytes(0x9a47d0, 1, 'D');

	WriteBytes(0x9a6c26, 1, 'E');
	WriteBytes(0x9a47c0, 1, 'E');

	WriteBytes(0x9a6c12, 1, 'F');
	WriteBytes(0x9a41b4, 1, 'F');

	WriteBytes(0x9a6bfe, 1, 'G');
	WriteBytes(0x9a47a0, 1, 'G');

	WriteBytes(0x9a6bea, 1, 'H');
	WriteBytes(0x9a4790, 1, 'H');

	WriteBytes(0x9a6bd6, 1, 'I');
	WriteBytes(0x9a4780, 1, 'I');

	WriteBytes(0x9a6bbe, 2, 'J', '\0');
	WriteBytes(0x9a4770, 2, 'J', '\0');
}