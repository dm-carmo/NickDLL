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
DWORD table_start_offset = 0xDEA000;

int fifa_world_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* final_bytes = (BYTE*)comp_data->stages[15];
	BYTE* third_playoff_bytes = (BYTE*)comp_data->stages[14];
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
	DWORD host1_id, host2_id;
	get_host_ids_5FA730((BYTE*)*b5e134, comp_data->competition_db->ClubCompID, comp_data->year, &host1_id, &host2_id, 1);
	sub_4AFCE0_add_history_entry(_this, first, second, third, get_national_team(host1_id));

	sub_775420((BYTE*)*b74318, comp_data->competition_db);
	return 0;
}

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
	convert_to_cm_date(cm_date, 6, April, data->year, -1);
	*((WORD*)(_this + 0x18E)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0x190)) = 0;

	cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 13, April, data->year, -1);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = 0;

	DWORD v1 = *(DWORD*)_this;
	data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

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

DWORD fifa_world_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 11) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixture(pMem, 0, Date(year, 6, 14), year, Sunday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 0, 2);
		AddFixture(pMem, 1, Date(year, 6, 20), year, Saturday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 1, 2);
		AddFixture(pMem, 2, Date(year, 6, 26), year, Friday, Afternoon, VenueUnknown_1);
		AddFixtureTV(pMem, 2, 2);
		if (stage_idx == -1) {
			AddFixtureTV(pMem, 0, 0, 3, Thursday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 0, 1, 3, Thursday, Evening, LargestStadium9);
			AddFixtureTV(pMem, 1, 0, 3, Thursday, Morning, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Thursday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 0, 3, Wednesday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 1, 3, Wednesday, Afternoon, LargestStadium2);
		}
		else if (stage_idx == 0) {
			AddFixtureTV(pMem, 0, 0, 3, Friday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 0, 1, 3, Saturday, Morning, LargestStadium5);
			AddFixtureTV(pMem, 1, 0, 3, Thursday, Morning, LargestStadium3);
			AddFixtureTV(pMem, 1, 1, 3, Thursday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 0, 3, Wednesday, Morning, LargestStadium4);
			AddFixtureTV(pMem, 2, 1, 3, Wednesday, Morning, LargestStadium9);
		}
		else if (stage_idx == 1) {
			AddFixtureTV(pMem, 0, 0, 3, Saturday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 0, 1, 3, Saturday, Evening, LargestStadium3);
			AddFixtureTV(pMem, 1, 0, 3, Friday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 1, 1, 3, Friday, Evening, LargestStadium7);
			AddFixtureTV(pMem, 2, 0, 3, Wednesday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 2, 1, 3, Wednesday, Afternoon, LargestStadium8);
		}
		else if (stage_idx == 2) {
			AddFixtureTV(pMem, 0, 0, 3, Friday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 0, 1, 3, Saturday, Evening, NationalStadium);
			AddFixtureTV(pMem, 1, 0, 3, Friday, Morning, LargestStadium9);
			AddFixtureTV(pMem, 1, 1, 3, Friday, Evening, LargestStadium5);
			AddFixtureTV(pMem, 2, 0, 3, Thursday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 2, 1, 3, Thursday, Afternoon, LargestStadium5);
		}
		else if (stage_idx == 3) {
			AddFixtureTV(pMem, 0, 0, 3, Sunday, Morning, LargestStadium6);
			AddFixtureTV(pMem, 0, 1, 3, Sunday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 0, 3, Saturday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Saturday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 2, 0, 3, Thursday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 2, 1, 3, Thursday, Afternoon, LargestStadium1);
		}
		else if (stage_idx == 4) {
			AddFixtureTV(pMem, 0, 0, 3, Sunday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 0, 1, 3, Sunday, Evening, LargestStadium5);
			AddFixtureTV(pMem, 1, 0, 3, Saturday, Morning, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Saturday, Evening, LargestStadium9);
			AddFixtureTV(pMem, 2, 0, 3, Thursday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 2, 1, 3, Thursday, Afternoon, LargestStadium4);
		}
		else if (stage_idx == 5) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Morning, LargestStadium9);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 1, 0, 3, Sunday, Morning, LargestStadium3);
			AddFixtureTV(pMem, 1, 1, 3, Sunday, Afternoon, NationalStadium);
			AddFixtureTV(pMem, 2, 0, 3, Friday, Evening, LargestStadium9);
			AddFixtureTV(pMem, 2, 1, 3, Friday, Evening, LargestStadium4);
		}
		else if (stage_idx == 6) {
			AddFixtureTV(pMem, 0, 0, 3, Monday, Morning, LargestStadium8);
			AddFixtureTV(pMem, 0, 1, 3, Monday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, 1, 0, 3, Sunday, Morning, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Sunday, Afternoon, LargestStadium9);
			AddFixtureTV(pMem, 2, 0, 3, Friday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 1, 3, Friday, Afternoon, LargestStadium1);
		}
		else if (stage_idx == 7) {
			AddFixtureTV(pMem, 0, 0, 3, Tuesday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 0, 1, 3, Tuesday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 1, 0, 3, Monday, Afternoon, LargestStadium7);
			AddFixtureTV(pMem, 1, 1, 3, Monday, Evening, LargestStadium1);
			AddFixtureTV(pMem, 2, 0, 3, Friday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, 2, 1, 3, Friday, Afternoon, NationalStadium);
		}
		else if (stage_idx == 8) {
			AddFixtureTV(pMem, 0, 0, 3, Tuesday, Evening, LargestStadium4);
			AddFixtureTV(pMem, 0, 1, 3, Tuesday, Evening, LargestStadium5);
			AddFixtureTV(pMem, 1, 0, 3, Monday, Morning, LargestStadium2);
			AddFixtureTV(pMem, 1, 1, 3, Monday, Evening, LargestStadium5);
			AddFixtureTV(pMem, 2, 0, 3, Saturday, Evening, LargestStadium4);
			AddFixtureTV(pMem, 2, 1, 3, Saturday, Evening, LargestStadium2);
		}
		else if (stage_idx == 9) {
			AddFixtureTV(pMem, 0, 0, 3, Wednesday, Morning, LargestStadium6);
			AddFixtureTV(pMem, 0, 1, 3, Wednesday, Evening, NationalStadium);
			AddFixtureTV(pMem, 1, 0, 3, Tuesday, Morning, LargestStadium6);
			AddFixtureTV(pMem, 1, 1, 3, Tuesday, Evening, LargestStadium7);
			AddFixtureTV(pMem, 2, 0, 3, Saturday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, 2, 1, 3, Saturday, Afternoon, LargestStadium8);
		}
		else if (stage_idx == 10) {
			AddFixtureTV(pMem, 0, 0, 3, Wednesday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, 0, 1, 3, Wednesday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, 1, 0, 3, Tuesday, Afternoon, LargestStadium8);
			AddFixtureTV(pMem, 1, 1, 3, Tuesday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 2, 0, 3, Saturday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, 2, 1, 3, Saturday, Afternoon, LargestStadium7);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 12) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = WorldCupPath1;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 27), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 1), year, Wednesday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Afternoon, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Morning, LargestStadium4);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Afternoon, LargestStadium9);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Morning, LargestStadium6);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Wednesday, Afternoon, LargestStadium7);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Afternoon, LargestStadium5);
		FillFixtureDetails(pMem, fixture_id++, RoundOf32, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 16, 8, 16, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 3), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 6), year, Monday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Morning, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Afternoon, LargestStadium5);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 8, 4, 0, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 8), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 10), year, Friday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Afternoon, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Friday, Morning, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 12), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 14), year, Tuesday, Afternoon, LargestStadium1);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 13) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = WorldCupPath2;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 27), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 1), year, Wednesday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Monday, Morning, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Morning, LargestStadium4);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Wednesday, Morning, LargestStadium9);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Friday, Afternoon, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Friday, Afternoon, LargestStadium6);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Evening, LargestStadium7);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Thursday, Evening, LargestStadium8);
		FillFixtureDetails(pMem, fixture_id++, RoundOf32, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 16, 8, 16, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 3), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 6), year, Monday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Evening, LargestStadium4);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Sunday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Evening, LargestStadium7);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Tuesday, Afternoon, LargestStadium8);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 8, 4, 0, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 8), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 10), year, Friday, Afternoon, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Afternoon, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 3, Saturday, Evening, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 4, 2, 0, 0, 0, 1, 0);
		tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 12), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 15), year, Wednesday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 14) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = ThirdPlacePlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 18), year, Saturday, Afternoon, LargestStadium2);
		FillFixtureDetails(pMem, fixture_id++, None, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 15) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 19), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

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
		for (int i = 16; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 32; i < 40; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 40; i < 48; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 41);
		}
		for (WORD i = 0; i < comp_data->special_nteams_seedings; i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

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
	if (stage < 11) {
		ret_current = 1 + 12 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 12 * (min - 1);
		if (max < 3) ret_max = 17;
		else ret_max = 1 + 12 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 11) {
		if (current < 9) ret_current = 17;
		else ret_current = 33;
		if (min < 9) ret_min = 1;
		else ret_min = 33;
		if (max < 9) ret_max = 17;
		else ret_max = 33;
	}
	else if (stage == 12 || stage == 13) {
		if (current > 1) ret_current = current + (current - 1);
		if (min > 1) ret_min = min + (min - 1);
		if (max > 1) ret_max = max + (max - 1);
		else max = 2;
	}
	else if (stage == 14) {
		ret_current = current + 2;
		ret_min = min + 2;
		ret_max = max + 2;
	}
	else if (stage == 15) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

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

void fifa_world_cup_setup_first_group(BYTE* _this, BYTE* pMem) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* tMem = (BYTE*)sub_944E46_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)tMem;

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < 48 && teamsAdded < 4; i++) {
		if (*((BYTE*)(pMem + 5 * i + 4)) == 1) {
			DWORD club_id = *((DWORD*)(pMem + 5 * i));
			add_team_call(_this, teamsAdded++, get_club(club_id), 0, 0);
		}
	}
	sub_684230(_this);
}

void fifa_world_cup_setup_groups(BYTE* _this, BYTE* pMem, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

	BYTE teamsAdded = 0;
	for (BYTE i = 0; i < 48 && teamsAdded < 4; i++) {
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

void fifa_world_cup_best_placed_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	char stage_num = 11;
	//BYTE stage_num = *(BYTE*)(_this + 0x100);

	WORD v26[4];
	WORD v27[4];
	DWORD v23[2];
	DWORD lpMem[2];
	sub_54A110((BYTE*)v26);
	sub_54A110((BYTE*)v27);

	WORD year = data->year;
	BYTE* ba = (BYTE*)data->fixtures_table;
	BYTE* cm_date = new BYTE[8];
	if (year == 1998) { // change?
		convert_to_cm_date(cm_date, 1, June, 1998, -1);
	}
	else {
		sub_549EF0(cm_date, *(WORD*)(ba)-3, year + *(WORD*)(ba + 2));
	}
	sub_417C10((BYTE*)v26, v23, cm_date);
	WORD a9 = *(WORD*)(_this + 0xA9);
	sub_549EF0(cm_date, *(WORD*)(ba + a9 * fixture_dates_sz - fixture_dates_sz),
		year + *(WORD*)(ba + a9 * fixture_dates_sz - fixture_dates_sz + 2));
	sub_54C770(cm_date, (BYTE*)v23, 1);
	sub_417C10((BYTE*)v27, lpMem, (BYTE*)v23);
	comp_stats* curr_stage = data;
	for (char al = -1; al < 11; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		sub_6827D0((BYTE*)curr_stage, 0);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls_third = table_teams[2];
		cm3_clubs* third_club = tls_third.club;
		DWORD* pMem = (DWORD*)sub_944E46_malloc(4 * curr_stage->n_teams);
		for (WORD i = 0; i < curr_stage->n_teams; i++) {
			*((DWORD*)(&pMem[i])) = table_teams[i].club->ClubID;
		}
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		comp_stats* stage_data = (comp_stats*)pStage;
		WORD n = curr_stage->n_teams;
		sub_88C6D0(pStage, curr_stage->n_teams, pMem, -1, -1, v26, v27, data->competition_db->ClubCompID, data->pts_for_win, data->pts_for_draw, (BYTE*)(_this + 0xC5), 9 * (n * (n - 1)), data->f16);
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

void fifa_world_cup_setup_best_placed(BYTE* _this) {
	char stage_num = 11;
	//BYTE stage_num = *(BYTE*)(_this + 0x100);
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	BYTE prom_rel[4] = { 0, 8, 0, 0 };
	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };
	create_league_stage_data(pStage, _this, 12, 0, 0, (DWORD)(data->competition_db), 0, 0,
		data->pts_for_win, data->pts_for_draw, data->f196, &tiebreaks[0], &prom_rel[0],
		year, stage_num, SecondPlacedTeams, 0, 1, 0, 2, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	data->current_stage = stage_num;
	fifa_world_cup_best_placed_update(_this);
}

void fifa_world_cup_seeded_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	data->special_nteams_seedings = 0;
	WORD count = data->special_nteams_seedings;
	teamList[count].f5 = 2;
	WORD year = data->year;
	DWORD host1_id, host2_id;
	char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
	if (num_hosts > 0) {
		teamList[count].club = get_national_team(host1_id);
		teamList[count].f5 = 1;
		count++;
		if (count > 0 && teamList[0].club == teamList[count].club) count--;
	}
	if (num_hosts > 1) {
		teamList[count].club = get_national_team(host2_id);
		teamList[count].f5 = 1;
		count++;
		if (count > 0 && teamList[0].club == teamList[count].club) count--;
	}
	for (WORD i = count; i < 48; i++) teamList[i].f5 = 6;
	if (year == 2026) {
		teamList[count].club = get_national_team(NATION_CANADA_9CF());
		teamList[count++].f5 = 1;
		teamList[count++].club = get_national_team(NATION_SPAIN_9CF());
		teamList[count++].club = get_national_team(NATION_ARGENTINA_9CF());
		teamList[count++].club = get_national_team(NATION_FRANCE_9CF());
		teamList[count++].club = get_national_team(NATION_ENGLAND_9CF());
		teamList[count++].club = get_national_team(NATION_BRAZIL_9CF());
		teamList[count++].club = get_national_team(NATION_PORTUGAL_9CF());
		teamList[count++].club = get_national_team(NATION_NETHERLANDS_9CF());
		teamList[count++].club = get_national_team(NATION_BELGIUM_9CF());
		teamList[count++].club = get_national_team(NATION_GERMANY_9CF());
		teamList[count++].club = get_national_team(NATION_CROATIA_9CF());
		teamList[count++].club = get_national_team(NATION_MOROCCO_9CF());
		teamList[count++].club = get_national_team(NATION_COLOMBIA_9CF());
		teamList[count++].club = get_national_team(NATION_URUGUAY_9CF());
		teamList[count++].club = get_national_team(NATION_SWITZERLAND_9CF());
		teamList[count++].club = get_national_team(NATION_JAPAN_9CF());
		teamList[count++].club = get_national_team(NATION_SENEGAL_9CF());
		teamList[count++].club = get_national_team(NATION_IRAN_9CF());
		teamList[count++].club = get_national_team(NATION_SOUTH_KOREA_9CF());
		teamList[count++].club = get_national_team(NATION_ECUADOR_9CF());
		teamList[count++].club = get_national_team(NATION_AUSTRIA_9CF());
		teamList[count++].club = get_national_team(NATION_AUSTRALIA_9CF());
		teamList[count++].club = get_national_team(NATION_NORWAY_9CF());
		teamList[count++].club = get_national_team(NATION_PANAMA_9CF());
		teamList[count++].club = get_national_team(NATION_EGYPT_9CF());
		teamList[count++].club = get_national_team(NATION_ALGERIA_9CF());
		teamList[count++].club = get_national_team(NATION_SCOTLAND_9CF());
		teamList[count++].club = get_national_team(NATION_PARAGUAY_9CF());
		teamList[count++].club = get_national_team(NATION_TUNISIA_9CF());
		teamList[count++].club = get_national_team(NATION_IVORY_COAST_9CF());
		teamList[count++].club = get_national_team(NATION_UZBEKISTAN_9CF());
		teamList[count++].club = get_national_team(NATION_QATAR_9CF());
		teamList[count++].club = get_national_team(NATION_SAUDI_ARABIA_9CF());
		teamList[count++].club = get_national_team(NATION_SOUTH_AFRICA_9CF());
		teamList[count++].club = get_national_team(NATION_JORDAN_9CF());
		teamList[count++].club = get_national_team(NATION_CAPE_VERDE_9CF());
		teamList[count++].club = get_national_team(NATION_GHANA_9CF());
		teamList[count++].club = get_national_team(NATION_CURACAO_9CF());
		teamList[count++].club = get_national_team(NATION_HAITI_9CF());
		teamList[count++].club = get_national_team(NATION_NEW_ZEALAND_9CF());
		teamList[count++].club = get_national_team(NATION_BOSNIA_9CF());
		teamList[count++].club = get_national_team(NATION_SWEDEN_9CF());
		teamList[count++].club = get_national_team(NATION_TURKEY_9CF());
		teamList[count++].club = get_national_team(NATION_CZECH_REPUBLIC_9CF());
		teamList[count++].club = get_national_team(NATION_DR_CONGO_9CF());
		teamList[count++].club = get_national_team(NATION_IRAQ_9CF());
	}
	data->special_nteams_seedings = count;
}

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
	data->f75 = 1;
	fifa_world_cup_seeded_teams(_this);
	fifa_world_cup_subs(_this);
	data->team_league_table = 0;
	return 1;
}

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
	if (stage < 11) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf32, 0x1E);
			return 0;
		default:
			//staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), GroupStage, 0x1E);
			return 0;
		}
	}
	else if (stage == 11) {
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf32, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), GroupStage, 0x1E);
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 12 || stage == 13) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		char c;
		switch (fate) {
		case TopPlayoff:
			c = sub_4BF850(50, 100, current_round, 5);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Final, c);
			return 0;
		case Promoted:
			c = sub_4BF850(50, 100, current_round, 5);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			c = sub_4BF850(50, 100, current_round, 5);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, ThirdPlacePlayoff, c);
			return 0;
		default:
			c = sub_4BF850(50, 100, current_round, 5);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 14) {
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
			c = sub_4BF850(50, 100, current_round, 5);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			break;
		default:
			c = sub_4BF850(50, 100, current_round, 5);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
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
		char c;
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			*a5 = 4;
			break;
		case Promoted:
			c = sub_4BF850(50, 100, current_round, 5);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			break;
		default:
			c = sub_4BF850(50, 100, current_round, 5);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

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

#pragma warning(push)
#pragma warning(disable:6385)
void fifa_world_cup_paths_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;

	char stage_num = 12;

	BYTE playoff_teams = 16;
	DWORD* pTeams1 = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	DWORD* pTeams2 = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 11; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
		staff_history_failed_qual_86C1D0(staff_hist_ptr, table_teams[3].club, (DWORD)(data->competition_db), GroupStage, 0x1E);
	}
	comp_stats* best_placed_stage = (comp_stats*)(data->stages[11]);
	team_league_stats* best_placed_table = (team_league_stats*)(best_placed_stage->team_league_table);
	char best_third_letters[9] = { 0,0,0,0,0,0,0,0,0 };
	char letter_idx = 0;
	curr_stage = data;
	for (char al = -1; al < 11; al++) {
		if (al > -1) curr_stage = (comp_stats*)(data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		cm3_clubs* third = table_teams[2].club;
		for (WORD i = 0; i < best_placed_stage->prom_playoff; i++) {
			if (best_placed_table[i].club == third) {
				best_third_letters[letter_idx++] = 65 + al + 1;
				clubs.push_back(third);
				table_teams[2].league_fate = Qualified1;
				curr_stage->promotions++;
				break;
			}
		}
	}
	for (WORD i = 8; i < best_placed_stage->n_teams; i++)
		staff_history_failed_qual_86C1D0(staff_hist_ptr, best_placed_table[i].club, (DWORD)(data->competition_db), GroupStage, 0x1E);

	char key[9] = { '\0' };
	char indexes[9] = { '\0' };
	for (int i = 0; i < 495; i++) {
		strncpy_s(key, (char*)(table_start_offset + 16 * i), 8);
		if (strcmp(key, best_third_letters) == 0) {
			strncpy_s(indexes, (char*)(table_start_offset + 16 * i + 8), 8);
			break;
		}
	}

	BYTE table_order[8] = { 21,29,13,1,15,3,31,23 };
	BYTE team_order[32] = { 20,4,28,5,16,7,12,26,0,18,6,17,14,27,10,25,2,19,24,11,30,8,22,9 };
	for (char i = 0; i < 8; i++) team_order[i + 24] = table_order[indexes[i] - 1];
	for (WORD j = 0; j < playoff_teams * 2; j++) {
		BYTE order = team_order[j];
		if (order < playoff_teams) *((DWORD*)(&pTeams1[team_order[j]])) = (DWORD)clubs[j];
		else *((DWORD*)(&pTeams2[team_order[j] - playoff_teams])) = (DWORD)clubs[j];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams1, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 4, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	stage_num++;

	num_rounds = 0;
	stage_name_id = 0;
	pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams2, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 4, stage_name_id, 0x14, 1, 0, 0, 0);
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);

	data->current_stage = (long)stage_num;
}
#pragma warning(pop)

void fifa_world_cup_final_stage_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	char stage_num = 14;

	BYTE playoff_teams = 2;
	DWORD* pTeams1 = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	DWORD* pTeams2 = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* path1 = (comp_stats*)(data->stages[12]);
	comp_stats* path2 = (comp_stats*)(data->stages[13]);

	for (WORD j = 0; j < path1->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)path1->teams_list)[j];
		if (t.f6 == 1) {
			*((DWORD*)(&pTeams1[0])) = (DWORD)t.club;
		}
		else if (t.f6 == 2) {
			*((DWORD*)(&pTeams2[0])) = (DWORD)t.club;
		}
	}
	for (WORD j = 0; j < path2->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)path2->teams_list)[j];
		if (t.f6 == 1) {
			*((DWORD*)(&pTeams1[1])) = (DWORD)t.club;
		}
		else if (t.f6 == 2) {
			*((DWORD*)(&pTeams2[1])) = (DWORD)t.club;
		}
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams2, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 4, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	stage_num++;

	num_rounds = 0;
	stage_name_id = 0;
	pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams1, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 4, stage_name_id, 0x14, 1, 0, 0, 0);
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);

	data->current_stage = (long)stage_num;
}

void fifa_world_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 12) {
			fifa_world_cup_paths_setup(_this);
		}
		else if (current == 14) {
			fifa_world_cup_final_stage_setup(_this);
		}
	}
}

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

void fifa_world_cup_setup1(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	WORD n = data->special_nteams_seedings;
	WORD di = 0;
	if (data->year != 2026) {
		data->f75 = 0;
		if (n < 48) {
			string msg = "Not enough teams in World Cup: needed 48 but only had " + to_string(n);
			create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
			vector<cm3_clubs*> nat_teams = get_all_national_teams();
			sort(nat_teams.begin(), nat_teams.end(), compareNationRanking);
			for (WORD i = n, idx = 0; i < 48; i++, idx++) {
				cm3_clubs* c = nat_teams[idx];
				for (WORD j = 0; j < n; j++) {
					if (teamList[j].club == c) {
						i--;
						continue;
					}
				}
				teamList[i].club = c;
			}
			data->special_nteams_seedings = 48;
		}
		n = 48;
		vector<cm3_clubs*> qualified_teams;
		for (WORD i = 0; i < n; i++) qualified_teams.push_back(teamList[i].club);
		sort(qualified_teams.begin(), qualified_teams.end(), compareNationRanking);
		WORD year = data->year;
		DWORD host1_id, host2_id;
		char num_hosts = get_host_ids_5FA730((BYTE*)*b5e134, data->competition_db->ClubCompID, year, &host1_id, &host2_id, 1);
		cm3_clubs* host1, * host2;
		if (host1_id == -1) host1 = 0;
		else host1 = get_national_team(host1_id);
		if (host2_id == -1) host2 = 0;
		else host2 = get_national_team(host2_id);
		WORD bl = 0;
		for (WORD i = 0; i < n; i++) {
			if (qualified_teams[i] == host1) {
				cm3_clubs* c1 = qualified_teams[1];
				qualified_teams[1] = qualified_teams[i];
				qualified_teams[i] = c1;
				if (bl < 1) bl = 1;
			}
			if (qualified_teams[i] == host2) {
				cm3_clubs* c1 = qualified_teams[2];
				qualified_teams[2] = qualified_teams[i];
				qualified_teams[i] = c1;
				if (bl < 2) bl = 2;
			}
		}
		if (host1 == host2) bl = 1;
		sort(qualified_teams.begin() + bl, qualified_teams.end(), compareNationRanking);
		for (WORD i = 0; i < n; i++) {
			cm3_clubs* c = qualified_teams[i];
			teamList[i].club = c;
			if (i < 12) teamList[i].f5 = 3;
			else if (i < 24) teamList[i].f5 = 10;
			else if (i < 36) teamList[i].f5 = 11;
			else teamList[i].f5 = 12;
		}
	}
}

BYTE* fifa_world_cup_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(48 * 5);
	BYTE counts[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	for (WORD i = 0; i < 12; i++) {
		counts[i]++;
		if (i == 0) {
			*((DWORD*)(pMem)) = teamList[0].club->ClubID;
			*((BYTE*)(pMem + 4)) = 1;
			teamList[0].f5 = -1;
		}
		else {
			BYTE r = rand() % 11 + 1;
			while (teamList[r].f5 == -1) r = rand() % 11 + 1;
			*((DWORD*)(pMem + 5 * i)) = teamList[r].club->ClubID;
			*((BYTE*)(pMem + 5 * i + 4)) = i + 1;
		}
	}
	DWORD dx = 0;
	for (DWORD i = 12; i < 48; i++) {
		DWORD b = i / 12 + 1;
		DWORD r = rand() % 12;
		while (counts[r] >= b) r = rand() % 12;
		*((DWORD*)(pMem + 5 * i)) = teamList[i].club->ClubID;
		*((BYTE*)(pMem + 5 * i + 4)) = (BYTE)(r + 1);
		counts[r]++;
	}
	WORD year = data->year;
	if (year == 2026) {
		WORD x = 0;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_MEXICO_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SOUTH_AFRICA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SOUTH_KOREA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CZECH_REPUBLIC_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CANADA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BOSNIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_QATAR_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SWITZERLAND_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BRAZIL_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_MOROCCO_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_HAITI_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SCOTLAND_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_USA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PARAGUAY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_AUSTRALIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_TURKEY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_GERMANY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CURACAO_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_IVORY_COAST_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ECUADOR_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_NETHERLANDS_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_JAPAN_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SWEDEN_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_TUNISIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_BELGIUM_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_EGYPT_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_IRAN_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_NEW_ZEALAND_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SPAIN_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CAPE_VERDE_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SAUDI_ARABIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_URUGUAY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_FRANCE_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_SENEGAL_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_IRAQ_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_NORWAY_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ARGENTINA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ALGERIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_AUSTRIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_JORDAN_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PORTUGAL_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_DR_CONGO_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_UZBEKISTAN_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_COLOMBIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_ENGLAND_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_CROATIA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_GHANA_9CF())->ClubID;
		*((DWORD*)(pMem + 5 * (x++))) = get_national_team(NATION_PANAMA_9CF())->ClubID;

		teams_seeded* teamList = (teams_seeded*)data->special_teams_seedings;
		for (BYTE i = 0; i < 48; i++) {
			teamList[i].club = get_club(*((DWORD*)(pMem + 5 * i)));
			teamList[i].f5 = 6;
			*((BYTE*)(pMem + 5 * i + 4)) = (i >> 2) + 1;
		}
		teamList[0].f5 = 1;
		teamList[4].f5 = 1;
		teamList[12].f5 = 1;
		data->special_nteams_seedings = 48;
	}
	else for (BYTE i = 0; i < 48; i++) teamList[i].f5 = 6;
	return pMem;
}

void fifa_world_cup_setup2(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* pMem = fifa_world_cup_all_teams(_this);
	fifa_world_cup_setup_first_group(_this, pMem);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	data->f69 = 1;
	for (BYTE i = 0; i < 11; i++) fifa_world_cup_setup_groups(_this, pMem, i);
	fifa_world_cup_setup_best_placed(_this);
	sub_9452CA_free(pMem);
	fifa_world_cup_reputation_setup(_this);
	DWORD* ae28f0_ptr = (DWORD*)*(DWORD*)*ae28f0;
	sub_7E9180(((BYTE*)(ae28f0_ptr[data->rules])), 0);
}

void fifa_world_cup_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	WORD day1 = *(WORD*)(_this + 0x18E);
	short year1 = *(short*)(_this + 0x190);
	if (*(WORD*)(current_date + 2) > data->year + year1 ||
		(*(WORD*)(current_date + 2) == data->year + year1 && *(WORD*)(current_date) >= day1)) {
		if (day1 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year1) {
			if (a3) fifa_world_cup_setup1(_this);
		}
		else {
			WORD day2 = *(WORD*)(_this + 0xB6);
			short year2 = *(short*)(_this + 0xB8);
			if (day2 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year2) {
				if (a3) fifa_world_cup_setup2(_this);
			}
			else if (*(WORD*)(current_date) > day2 || *(WORD*)(current_date + 2) > data->year + year2) {
				char ret = sub_5AE6D0((BYTE*)current_date, data->competition_db->ClubCompID);
				if (ret) fifa_world_cup_best_placed_update(_this);
			}
		}
	}
	sub_6847C0(_this, current_date, a3);
}

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
	data->f56 = 48;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(48 * 6);
	for (int i = 0; i < 48 * 6; i++) pMem[i] = 0;
	data->special_teams_seedings = (DWORD*)pMem;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f217 = 0x28;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 16;
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
	if (data->year == year) data->special_nteams_seedings = 48;
	else data->f69 = 0;
	data->team_league_table = 0;
	data->n_teams = 0;
}

WORD fifa_world_cup_vtable29(BYTE* _this, cm3_clubs* club) {
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
		short ret = (val > 32) - 1;
		return (ret & 0x18) - 4;
	}
}

void __declspec(naked) fifa_world_cup_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_world_cup_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE fifa_world_cup_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	if (al < 3) {
		if (bl < 5) return 0;
		else if (bl < 9) return -1;
		else return (bl < 17) - 3;
	}
	else if (al < 9) {
		if (bl < 5) return 2;
		else if (bl < 9) return 0;
		else return (bl < 17) - 2;
	}
	else if (al < 17) {
		if (bl < 5) return 3;
		else if (bl < 9) return 2;
		else return (bl < 17) - 1;
	}
	else {
		if (bl < 9) return 3;
		else return 2 * (bl < 17);
	}
}

void __declspec(naked) fifa_world_cup_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_world_cup_vtable30
		add esp, 0x8
		ret 4
	}
}

int fifa_world_cup_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 11) {
		if (fate == Qualified1) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 11) {
		if (fate == Qualified1) {
			sub_66F4E0(0xDE1F64, 0x9C4800, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
				&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
		//else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 12 || stage_id == 13)
	{
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case BottomPlayoff:
				sub_66F4E0(0xDE1F64, 0x98713C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
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
	else if (stage_id == 14)
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
	else if (stage_id == 15)
	{
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0x98732C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case BottomPlayoff:
				sub_66F4E0(0xDE1F64, 0x9872C8, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
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

void __declspec(naked) fifa_world_cup_stage_news_c()
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
		call fifa_world_cup_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void fifa_world_cup_48CAB0(BYTE* _this, char* a1, int a2, __int16 a3, __int16 a4, char a5, int a6) {
	// Shows the right text in club's Competitions history if they win in the Champions Third Qualifying Round then lose in the Playoff
	if (a3 == WorldCupPath1 || a3 == WorldCupPath2)
	{
		if (a4 == SemiFinal)
		{
			if (a5 == 1) return sub_48CAB0(_this, a1, a2, None, Final, 0, a6);
			else if (a5 == 2) return sub_48CAB0(_this, a1, a2, ThirdPlacePlayoff, None, 0, a6);
		}
		return sub_48CAB0(_this, a1, a2, None, a4, a5, a6);
	}
	else if (a3 == ThirdPlacePlayoff && a4 == None)
	{
		if (a5 == 1) return sub_48CAB0(_this, a1, a2, None, None, 3, a6);
		else return sub_48CAB0(_this, a1, a2, None, SemiFinal, -1, a6);
	}
	else if (a3 == None && a4 == Final)
	{
		if (a5 == 1 || a5 == 2) return sub_48CAB0(_this, a1, a2, None, None, a5, a6);
	}
	return sub_48CAB0(_this, a1, a2, a3, a4, a5, a6);
}

void __declspec(naked) fifa_world_cup_48CAB0_c()
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
		call fifa_world_cup_48CAB0
		add esp, 0x1c
		ret 0x18
	}
}

void setup_fifa_world_cup() {
	WriteVTablePtr(fifa_world_cup_vtable, VTableSubsRounds, (DWORD)&fifa_world_cup_subs_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableLeagueSplit, (DWORD)&fifa_world_cup_init2_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableEoSUpdate, (DWORD)&fifa_world_cup_update_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableReputationCalc, (DWORD)&fifa_world_cup_reputation_calc_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableReputationSetup, (DWORD)&fifa_world_cup_reputation_setup_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableSetChampion, (DWORD)&fifa_world_cup_set_champion_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableFixtures, (DWORD)&fifa_world_cup_fixture_caller);
	WriteVTablePtr(fifa_world_cup_vtable, VTablePlayoffQual, (DWORD)&fifa_world_cup_stages_create_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableTableFates, (DWORD)&fifa_world_cup_set_table_fate);
	WriteVTablePtr(fifa_world_cup_vtable, VTableStageNews, (DWORD)&fifa_world_cup_stage_news_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTable29, (DWORD)&fifa_world_cup_vtable29_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTable30, (DWORD)&fifa_world_cup_vtable30_c);
	WriteVTablePtr(fifa_world_cup_vtable, VTableClubLandmarks, (DWORD)&fifa_world_cup_48CAB0_c);

	// move awards 1 week later
	WriteBytes(0x92fe22, 1, 20);

	// autumn/spring stages to path 1/2
	WriteBytes(0x9a4654, 6, 0x50, 0x61, 0x74, 0x68, 0x20, 0x31); // Path 1 short
	WriteBytes(0x9a464c, 6, 0x50, 0x61, 0x74, 0x68, 0x20, 0x32); // Path 2 short
	WriteBytes(0x9a6a08, 7, 0x50, 0x61, 0x74, 0x68, 0x20, 0x31, 0x0); // Path 1 long
	WriteBytes(0x9a69f8, 7, 0x50, 0x61, 0x74, 0x68, 0x20, 0x32, 0x0); // Path 2 long

	// third placed teams table
	map<char*, char*> table = {
		{"EFGHIJKL", "EJIFHGLK"},
		{"DFGHIJKL", "HGIDJFLK"},
		{"DEGHIJKL", "EJIDHGLK"},
		{"DEFHIJKL", "EJIDHFLK"},
		{"DEFGIJKL", "EGIDJFLK"},
		{"DEFGHJKL", "EGJDHFLK"},
		{"DEFGHIKL", "EGIDHFLK"},
		{"DEFGHIJL", "EGJDHFLI"},
		{"DEFGHIJK", "EGJDHFIK"},
		{"CFGHIJKL", "HGICJFLK"},
		{"CEGHIJKL", "EJICHGLK"},
		{"CEFHIJKL", "EJICHFLK"},
		{"CEFGIJKL", "EGICJFLK"},
		{"CEFGHJKL", "EGJCHFLK"},
		{"CEFGHIKL", "EGICHFLK"},
		{"CEFGHIJL", "EGJCHFLI"},
		{"CEFGHIJK", "EGJCHFIK"},
		{"CDGHIJKL", "HGICJDLK"},
		{"CDFHIJKL", "CJIDHFLK"},
		{"CDFGIJKL", "CGIDJFLK"},
		{"CDFGHJKL", "CGJDHFLK"},
		{"CDFGHIKL", "CGIDHFLK"},
		{"CDFGHIJL", "CGJDHFLI"},
		{"CDFGHIJK", "CGJDHFIK"},
		{"CDEHIJKL", "EJICHDLK"},
		{"CDEGIJKL", "EGICJDLK"},
		{"CDEGHJKL", "EGJCHDLK"},
		{"CDEGHIKL", "EGICHDLK"},
		{"CDEGHIJL", "EGJCHDLI"},
		{"CDEGHIJK", "EGJCHDIK"},
		{"CDEFIJKL", "CJEDIFLK"},
		{"CDEFHJKL", "CJEDHFLK"},
		{"CDEFHIKL", "CEIDHFLK"},
		{"CDEFHIJL", "CJEDHFLI"},
		{"CDEFHIJK", "CJEDHFIK"},
		{"CDEFGJKL", "CGEDJFLK"},
		{"CDEFGIKL", "CGEDIFLK"},
		{"CDEFGIJL", "CGEDJFLI"},
		{"CDEFGIJK", "CGEDJFIK"},
		{"CDEFGHKL", "CGEDHFLK"},
		{"CDEFGHJL", "CGJDHFLE"},
		{"CDEFGHJK", "CGJDHFEK"},
		{"CDEFGHIL", "CGEDHFLI"},
		{"CDEFGHIK", "CGEDHFIK"},
		{"CDEFGHIJ", "CGJDHFEI"},
		{"BFGHIJKL", "HJBFIGLK"},
		{"BEGHIJKL", "EJIBHGLK"},
		{"BEFHIJKL", "EJBFIHLK"},
		{"BEFGIJKL", "EJBFIGLK"},
		{"BEFGHJKL", "EJBFHGLK"},
		{"BEFGHIKL", "EGBFIHLK"},
		{"BEFGHIJL", "EJBFHGLI"},
		{"BEFGHIJK", "EJBFHGIK"},
		{"BDGHIJKL", "HJBDIGLK"},
		{"BDFHIJKL", "HJBDIFLK"},
		{"BDFGIJKL", "IGBDJFLK"},
		{"BDFGHJKL", "HGBDJFLK"},
		{"BDFGHIKL", "HGBDIFLK"},
		{"BDFGHIJL", "HGBDJFLI"},
		{"BDFGHIJK", "HGBDJFIK"},
		{"BDEHIJKL", "EJBDIHLK"},
		{"BDEGIJKL", "EJBDIGLK"},
		{"BDEGHJKL", "EJBDHGLK"},
		{"BDEGHIKL", "EGBDIHLK"},
		{"BDEGHIJL", "EJBDHGLI"},
		{"BDEGHIJK", "EJBDHGIK"},
		{"BDEFIJKL", "EJBDIFLK"},
		{"BDEFHJKL", "EJBDHFLK"},
		{"BDEFHIKL", "EIBDHFLK"},
		{"BDEFHIJL", "EJBDHFLI"},
		{"BDEFHIJK", "EJBDHFIK"},
		{"BDEFGJKL", "EGBDJFLK"},
		{"BDEFGIKL", "EGBDIFLK"},
		{"BDEFGIJL", "EGBDJFLI"},
		{"BDEFGIJK", "EGBDJFIK"},
		{"BDEFGHKL", "EGBDHFLK"},
		{"BDEFGHJL", "HGBDJFLE"},
		{"BDEFGHJK", "HGBDJFEK"},
		{"BDEFGHIL", "EGBDHFLI"},
		{"BDEFGHIK", "EGBDHFIK"},
		{"BDEFGHIJ", "HGBDJFEI"},
		{"BCGHIJKL", "HJBCIGLK"},
		{"BCFHIJKL", "HJBCIFLK"},
		{"BCFGIJKL", "IGBCJFLK"},
		{"BCFGHJKL", "HGBCJFLK"},
		{"BCFGHIKL", "HGBCIFLK"},
		{"BCFGHIJL", "HGBCJFLI"},
		{"BCFGHIJK", "HGBCJFIK"},
		{"BCEHIJKL", "EJBCIHLK"},
		{"BCEGIJKL", "EJBCIGLK"},
		{"BCEGHJKL", "EJBCHGLK"},
		{"BCEGHIKL", "EGBCIHLK"},
		{"BCEGHIJL", "EJBCHGLI"},
		{"BCEGHIJK", "EJBCHGIK"},
		{"BCEFIJKL", "EJBCIFLK"},
		{"BCEFHJKL", "EJBCHFLK"},
		{"BCEFHIKL", "EIBCHFLK"},
		{"BCEFHIJL", "EJBCHFLI"},
		{"BCEFHIJK", "EJBCHFIK"},
		{"BCEFGJKL", "EGBCJFLK"},
		{"BCEFGIKL", "EGBCIFLK"},
		{"BCEFGIJL", "EGBCJFLI"},
		{"BCEFGIJK", "EGBCJFIK"},
		{"BCEFGHKL", "EGBCHFLK"},
		{"BCEFGHJL", "HGBCJFLE"},
		{"BCEFGHJK", "HGBCJFEK"},
		{"BCEFGHIL", "EGBCHFLI"},
		{"BCEFGHIK", "EGBCHFIK"},
		{"BCEFGHIJ", "HGBCJFEI"},
		{"BCDHIJKL", "HJBCIDLK"},
		{"BCDGIJKL", "IGBCJDLK"},
		{"BCDGHJKL", "HGBCJDLK"},
		{"BCDGHIKL", "HGBCIDLK"},
		{"BCDGHIJL", "HGBCJDLI"},
		{"BCDGHIJK", "HGBCJDIK"},
		{"BCDFIJKL", "CJBDIFLK"},
		{"BCDFHJKL", "CJBDHFLK"},
		{"BCDFHIKL", "CIBDHFLK"},
		{"BCDFHIJL", "CJBDHFLI"},
		{"BCDFHIJK", "CJBDHFIK"},
		{"BCDFGJKL", "CGBDJFLK"},
		{"BCDFGIKL", "CGBDIFLK"},
		{"BCDFGIJL", "CGBDJFLI"},
		{"BCDFGIJK", "CGBDJFIK"},
		{"BCDFGHKL", "CGBDHFLK"},
		{"BCDFGHJL", "CGBDHFLJ"},
		{"BCDFGHJK", "HGBCJFDK"},
		{"BCDFGHIL", "CGBDHFLI"},
		{"BCDFGHIK", "CGBDHFIK"},
		{"BCDFGHIJ", "HGBCJFDI"},
		{"BCDEIJKL", "EJBCIDLK"},
		{"BCDEHJKL", "EJBCHDLK"},
		{"BCDEHIKL", "EIBCHDLK"},
		{"BCDEHIJL", "EJBCHDLI"},
		{"BCDEHIJK", "EJBCHDIK"},
		{"BCDEGJKL", "EGBCJDLK"},
		{"BCDEGIKL", "EGBCIDLK"},
		{"BCDEGIJL", "EGBCJDLI"},
		{"BCDEGIJK", "EGBCJDIK"},
		{"BCDEGHKL", "EGBCHDLK"},
		{"BCDEGHJL", "HGBCJDLE"},
		{"BCDEGHJK", "HGBCJDEK"},
		{"BCDEGHIL", "EGBCHDLI"},
		{"BCDEGHIK", "EGBCHDIK"},
		{"BCDEGHIJ", "HGBCJDEI"},
		{"BCDEFJKL", "CJBDEFLK"},
		{"BCDEFIKL", "CEBDIFLK"},
		{"BCDEFIJL", "CJBDEFLI"},
		{"BCDEFIJK", "CJBDEFIK"},
		{"BCDEFHKL", "CEBDHFLK"},
		{"BCDEFHJL", "CJBDHFLE"},
		{"BCDEFHJK", "CJBDHFEK"},
		{"BCDEFHIL", "CEBDHFLI"},
		{"BCDEFHIK", "CEBDHFIK"},
		{"BCDEFHIJ", "CJBDHFEI"},
		{"BCDEFGKL", "CGBDEFLK"},
		{"BCDEFGJL", "CGBDJFLE"},
		{"BCDEFGJK", "CGBDJFEK"},
		{"BCDEFGIL", "CGBDEFLI"},
		{"BCDEFGIK", "CGBDEFIK"},
		{"BCDEFGIJ", "CGBDJFEI"},
		{"BCDEFGHL", "CGBDHFLE"},
		{"BCDEFGHK", "CGBDHFEK"},
		{"BCDEFGHJ", "HGBCJFDE"},
		{"BCDEFGHI", "CGBDHFEI"},
		{"AFGHIJKL", "HJIFAGLK"},
		{"AEGHIJKL", "EJIAHGLK"},
		{"AEFHIJKL", "EJIFAHLK"},
		{"AEFGIJKL", "EJIFAGLK"},
		{"AEFGHJKL", "EGJFAHLK"},
		{"AEFGHIKL", "EGIFAHLK"},
		{"AEFGHIJL", "EGJFAHLI"},
		{"AEFGHIJK", "EGJFAHIK"},
		{"ADGHIJKL", "HJIDAGLK"},
		{"ADFHIJKL", "HJIDAFLK"},
		{"ADFGIJKL", "IGJDAFLK"},
		{"ADFGHJKL", "HGJDAFLK"},
		{"ADFGHIKL", "HGIDAFLK"},
		{"ADFGHIJL", "HGJDAFLI"},
		{"ADFGHIJK", "HGJDAFIK"},
		{"ADEHIJKL", "EJIDAHLK"},
		{"ADEGIJKL", "EJIDAGLK"},
		{"ADEGHJKL", "EGJDAHLK"},
		{"ADEGHIKL", "EGIDAHLK"},
		{"ADEGHIJL", "EGJDAHLI"},
		{"ADEGHIJK", "EGJDAHIK"},
		{"ADEFIJKL", "EJIDAFLK"},
		{"ADEFHJKL", "HJEDAFLK"},
		{"ADEFHIKL", "HEIDAFLK"},
		{"ADEFHIJL", "HJEDAFLI"},
		{"ADEFHIJK", "HJEDAFIK"},
		{"ADEFGJKL", "EGJDAFLK"},
		{"ADEFGIKL", "EGIDAFLK"},
		{"ADEFGIJL", "EGJDAFLI"},
		{"ADEFGIJK", "EGJDAFIK"},
		{"ADEFGHKL", "HGEDAFLK"},
		{"ADEFGHJL", "HGJDAFLE"},
		{"ADEFGHJK", "HGJDAFEK"},
		{"ADEFGHIL", "HGEDAFLI"},
		{"ADEFGHIK", "HGEDAFIK"},
		{"ADEFGHIJ", "HGJDAFEI"},
		{"ACGHIJKL", "HJICAGLK"},
		{"ACFHIJKL", "HJICAFLK"},
		{"ACFGIJKL", "IGJCAFLK"},
		{"ACFGHJKL", "HGJCAFLK"},
		{"ACFGHIKL", "HGICAFLK"},
		{"ACFGHIJL", "HGJCAFLI"},
		{"ACFGHIJK", "HGJCAFIK"},
		{"ACEHIJKL", "EJICAHLK"},
		{"ACEGIJKL", "EJICAGLK"},
		{"ACEGHJKL", "EGJCAHLK"},
		{"ACEGHIKL", "EGICAHLK"},
		{"ACEGHIJL", "EGJCAHLI"},
		{"ACEGHIJK", "EGJCAHIK"},
		{"ACEFIJKL", "EJICAFLK"},
		{"ACEFHJKL", "HJECAFLK"},
		{"ACEFHIKL", "HEICAFLK"},
		{"ACEFHIJL", "HJECAFLI"},
		{"ACEFHIJK", "HJECAFIK"},
		{"ACEFGJKL", "EGJCAFLK"},
		{"ACEFGIKL", "EGICAFLK"},
		{"ACEFGIJL", "EGJCAFLI"},
		{"ACEFGIJK", "EGJCAFIK"},
		{"ACEFGHKL", "HGECAFLK"},
		{"ACEFGHJL", "HGJCAFLE"},
		{"ACEFGHJK", "HGJCAFEK"},
		{"ACEFGHIL", "HGECAFLI"},
		{"ACEFGHIK", "HGECAFIK"},
		{"ACEFGHIJ", "HGJCAFEI"},
		{"ACDHIJKL", "HJICADLK"},
		{"ACDGIJKL", "IGJCADLK"},
		{"ACDGHJKL", "HGJCADLK"},
		{"ACDGHIKL", "HGICADLK"},
		{"ACDGHIJL", "HGJCADLI"},
		{"ACDGHIJK", "HGJCADIK"},
		{"ACDFIJKL", "CJIDAFLK"},
		{"ACDFHJKL", "HJFCADLK"},
		{"ACDFHIKL", "HFICADLK"},
		{"ACDFHIJL", "HJFCADLI"},
		{"ACDFHIJK", "HJFCADIK"},
		{"ACDFGJKL", "CGJDAFLK"},
		{"ACDFGIKL", "CGIDAFLK"},
		{"ACDFGIJL", "CGJDAFLI"},
		{"ACDFGIJK", "CGJDAFIK"},
		{"ACDFGHKL", "HGFCADLK"},
		{"ACDFGHJL", "CGJDAFLH"},
		{"ACDFGHJK", "HGJCAFDK"},
		{"ACDFGHIL", "HGFCADLI"},
		{"ACDFGHIK", "HGFCADIK"},
		{"ACDFGHIJ", "HGJCAFDI"},
		{"ACDEIJKL", "EJICADLK"},
		{"ACDEHJKL", "HJECADLK"},
		{"ACDEHIKL", "HEICADLK"},
		{"ACDEHIJL", "HJECADLI"},
		{"ACDEHIJK", "HJECADIK"},
		{"ACDEGJKL", "EGJCADLK"},
		{"ACDEGIKL", "EGICADLK"},
		{"ACDEGIJL", "EGJCADLI"},
		{"ACDEGIJK", "EGJCADIK"},
		{"ACDEGHKL", "HGECADLK"},
		{"ACDEGHJL", "HGJCADLE"},
		{"ACDEGHJK", "HGJCADEK"},
		{"ACDEGHIL", "HGECADLI"},
		{"ACDEGHIK", "HGECADIK"},
		{"ACDEGHIJ", "HGJCADEI"},
		{"ACDEFJKL", "CJEDAFLK"},
		{"ACDEFIKL", "CEIDAFLK"},
		{"ACDEFIJL", "CJEDAFLI"},
		{"ACDEFIJK", "CJEDAFIK"},
		{"ACDEFHKL", "HEFCADLK"},
		{"ACDEFHJL", "HJFCADLE"},
		{"ACDEFHJK", "HJECAFDK"},
		{"ACDEFHIL", "HEFCADLI"},
		{"ACDEFHIK", "HEFCADIK"},
		{"ACDEFHIJ", "HJECAFDI"},
		{"ACDEFGKL", "CGEDAFLK"},
		{"ACDEFGJL", "CGJDAFLE"},
		{"ACDEFGJK", "CGJDAFEK"},
		{"ACDEFGIL", "CGEDAFLI"},
		{"ACDEFGIK", "CGEDAFIK"},
		{"ACDEFGIJ", "CGJDAFEI"},
		{"ACDEFGHL", "HGFCADLE"},
		{"ACDEFGHK", "HGECAFDK"},
		{"ACDEFGHJ", "HGJCAFDE"},
		{"ACDEFGHI", "HGECAFDI"},
		{"ABGHIJKL", "HJBAIGLK"},
		{"ABFHIJKL", "HJBAIFLK"},
		{"ABFGIJKL", "IJBFAGLK"},
		{"ABFGHJKL", "HJBFAGLK"},
		{"ABFGHIKL", "HGBAIFLK"},
		{"ABFGHIJL", "HJBFAGLI"},
		{"ABFGHIJK", "HJBFAGIK"},
		{"ABEHIJKL", "EJBAIHLK"},
		{"ABEGIJKL", "EJBAIGLK"},
		{"ABEGHJKL", "EJBAHGLK"},
		{"ABEGHIKL", "EGBAIHLK"},
		{"ABEGHIJL", "EJBAHGLI"},
		{"ABEGHIJK", "EJBAHGIK"},
		{"ABEFIJKL", "EJBAIFLK"},
		{"ABEFHJKL", "EJBFAHLK"},
		{"ABEFHIKL", "EIBFAHLK"},
		{"ABEFHIJL", "EJBFAHLI"},
		{"ABEFHIJK", "EJBFAHIK"},
		{"ABEFGJKL", "EJBFAGLK"},
		{"ABEFGIKL", "EGBAIFLK"},
		{"ABEFGIJL", "EJBFAGLI"},
		{"ABEFGIJK", "EJBFAGIK"},
		{"ABEFGHKL", "EGBFAHLK"},
		{"ABEFGHJL", "HJBFAGLE"},
		{"ABEFGHJK", "HJBFAGEK"},
		{"ABEFGHIL", "EGBFAHLI"},
		{"ABEFGHIK", "EGBFAHIK"},
		{"ABEFGHIJ", "HJBFAGEI"},
		{"ABDHIJKL", "IJBDAHLK"},
		{"ABDGIJKL", "IJBDAGLK"},
		{"ABDGHJKL", "HJBDAGLK"},
		{"ABDGHIKL", "IGBDAHLK"},
		{"ABDGHIJL", "HJBDAGLI"},
		{"ABDGHIJK", "HJBDAGIK"},
		{"ABDFIJKL", "IJBDAFLK"},
		{"ABDFHJKL", "HJBDAFLK"},
		{"ABDFHIKL", "HIBDAFLK"},
		{"ABDFHIJL", "HJBDAFLI"},
		{"ABDFHIJK", "HJBDAFIK"},
		{"ABDFGJKL", "FJBDAGLK"},
		{"ABDFGIKL", "IGBDAFLK"},
		{"ABDFGIJL", "FJBDAGLI"},
		{"ABDFGIJK", "FJBDAGIK"},
		{"ABDFGHKL", "HGBDAFLK"},
		{"ABDFGHJL", "HGBDAFLJ"},
		{"ABDFGHJK", "HGBDAFJK"},
		{"ABDFGHIL", "HGBDAFLI"},
		{"ABDFGHIK", "HGBDAFIK"},
		{"ABDFGHIJ", "HGBDAFIJ"},
		{"ABDEIJKL", "EJBAIDLK"},
		{"ABDEHJKL", "EJBDAHLK"},
		{"ABDEHIKL", "EIBDAHLK"},
		{"ABDEHIJL", "EJBDAHLI"},
		{"ABDEHIJK", "EJBDAHIK"},
		{"ABDEGJKL", "EJBDAGLK"},
		{"ABDEGIKL", "EGBAIDLK"},
		{"ABDEGIJL", "EJBDAGLI"},
		{"ABDEGIJK", "EJBDAGIK"},
		{"ABDEGHKL", "EGBDAHLK"},
		{"ABDEGHJL", "HJBDAGLE"},
		{"ABDEGHJK", "HJBDAGEK"},
		{"ABDEGHIL", "EGBDAHLI"},
		{"ABDEGHIK", "EGBDAHIK"},
		{"ABDEGHIJ", "HJBDAGEI"},
		{"ABDEFJKL", "EJBDAFLK"},
		{"ABDEFIKL", "EIBDAFLK"},
		{"ABDEFIJL", "EJBDAFLI"},
		{"ABDEFIJK", "EJBDAFIK"},
		{"ABDEFHKL", "HEBDAFLK"},
		{"ABDEFHJL", "HJBDAFLE"},
		{"ABDEFHJK", "HJBDAFEK"},
		{"ABDEFHIL", "HEBDAFLI"},
		{"ABDEFHIK", "HEBDAFIK"},
		{"ABDEFHIJ", "HJBDAFEI"},
		{"ABDEFGKL", "EGBDAFLK"},
		{"ABDEFGJL", "EGBDAFLJ"},
		{"ABDEFGJK", "EGBDAFJK"},
		{"ABDEFGIL", "EGBDAFLI"},
		{"ABDEFGIK", "EGBDAFIK"},
		{"ABDEFGIJ", "EGBDAFIJ"},
		{"ABDEFGHL", "HGBDAFLE"},
		{"ABDEFGHK", "HGBDAFEK"},
		{"ABDEFGHJ", "HGBDAFEJ"},
		{"ABDEFGHI", "HGBDAFEI"},
		{"ABCHIJKL", "IJBCAHLK"},
		{"ABCGIJKL", "IJBCAGLK"},
		{"ABCGHJKL", "HJBCAGLK"},
		{"ABCGHIKL", "IGBCAHLK"},
		{"ABCGHIJL", "HJBCAGLI"},
		{"ABCGHIJK", "HJBCAGIK"},
		{"ABCFIJKL", "IJBCAFLK"},
		{"ABCFHJKL", "HJBCAFLK"},
		{"ABCFHIKL", "HIBCAFLK"},
		{"ABCFHIJL", "HJBCAFLI"},
		{"ABCFHIJK", "HJBCAFIK"},
		{"ABCFGJKL", "CJBFAGLK"},
		{"ABCFGIKL", "IGBCAFLK"},
		{"ABCFGIJL", "CJBFAGLI"},
		{"ABCFGIJK", "CJBFAGIK"},
		{"ABCFGHKL", "HGBCAFLK"},
		{"ABCFGHJL", "HGBCAFLJ"},
		{"ABCFGHJK", "HGBCAFJK"},
		{"ABCFGHIL", "HGBCAFLI"},
		{"ABCFGHIK", "HGBCAFIK"},
		{"ABCFGHIJ", "HGBCAFIJ"},
		{"ABCEIJKL", "EJBAICLK"},
		{"ABCEHJKL", "EJBCAHLK"},
		{"ABCEHIKL", "EIBCAHLK"},
		{"ABCEHIJL", "EJBCAHLI"},
		{"ABCEHIJK", "EJBCAHIK"},
		{"ABCEGJKL", "EJBCAGLK"},
		{"ABCEGIKL", "EGBAICLK"},
		{"ABCEGIJL", "EJBCAGLI"},
		{"ABCEGIJK", "EJBCAGIK"},
		{"ABCEGHKL", "EGBCAHLK"},
		{"ABCEGHJL", "HJBCAGLE"},
		{"ABCEGHJK", "HJBCAGEK"},
		{"ABCEGHIL", "EGBCAHLI"},
		{"ABCEGHIK", "EGBCAHIK"},
		{"ABCEGHIJ", "HJBCAGEI"},
		{"ABCEFJKL", "EJBCAFLK"},
		{"ABCEFIKL", "EIBCAFLK"},
		{"ABCEFIJL", "EJBCAFLI"},
		{"ABCEFIJK", "EJBCAFIK"},
		{"ABCEFHKL", "HEBCAFLK"},
		{"ABCEFHJL", "HJBCAFLE"},
		{"ABCEFHJK", "HJBCAFEK"},
		{"ABCEFHIL", "HEBCAFLI"},
		{"ABCEFHIK", "HEBCAFIK"},
		{"ABCEFHIJ", "HJBCAFEI"},
		{"ABCEFGKL", "EGBCAFLK"},
		{"ABCEFGJL", "EGBCAFLJ"},
		{"ABCEFGJK", "EGBCAFJK"},
		{"ABCEFGIL", "EGBCAFLI"},
		{"ABCEFGIK", "EGBCAFIK"},
		{"ABCEFGIJ", "EGBCAFIJ"},
		{"ABCEFGHL", "HGBCAFLE"},
		{"ABCEFGHK", "HGBCAFEK"},
		{"ABCEFGHJ", "HGBCAFEJ"},
		{"ABCEFGHI", "HGBCAFEI"},
		{"ABCDIJKL", "IJBCADLK"},
		{"ABCDHJKL", "HJBCADLK"},
		{"ABCDHIKL", "HIBCADLK"},
		{"ABCDHIJL", "HJBCADLI"},
		{"ABCDHIJK", "HJBCADIK"},
		{"ABCDGJKL", "CJBDAGLK"},
		{"ABCDGIKL", "IGBCADLK"},
		{"ABCDGIJL", "CJBDAGLI"},
		{"ABCDGIJK", "CJBDAGIK"},
		{"ABCDGHKL", "HGBCADLK"},
		{"ABCDGHJL", "HGBCADLJ"},
		{"ABCDGHJK", "HGBCADJK"},
		{"ABCDGHIL", "HGBCADLI"},
		{"ABCDGHIK", "HGBCADIK"},
		{"ABCDGHIJ", "HGBCADIJ"},
		{"ABCDFJKL", "CJBDAFLK"},
		{"ABCDFIKL", "CIBDAFLK"},
		{"ABCDFIJL", "CJBDAFLI"},
		{"ABCDFIJK", "CJBDAFIK"},
		{"ABCDFHKL", "HFBCADLK"},
		{"ABCDFHJL", "CJBDAFLH"},
		{"ABCDFHJK", "HJBCAFDK"},
		{"ABCDFHIL", "HFBCADLI"},
		{"ABCDFHIK", "HFBCADIK"},
		{"ABCDFHIJ", "HJBCAFDI"},
		{"ABCDFGKL", "CGBDAFLK"},
		{"ABCDFGJL", "CGBDAFLJ"},
		{"ABCDFGJK", "CGBDAFJK"},
		{"ABCDFGIL", "CGBDAFLI"},
		{"ABCDFGIK", "CGBDAFIK"},
		{"ABCDFGIJ", "CGBDAFIJ"},
		{"ABCDFGHL", "CGBDAFLH"},
		{"ABCDFGHK", "HGBCAFDK"},
		{"ABCDFGHJ", "HGBCAFDJ"},
		{"ABCDFGHI", "HGBCAFDI"},
		{"ABCDEJKL", "EJBCADLK"},
		{"ABCDEIKL", "EIBCADLK"},
		{"ABCDEIJL", "EJBCADLI"},
		{"ABCDEIJK", "EJBCADIK"},
		{"ABCDEHKL", "HEBCADLK"},
		{"ABCDEHJL", "HJBCADLE"},
		{"ABCDEHJK", "HJBCADEK"},
		{"ABCDEHIL", "HEBCADLI"},
		{"ABCDEHIK", "HEBCADIK"},
		{"ABCDEHIJ", "HJBCADEI"},
		{"ABCDEGKL", "EGBCADLK"},
		{"ABCDEGJL", "EGBCADLJ"},
		{"ABCDEGJK", "EGBCADJK"},
		{"ABCDEGIL", "EGBCADLI"},
		{"ABCDEGIK", "EGBCADIK"},
		{"ABCDEGIJ", "EGBCADIJ"},
		{"ABCDEGHL", "HGBCADLE"},
		{"ABCDEGHK", "HGBCADEK"},
		{"ABCDEGHJ", "HGBCADEJ"},
		{"ABCDEGHI", "HGBCADEI"},
		{"ABCDEFKL", "CEBDAFLK"},
		{"ABCDEFJL", "CJBDAFLE"},
		{"ABCDEFJK", "CJBDAFEK"},
		{"ABCDEFIL", "CEBDAFLI"},
		{"ABCDEFIK", "CEBDAFIK"},
		{"ABCDEFIJ", "CJBDAFEI"},
		{"ABCDEFHL", "HFBCADLE"},
		{"ABCDEFHK", "HEBCAFDK"},
		{"ABCDEFHJ", "HJBCAFDE"},
		{"ABCDEFHI", "HEBCAFDI"},
		{"ABCDEFGL", "CGBDAFLE"},
		{"ABCDEFGK", "CGBDAFEK"},
		{"ABCDEFGJ", "CGBDAFEJ"},
		{"ABCDEFGI", "CGBDAFEI"},
		{"ABCDEFGH", "HGBCAFDE"},
	};
	DWORD off = table_start_offset;
	for (auto const& x : table)
	{
		for (int i = 0; i < 8; i++) WriteBytes(off++, 1, x.first[i]);
		for (int i = 0; i < 8; i++) WriteBytes(off++, 1, strchr(x.second, x.first[i]) - x.second + 1);
	}
}