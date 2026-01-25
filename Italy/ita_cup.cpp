#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers/new_league_ids.h>

DWORD* ita_cup_vtable = (DWORD*)0x96C318;

void ita_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = ita_cup_vtable;
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

void ita_cup_free(BYTE* _this, BYTE a2) {
	ita_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) ita_cup_free_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_cup_free
		add esp, 0x8
		ret 4
	}
}

DWORD CreateItalyCupFixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = *(WORD*)(_this + 0x40);
		*num_rounds = 7;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 6), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 10), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, QualifyingRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 12, 6, 12, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 11), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 32, 16, 26, 12, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 18), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 24), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 26), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 16, 8, 8, 38, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 3), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 16), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 0, 0, 0, 2, 49);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 13), year, Wednesday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ita_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call CreateItalyCupFixtures
		add esp, 0x14
		ret 0x10
	}
}

int ita_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	vec.clear();
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 46;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// Serie C - review later
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(serie_c_id);
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	for (DWORD i = 0; i < 6; i++) {
		vec.push_back(division_clubs[i]);
	}
	// Serie B
	division_clubs = find_clubs_of_comp(Get9CF(0x9CF574));
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Serie A
	division_clubs = find_clubs_of_comp(Get9CF(0x9CF570));
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
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

void ita_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = ita_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = 0x12;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	ita_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	data->f40 = 600000;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_5223A0(_this);
}

char ita_cup_update(BYTE* _this) {
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
	ita_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) ita_cup_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_cup_update
		add esp, 0x4
		ret
	}
}

void setup_ita_cup()
{
	WriteVTablePtr(ita_cup_vtable, VTableInitFree, (DWORD)&ita_cup_free_c);
	WriteVTablePtr(ita_cup_vtable, VTableEoSUpdate, (DWORD)&ita_cup_update_c);
	WriteVTablePtr(ita_cup_vtable, VTableFixtures, (DWORD)&ita_cup_fixture_caller);
	WriteVTablePtr(ita_cup_vtable, VTable2, 0x51A150);
	WriteVTablePtr(ita_cup_vtable, VTable5, 0x521E00);
	WriteVTablePtr(ita_cup_vtable, VTable6, 0x51F890);
	WriteVTablePtr(ita_cup_vtable, VTable7, 0x51FC00);
	WriteVTablePtr(ita_cup_vtable, VTable8, 0x5210F0);
	WriteVTablePtr(ita_cup_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(ita_cup_vtable, VTable10, 0x48CEA0);
	WriteVTablePtr(ita_cup_vtable, VTablePlayoffQual, 0x5A8F60);
	WriteVTablePtr(ita_cup_vtable, VTable13, 0x519A90);
	WriteVTablePtr(ita_cup_vtable, VTable17, 0x519690);
	WriteVTablePtr(ita_cup_vtable, VTableTableFates, 0x519890);
	WriteVTablePtr(ita_cup_vtable, VTableStageNews, 0x48C6D0);
	WriteVTablePtr(ita_cup_vtable, VTable22, 0x5221F0);
	WriteVTablePtr(ita_cup_vtable, VTable24, 0x5223A0);
	WriteVTablePtr(ita_cup_vtable, VTable27, 0x48E380);
	WriteVTablePtr(ita_cup_vtable, VTable33, 0x522910);
	WriteVTablePtr(ita_cup_vtable, VTable34, 0x522C50);
	WriteVTablePtr(ita_cup_vtable, VTableSubsRounds, 0x4C15F0);
	WriteVTablePtr(ita_cup_vtable, VTable37, 0x522360);
	WriteVTablePtr(ita_cup_vtable, VTable38, 0x518790);
	WriteVTablePtr(ita_cup_vtable, VTable39, 0x51C020);
	WriteVTablePtr(ita_cup_vtable, VTable40, 0x51F2F0);
}
