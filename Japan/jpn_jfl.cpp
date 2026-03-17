#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* jpn_jfl_vtable = new vtable((BYTE*)0x96CAF4, 0xB4);

void jpn_jfl_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(jpn_jfl_vtable->vtable_ptr);
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

void jpn_jfl_free(BYTE* _this, BYTE a2) {
	jpn_jfl_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) jpn_jfl_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_jfl_free
		add esp, 0x8
		ret 4
	}
}

void jpn_jfl_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 2;

	comp_data->promotes_to = JPN_THIRD_9CF();
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) jpn_jfl_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call jpn_jfl_subs
		add esp, 0x4
		ret
	}
}

DWORD jpn_jfl_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 9), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 16), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 23), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 30), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 6), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 13), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 20), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 4), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 18), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 29), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 6), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 13), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 20), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 27), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 31), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 28), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 2), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 16), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 23), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) jpn_jfl_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_jfl_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int jpn_jfl_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	cm3_club_comps* jpn_third = get_comp(JPN_THIRD_9CF());
	if (stage == -1) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(jpn_third), None, Playoff, 0x1E);
			return 0;
		case BottomPlayoff:
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) jpn_jfl_set_table_fate()
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
		call jpn_jfl_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void jpn_jfl_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) jpn_jfl_reputation_calc_c()
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
		call jpn_jfl_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char jpn_jfl_update(BYTE* _this) {
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
	jpn_jfl_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) jpn_jfl_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call jpn_jfl_update
		add esp, 0x4
		ret
	}
}

void jpn_jfl_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(jpn_jfl_vtable->vtable_ptr);
	jpn_jfl_vtable->SetPointer(VTableEoSUpdate, (DWORD)&jpn_jfl_update_c);
	jpn_jfl_vtable->SetPointer(VTableSubsRounds, (DWORD)&jpn_jfl_subs_c);
	jpn_jfl_vtable->SetPointer(VTableFixtures, (DWORD)&jpn_jfl_fixtures_c);
	jpn_jfl_vtable->SetPointer(VTableInitFree, (DWORD)&jpn_jfl_free_c);
	jpn_jfl_vtable->SetPointer(VTableTableFates, (DWORD)&jpn_jfl_set_table_fate);
	jpn_jfl_vtable->SetPointer(VTableReputationCalc, (DWORD)&jpn_jfl_reputation_calc_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) jpn_jfl_vtable->SetPointer(VTable21, 0x4110b0);
	data->year = year;
	data->rules = 0x13;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	jpn_jfl_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	reputation_setup_generic_68A850(_this);
}

void setup_jpn_jfl()
{

}