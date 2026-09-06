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

DWORD* copa_america_vtable = (DWORD*)0x96B400;

int copa_america_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* final_bytes = (BYTE*)comp_data->stages[3];
	BYTE* third_playoff_bytes = (BYTE*)comp_data->stages[4];
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

void __declspec(naked) copa_america_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call copa_america_set_champion
		add esp, 0x4
		ret 0
	}
}

void copa_america_subs(BYTE* _this)
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
	convert_to_cm_date(cm_date, 17, May, data->year, Saturday);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = 0;

	DWORD v1 = *(DWORD*)_this;
	data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) copa_america_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call copa_america_subs
		add esp, 0x4
		ret
	}
}

DWORD copa_america_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddFixture(pMem, 0, Date(year, 6, 22), year, Saturday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 0, 2);
		AddFixture(pMem, 1, Date(year, 6, 26), year, Wednesday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 1, 2);
		AddFixture(pMem, 2, Date(year, 6, 30), year, Sunday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 2, 2);
		if (stage_idx == -1) {
			AddFixtureTV(pMem, 0, 0, 3, Thursday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 0, 1, 3, Friday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 1, 0, 3, Tuesday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 1, 1, 3, Tuesday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 0, 3, Saturday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 1, 3, Saturday, Afternoon, LargestStadium1);
		}
		else if (stage_idx == 0) {
			AddFixtureTV(pMem, 0, 0, 3, Saturday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 0, 1, 3, Saturday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 1, 0, 3, Wednesday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 1, 1, 3, Wednesday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 0, 3, Sunday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 1, 3, Sunday, Afternoon, LargestStadium3);
		}
		else if (stage_idx == 1) {
			AddFixtureTV(pMem, 0, 0, 3, Sunday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 0, 1, 3, Sunday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 1, 0, 3, Thursday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 1, 1, 3, Thursday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 2, 0, 3, Monday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 2, 1, 3, Monday, Afternoon, LargestStadium4);
		}
		else if (stage_idx == 2) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 0, 3, Friday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 1, 3, Friday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 0, 3, Tuesday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 1, 3, Tuesday, Afternoon, LargestStadium7);
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 3), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 5), year, Friday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Afternoon, LargestStadium4);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Friday, Afternoon, LargestStadium6);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium5);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium7);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 8, 4, 8, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 7), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 10), year, Wednesday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Wednesday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 14), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = ThirdPlacePlayoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 10), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 13), year, Saturday, Afternoon, LargestStadium2);
		FillFixtureDetails(pMem, fixture_id++, None, 0, Penalties | ExtraTime, NoTiebreak, 10, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) copa_america_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call copa_america_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void copa_america_reputation_setup(BYTE* _this) {
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

void __declspec(naked) copa_america_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call copa_america_reputation_setup
		add esp, 0x4
		ret
	}
}

void copa_america_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
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

void __declspec(naked) copa_america_reputation_calc_c()
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
		call copa_america_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void copa_america_setup_first_group(BYTE* _this, BYTE* pMem) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* tMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)tMem;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < 16 && teamsAdded < 4; i++) {
		if (*((BYTE*)(pMem + 5 * i + 4)) == 1) {
			DWORD club_id = *((DWORD*)(pMem + 5 * i));
			add_team_call(_this, teamsAdded++, get_club(club_id), 0, 0);
		}
	}
	sub_684230(_this);
}

void copa_america_setup_groups(BYTE* _this, BYTE idx, BYTE* pMem) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < 16 && teamsAdded < data->n_teams; i++) {
		if (*((BYTE*)(pMem + 5 * i + 4)) == (idx + 2)) {
			DWORD club_id = *((DWORD*)(pMem + 5 * i));
			*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)get_club(club_id);
		}
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

void copa_america_seeded_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	data->special_nteams_seedings = 0;
	WORD count = data->special_nteams_seedings;
	WORD year = data->year;
	DWORD host1_id = -1, host2_id = -1;
	WORD num_hosts = get_comp_hosts_in_continent(_this, COPA_AMERICA_9CF(), SOUTH_AMERICA_9CF(), &host1_id, &host2_id);
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
	vector<cm3_clubs*> sam_countries = get_national_teams_of_continent(SOUTH_AMERICA_9CF());
	for (cm3_clubs* c : sam_countries) {
		if (c->ClubNation->NationID != host1_id && c->ClubNation->NationID != host2_id) {
			teamList[count].club = c;
			teamList[count].seeding = 6;
			count++;
		}
	}
	for (WORD i = count; i < 16; i++)
	{
		teamList[i].club = 0;
		teamList[i].seeding = 6;
	}
	if (year == 2024) {
		teamList[count++].club = get_national_team(NATION_ARGENTINA_9CF());
		teamList[count++].club = get_national_team(NATION_MEXICO_9CF());
		teamList[count++].club = get_national_team(NATION_USA_9CF());
		teamList[count++].club = get_national_team(NATION_BRAZIL_9CF());
		teamList[count++].club = get_national_team(NATION_PERU_9CF());
		teamList[count++].club = get_national_team(NATION_ECUADOR_9CF());
		teamList[count++].club = get_national_team(NATION_URUGUAY_9CF());
		teamList[count++].club = get_national_team(NATION_COLOMBIA_9CF());
		teamList[count++].club = get_national_team(NATION_CHILE_9CF());
		teamList[count++].club = get_national_team(NATION_VENEZUELA_9CF());
		teamList[count++].club = get_national_team(NATION_PANAMA_9CF());
		teamList[count++].club = get_national_team(NATION_PARAGUAY_9CF());
		teamList[count++].club = get_national_team(NATION_CANADA_9CF());
		teamList[count++].club = get_national_team(NATION_JAMAICA_9CF());
		teamList[count++].club = get_national_team(NATION_BOLIVIA_9CF());
		teamList[count++].club = get_national_team(NATION_COSTA_RICA_9CF());
	}
	data->special_nteams_seedings = count;
}

char copa_america_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* copa_america_quals = get_loaded_league(COPA_AMERICA_QUALIFYING_9CF());

	DWORD v1 = *(DWORD*)copa_america_quals;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(copa_america_quals);

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
	data->year += 4;
	data->f68 = -1;
	data->current_stage = -1;
	data->f75 = 1;
	copa_america_seeded_teams(_this);
	copa_america_subs(_this);
	data->team_league_table = 0;
	return 1;
}

void __declspec(naked) copa_america_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call copa_america_update
		add esp, 0x4
		ret
	}
}

void copa_america_final_stage_setup(BYTE* _this) {
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

	BYTE team_order[8] = { 0,2,3,1,4,6,7,5 };
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

void copa_america_third_place_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	char stage_num = 4;

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

void copa_america_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 3) {
			copa_america_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) copa_america_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call copa_america_stages_create
		add esp, 0x4
		ret
	}
}

void copa_america_setup1(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	WORD n = data->special_nteams_seedings;
	vector<cm3_clubs*> qualified_teams;
	for (WORD i = 0; i < n; i++) qualified_teams.push_back(teamList[i].club);
	if (data->year != 2024) {
		data->f75 = 0;
		if (n < 16) {
			string msg = "Not enough teams in Copa América: needed 16 but only had " + to_string(n);
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
			string msg = "Something went wrong... only have " + to_string(n) + " teams for the Copa América!";
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
			if (i < 4) teamList[i].seeding = 3;
			else if (i < 8) teamList[i].seeding = 10;
			else if (i < 12) teamList[i].seeding = 11;
			else teamList[i].seeding = 12;
		}
	}
}

void copa_america_update_continent_counts(cm3_clubs* club, DWORD idx, BYTE concacaf[], BYTE conmebol[]) {
	if (club->ClubNation->NationContinent->ContinentID == NORTH_AMERICA_9CF())
	{
		concacaf[idx]++;
	}
	else {
		conmebol[idx]++;
	}
}

bool copa_america_can_team_enter_group(cm3_clubs* club, DWORD idx, BYTE concacaf[], BYTE conmebol[]) {
	if (club->ClubNation->NationContinent->ContinentID == NORTH_AMERICA_9CF())
	{
		return concacaf[idx] < 2;
	}
	else
	{
		return conmebol[idx] < 3;
	}
	return true;
}

BYTE* copa_america_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	BYTE* pMem = (BYTE*)cm0102_malloc(16 * 5);
	if (year == 2024) {
		WORD x = 0;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ARGENTINA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_MEXICO_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_USA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BRAZIL_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PERU_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ECUADOR_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_URUGUAY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_COLOMBIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CHILE_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_VENEZUELA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PANAMA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PARAGUAY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CANADA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_JAMAICA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BOLIVIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_COSTA_RICA_9CF())->ClubID;

		for (BYTE i = 0; i < 16; i++) {
			teamList[i].club = get_club(*((DWORD*)(pMem + 5 * i)));
			teamList[i].seeding = 6;
			*((BYTE*)(pMem + 5 * i + 4)) = (i >> 2) + 1;
		}
		teamList[0].seeding = 1;
		data->special_nteams_seedings = 16;
	}
	else
	{
		BYTE counts[4] = { 0,0,0,0 };
		BYTE counts_concacaf[4] = { 0,0,0,0 };
		BYTE counts_conmebol[4] = { 0,0,0,0 };
		DWORD host1_id = -1, host2_id = -1;
		char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
		BYTE offset = 4 - num_hosts;
		for (WORD i = 0; i < 4; i++) {
			counts[i]++;
			if (i == 0) {
				*((DWORD*)(pMem)) = teamList[0].club->ClubID;
				*((BYTE*)(pMem + 4)) = 1;
				teamList[0].seeding = -1;
				copa_america_update_continent_counts(teamList[0].club, 0, counts_concacaf, counts_conmebol);
			}
			else if (i == 1 && num_hosts > 1) {
				*((DWORD*)(pMem + 5)) = teamList[1].club->ClubID;
				*((BYTE*)(pMem + 9)) = 2;
				teamList[1].seeding = -1;
				copa_america_update_continent_counts(teamList[1].club, 1, counts_concacaf, counts_conmebol);
			}
			else {
				BYTE r = rand() % offset + num_hosts;
				while (teamList[r].seeding == -1) r = rand() % offset + num_hosts;
				*((DWORD*)(pMem + 5 * i)) = teamList[r].club->ClubID;
				*((BYTE*)(pMem + 5 * i + 4)) = i + 1;
				teamList[r].seeding = -1;
				copa_america_update_continent_counts(teamList[r].club, i, counts_concacaf, counts_conmebol);
			}
		}
		for (DWORD i = 4; i < 16; i++) {
			cm3_clubs* club = teamList[i].club;
			DWORD b = i / 4 + 1;
			DWORD r = rand() % 4;
			bool valid = false;
			for (WORD iters = 0; iters < 24; iters++) {
				if (counts[r] >= b) {
					r = rand() % 4;
					continue;
				}
				if (!copa_america_can_team_enter_group(club, r, counts_concacaf, counts_conmebol)) {
					r = rand() % 4;
					continue;
				}
				valid = true;
				break;
			}
			if (!valid) {
				for (DWORD j = 4; j <= i; j++) teamList[j].seeding = 6;
				for (DWORD j = 0; j < 4; j++)
				{
					counts[j] = 1;
					counts_concacaf[j] = 0;
					counts_conmebol[j] = 0;
				}
				for (DWORD j = 0; j < 4; j++)
				{
					copa_america_update_continent_counts(get_club(*((DWORD*)(pMem + 5 * j))), *((BYTE*)(pMem + 5 * j + 4)) - 1, counts_concacaf, counts_conmebol);
				}
				i = 3;
				continue;
			}
			*((DWORD*)(pMem + 5 * i)) = club->ClubID;
			*((BYTE*)(pMem + 5 * i + 4)) = (BYTE)(r + 1);
			teamList[i].seeding = -1;
			counts[r]++;
			copa_america_update_continent_counts(club, r, counts_concacaf, counts_conmebol);
		}
		for (WORD i = 0; i < 16; i++) {
			if (i < 4) teamList[i].seeding = 3;
			else if (i < 8) teamList[i].seeding = 10;
			else if (i < 12) teamList[i].seeding = 11;
			else teamList[i].seeding = 12;
		}
	}
	return pMem;
}

void copa_america_setup2(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* pMem = copa_america_all_teams(_this);
	copa_america_setup_first_group(_this, pMem);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	data->f69 = 1;
	for (BYTE i = 0; i < 3; i++) copa_america_setup_groups(_this, i, pMem);
	sub_9452CA_free(pMem);
	copa_america_reputation_setup(_this);
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);
}

void copa_america_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	WORD day2 = *(WORD*)(_this + 0xB6);
	short year2 = *(short*)(_this + 0xB8);
	if (day2 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year2) {
		if (a3) {
			copa_america_setup1(_this);
			copa_america_setup2(_this);
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) copa_america_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call copa_america_init2
		add esp, 0xc
		ret 8
	}
}

void copa_america_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = copa_america_vtable;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f75 = 1;
	data->rules = RulesInternational;
	data->year = year + 1;
	while (data->year % 4 != 0) data->year++;
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
	data->num_stages = 5;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	copa_america_seeded_teams(_this);
	copa_america_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	if (data->year == year) data->special_nteams_seedings = 16;
	else data->f69 = 0;
	data->team_league_table = 0;
	data->n_teams = 0;
}

int copa_america_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
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
			WORD round_name = *(WORD*)(rounds + playoff_dates_sz * current_round + 7);
			if (round_name == SemiFinal) {
				if (comp_data->current_stage < comp_data->num_stages - 1) copa_america_third_place_setup(_this);
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
	else if (stage == 4) {
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

void __declspec(naked) copa_america_table_fates_c()
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
		call copa_america_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

WORD copa_america_vtable29(BYTE* _this, cm3_clubs* club) {
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

void __declspec(naked) copa_america_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call copa_america_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE copa_america_vtable30(BYTE* _this, cm3_clubs* club) {
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

void __declspec(naked) copa_america_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call copa_america_vtable30
		add esp, 0x8
		ret 4
	}
}

int copa_america_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 3) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 3) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 4)
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

void __declspec(naked) copa_america_stage_news_c()
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
		call copa_america_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void copa_america_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
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

void __declspec(naked) copa_america_landmarks_c()
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
		call copa_america_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

void setup_copa_america() {
	WriteVTablePtr(copa_america_vtable, VTableSubsRounds, (DWORD)&copa_america_subs_c);
	WriteVTablePtr(copa_america_vtable, VTableLeagueSplit, (DWORD)&copa_america_init2_c);
	WriteVTablePtr(copa_america_vtable, VTableEoSUpdate, (DWORD)&copa_america_update_c);
	WriteVTablePtr(copa_america_vtable, VTableReputationCalc, (DWORD)&copa_america_reputation_calc_c);
	WriteVTablePtr(copa_america_vtable, VTableReputationSetup, (DWORD)&copa_america_reputation_setup_c);
	WriteVTablePtr(copa_america_vtable, VTableSetChampion, (DWORD)&copa_america_set_champion_c);
	WriteVTablePtr(copa_america_vtable, VTableFixtures, (DWORD)&copa_america_fixture_caller);
	WriteVTablePtr(copa_america_vtable, VTablePlayoffQual, (DWORD)&copa_america_stages_create_c);
	WriteVTablePtr(copa_america_vtable, VTableTableFates, (DWORD)&copa_america_table_fates_c);
	WriteVTablePtr(copa_america_vtable, VTableStageNews, (DWORD)&copa_america_stage_news_c);
	WriteVTablePtr(copa_america_vtable, VTable29, (DWORD)&copa_america_vtable29_c);
	WriteVTablePtr(copa_america_vtable, VTable30, (DWORD)&copa_america_vtable30_c);
	WriteVTablePtr(copa_america_vtable, VTableClubLandmarks, (DWORD)&copa_america_landmarks_c);
	WriteVTablePtr(copa_america_vtable, VTableShowHostsInHistory, 0x404480);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(copa_america_vtable, VTableShowThirdInHistory, 0x4110b0);
}