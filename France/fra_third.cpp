#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* fra_third_vtable = (DWORD*)0x96AD80;

void fra_third_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->promotions = 2;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 0;
	if (comp_data->year == 2025) comp_data->relegations = 2;
	else comp_data->relegations = 3;

	comp_data->promotes_to = FRA_SECOND_9CF();
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) fra_third_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fra_third_subs
		add esp, 0x4
		ret
	}
}

DWORD fra_third_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1 + numberOfLeagueTeams % 2) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 8), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 15), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 22), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 29), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 5), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 12), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 19), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 26), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 3), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 17), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 21), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 31), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 7), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 21), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 5), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 12), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 16), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 23), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 30), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 6), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 13), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 20), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 27), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 6), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 13), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 20), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 27), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 3), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 10), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 17), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 24), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 1), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 8), year, Friday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 15), year, Friday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) fra_third_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fra_third_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void fra_third_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = fra_third_vtable;
	data->year = year;
	data->rules = RulesFrance;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	fra_third_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

char fra_third_update(BYTE* _this) {
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
			data->stages[i] = 0;
		}
	}
	data->year++;
	data->current_stage = -1;
	*((DWORD*)(_this + 0xA7)) = -1;
	fra_third_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) fra_third_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fra_third_update
		add esp, 0x4
		ret
	}
}

int fra_third_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		cm3_club_comps* fra_second = get_comp(FRA_SECOND_9CF());
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)fra_second, None, Playoff, 0xF);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
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

void __declspec(naked) fra_third_set_table_fate()
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
		call fra_third_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void setup_fra_third()
{
	WriteVTablePtr(fra_third_vtable, VTableSubsRounds, (DWORD)&fra_third_subs_c);
	WriteVTablePtr(fra_third_vtable, VTableEoSUpdate, (DWORD)&fra_third_update_c);
	WriteVTablePtr(fra_third_vtable, VTableFixtures, (DWORD)&fra_third_fixtures_c);
	WriteVTablePtr(fra_third_vtable, VTableTableFates, (DWORD)&fra_third_set_table_fate);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(fra_third_vtable, VTable21, 0x4110b0);
}
