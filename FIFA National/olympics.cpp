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

DWORD* olympics_vtable = (DWORD*)0x96E1D0;
DWORD olympics_table_start_offset = 0x7a0230;

int olympics_set_champion(BYTE* _this) {
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
		if (teams[i].f6 == 1) third = get_national_team(teams[i].club->ClubNation->NationID);
	}
	teams = (teams_seeded*)final_data->teams_list;
	for (WORD i = 0; i < final_data->n_teams; i++) {
		if (teams[i].f6 == 1) first = get_national_team(teams[i].club->ClubNation->NationID);
		else if (teams[i].f6 == 2) second = get_national_team(teams[i].club->ClubNation->NationID);
	}
	DWORD host1_id = -1, host2_id = -1;
	char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, comp_data->competition_db->ClubCompID, comp_data->year, &host1_id, &host2_id, 1);
	sub_4AFCE0_add_history_entry(_this, first, second, third, num_hosts > 0 ? get_national_team(host1_id) : 0);
	return 0;
}

void __declspec(naked) olympics_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call olympics_set_champion
		add esp, 0x4
		ret 0
	}
}

void olympics_subs(BYTE* _this)
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
	convert_to_cm_date(cm_date, 23, May, data->year, Thursday);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = 0;

	DWORD v1 = *(DWORD*)_this;
	data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) olympics_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call olympics_subs
		add esp, 0x4
		ret
	}
}

DWORD olympics_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixture(pMem, 0, Date(year, 7, 10), year, Monday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 0, 2);
		AddFixture(pMem, 1, Date(year, 7, 13), year, Thursday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 1, 2);
		AddFixture(pMem, 2, Date(year, 7, 16), year, Sunday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 2, 2);
		if (stage_idx == -1) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 1, 0, 3, Thursday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Thursday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 2, 0, 3, Sunday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 2, 1, 3, Sunday, Afternoon, LargestStadium4);
		}
		else if (stage_idx == 0) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Afternoon, LargestStadium9);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 1, 0, 3, Thursday, Afternoon, LargestStadium9);
			AddFixtureTV(pMem, 1, 1, 3, Thursday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 0, 3, Sunday, Afternoon, LargestStadium9);
			AddFixtureTV(pMem, 2, 1, 3, Sunday, Afternoon, LargestStadium6);
		}
		else if (stage_idx == 1) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 0, 3, Thursday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 1, 1, 3, Thursday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 2, 0, 3, Sunday, Afternoon, LargestStadium5);
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 17), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 20), year, Thursday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Afternoon, LargestStadium6);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Afternoon, LargestStadium5);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Afternoon, LargestStadium4);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 8, 4, 8, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 21), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 24), year, Monday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 22), year, Tuesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 28), year, Friday, Afternoon, NationalStadium);
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 21), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 27), year, Thursday, Afternoon, LargestStadium1);
		FillFixtureDetails(pMem, fixture_id++, None, 0, Penalties | ExtraTime, NoTiebreak, 10, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) olympics_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call olympics_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void olympics_reputation_setup(BYTE* _this) {
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
		for (int i = 8; i < 9; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 9; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 10);
		}
	}
}

void __declspec(naked) olympics_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call olympics_reputation_setup
		add esp, 0x4
		ret
	}
}

void olympics_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 2) {
		ret_current = 1 + 3 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 3 * (min - 1);
		if (max < 3) ret_max = 5;
		else ret_max = 1 + 3 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 2) {
		if (current < 3) ret_current = 5;
		else ret_current = 9;
		if (min < 3) ret_min = 1;
		else ret_min = 9;
		if (max < 3) ret_max = 5;
		else ret_max = 9;
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

void __declspec(naked) olympics_reputation_calc_c()
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
		call olympics_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void olympics_setup_first_group(BYTE* _this, BYTE* pMem) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* tMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)tMem;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < 12 && teamsAdded < 4; i++) {
		if (*((BYTE*)(pMem + 5 * i + 4)) == 1) {
			DWORD club_id = *((DWORD*)(pMem + 5 * i));
			add_team_call(_this, teamsAdded++, get_club(club_id), 0, 0);
		}
	}
	sub_684230(_this);
}

void olympics_setup_groups(BYTE* _this, BYTE idx, BYTE* pMem) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < 12 && teamsAdded < data->n_teams; i++) {
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

void olympics_best_placed_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	char stage_num = 2;

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
	for (char al = -1; al < 2; al++) {
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

void olympics_setup_best_placed(BYTE* _this) {
	char stage_num = 2;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 2, 0, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };
	create_league_stage_data(pStage, _this, 3, 0, 0, (DWORD)(data->competition_db), 0, 0,
		data->pts_for_win, data->pts_for_draw, data->f196, &tiebreaks[0], &prom_rel[0],
		year, stage_num, BestPlacedTeams, 0, 1, 0, 0x28, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	data->current_stage = stage_num;
	olympics_best_placed_update(_this);
}

void olympics_seeded_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	data->special_nteams_seedings = 0;
	WORD count = data->special_nteams_seedings;
	WORD year = data->year;
	DWORD host1_id = -1, host2_id = -1;
	DWORD host_continent = -1;
	char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
	if (num_hosts > 0) {
		teamList[count].club = get_national_team(host1_id, true);
		teamList[count].seeding = 1;
		host_continent = teamList[count].club->ClubNation->NationContinent->ContinentID;
		count++;
	}
	for (WORD i = count; i < 12; i++)
	{
		teamList[i].club = 0;
		teamList[i].seeding = 6;
	}
	if (year == 2024) {
		//teamList[count++].club = get_national_team(NATION_MOROCCO_9CF());
		//teamList[count++].club = get_national_team(NATION_MALI_9CF());
		//teamList[count++].club = get_national_team(NATION_COMOROS_9CF());
		//teamList[count++].club = get_national_team(NATION_ZAMBIA_9CF());
		//teamList[count++].club = get_national_team(NATION_EGYPT_9CF());
		//teamList[count++].club = get_national_team(NATION_SOUTH_AFRICA_9CF());
		//teamList[count++].club = get_national_team(NATION_ANGOLA_9CF());
		//teamList[count++].club = get_national_team(NATION_ZIMBABWE_9CF());
		//teamList[count++].club = get_national_team(NATION_NIGERIA_9CF());
		//teamList[count++].club = get_national_team(NATION_TUNISIA_9CF());
		//teamList[count++].club = get_national_team(NATION_TANZANIA_9CF());
		//teamList[count++].club = get_national_team(NATION_UGANDA_9CF());
		//teamList[count++].club = get_national_team(NATION_SENEGAL_9CF());
		//teamList[count++].club = get_national_team(NATION_DR_CONGO_9CF());
		//teamList[count++].club = get_national_team(NATION_BENIN_9CF());
		//teamList[count++].club = get_national_team(NATION_BOTSWANA_9CF());
		//teamList[count++].club = get_national_team(NATION_ALGERIA_9CF());
		//teamList[count++].club = get_national_team(NATION_BURKINA_FASO_9CF());
		//teamList[count++].club = get_national_team(NATION_SUDAN_9CF());
		//teamList[count++].club = get_national_team(NATION_EQUATORIAL_GUINEA_9CF());
		//teamList[count++].club = get_national_team(NATION_IVORY_COAST_9CF());
		//teamList[count++].club = get_national_team(NATION_CAMEROON_9CF());
		//teamList[count++].club = get_national_team(NATION_MOZAMBIQUE_9CF());
		//teamList[count++].club = get_national_team(NATION_GABON_9CF());
	}
	// no qualifiers, pick random teams for now
	else {
		vector<cm3_clubs*> nations = get_national_teams_of_continent_fifa_members(EUROPE_9CF(), true);
		sort(nations.begin(), nations.end(), compareNationRanking);
		cm3_clubs* russia = get_national_team(NATION_RUSSIA_9CF(), true);
		auto it = find(nations.begin(), nations.end(), russia);
		if (it != nations.end()) nations.erase(it);
		size_t size = 16;
		vector<cm3_clubs*> nations_filter = vector(nations.begin(), nations.begin() + size);
		vector<cm3_clubs*> quals = get_random_weighted_national_teams(nations_filter, 3 - (host_continent == EUROPE_9CF()));
		for (cm3_clubs* n : quals) teamList[count++].club = n;

		nations = get_national_teams_of_continent_fifa_members(AFRICA_9CF(), true);
		sort(nations.begin(), nations.end(), compareNationRanking);
		size = 12;
		nations_filter = vector(nations.begin(), nations.begin() + size);
		quals = get_random_weighted_national_teams(nations_filter, 2 - (host_continent == AFRICA_9CF()));
		for (cm3_clubs* n : quals) teamList[count++].club = n;

		nations = get_national_teams_of_continent_fifa_members(ASIA_9CF(), true);
		sort(nations.begin(), nations.end(), compareNationRanking);
		size = 12;
		nations_filter = vector(nations.begin(), nations.begin() + size);
		quals = get_random_weighted_national_teams(nations_filter, 2 - (host_continent == ASIA_9CF()));
		for (cm3_clubs* n : quals) teamList[count++].club = n;

		nations = get_national_teams_of_continent_fifa_members(NORTH_AMERICA_9CF(), true);
		sort(nations.begin(), nations.end(), compareNationRanking);
		size = 8;
		nations_filter = vector(nations.begin(), nations.begin() + size);
		quals = get_random_weighted_national_teams(nations_filter, 2 - (host_continent == NORTH_AMERICA_9CF()));
		for (cm3_clubs* n : quals) teamList[count++].club = n;

		nations = get_national_teams_of_continent_fifa_members(SOUTH_AMERICA_9CF(), true);
		sort(nations.begin(), nations.end(), compareNationRanking);
		size = 6;
		nations_filter = vector(nations.begin(), nations.begin() + size);
		quals = get_random_weighted_national_teams(nations_filter, 2 - (host_continent == SOUTH_AMERICA_9CF()));
		for (cm3_clubs* n : quals) teamList[count++].club = n;

		nations = get_national_teams_of_continent_fifa_members(OCEANIA_9CF(), true);
		sort(nations.begin(), nations.end(), compareNationRanking);
		size = 2;
		nations_filter = vector(nations.begin(), nations.begin() + size);
		quals = get_random_weighted_national_teams(nations_filter, 1 - (host_continent == OCEANIA_9CF()));
		for (cm3_clubs* n : quals) teamList[count++].club = n;

		if (count != 12)
		{
			string msg = "Wrong number of teams: " + to_string(count);
			create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
		}
	}
	data->special_nteams_seedings = count;
}

char olympics_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

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
	olympics_seeded_teams(_this);
	olympics_subs(_this);
	data->team_league_table = 0;
	return 1;
}

void __declspec(naked) olympics_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call olympics_update
		add esp, 0x4
		ret
	}
}

#pragma warning(push)
#pragma warning(disable:6385)
void olympics_final_stage_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;

	char stage_num = 3;

	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 2; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
		staff_history_failed_qual_86C1D0(staff_hist_ptr, table_teams[3].club, (DWORD)(data->competition_db), GroupStage, 0x1E);
	}
	comp_stats* best_placed_stage = (comp_stats*)(data->stages[2]);
	team_league_stats* best_placed_table = (team_league_stats*)(best_placed_stage->team_league_table);
	char best_third_letters[3] = { 0,0,0, };
	char letter_idx = 0;
	curr_stage = data;
	for (char al = -1; al < 2; al++) {
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
	for (WORD i = 2; i < best_placed_stage->n_teams; i++)
	{
		staff_history_failed_qual_86C1D0(staff_hist_ptr, best_placed_table[i].club, (DWORD)(data->competition_db), GroupStage, 0x1E);
	}

	char key[5] = { '\0' };
	char indexes[5] = { '\0' };
	for (int i = 0; i < 3; i++) {
		strncpy_s(key, (char*)(olympics_table_start_offset + 4 * i), 2);
		if (strcmp(key, best_third_letters) == 0) {
			strncpy_s(indexes, (char*)(olympics_table_start_offset + 4 * i + 2), 2);
			break;
		}
	}

	BYTE table_order[2] = { 1,3, };
	BYTE team_order[8] = { 0,6,4,7,2,5, };
	for (char i = 0; i < 2; i++) team_order[i + 6] = table_order[indexes[i] - 1];
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

void olympics_third_place_setup(BYTE* _this) {
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

void olympics_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 3) {
			olympics_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) olympics_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call olympics_stages_create
		add esp, 0x4
		ret
	}
}

void olympics_setup1(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	WORD n = data->special_nteams_seedings;
	vector<cm3_clubs*> qualified_teams;
	for (WORD i = 0; i < n; i++) qualified_teams.push_back(teamList[i].club);
	if (data->year != 2024) {
		data->f75 = 0;
		if (n < 12) {
			string msg = "Not enough teams in Olympics: needed 12 but only had " + to_string(n);
			vector<cm3_clubs*> nat_teams = get_all_national_teams(true);
			sort(nat_teams.begin(), nat_teams.end(), compareNationRanking);
			for (WORD i = 0; n < 12 && i < nat_teams.size(); i++) {
				cm3_clubs* c = nat_teams[i];
				if (!vector_contains_element(qualified_teams, c)) {
					teamList[n++].club = c;
					qualified_teams.push_back(c);
				}
			}
			data->special_nteams_seedings = 12;
			create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
		}
		if (n < 12) {
			string msg = "Something went wrong... only have " + to_string(n) + " teams for the Olympics!";
			create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
		}
		WORD year = data->year;
		DWORD host1_id = -1, host2_id = -1;
		char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
		cm3_clubs* host1, * host2;
		if (num_hosts < 1) host1 = 0;
		else host1 = get_national_team(host1_id, true);
		if (num_hosts < 2) host2 = 0;
		else host2 = get_national_team(host2_id, true);
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
			if (i < 3) teamList[i].seeding = 3;
			else if (i < 6) teamList[i].seeding = 10;
			else if (i < 9) teamList[i].seeding = 11;
			else teamList[i].seeding = 12;
		}
	}
}

BYTE* olympics_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	BYTE* pMem = (BYTE*)cm0102_malloc(12 * 5);
	if (year == 2024) {
		//WORD x = 0;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_MEXICO_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SOUTH_AFRICA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SOUTH_KOREA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CZECH_REPUBLIC_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CANADA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BOSNIA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_QATAR_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SWITZERLAND_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BRAZIL_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_MOROCCO_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_HAITI_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SCOTLAND_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_USA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PARAGUAY_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_AUSTRALIA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_TURKEY_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_GERMANY_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CURACAO_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_IVORY_COAST_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ECUADOR_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_NETHERLANDS_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_JAPAN_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SWEDEN_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_TUNISIA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BELGIUM_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_EGYPT_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_IRAN_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_NEW_ZEALAND_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SPAIN_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CAPE_VERDE_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SAUDI_ARABIA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_URUGUAY_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_FRANCE_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SENEGAL_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_IRAQ_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_NORWAY_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ARGENTINA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ALGERIA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_AUSTRIA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_JORDAN_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PORTUGAL_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_DR_CONGO_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_UZBEKISTAN_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_COLOMBIA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ENGLAND_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CROATIA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_GHANA_9CF())->ClubID;
		//*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PANAMA_9CF())->ClubID;

		for (BYTE i = 0; i < 12; i++) {
			teamList[i].club = get_club(*((DWORD*)(pMem + 5 * i)));
			teamList[i].seeding = 6;
			*((BYTE*)(pMem + 5 * i + 4)) = (i >> 2) + 1;
		}
		teamList[0].seeding = 1;
		data->special_nteams_seedings = 12;
	}
	else
	{
		BYTE counts[3] = { 0,0,0 };
		BYTE group_continents[3][6] = {
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
		};
		DWORD host1_id = -1, host2_id = -1;
		char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
		num_hosts = (num_hosts > 0);
		BYTE offset = 3 - num_hosts;
		for (WORD i = 0; i < 3; i++) {
			if (i == 0 && num_hosts > 0) {
				*((DWORD*)(pMem)) = teamList[0].club->ClubID;
				*((BYTE*)(pMem + 4)) = 1;
				counts[0]++;
				teamList[0].seeding = -1;
				group_continents[0][teamList[0].club->ClubNation->NationContinent->ContinentID] = 1;
			}
			else {
				BYTE r = rand() % offset + num_hosts;
				while (teamList[r].seeding == -1) r = rand() % offset + num_hosts;
				*((DWORD*)(pMem + 5 * i)) = teamList[r].club->ClubID;
				*((BYTE*)(pMem + 5 * i + 4)) = i + 1;
				teamList[r].seeding = -1;
				counts[r]++;
				group_continents[r][teamList[r].club->ClubNation->NationContinent->ContinentID] = 1;
			}
		}
		for (DWORD i = 3; i < 12; i++) {
			cm3_clubs* club = teamList[i].club;
			DWORD b = i / 3 + 1;
			DWORD r;
			r = rand() % 3;
			bool valid = false;
			for (WORD iters = 0; iters < 12; iters++) {
				if (counts[r] >= b) {
					r = rand() % 3;
					continue;
				}
				if (group_continents[r][club->ClubNation->NationContinent->ContinentID] > 0) {
					r = rand() % 3;
					continue;
				}
				valid = true;
				break;
			}
			if (!valid) {
				for (DWORD j = 3; j <= i; j++) teamList[j].seeding = 6;
				for (DWORD j = 0; j < 3; j++)
				{
					counts[j] = 1;
					for (DWORD k = 0; k < 6; k++) group_continents[j][k] = 0;
				}
				for (DWORD j = 0; j < 3; j++)
				{
					group_continents[j][teamList[j].club->ClubNation->NationContinent->ContinentID] = 1;
				}
				i = 2;
				continue;
			}
			*((DWORD*)(pMem + 5 * i)) = club->ClubID;
			*((BYTE*)(pMem + 5 * i + 4)) = (BYTE)(r + 1);
			teamList[i].seeding = -1;
			counts[r]++;
			group_continents[r][teamList[i].club->ClubNation->NationContinent->ContinentID] = 1;
		}
		for (WORD i = 0; i < 12; i++) {
			if (i < 3) teamList[i].seeding = 3;
			else if (i < 6) teamList[i].seeding = 10;
			else if (i < 9) teamList[i].seeding = 11;
			else teamList[i].seeding = 12;
		}
	}
	return pMem;
}

void olympics_setup2(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* pMem = olympics_all_teams(_this);
	olympics_setup_first_group(_this, pMem);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	data->f69 = 1;
	for (BYTE i = 0; i < 2; i++) olympics_setup_groups(_this, i, pMem);
	olympics_setup_best_placed(_this);
	sub_9452CA_free(pMem);
	olympics_reputation_setup(_this);
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);
}

void olympics_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	WORD day2 = *(WORD*)(_this + 0xB6);
	short year2 = *(short*)(_this + 0xB8);
	if (day2 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year2) {
		if (a3) {
			olympics_setup1(_this);
			olympics_setup2(_this);
		}
	}
	else if (*(WORD*)(current_date) > day2 || *(WORD*)(current_date + 2) > data->year + year2) {
		char ret = sub_5AE6D0((BYTE*)current_date, data->competition_db->ClubCompID);
		if (ret) olympics_best_placed_update(_this);
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) olympics_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call olympics_init2
		add esp, 0xc
		ret 8
	}
}

void olympics_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = olympics_vtable;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f75 = 1;
	data->rules = RulesInternational;
	data->year = year;
	while (data->year % 4 != 0) data->year++;
	data->f81 = 0xf;
	data->special_nteams_seedings = 0;
	data->f56 = 12;
	BYTE* pMem = (BYTE*)cm0102_malloc(12 * 6);
	data->special_teams_seedings = (DWORD*)pMem;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f217 = 0x28;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 5;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	olympics_seeded_teams(_this);
	olympics_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	if (data->year == year) data->special_nteams_seedings = 12;
	else data->f69 = 0;
	data->team_league_table = 0;
	data->n_teams = 0;
}

int olympics_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 2) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		default:
			//staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), GroupStage, 0x1E);
			return 0;
		}
	}
	else if (stage == 2) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), GroupStage, 0x1E);
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
			//*a5 = 4;
			return 0;
		case Promoted:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			return 0;
		default:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			WORD round_name = *(WORD*)(rounds + playoff_dates_sz * current_round + 7);
			if (round_name == SemiFinal) {
				if (comp_data->current_stage < comp_data->num_stages - 1) olympics_third_place_setup(_this);
				comp_stats* stage = (comp_stats*)comp_data->stages[comp_data->current_stage];
				teams_seeded* teams = (teams_seeded*)stage->teams_list;
				if (!teams[0].club) teams[0].club = club;
				else if (!teams[1].club) teams[1].club = club;
			}
			return 0;
		}
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
			//*a5 = 4;
			return 0;
		case Promoted:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			return 0;
		default:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) olympics_table_fates_c()
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
		call olympics_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

int olympics_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 2) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 2) {
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

void __declspec(naked) olympics_stage_news_c()
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
		call olympics_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void olympics_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
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

void __declspec(naked) olympics_landmarks_c()
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
		call olympics_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

void setup_olympics() {
	WriteVTablePtr(olympics_vtable, VTableSubsRounds, (DWORD)&olympics_subs_c);
	WriteVTablePtr(olympics_vtable, VTableLeagueSplit, (DWORD)&olympics_init2_c);
	WriteVTablePtr(olympics_vtable, VTableEoSUpdate, (DWORD)&olympics_update_c);
	WriteVTablePtr(olympics_vtable, VTableReputationCalc, (DWORD)&olympics_reputation_calc_c);
	WriteVTablePtr(olympics_vtable, VTableReputationSetup, (DWORD)&olympics_reputation_setup_c);
	WriteVTablePtr(olympics_vtable, VTableSetChampion, (DWORD)&olympics_set_champion_c);
	WriteVTablePtr(olympics_vtable, VTableFixtures, (DWORD)&olympics_fixture_caller);
	WriteVTablePtr(olympics_vtable, VTablePlayoffQual, (DWORD)&olympics_stages_create_c);
	WriteVTablePtr(olympics_vtable, VTableTableFates, (DWORD)&olympics_table_fates_c);
	WriteVTablePtr(olympics_vtable, VTableStageNews, (DWORD)&olympics_stage_news_c);
	WriteVTablePtr(olympics_vtable, VTableClubLandmarks, (DWORD)&olympics_landmarks_c);

	// third placed teams table
	map<char*, char*> table = {
		{"AB", "BA"},
		{"AC", "CA"},
		{"BC", "CB"},
	};
	DWORD off = olympics_table_start_offset;
	for (auto const& x : table)
	{
		for (int i = 0; i < 2; i++) WriteBytes(off++, 1, x.first[i]);
		for (int i = 0; i < 2; i++) WriteBytes(off++, 1, strchr(x.second, x.first[i]) - x.second + 1);
	}
}