#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <Helpers\9cf_constants.h>

DWORD* ita_c_supercup_vtable = (DWORD*)0x96C0C8;

void ita_c_supercup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = ita_c_supercup_vtable;
	DWORD x = 0;
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
	sub_682300(_this);
}

void ita_c_supercup_free(BYTE* _this, BYTE a2) {
	ita_c_supercup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) ita_c_supercup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_c_supercup_free
		add esp, 0x8
		ret 4
	}
}

void ita_c_supercup_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = NoTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) ita_c_supercup_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_c_supercup_subs
		add esp, 0x4
		ret
	}
}

char ita_c_supercup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	sub_687970(_this, ebx);
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
		}
	}
	data->year++;
	data->current_stage = -1;
	ita_c_supercup_subs(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) ita_c_supercup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_c_supercup_update
		add esp, 0x4
		ret
	}
}

DWORD ita_c_supercup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 3;
		*num_rounds = numberOfLeagueTeams * data->n_rounds;
		*num_rounds = numberOfLeagueTeams * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 16), year, Saturday);

		if (fixture_id != 3) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ita_c_supercup_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_c_supercup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int ita_c_supercup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 3;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(league_team_list_sz * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->team_league_table = (DWORD*)pMem;

	comp_stats* ita_ser_c_data = (comp_stats*)get_loaded_league(ITA_SERIE_C_9CF());
	comp_stats* curr_stage = ita_ser_c_data;
	BYTE teamsAdded = 0;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(ita_ser_c_data->stages[al]);
		}
		// 0-index so 1 = second place
		cm3_clubs* club = ((team_league_stats*)curr_stage->team_league_table)[0].club;
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}

	return 1;
}

void ita_c_supercup_63B300(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		comp_stats* ita_ser_c_data = (comp_stats*)get_loaded_league(ITA_SERIE_C_9CF());
		if (ita_ser_c_data->current_stage > 1) {
			if (!a3) {
				ita_c_supercup_teams(_this);
				sub_6835C0(_this);
				sub_6827D0(_this, 0);
				DWORD v1 = *(DWORD*)_this;
				(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
				data->f69 = 1;
			}
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) ita_c_supercup_63B300_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_c_supercup_63B300
		add esp, 0xc
		ret 8
	}
}

void ita_c_supercup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = ita_c_supercup_vtable;
	data->year = year;
	data->rules = 0x11;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_PURPLE_2_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_GOLD_9CF());
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	ita_c_supercup_subs(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void setup_ita_c_supercup()
{
	WriteVTablePtr(ita_c_supercup_vtable, VTableInitFree, (DWORD)&ita_c_supercup_free_c);
	WriteVTablePtr(ita_c_supercup_vtable, VTableEoSUpdate, (DWORD)&ita_c_supercup_update_c);
	WriteVTablePtr(ita_c_supercup_vtable, VTableLeagueSplit, (DWORD)&ita_c_supercup_63B300_c);
	WriteVTablePtr(ita_c_supercup_vtable, VTableFixtures, (DWORD)&ita_c_supercup_fixtures_c);
	WriteVTablePtr(ita_c_supercup_vtable, VTableSubsRounds, (DWORD)&ita_c_supercup_subs_c);
	WriteVTablePtr(ita_c_supercup_vtable, VTableTableFates, 0x686940);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(ita_c_supercup_vtable, VTable21, 0x4110b0);
}
