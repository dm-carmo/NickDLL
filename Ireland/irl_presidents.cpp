#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers/9cf_constants.h>

DWORD* irl_presidents_vtable = (DWORD*)0x96BF74;

DWORD irl_presidents_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 12), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 7), year, Friday, Evening, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, None, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) irl_presidents_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call irl_presidents_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int irl_presidents_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 2;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	cm3_club_comps* irl_d1 = get_comp(IRL_PREMIER_9CF());
	cm3_club_comps* irl_cup = get_comp(IRL_CHALLENGE_CUP_9CF());
	cm3_clubs* irl_d1_champ = get_last_comp_winner(irl_d1);
	if (irl_d1_champ) vec.push_back(irl_d1_champ);
	cm3_clubs* irl_cup_champ = get_last_comp_winner(irl_cup);
	if (irl_cup_champ && !vector_contains_element(vec, irl_cup_champ)) vec.push_back(irl_cup_champ);
	else {
		cm3_clubs* irl_d1_second = get_last_comp_runner_up(irl_d1);
		if (irl_d1_second && !vector_contains_element(vec, irl_d1_second)) vec.push_back(irl_d1_second);
		else {
			cm3_clubs* irl_cup_second = get_last_comp_runner_up(irl_cup);
			if (irl_cup_second) vec.push_back(irl_cup_second);
		}
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void __declspec(naked) irl_presidents_teams_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_presidents_teams
		add esp, 0x4
		ret
	}
}

void setup_irl_presidents()
{
	WriteVTablePtr(irl_presidents_vtable, VTableFixtures, (DWORD)&irl_presidents_fixture_caller);
	PatchFunction(0x639670, (DWORD)&irl_presidents_teams_c);
}
