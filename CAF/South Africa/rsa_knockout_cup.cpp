#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include "Helpers\9cf_constants.h"

vtable* rsa_knockout_cup_vtable = new vtable((BYTE*)0x96C8B8, 0xA0);

void rsa_knockout_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(rsa_knockout_cup_vtable->vtable_ptr);
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
	sub_518690(_this);
}

void rsa_knockout_cup_free(BYTE* _this, BYTE a2) {
	rsa_knockout_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) rsa_knockout_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call rsa_knockout_cup_free
		add esp, 0x8
		ret 4
	}
}

int rsa_knockout_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 16;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// D1
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(RSA_PREMIER_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

char rsa_knockout_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
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
	rsa_knockout_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) rsa_knockout_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rsa_knockout_cup_update
		add esp, 0x4
		ret
	}
}

DWORD rsa_knockout_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 1), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, ExtraTime | Penalties, NoTiebreak, 4, 16, 8, 16, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("rsa_knockout_cup_r16_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTime | Penalties, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("rsa_knockout_cup_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTime | Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("rsa_knockout_cup_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 10), year, Wednesday, Evening, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTime | Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("rsa_knockout_cup_final_win"), prizeMoneyFile.GetInt("rsa_knockout_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) rsa_knockout_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call rsa_knockout_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void rsa_knockout_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(rsa_knockout_cup_vtable->vtable_ptr);
	rsa_knockout_cup_vtable->SetPointer(VTableInitFree, (DWORD)&rsa_knockout_cup_free_c);
	rsa_knockout_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&rsa_knockout_cup_update_c);
	rsa_knockout_cup_vtable->SetPointer(VTableFixtures, (DWORD)&rsa_knockout_cup_fixture_caller);
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesSouthAfrica;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	rsa_knockout_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

void setup_rsa_knockout_cup() {

}