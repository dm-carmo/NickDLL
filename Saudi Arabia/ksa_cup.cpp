#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

vtable* ksa_cup_vtable = new vtable((BYTE*)0x96E650, 0xA0);

void ksa_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)ksa_cup_vtable->vtable_ptr;
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

void ksa_cup_free(BYTE* _this, BYTE a2) {
	ksa_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) ksa_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ksa_cup_free
		add esp, 0x8
		ret 4
	}
}

int ksa_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 32;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// D1
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(KSA_PREMIER_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// D2
	division_clubs = find_clubs_of_comp(KSA_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	for (cm3_clubs* club : division_clubs)
	{
		if (vec.size() >= total_teams) break;
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

char ksa_cup_update(BYTE* _this) {
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
	ksa_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) ksa_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ksa_cup_update
		add esp, 0x4
		ret
	}
}

DWORD ksa_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 5;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 24), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 32, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 18), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 19), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 8), year, Friday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("ksa_cup_final_win"), prizeMoneyFile.GetInt("ksa_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ksa_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ksa_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void ksa_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(ksa_cup_vtable->vtable_ptr);
	ksa_cup_vtable->SetPointer(VTableInitFree, (DWORD)&ksa_cup_free_c);
	ksa_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&ksa_cup_update_c);
	ksa_cup_vtable->SetPointer(VTableFixtures, (DWORD)&ksa_cup_fixture_caller);
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesSaudi;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	ksa_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

void setup_ksa_cup() {

}