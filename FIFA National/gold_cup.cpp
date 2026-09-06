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

vtable* gold_cup_vtable = new vtable((BYTE*)0x96B400, 0xB4);

void gold_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(gold_cup_vtable->vtable_ptr);
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

void gold_cup_free(BYTE* _this, BYTE a2) {
	gold_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) gold_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_free
		add esp, 0x8
		ret 4
	}
}

int gold_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* final_bytes = (BYTE*)comp_data->stages[3];
	comp_stats* final_data = (comp_stats*)final_bytes;
	cm3_clubs* first = 0;
	cm3_clubs* second = 0;
	teams_seeded* teams = (teams_seeded*)final_data->teams_list;
	for (WORD i = 0; i < final_data->n_teams; i++) {
		if (teams[i].f6 == 1) first = teams[i].club;
		else if (teams[i].f6 == 2) second = teams[i].club;
	}
	DWORD host1_id = -1, host2_id = -1;
	char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, comp_data->competition_db->ClubCompID, comp_data->year, &host1_id, &host2_id, 1);
	sub_4AFCE0_add_history_entry(_this, first, second, 0, num_hosts > 0 ? get_national_team(host1_id) : 0);

	sub_775420((BYTE*)*b74318, comp_data->competition_db);
	return 0;
}

void __declspec(naked) gold_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gold_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

void gold_cup_subs(BYTE* _this)
{
	comp_stats* data = (comp_stats*)_this;

	data->f67 = 2;
	data->n_rounds = 1;
	data->pts_for_win = 3;
	data->pts_for_draw = 1;
	data->f196 = 10;
	data->tiebreaker_1 = GoalDifferenceTiebreaker;
	data->tiebreaker_2 = GoalsForTiebreaker;
	data->tiebreaker_3 = CurrentPositionTiebreaker;
	data->tiebreaker_4 = NoTiebreaker;

	data->promotions = 2;
	data->prom_playoff = 0;
	data->rele_playoff = 0;
	data->relegations = 0;

	data->n_games = 1000;
	data->max_bench = 9;
	data->max_subs = 5;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 17, April, data->year, Thursday);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = 0;

	DWORD v1 = *(DWORD*)_this;
	data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) gold_cup_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gold_cup_subs
		add esp, 0x4
		ret
	}
}

DWORD gold_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixture(pMem, 0, Date(year, 6, 19), year, Monday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 0, 2);
		AddFixture(pMem, 1, Date(year, 6, 23), year, Friday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 1, 2);
		AddFixture(pMem, 2, Date(year, 6, 26), year, Monday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 2, 2);
		if (stage_idx == -1) {
			AddFixtureTV(pMem, 0, 0, 3, Saturday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 0, 1, 3, Sunday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 1, 0, 3, Wednesday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 1, 1, 3, Wednesday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 0, 3, Sunday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 1, 3, Sunday, Afternoon, LargestStadium1);
		}
		else if (stage_idx == 0) {
			AddFixtureTV(pMem, 0, 0, 3, Tuesday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 0, 1, 3, Tuesday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 1, 0, 3, Saturday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 1, 1, 3, Saturday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 0, 3, Tuesday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 1, 3, Tuesday, Afternoon, LargestStadium3);
		}
		else if (stage_idx == 1) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 1, 0, 3, Friday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 1, 1, 3, Friday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 2, 0, 3, Tuesday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 2, 1, 3, Tuesday, Afternoon, LargestStadium4);
		}
		else if (stage_idx == 2) {
			AddFixtureTV(pMem, 0, 0, 3, Sunday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 0, 1, 3, Sunday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 0, 3, Thursday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 1, 3, Thursday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 0, 3, Sunday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 1, 3, Sunday, Afternoon, LargestStadium7);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 3) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 1), year, Saturday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium4);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium6);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Afternoon, LargestStadium5);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Afternoon, LargestStadium7);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 8, 4, 8, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 3), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 5), year, Wednesday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Wednesday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Wednesday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 6), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 9), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) gold_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void gold_cup_reputation_setup(BYTE* _this) {
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
		for (int i = 8; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 12; i < 16; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (WORD i = 0; i < comp_data->special_nteams_seedings; i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) gold_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gold_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void gold_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 3) {
		ret_current = 1 + 4 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 4 * (min - 1);
		if (max < 3) ret_max = 9;
		else ret_max = 1 + 4 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 3) {
		// do nothing
	}
	else if (stage == 4) {
		ret_current = current + 2;
		ret_min = min + 2;
		ret_max = max + 2;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) gold_cup_reputation_calc_c()
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
		call gold_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void gold_cup_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* tMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)tMem;

	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < total_teams; i++) {
		add_team_call(_this, teamsAdded++, teamList[i * 4].club, 0, 0);
	}
	sub_684230(_this);
}

void gold_cup_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < data->n_teams; i++) {
		*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)teamList[i * 4 + (idx + 1)].club;
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

void gold_cup_seeded_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	data->special_nteams_seedings = 0;
	WORD count = data->special_nteams_seedings;
	WORD year = data->year;
	for (WORD i = count; i < 16; i++)
	{
		teamList[i].club = 0;
		teamList[i].seeding = 6;
	}
	if (year == 2025) {
		teamList[count++].club = get_national_team(NATION_MEXICO_9CF());
		teamList[count++].club = get_national_team(NATION_COSTA_RICA_9CF());
		teamList[count++].club = get_national_team(NATION_DOMINICAN_REPUBLIC_9CF());
		teamList[count++].club = get_national_team(NATION_SURINAM_9CF());
		teamList[count++].club = get_national_team(NATION_CANADA_9CF());
		teamList[count++].club = get_national_team(NATION_HONDURAS_9CF());
		teamList[count++].club = get_national_team(NATION_CURACAO_9CF());
		teamList[count++].club = get_national_team(NATION_EL_SALVADOR_9CF());
		teamList[count++].club = get_national_team(NATION_PANAMA_9CF());
		teamList[count++].club = get_national_team(NATION_GUATEMALA_9CF());
		teamList[count++].club = get_national_team(NATION_JAMAICA_9CF());
		teamList[count++].club = get_national_team(NATION_GUADELOUPE_9CF());
		teamList[count++].club = get_national_team(NATION_USA_9CF());
		teamList[count++].club = get_national_team(NATION_SAUDI_ARABIA_9CF());
		teamList[count++].club = get_national_team(NATION_TRINIDAD_TOBAGO_9CF());
		teamList[count++].club = get_national_team(NATION_HAITI_9CF());
	}
	else {
		if (year % 4 == 3) teamList[count++].club = get_national_team(NATION_SAUDI_ARABIA_9CF());
		else teamList[count++].club = get_national_team(NATION_QATAR_9CF());
	}
	data->special_nteams_seedings = count;
}

char gold_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* gold_cup_quals = get_loaded_league(GOLD_CUP_QUALIFYING_9CF());

	DWORD v1 = *(DWORD*)gold_cup_quals;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(gold_cup_quals);

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
	data->year += 2;
	data->f68 = -1;
	data->current_stage = -1;
	data->f75 = 1;
	gold_cup_seeded_teams(_this);
	gold_cup_subs(_this);
	data->team_league_table = 0;
	return 1;
}

void __declspec(naked) gold_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gold_cup_update
		add esp, 0x4
		ret
	}
}

void gold_cup_final_stage_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;

	char stage_num = 3;

	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 3; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
	}

	BYTE team_order[8] = { 4,1,2,7,6,3,0,5 };
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

void gold_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 3) {
			gold_cup_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) gold_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gold_cup_stages_create
		add esp, 0x4
		ret
	}
}

void gold_cup_setup1(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	WORD n = data->special_nteams_seedings;
	vector<cm3_clubs*> qualified_teams;
	for (WORD i = 0; i < n; i++) qualified_teams.push_back(teamList[i].club);
	if (data->year != 2025) {
		data->f75 = 0;
		if (n < 16) {
			string msg = "Not enough teams in Gold Cup: needed 16 but only had " + to_string(n);
			vector<cm3_clubs*> nat_teams = get_national_teams_of_continent_fifa_members(NORTH_AMERICA_9CF());
			sort(nat_teams.begin(), nat_teams.end(), compareNationRanking);
			for (WORD i = 0; n < 16 && i < nat_teams.size(); i++) {
				cm3_clubs* c = nat_teams[i];
				if (!vector_contains_element(qualified_teams, c)) {
					teamList[n++].club = c;
					qualified_teams.push_back(c);
				}
			}
			data->special_nteams_seedings = 16;
			create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
		}
		if (n < 16) {
			string msg = "Something went wrong... only have " + to_string(n) + " teams for the Gold Cup!";
			create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
		}
		sort(qualified_teams.begin(), qualified_teams.end(), compareNationRanking);
		for (WORD i = 0; i < n; i++) {
			cm3_clubs* c = qualified_teams[i];
			teamList[i].club = c;
			if (i < 4) teamList[i].seeding = 3;
			else if (i < 8) teamList[i].seeding = 10;
			else if (i < 12) teamList[i].seeding = 11;
			else teamList[i].seeding = 12;
		}
	}
}

void gold_cup_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	if (year == 2025) {
		vector<cm3_clubs*> clubs;
		clubs.push_back(get_national_team(NATION_MEXICO_9CF()));
		clubs.push_back(get_national_team(NATION_COSTA_RICA_9CF()));
		clubs.push_back(get_national_team(NATION_DOMINICAN_REPUBLIC_9CF()));
		clubs.push_back(get_national_team(NATION_SURINAM_9CF()));
		clubs.push_back(get_national_team(NATION_CANADA_9CF()));
		clubs.push_back(get_national_team(NATION_HONDURAS_9CF()));
		clubs.push_back(get_national_team(NATION_CURACAO_9CF()));
		clubs.push_back(get_national_team(NATION_EL_SALVADOR_9CF()));
		clubs.push_back(get_national_team(NATION_PANAMA_9CF()));
		clubs.push_back(get_national_team(NATION_GUATEMALA_9CF()));
		clubs.push_back(get_national_team(NATION_JAMAICA_9CF()));
		clubs.push_back(get_national_team(NATION_GUADELOUPE_9CF()));
		clubs.push_back(get_national_team(NATION_USA_9CF()));
		clubs.push_back(get_national_team(NATION_SAUDI_ARABIA_9CF()));
		clubs.push_back(get_national_team(NATION_TRINIDAD_TOBAGO_9CF()));
		clubs.push_back(get_national_team(NATION_HAITI_9CF()));

		for (BYTE i = 0; i < 16; i++) {
			teamList[i].club = clubs[i];
			teamList[i].seeding = 6;
		}
		teamList[0].seeding = 1;
		data->special_nteams_seedings = 16;
	}
	else
	{
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < 16; i++) clubs.push_back(teamList[i].club);
		shuffle(clubs.begin(), clubs.begin() + 4, rng);
		shuffle(clubs.begin() + 4, clubs.begin() + 8, rng);
		shuffle(clubs.begin() + 8, clubs.begin() + 12, rng);
		shuffle(clubs.begin() + 12, clubs.end(), rng);
		for (int i = 0; i < 12; i++) teamList[i].club = clubs[i];
	}
}

void gold_cup_setup2(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	gold_cup_all_teams(_this);
	gold_cup_setup_first_group(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	data->f69 = 1;
	for (BYTE i = 0; i < 3; i++) gold_cup_setup_groups(_this, i);
	gold_cup_reputation_setup(_this);
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);
}

void gold_cup_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	WORD day2 = *(WORD*)(_this + 0xB6);
	short year2 = *(short*)(_this + 0xB8);
	if (day2 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year2) {
		if (a3) {
			gold_cup_setup1(_this);
			gold_cup_setup2(_this);
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) gold_cup_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_init2
		add esp, 0xc
		ret 8
	}
}

int gold_cup_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 3) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), GroupStage, 0x1E);
			sub_775000((BYTE*)*b74318, club->ClubNation);
			return 0;
		}
	}
	else if (stage == 3) {
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
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) gold_cup_table_fates_c()
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
		call gold_cup_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

WORD gold_cup_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	if (val == 1) return -1;
	else if (val == 2) return Final;
	else if (val < 5) return SemiFinal;
	else if (val < 9) return QuarterFinal;
	else
	{
		short ret = (val > 9) - 1;
		return (ret & 0x18) - 4;
	}
}

void __declspec(naked) gold_cup_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE gold_cup_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	if (al < 3) {
		if (bl < 3) return 1;
		else if (bl < 5) return 0;
		else return (bl < 9) - 2;
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
		else return (bl < 13) - 1;
	}
	else {
		if (bl < 3) return 3;
		else if (bl < 5) return 2;
		else if (bl < 9) return 1;
		else return 0;
	}
}

void __declspec(naked) gold_cup_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_vtable30
		add esp, 0x8
		ret 4
	}
}

int gold_cup_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 3) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 3) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	return 0;
}

void __declspec(naked) gold_cup_stage_news_c()
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
		call gold_cup_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void gold_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)gold_cup_vtable->vtable_ptr;
	gold_cup_vtable->SetPointer(VTableInitFree, (DWORD)&gold_cup_free_c);
	gold_cup_vtable->SetPointer(VTableSubsRounds, (DWORD)&gold_cup_subs_c);
	gold_cup_vtable->SetPointer(VTableLeagueSplit, (DWORD)&gold_cup_init2_c);
	gold_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&gold_cup_update_c);
	gold_cup_vtable->SetPointer(VTableReputationCalc, (DWORD)&gold_cup_reputation_calc_c);
	gold_cup_vtable->SetPointer(VTableReputationSetup, (DWORD)&gold_cup_reputation_setup_c);
	gold_cup_vtable->SetPointer(VTableSetChampion, (DWORD)&gold_cup_set_champion_c);
	gold_cup_vtable->SetPointer(VTableFixtures, (DWORD)&gold_cup_fixture_caller);
	gold_cup_vtable->SetPointer(VTablePlayoffQual, (DWORD)&gold_cup_stages_create_c);
	gold_cup_vtable->SetPointer(VTableTableFates, (DWORD)&gold_cup_table_fates_c);
	gold_cup_vtable->SetPointer(VTableStageNews, (DWORD)&gold_cup_stage_news_c);
	gold_cup_vtable->SetPointer(VTable29, (DWORD)&gold_cup_vtable29_c);
	gold_cup_vtable->SetPointer(VTable30, (DWORD)&gold_cup_vtable30_c);
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f75 = 1;
	data->rules = RulesInternational;
	data->year = year + 1;
	while (data->year % 2 != 1) data->year++;
	data->f81 = 0xf;
	data->special_nteams_seedings = 0;
	data->f56 = 16;
	BYTE* pMem = (BYTE*)cm0102_malloc(16 * 6);
	data->special_teams_seedings = (DWORD*)pMem;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f217 = 0x28;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 4;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	gold_cup_seeded_teams(_this);
	gold_cup_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	if (data->year == year) data->special_nteams_seedings = 16;
	else data->f69 = 0;
	data->team_league_table = 0;
	data->n_teams = 0;
}

void setup_gold_cup() {
}