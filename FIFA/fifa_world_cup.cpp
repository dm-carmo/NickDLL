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

DWORD* fifa_world_cup_vtable = (DWORD*)0x9712F0;

// done
int fifa_world_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[7];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
	sub_775420((BYTE*)*b74318, comp_data->competition_db);
	return 0;
}

// done
void __declspec(naked) fifa_world_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_world_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

// done
void fifa_world_cup_subs(BYTE* _this)
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
	convert_to_cm_date(cm_date, 15, December, data->year, -1);
	*((WORD*)(_this + 0x18E)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0x190)) = -1;

	cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 27, December, data->year, -1);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = -1;

	DWORD v1 = *(DWORD*)_this;
	data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

// done
void __declspec(naked) fifa_world_cup_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_world_cup_subs
		add esp, 0x4
		ret
	}
}

// done
DWORD fifa_world_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddFixture(pMem, 0, Date(year, 6, 12), year, Friday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 0, 2);
		AddFixture(pMem, 1, Date(year, 6, 19), year, Friday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 1, 2);
		AddFixture(pMem, 2, Date(year, 6, 24), year, Wednesday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 2, 2);
		if (stage_idx == -1) {
			AddFixtureTV(pMem, 0, 0, 3, Wednesday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 0, 1, 3, Wednesday, Evening, LargestStadium9);
			AddFixtureTV(pMem, 1, 0, 3, Tuesday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 1, 3, Tuesday, Evening, LargestStadium5);
			AddFixtureTV(pMem, 2, 0, 3, Tuesday, Evening, LargestStadium1);
			AddFixtureTV(pMem, 2, 1, 3, Tuesday, Evening, LargestStadium8);
		}
		else if (stage_idx == 0) {
			AddFixtureTV(pMem, 0, 0, 3, Thursday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 0, 1, 3, Thursday, Evening, LargestStadium6);
			AddFixtureTV(pMem, 1, 0, 3, Wednesday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Wednesday, Evening, LargestStadium9);
			AddFixtureTV(pMem, 2, 0, 3, Tuesday, Evening, NationalStadium);
			AddFixtureTV(pMem, 2, 1, 3, Tuesday, Evening, LargestStadium5);
		}
		else if (stage_idx == 1) {
			AddFixtureTV(pMem, 0, 0, 3, Friday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 0, 1, 3, Friday, Evening, LargestStadium1);
			AddFixtureTV(pMem, 1, 0, 3, Thursday, Evening, LargestStadium6);
			AddFixtureTV(pMem, 1, 1, 3, Thursday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 0, 3, Wednesday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 2, 1, 3, Wednesday, Afternoon, LargestStadium3);
		}
		else if (stage_idx == 2) {
			AddFixtureTV(pMem, 0, 0, 3, Friday, Afternoon, LargestStadium9);
			AddFixtureTV(pMem, 0, 1, 3, Saturday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 1, 0, 3, Saturday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Saturday, Evening, LargestStadium2);
			AddFixtureTV(pMem, 2, 0, 3, Wednesday, Evening, LargestStadium4);
			AddFixtureTV(pMem, 2, 1, 3, Wednesday, Evening, LargestStadium6);
		}
		else if (stage_idx == 3) {
			AddFixtureTV(pMem, 0, 0, 3, Saturday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 0, 1, 3, Saturday, Evening, NationalStadium);
			AddFixtureTV(pMem, 1, 0, 3, Saturday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 1, 3, Saturday, Evening, LargestStadium1);
			AddFixtureTV(pMem, 2, 0, 3, Thursday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 2, 1, 3, Thursday, Afternoon, LargestStadium2);
		}
		else if (stage_idx == 4) {
			AddFixtureTV(pMem, 0, 0, 3, Sunday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Evening, LargestStadium2);
			AddFixtureTV(pMem, 1, 0, 3, Sunday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 1, 1, 3, Sunday, Evening, LargestStadium3);
			AddFixtureTV(pMem, 2, 0, 3, Thursday, Evening, LargestStadium9);
			AddFixtureTV(pMem, 2, 1, 3, Thursday, Evening, LargestStadium5);
		}
		else if (stage_idx == 5) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Evening, LargestStadium3);
			AddFixtureTV(pMem, 1, 0, 3, Monday, Afternoon, LargestStadium9);
			AddFixtureTV(pMem, 1, 1, 3, Monday, Evening, LargestStadium6);
			AddFixtureTV(pMem, 2, 0, 3, Friday, Evening, NationalStadium);
			AddFixtureTV(pMem, 2, 1, 3, Friday, Evening, LargestStadium4);
		}
		else if (stage_idx == 6) {
			AddFixtureTV(pMem, 0, 0, 3, Sunday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 0, 1, 3, Sunday, Evening, LargestStadium4);
			AddFixtureTV(pMem, 1, 0, 3, Saturday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 1, 1, 3, Sunday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 0, 3, Friday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 2, 1, 3, Friday, Afternoon, LargestStadium3);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 7) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 5;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 26), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 30), year, Monday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Evening, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Evening, LargestStadium4);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Evening, LargestStadium9);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, LargestStadium6);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Evening, LargestStadium7);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Afternoon, LargestStadium8);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 16, 8, 16, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 1), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 4), year, Saturday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Friday, Evening, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Friday, Afternoon, LargestStadium5);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Evening, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 8, 4, 0, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 8), year, Wednesday, Evening, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Evening, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Wednesday, Evening, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 9), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 12), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 9), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 11), year, Saturday, Afternoon, LargestStadium2);
		FillFixtureDetails(pMem, fixture_id++, ThirdPlacePlayoff, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

// done
void __declspec(naked) fifa_world_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_world_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

// done
void fifa_world_cup_reputation_setup(BYTE* _this) {
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
		for (WORD i = 0; i < comp_data->special_nteams_seedings; i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

// done
void __declspec(naked) fifa_world_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_world_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void fifa_world_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
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

// done
void __declspec(naked) fifa_world_cup_reputation_calc_c()
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
		call fifa_world_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

// done
void fifa_world_cup_setup_first_group(BYTE* _this, BYTE* pMem) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* tMem = (BYTE*)sub_944E46_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)tMem;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < 32 && teamsAdded < 4; i++) {
		if (*((BYTE*)(pMem + 5 * i + 4)) == 1) {
			DWORD club_id = *((DWORD*)(pMem + 5 * i));
			add_team_call(_this, teamsAdded++, get_club(club_id), 0, 0);
		}
	}
	sub_684230(_this);
}

// done
void fifa_world_cup_setup_groups(BYTE* _this, BYTE* pMem, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < 32 && teamsAdded < 4; i++) {
		if (*((BYTE*)(pMem + 5 * i + 4)) == (idx + 2)) {
			DWORD club_id = *((DWORD*)(pMem + 5 * i));
			*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)get_club(club_id);
		}
	}

	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, 4, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 4, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

// done
void fifa_world_cup_seeded_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	data->special_nteams_seedings = 0;
	WORD count = data->special_nteams_seedings;
	teamList[count].f5 = 2;
	cm3_club_comps* comp = get_comp(FIFA_WORLD_CUP_9CF());
	cm3_clubs* last_winner = get_last_comp_winner(comp);
	teamList[count].club = last_winner;
	count++;
	WORD year = data->year;
	DWORD host1_id, host2_id;
	char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
	if (num_hosts > 0) {
		teamList[count].club = get_national_team(host1_id);
		teamList[count].f5 = 1;
		count++;
		if (count > 0 && teamList[0].club == teamList[0].club) count--;
	}
	if (num_hosts > 1) {
		teamList[count].club = get_national_team(host2_id);
		teamList[count].f5 = 1;
		count++;
		if (count > 0 && teamList[0].club == teamList[0].club) count--;
	}
	//teamList[count++].club = get_national_team(NATION_FRANCE_9CF());
	//teamList[count++].club = get_national_team(NATION_ITALY_9CF());
	//teamList[count++].club = get_national_team(NATION_SPAIN_9CF());
	//teamList[count++].club = get_national_team(NATION_ARGENTINA_9CF());
	//teamList[count++].club = get_national_team(NATION_ROMANIA_9CF());
	//teamList[count++].club = get_national_team(NATION_NETHERLANDS_9CF());
	//teamList[count++].club = get_national_team(NATION_NIGERIA_9CF());
	//teamList[count++].club = get_national_team(NATION_SOUTH_AFRICA_9CF());
	//teamList[count++].club = get_national_team(NATION_CAMEROON_9CF());
	//teamList[count++].club = get_national_team(NATION_TUNISIA_9CF());
	//teamList[count++].club = get_national_team(NATION_MOROCCO_9CF());
	//teamList[count++].club = get_national_team(NATION_MEXICO_9CF());
	//teamList[count++].club = get_national_team(NATION_JAMAICA_9CF());
	//teamList[count++].club = get_national_team(NATION_USA_9CF());
	//teamList[count++].club = get_national_team(NATION_ENGLAND_9CF());
	//teamList[count++].club = get_national_team(NATION_SCOTLAND_9CF());
	//teamList[count++].club = get_national_team(NATION_DENMARK_9CF());
	//teamList[count++].club = get_national_team(NATION_BULGARIA_9CF());
	//teamList[count++].club = get_national_team(NATION_SERBIA_9CF());
	//teamList[count++].club = get_national_team(NATION_NORWAY_9CF());
	//teamList[count++].club = get_national_team(NATION_BELGIUM_9CF());
	//teamList[count++].club = get_national_team(NATION_CROATIA_9CF());
	//teamList[count++].club = get_national_team(NATION_AUSTRIA_9CF());
	//teamList[count++].club = get_national_team(NATION_COLOMBIA_9CF());
	//teamList[count++].club = get_national_team(NATION_PARAGUAY_9CF());
	//teamList[count++].club = get_national_team(NATION_CHILE_9CF());
	//teamList[count++].club = get_national_team(NATION_SOUTH_KOREA_9CF());
	//teamList[count++].club = get_national_team(NATION_JAPAN_9CF());
	//teamList[count++].club = get_national_team(NATION_SAUDI_ARABIA_9CF());
	//teamList[count++].club = get_national_team(NATION_IRAN_9CF());
	data->special_nteams_seedings = count;
}

// done
char fifa_world_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	BYTE* wcq_concacaf = get_loaded_league(WORLD_CUP_CONCACAF_QUALIFYING_9CF());
	BYTE* wcq_ofc = get_loaded_league(WORLD_CUP_OFC_QUALIFYING_9CF());
	BYTE* wcq_afc = get_loaded_league(WORLD_CUP_AFC_QUALIFYING_9CF());
	BYTE* wcq_conmebol = get_loaded_league(WORLD_CUP_CONMEBOL_QUALIFYING_9CF());
	BYTE* wcq_caf = get_loaded_league(WORLD_CUP_CAF_QUALIFYING_9CF());
	BYTE* wcq_uefa = get_loaded_league(WORLD_CUP_UEFA_QUALIFYING_9CF());

	DWORD v1 = *(DWORD*)wcq_concacaf;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(wcq_concacaf);

	v1 = *(DWORD*)wcq_ofc;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(wcq_ofc);

	v1 = *(DWORD*)wcq_afc;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(wcq_afc);

	v1 = *(DWORD*)wcq_conmebol;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(wcq_conmebol);

	v1 = *(DWORD*)wcq_caf;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(wcq_caf);

	v1 = *(DWORD*)wcq_uefa;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(wcq_uefa);

	BYTE* ebx = 0;
	sub_687970(_this, ebx);
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
	data->f75 = -1;
	fifa_world_cup_seeded_teams(_this);
	fifa_world_cup_subs(_this);
	data->team_league_table = 0;
	return 1;
}

// done
void __declspec(naked) fifa_world_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_world_cup_update
		add esp, 0x4
		ret
	}
}

int fifa_world_cup_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 7) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
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
			// instead of a7 uses result from 4bf850? params 0x32, 0x64, current_round, 5
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			*a5 = 4;
			//should not return
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			//should not return
			return 0;
		case Relegated:
			staff_history_comp_third_place_86B710(staff_hist_ptr, club, round_data, a7);
			//should not return
			return 0;
		case 4:
			//0092CE11   . E8 EA81E4FF    CALL cm0102.00775000
			return 0;
		default:
			// instead of a7 uses result from 4bf850? params 0x32, 0x64, current_round, 5
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			//should not return
			return 0;
		}
		//0092CE8C   . E8 6F81E4FF    CALL cm0102.00775000
		return 0;
	}
	return 0;
}

// done
void __declspec(naked) fifa_world_cup_set_table_fate()
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
		call fifa_world_cup_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

// done
void fifa_world_cup_final_stage_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);

	char stage_num = 7;

	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 7; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
	}

	BYTE team_order[16] = { 8,13,4,1,10,15,6,3,0,5,12,9,2,7,14,11 };
	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 4, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	data->current_stage = (long)stage_num;
}

// done
void fifa_world_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 7) {
			fifa_world_cup_final_stage_setup(_this);
		}
	}
}

// done
void __declspec(naked) fifa_world_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_world_cup_stages_create
		add esp, 0x4
		ret
	}
}

// done
void fifa_world_cup_setup1(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	WORD n = data->special_nteams_seedings;
	WORD di = 0;
	if (data->year != 2026) { // needs change?
		data->f75 = 0;
		if (n < 32) {
			vector<cm3_clubs*> nat_teams = get_all_national_teams();
			sort(nat_teams.begin(), nat_teams.end(), compareClubRep);
			for (WORD i = n, idx = 0; i < 32; i++, idx++) {
				cm3_clubs* c = nat_teams[idx];
				for (WORD j = 0; j < n; j++) {
					if (teamList[j].club == c) {
						i--;
						continue;
					}
				}
				teamList[i].club = c;
			}
			data->special_nteams_seedings = 32;
		}
		n = 32;
		// sort teamList by rep?
		WORD year = data->year;
		DWORD host1_id, host2_id;
		char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
		cm3_clubs* host1, * host2;
		if (host1_id == -1) host1 = 0;
		else host1 = get_national_team(host1_id);
		if (host2_id == -1) host2 = 0;
		else host2 = get_national_team(host2_id);
		cm3_club_comps* comp = get_comp(FIFA_WORLD_CUP_9CF());
		cm3_clubs* last_winner = get_last_comp_winner(comp);
		WORD bl = 0;
		for (WORD i = 0; i < n; i++) {
			if (teamList[i].club == last_winner) {
				cm3_clubs* c1 = teamList[0].club;
				BYTE b1 = teamList[0].f5;
				teamList[0].club = teamList[i].club;
				teamList[0].f5 = teamList[i].f5;
				teamList[i].club = c1;
				teamList[i].f5 = b1;
				if (bl < 1) {
					bl = 1;
				}
			}
			if (teamList[i].club == host1) {
				cm3_clubs* c1 = teamList[1].club;
				BYTE b1 = teamList[1].f5;
				teamList[1].club = teamList[i].club;
				teamList[1].f5 = teamList[i].f5;
				teamList[i].club = c1;
				teamList[i].f5 = b1;
				if (bl < 2) {
					bl = 2;
				}
			}
			if (teamList[i].club == host2) {
				cm3_clubs* c1 = teamList[2].club;
				BYTE b1 = teamList[2].f5;
				teamList[2].club = teamList[i].club;
				teamList[2].f5 = teamList[i].f5;
				teamList[i].club = c1;
				teamList[i].f5 = b1;
				if (bl < 3) {
					bl = 3;
				}
			}
		}
		if (host1 == host2) {
			bl = 2;
			if (host2 == last_winner)  bl = 1;
		}
		else if (host1 == last_winner) {
			bl = 2;
			if (host2 == last_winner)  bl = 1;
		}
		//sort teamList without first "bl" items? by reputation
		for (WORD i = 0; i < n; i++) {
			cm3_clubs* c = teamList[i].club;
			*((DWORD*)(_this + 0xF2 + (i * 5) - 4)) = c->ClubID;
			if (i < 8) {
				*((BYTE*)(_this + 0xF2 + (i * 5))) = 0;
				teamList[i].f5 = 3;
			}
			else {
				cm3_continents* cont = c->ClubNation->NationContinent;
				if (cont->ContinentID == EUROPE_9CF()) {
					*((BYTE*)(_this + 0xF2 + (i * 5))) = 1;
					teamList[i].f5 = 10;
				}
				else if (cont->ContinentID == AFRICA_9CF() || cont->ContinentID == NORTH_AMERICA_9CF()) {
					*((BYTE*)(_this + 0xF2 + (i * 5))) = 3;
					teamList[i].f5 = 12;
				}
				else {
					*((BYTE*)(_this + 0xF2 + (i * 5))) = 2;
					teamList[i].f5 = 11;
				}
			}
		}
		// sort teamList by f5
		// sort ESI+116 by f5
	}
}

// done
BYTE* fifa_world_cup_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(32 * 5);
	BYTE counts[8] = { 0,0,0,0,0,0,0,0 };
	for (WORD i = 0; i < 8; i++) {
		counts[i]++;
		if (i == 0) {
			*((DWORD*)(pMem)) = *((DWORD*)(_this + 0xEE));
			*((BYTE*)(pMem + 4)) = 1;
			*((BYTE*)(_this + 0xF2)) = 0xFF;
		}
		else if (i == 2) {
			*((DWORD*)(pMem + 10)) = *((DWORD*)(_this + 0xF3));
			*((BYTE*)(pMem + 14)) = 3;
			*((BYTE*)(_this + 0xF7)) = 0xFF;
		}
		else {
			BYTE r = rand() % 6 + 2;
			while (*((BYTE*)(_this + 5 * r + 0xF2)) == 0xFF) {
				r = rand() % 6 + 2;
			}
			*((DWORD*)(pMem + 5 * i)) = *((DWORD*)(_this + 0xEE + 5 * r));
			*((BYTE*)(pMem + 5 * i + 4)) = i + 1;
			*((BYTE*)(_this + 0xEE + 5 * r)) = 0xFF;
		}
	}
	DWORD dx = 0;
	for (DWORD i = 8; i < 32; i++) {
		DWORD b = (i >> 3) + 1;
		DWORD r = rand() % 8;
		while (counts[r] >= b) {
			r = rand() % 8;
		}
		*((DWORD*)(pMem + 5 * i)) = *((DWORD*)(_this + 0xEE + 5 * i));
		*((BYTE*)(pMem + 5 * i + 4)) = (BYTE)(r + 1);
		counts[r]++;
	}
	WORD year = data->year;
	if (year == 2026) {
		WORD x = 0;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_FRANCE_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SENEGAL_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_URUGUAY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_DENMARK_9CF())->ClubID;

		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SPAIN_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SLOVENIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PARAGUAY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SOUTH_AFRICA_9CF())->ClubID;

		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BRAZIL_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_TURKEY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CHINA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_COSTA_RICA_9CF())->ClubID;

		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SOUTH_KOREA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_POLAND_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_USA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PORTUGAL_9CF())->ClubID;

		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_GERMANY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SAUDI_ARABIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_IRELAND_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CAMEROON_9CF())->ClubID;

		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ARGENTINA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_NIGERIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ENGLAND_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SWEDEN_9CF())->ClubID;

		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ITALY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ECUADOR_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CROATIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_MEXICO_9CF())->ClubID;

		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_JAPAN_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BELGIUM_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_RUSSIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_TUNISIA_9CF())->ClubID;

		teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
		for (BYTE i = 0; i < 32; i++) {
			teamList[i].club = get_club(*((DWORD*)(pMem + 5 * i)));
			teamList[i].f5 = 6;
			*((BYTE*)(pMem + 5 * i + 4)) = (i >> 2) + 1;
		}
		teamList[0].f5 = 2;
		teamList[12].f5 = 1;
		teamList[28].f5 = 1;
		data->special_nteams_seedings = 32;
	}
	return pMem;
}

// done
void fifa_world_cup_setup2(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* pMem = fifa_world_cup_all_teams(_this);
	fifa_world_cup_setup_first_group(_this, pMem);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	data->f69 = 1;
	for (BYTE i = 0; i < 7; i++) {
		fifa_world_cup_setup_groups(_this, pMem, i);
	}
	sub_9452CA_free(pMem);
	fifa_world_cup_reputation_setup(_this);
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);
}

// done
void fifa_world_cup_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	WORD day1 = *(WORD*)(_this + 0x18E);
	short year1 = *(short*)(_this + 0x190);
	if (day1 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year1) {
		if (a3) fifa_world_cup_setup1(_this);
	}
	WORD day2 = *(WORD*)(_this + 0xB6);
	short year2 = *(short*)(_this + 0xB8);
	if (day2 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year2) {
		if (a3) fifa_world_cup_setup2(_this);
	}
	sub_6847C0(_this, current_date, a3);
}

// done
void __declspec(naked) fifa_world_cup_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_world_cup_init2
		add esp, 0xc
		ret 8
	}
}

// done
void fifa_world_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = fifa_world_cup_vtable;
	WORD host_check = (year + 1 - 1994) & 0x80000003;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f75 = 1;
	data->rules = RulesInternational;
	data->year = year + 1;
	if (host_check < 0) {
		host_check--;
		host_check = host_check | 0xFFFFFFFC;
		host_check++;
	}
	while (host_check != 0) {
		data->year++;
		host_check = (data->year - 1994) & 0x80000003;
		if (host_check < 0) {
			host_check--;
			host_check = host_check | 0xFFFFFFFC;
			host_check++;
		}
	}
	data->f81 = 0xf;
	data->special_nteams_seedings = 0;
	data->f56 = 32;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(32 * 6);
	for (int i = 0; i < 32 * 6; i++) pMem[i] = 0;
	data->special_teams_seedings = (DWORD*)pMem;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f217 = 0x28;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 8;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	fifa_world_cup_seeded_teams(_this);
	fifa_world_cup_subs(_this);
	BYTE* ebx = 0;
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	if (data->year == year) {
		data->special_nteams_seedings = 32;
	}
	else {
		data->f69 = 0;
	}
	data->team_league_table = 0;
	data->n_teams = 0;
}

void setup_fifa_world_cup() {
	WriteVTablePtr(fifa_world_cup_vtable, VTableSubsRounds, (DWORD)&fifa_world_cup_subs_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableLeagueSplit, (DWORD)&fifa_world_cup_init2_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableEoSUpdate, (DWORD)&fifa_world_cup_update_c);
	//WriteVTablePtr(fifa_world_cup_vtable, VTableReputationCalc, (DWORD)&fifa_world_cup_reputation_calc_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableReputationSetup, (DWORD)&fifa_world_cup_reputation_setup_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableSetChampion, (DWORD)&fifa_world_cup_set_champion_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableFixtures, (DWORD)&fifa_world_cup_fixture_caller);
	WriteVTablePtr(fifa_world_cup_vtable, VTablePlayoffQual, (DWORD)&fifa_world_cup_stages_create_c);
	//WriteVTablePtr(fifa_world_cup_vtable, VTableTableFates, (DWORD)&fifa_world_cup_set_table_fate);
}