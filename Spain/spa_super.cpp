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

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 7), year, Wednesday, Evening, AhAhliKSAStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++, 1, Thursday, Evening, AhAhliKSAStadium);
		AddPlayoffTVFixture(pMem, fixture_id, tv_id++);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 + PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 4, 2, 4, 0, 0, 1, 0, 1729600, 864800, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 9), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 11), year, Sunday, Afternoon, AhAhliKSAStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 1729600, 0);

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
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;;
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
		if (!vector_contains_club(vec, c)) vec.push_back(c);
		if (vec.size() >= 4) break;
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void __declspec(naked) spa_super_teams_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_super_teams
		add esp, 0x4
		ret
	}
}

void setup_spa_super()
{
	WriteVTablePtr(spa_super_vtable, VTableFixtures, (DWORD)&spa_super_fixture_caller);
	PatchFunction(0x858AA0, (DWORD)&spa_super_teams_c);
}
