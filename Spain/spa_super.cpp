#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

DWORD* spa_super_vtable = (DWORD*)0x96FD38;

DWORD spa_super_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 3), year, Wednesday, Evening, AhAhliKSAStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Tuesday, Evening, AhAhliKSAStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 4, FixedTeamOrderInCup2 | Penalties, NoTiebreak, 6, 4, 2, 4, 0, 0, 1, 0, prizeMoneyFile.GetInt("spa_super_semi_qualify"), prizeMoneyFile.GetInt("spa_super_semi_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Sunday, Afternoon, AhAhliKSAStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("spa_super_final_win"), 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) spa_super_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call spa_super_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int spa_super_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	vector<cm3_clubs*> d1_clubs = find_clubs_of_comp_last_division(SPA_FIRST_9CF());
	sort(d1_clubs.begin(), d1_clubs.end(), compareClubLastDivPos);

	cm3_club_comps* spa_cup = get_comp(SPA_CUP_9CF());
	cm3_clubs* winner = get_last_comp_winner(spa_cup);
	if (winner) vec.push_back(winner);
	cm3_clubs* runner_up = get_last_comp_runner_up(spa_cup);
	if (runner_up) vec.push_back(runner_up);

	for (cm3_clubs* c : d1_clubs) {
		if (!vector_contains_element(vec, c)) vec.push_back(c);
		if (vec.size() >= 4) break;
	}

	for (BYTE i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = i % 2;
		teams[i].f6 = 0;
	}

	return 1;
}

char spa_super_update(BYTE* _this) {
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
	spa_super_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
}

void __declspec(naked) spa_super_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_super_update
		add esp, 0x4
		ret
	}
}

void spa_super_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = spa_super_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesSpainCup;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	spa_super_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
}

void setup_spa_super()
{
	WriteVTablePtr(spa_super_vtable, VTableFixtures, (DWORD)&spa_super_fixture_caller);
	WriteVTablePtr(spa_super_vtable, VTableEoSUpdate, (DWORD)&spa_super_update_c);
	WriteVTablePtr(spa_super_vtable, VTableSubsRounds, 0x858e70);
}
