#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers/9cf_constants.h>

DWORD* gre_super_vtable = (DWORD*)0x96B6D0;

DWORD gre_super_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 13), year, Wednesday, Evening, LargestStadium6);
		FillFixtureDetails(pMem, fixture_id++, None, 8, Penalties, NoTiebreak, 6, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) gre_super_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gre_super_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int gre_super_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 2;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	cm3_club_comps* league = get_comp(GRE_FIRST_9CF());
	cm3_club_comps* cup = get_comp(GRE_CUP_9CF());
	cm3_clubs* league_champ = get_last_comp_winner(league);
	if (league_champ) vec.push_back(league_champ);
	else {
		cm3_clubs* league_second = get_last_comp_runner_up(league);
		if (league_second) vec.push_back(league_second);
	}
	cm3_clubs* cup_champ = get_last_comp_winner(cup);
	if (cup_champ && !vector_contains_element(vec, cup_champ)) vec.push_back(cup_champ);
	else {
		cm3_clubs* cup_second = get_last_comp_runner_up(cup);
		if (cup_second && !vector_contains_element(vec, cup_second)) vec.push_back(cup_second);
	}

	for (BYTE i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = i;
		teams[i].f6 = 0;
	}

	return 1;
}

char gre_super_update(BYTE* _this) {
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
	gre_super_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
}

void __declspec(naked) gre_super_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gre_super_update
		add esp, 0x4
		ret
	}
}

void gre_super_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = gre_super_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesGreece;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	gre_super_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
}

void setup_gre_super()
{
	WriteVTablePtr(gre_super_vtable, VTableFixtures, (DWORD)&gre_super_fixture_caller);
	WriteVTablePtr(gre_super_vtable, VTableEoSUpdate, (DWORD)&gre_super_update_c);
	WriteVTablePtr(gre_super_vtable, VTableSubsRounds, 0x858e70);
}
