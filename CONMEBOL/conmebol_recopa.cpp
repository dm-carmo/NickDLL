#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* conmebol_recopa_vtable = (DWORD*)0x96BAD8;

DWORD conmebol_recopa_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 10), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 20), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, None, 8, NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 6, 2, 1, 2, 0, 0, 2, 7, 0, prizeMoneyFile.GetInt("conmebol_recopa_final_win"), prizeMoneyFile.GetInt("conmebol_recopa_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

int conmebol_recopa_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 2;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	cm3_club_comps* comp1 = get_comp(COPA_SUDAMERICANA_9CF());
	cm3_club_comps* comp2 = get_comp(COPA_LIBERTADORES_9CF());
	cm3_clubs* comp1_champ = get_last_comp_winner(comp1);
	if (comp1_champ) vec.push_back(comp1_champ);
	else {
		cm3_clubs* comp1_second = get_last_comp_runner_up(comp1);
		if (comp1_second) vec.push_back(comp1_second);
	}
	cm3_clubs* comp2_champ = get_last_comp_winner(comp2);
	if (comp2_champ && !vector_contains_element(vec, comp2_champ)) vec.push_back(comp2_champ);
	else {
		cm3_clubs* comp2_second = get_last_comp_runner_up(comp2);
		if (comp2_second && !vector_contains_element(vec, comp2_second)) vec.push_back(comp2_second);
	}

	for (BYTE i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = 1 - i;
		teams[i].f6 = 0;
	}

	return 1;
}

void __declspec(naked) conmebol_recopa_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call conmebol_recopa_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char conmebol_recopa_update(BYTE* _this) {
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
	conmebol_recopa_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
}

void __declspec(naked) conmebol_recopa_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_recopa_update
		add esp, 0x4
		ret
	}
}

void conmebol_recopa_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = conmebol_recopa_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesSouthAmerica;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	conmebol_recopa_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
}

void setup_conmebol_recopa()
{
	WriteVTablePtr(conmebol_recopa_vtable, VTableFixtures, (DWORD)&conmebol_recopa_fixture_caller);
	WriteVTablePtr(conmebol_recopa_vtable, VTableEoSUpdate, (DWORD)&conmebol_recopa_update_c);
}
