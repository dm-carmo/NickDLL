#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

DWORD* ita_super_vtable = (DWORD*)0x96C8B8;

DWORD ita_super_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 22), year, Saturday, Afternoon, AhAhliKSAStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 2, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("ita_super_final_win"), prizeMoneyFile.GetInt("ita_super_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ita_super_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_super_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int ita_super_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 2;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	cm3_club_comps* league = get_comp(ITA_SERIE_A_9CF());
	cm3_club_comps* cup = get_comp(ITA_CUP_9CF());
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

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void __declspec(naked) ita_super_teams_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_super_teams
		add esp, 0x4
		ret
	}
}

void setup_ita_super()
{
	WriteVTablePtr(ita_super_vtable, VTableFixtures, (DWORD)&ita_super_fixture_caller);
	PatchFunction(0x65fa60, (DWORD)&ita_super_teams_c);
}
