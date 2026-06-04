#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* nir_league_cup_vtable = (DWORD*)0x96DC18;

void nir_league_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = nir_league_cup_vtable;
	DWORD x = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
	}
	if ((DWORD*)data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
	}
	if (data->f8) {
		sub_49F450((BYTE*)(data->f8));
		sub_944C94_free((BYTE*)(data->f8));
	}
	DWORD y = -1;
	sub_518690(_this);
}

void nir_league_cup_free(BYTE* _this, BYTE a2) {
	nir_league_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) nir_league_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call nir_league_cup_free
		add esp, 0x8
		ret 4
	}
}

DWORD nir_league_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 25), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 12), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 12, 6, 12, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 13), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 7), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 26, 12, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 8), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 4), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 5), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 2), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 8, 4, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("nir_league_cup_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 13), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("nir_league_cup_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 14), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday, Afternoon, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("nir_league_cup_final_win"), prizeMoneyFile.GetInt("nir_league_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) nir_league_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call nir_league_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int nir_league_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 38;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// NIFL Intermediate
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(NIR_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// NIFL Championship
	division_clubs = find_clubs_of_comp(NIR_FIRST_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// NIFL Premier
	division_clubs = find_clubs_of_comp(NIR_PREMIER_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void nir_league_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = nir_league_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesNorthernIreland;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	nir_league_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

char nir_league_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
	if (data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
		data->rounds_list = 0;
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
				data->f173[i] = 0;
			}
		}
		sub_9452CA_free(data->f173);
		data->f173 = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	nir_league_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) nir_league_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nir_league_cup_update
		add esp, 0x4
		ret
	}
}

void setup_nir_league_cup()
{
	WriteVTablePtr(nir_league_cup_vtable, VTableInitFree, (DWORD)&nir_league_cup_free_c);
	WriteVTablePtr(nir_league_cup_vtable, VTableEoSUpdate, (DWORD)&nir_league_cup_update_c);
	WriteVTablePtr(nir_league_cup_vtable, VTableFixtures, (DWORD)&nir_league_cup_fixture_caller);
	WriteVTablePtr(nir_league_cup_vtable, VTablePostMatchUpdate, 0x51A150);
	WriteVTablePtr(nir_league_cup_vtable, VTable5, 0x521E00);
	WriteVTablePtr(nir_league_cup_vtable, VTableLeagueSplit, 0x51F890);
	WriteVTablePtr(nir_league_cup_vtable, VTable7, 0x51FC00);
	WriteVTablePtr(nir_league_cup_vtable, VTable8, 0x5210F0);
	WriteVTablePtr(nir_league_cup_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(nir_league_cup_vtable, VTable10, 0x48CEA0);
	WriteVTablePtr(nir_league_cup_vtable, VTablePlayoffQual, 0x5A8F60);
	WriteVTablePtr(nir_league_cup_vtable, VTableSetChampion, 0x519A90);
	WriteVTablePtr(nir_league_cup_vtable, VTable17, 0x519690);
	WriteVTablePtr(nir_league_cup_vtable, VTableTableFates, 0x519890);
	WriteVTablePtr(nir_league_cup_vtable, VTableStageNews, 0x48C6D0);
	WriteVTablePtr(nir_league_cup_vtable, VTable22, 0x5221F0);
	WriteVTablePtr(nir_league_cup_vtable, VTableReputationSetup, 0x5223A0);
	WriteVTablePtr(nir_league_cup_vtable, VTableReputationCalc, 0x48E380);
	WriteVTablePtr(nir_league_cup_vtable, VTable33, 0x522910);
	WriteVTablePtr(nir_league_cup_vtable, VTable34, 0x522C50);
	WriteVTablePtr(nir_league_cup_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(nir_league_cup_vtable, VTable37, 0x522360);
	WriteVTablePtr(nir_league_cup_vtable, VTable38, 0x518790);
	WriteVTablePtr(nir_league_cup_vtable, VTable39, 0x51C020);
	WriteVTablePtr(nir_league_cup_vtable, VTable40, 0x51F2F0);
}
