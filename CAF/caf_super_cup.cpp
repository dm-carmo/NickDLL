#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* caf_super_cup_vtable = (DWORD*)0x9676C8;

DWORD caf_super_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, None, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 2, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("caf_super_final_win"), prizeMoneyFile.GetInt("caf_super_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) caf_super_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call caf_super_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int caf_super_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 2;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	cm3_club_comps* caf_cl = get_comp(CAF_CHAMPIONS_LEAGUE_9CF());
	cm3_club_comps* caf_conf = get_comp(CAF_CONFEDERATION_CUP_9CF());
	cm3_clubs* caf_cl_champ = get_last_comp_winner(caf_cl);
	if (caf_cl_champ) vec.push_back(caf_cl_champ);
	cm3_clubs* caf_conf_champ = get_last_comp_winner(caf_conf);
	if (caf_conf_champ && !vector_contains_club(vec, caf_conf_champ)) vec.push_back(caf_conf_champ);
	else {
		cm3_clubs* caf_conf_second = get_last_comp_runner_up(caf_conf);
		if (caf_conf_second && !vector_contains_club(vec, caf_conf_second)) vec.push_back(caf_conf_second);
		else {
			cm3_clubs* caf_cl_second = get_last_comp_runner_up(caf_cl);
			if (caf_cl_second) vec.push_back(caf_cl_second);
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

void __declspec(naked) caf_super_cup_teams_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call caf_super_cup_teams
		add esp, 0x4
		ret
	}
}

char caf_super_cup_update(BYTE* _this) {
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
	caf_super_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
}

void __declspec(naked) caf_super_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call caf_super_cup_update
		add esp, 0x4
		ret
	}
}

void setup_caf_super_cup()
{
	WriteVTablePtr(caf_super_cup_vtable, VTableFixtures, (DWORD)&caf_super_cup_fixture_caller);
	WriteVTablePtr(caf_super_cup_vtable, VTableEoSUpdate, (DWORD)&caf_super_cup_update_c);
	PatchFunction(0x410a50, (DWORD)&caf_super_cup_teams_c);
}
