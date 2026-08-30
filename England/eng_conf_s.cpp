#pragma warning (disable : 4733)
#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include "eng_conf.h"
#include <Helpers\9cf_constants.h>

vtable* eng_conf_s_vtable = new vtable((BYTE*)0x969A74, 0xB4);

char* eng_conf_s_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* playoff_bytes = (BYTE*)comp_data->stages[0];
	comp_stats* playoff_data = (comp_stats*)playoff_bytes;
	cm3_clubs* po_win = 0;
	teams_seeded* teams = (teams_seeded*)playoff_data->teams_list;
	for (WORD i = 0; i < playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) po_win = teams[i].club;
	}
	team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
	cm3_clubs* first = table[0].club;
	cm3_clubs* second = table[1].club;
	cm3_clubs* third = table[2].club;
	return sub_4AFCE0_add_history_entry(_this, first, second, third, po_win);
}

void __declspec(naked) eng_conf_s_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_conf_s_set_champion
		add esp, 0x4
		ret 0
	}
}

void eng_conf_s_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(eng_conf_s_vtable->vtable_ptr);
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

void eng_conf_s_free(BYTE* _this, BYTE a2) {
	eng_conf_s_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) eng_conf_s_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call eng_conf_s_free
		add esp, 0x8
		ret 4
	}
}

int eng_conf_s_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 6;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 4;

	comp_data->promotes_to = ENG_CONFERENCE_NORTH_9CF();
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return 1;
}

char eng_conf_s_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	sub_687970(_this, 0);
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
	data->year++;
	data->current_stage = -1;
	eng_conf_s_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("eng_conf_ns_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) eng_conf_s_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_conf_s_update
		add esp, 0x4
		ret
	}
}

void __declspec(naked) eng_conf_s_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_conf_s_subs
		add esp, 0x4
		ret
	}
}

void __declspec(naked) eng_conf_s_reputation_calc_c()
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
		call eng_conf_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void eng_conf_s_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(eng_conf_s_vtable->vtable_ptr);
	eng_conf_s_vtable->SetPointer(VTableInitFree, (DWORD)&eng_conf_s_free_c);
	eng_conf_s_vtable->SetPointer(VTableEoSUpdate, (DWORD)&eng_conf_s_update_c);
	eng_conf_s_vtable->SetPointer(VTablePlayoffQual, (DWORD)&eng_conf_playoffs_c);
	eng_conf_s_vtable->SetPointer(VTableFixtures, (DWORD)&eng_conf_fixtures_c);
	eng_conf_s_vtable->SetPointer(VTableTableFates, (DWORD)&eng_conf_set_table_fate);
	eng_conf_s_vtable->SetPointer(VTableSubsRounds, (DWORD)&eng_conf_s_subs_c);
	eng_conf_s_vtable->SetPointer(VTableReputationCalc, (DWORD)&eng_conf_s_reputation_calc_c);
	eng_conf_s_vtable->SetPointer(VTableSetChampion, (DWORD)&eng_conf_s_set_champion_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) eng_conf_s_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	if (configFile.GetBool("showPlayoffWinnerInHistory", true)) eng_conf_s_vtable->SetPointer(VTableShowHostsInHistory, 0x404480);
	data->year = year;
	data->rules = RulesEngland;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 3000;
	data->min_stadium_seats = 250;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	eng_conf_s_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("eng_conf_ns_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_eng_conf_s() {
}