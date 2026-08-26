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

DWORD* world_cup_quals_conmebol_vtable = (DWORD*)0x970E2C;

void world_cup_quals_conmebol_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = world_cup_quals_conmebol_vtable;
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

void world_cup_quals_conmebol_free(BYTE* _this, BYTE a2) {
	world_cup_quals_conmebol_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) world_cup_quals_conmebol_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_conmebol_free
		add esp, 0x8
		ret 4
	}
}

void world_cup_quals_conmebol_subs(BYTE* _this)
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
	comp_data->promotions = 6;
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

void __declspec(naked) world_cup_quals_conmebol_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_conmebol_subs
		add esp, 0x4
		ret
	}
}

DWORD world_cup_quals_conmebol_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), SOUTH_AMERICA_9CF(), 0, 0);
		BYTE numberOfLeagueTeams = 10 - num_hosts;
		*num_rounds = (numberOfLeagueTeams - 1 + numberOfLeagueTeams % 2) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		//AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Thursday, Afternoon);
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 7), year, Thursday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		if (numberOfLeagueTeams > 8) AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 12), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 12), year, Thursday, Afternoon);
		if (numberOfLeagueTeams > 8) AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 17), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 16), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 21), year, Tuesday, Afternoon);
		//AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 9, 5), year, Thursday, Afternoon);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 9, 5), year, Thursday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		if (numberOfLeagueTeams > 8) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 9, 10), year, Tuesday, Afternoon);
		//AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 10, 10), year, Thursday, Afternoon);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 10, 10), year, Thursday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		if (numberOfLeagueTeams > 8) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 10, 15), year, Tuesday, Afternoon);
		//AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 11, 14), year, Thursday, Afternoon);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 11, 14), year, Thursday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 11, 19), year, Tuesday, Afternoon);
		//AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 20), year, Thursday, Afternoon);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 2, 3, 20), year, Thursday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 25), year, Tuesday, Afternoon);
		//AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 6, 5), year, Thursday, Afternoon);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 2, 6, 5), year, Thursday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 6, 10), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 9, 4), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 9, 9), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) world_cup_quals_conmebol_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_conmebol_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char world_cup_quals_conmebol_update(BYTE* _this) {
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
	world_cup_quals_conmebol_subs(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) world_cup_quals_conmebol_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_quals_conmebol_update
		add esp, 0x4
		ret
	}
}

void world_cup_quals_conmebol_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	vector<cm3_clubs*> countries = get_national_teams_of_continent_fifa_members(SOUTH_AMERICA_9CF());

	DWORD host1_id, host2_id;
	WORD num_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), SOUTH_AMERICA_9CF(), &host1_id, &host2_id);
	data->promotions -= num_hosts;
	data->prom_playoff += (num_hosts > 0);
	WORD total_teams_in_comp = (WORD)countries.size() - num_hosts;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	BYTE* pMem2 = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams_in_comp);
	data->n_teams = total_teams_in_comp;
	data->team_league_table = (DWORD*)pMem2;

	for (BYTE i = 0, j = 0; i < countries.size() && j < total_teams_in_comp; i++) {
		if (countries[i]->ClubNation->NationID == host1_id || countries[i]->ClubNation->NationID == host2_id) continue;
		teams[j].club = countries[i];
		teams[j].f5 = 6;
		teams[j].f6 = 0;
		add_team_call(_this, j++, countries[i], 0, 0);
	}
	sub_684230(_this);
}

void world_cup_quals_conmebol_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = world_cup_quals_conmebol_vtable;
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = WORLD_CUP_OFC_QUALIFYING_9CF();
	data->relegates_to = WORLD_CUP_CAF_QUALIFYING_9CF();
	data->rules = RulesInternational;
	data->f82 = 3;
	data->year = year;
	while (data->year % 4 != 3) data->year++;
	data->f81 = 0xf;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->f217 = 0x28;
	data->current_stage = -1;
	data->num_stages = 0;
	world_cup_quals_conmebol_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void world_cup_quals_conmebol_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 26, July, data->year, -1);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
			if (a3) {
				sub_775070((BYTE*)*b74318, get_continent(SOUTH_AMERICA_9CF()), 0);
				data->f69 = 1;
				world_cup_quals_conmebol_teams(_this);
				sub_6835C0(_this);
				sub_6827D0(_this, 0);
				DWORD v1 = *(DWORD*)_this;
				(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
			}
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) world_cup_quals_conmebol_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_conmebol_init2
		add esp, 0xc
		ret 8
	}
}

int world_cup_quals_conmebol_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		switch (fate) {
		case Qualified1:
			qualify_team_for_international_comp(club, FIFA_WORLD_CUP_9CF());
			return 0;
		case TopPlayoff:
			// has to be done separately
			//staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(get_comp(WORLD_CUP_PLAYOFFS_9CF())), None, None, 0x1E);
			return 0;
		default:
			staff_history_failed_qual_86C1D0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) world_cup_quals_conmebol_set_table_fate()
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
		call world_cup_quals_conmebol_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int world_cup_quals_conmebol_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1) {
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
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	return 0;
}

void __declspec(naked) world_cup_quals_conmebol_stage_news_c()
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
		call world_cup_quals_conmebol_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void world_cup_quals_conmebol_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if (main_stage_id == None) {
		if (fate == Qualified1) {
			sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else if (fate == TopPlayoff) {
			sub_66F4E0(dest_ptr, (DWORD)&qualified_wc_playoffs[0]);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, 0xAD4DDC, club->ClubGenderName, 0xAD9C64);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) world_cup_quals_conmebol_landmarks_c()
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
		call world_cup_quals_conmebol_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

BYTE world_cup_quals_conmebol_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	BYTE cutoff = data->promotions + data->prom_playoff;
	if (al < cutoff) return (bl < cutoff) - 1;
	else return bl < cutoff;
}

void __declspec(naked) world_cup_quals_conmebol_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_quals_conmebol_vtable30
		add esp, 0x8
		ret 4
	}
}

void setup_world_cup_quals_conmebol() {
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableInitFree, (DWORD)&world_cup_quals_conmebol_free_c);
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableEoSUpdate, (DWORD)&world_cup_quals_conmebol_update_c);
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableLeagueSplit, (DWORD)&world_cup_quals_conmebol_init2_c);
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableTableFates, (DWORD)&world_cup_quals_conmebol_set_table_fate);
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableFixtures, (DWORD)&world_cup_quals_conmebol_fixture_caller);
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableStageNews, (DWORD)&world_cup_quals_conmebol_stage_news_c);
	//WriteVTablePtr(world_cup_quals_conmebol_vtable, VTable29, (DWORD)&world_cup_quals_conmebol_vtable29_c);
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTable30, (DWORD)&world_cup_quals_conmebol_vtable30_c);
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableClubLandmarks, (DWORD)&world_cup_quals_conmebol_landmarks_c);

	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTable10, 0x48CEA0);

	WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableSubsRounds, (DWORD)&world_cup_quals_conmebol_subs_c);
	//WriteVTablePtr(world_cup_quals_conmebol_vtable, VTableSetChampion, 0x519A90);
}