#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* cro_cup_vtable = (DWORD*)0x9692E0;

DWORD cro_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 3), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 27), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 32, 0, 0, 1, 0, 1298);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 28), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 10), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 16, 32, 0, 1, 0, 1730);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 2163);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 2595);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 8), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 5191);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 9), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 13), year, Wednesday, Evening, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1,0, 0, 17303, 8652);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) cro_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call cro_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int cro_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 48;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// Lower
	vector<cm3_clubs*> club_list = find_clubs_of_comp(CRO_FOURTH_9CF());
	sort(club_list.begin(), club_list.end(), compareClubRep);
	int max_to_check = (club_list.size() > 15 ? 15 : club_list.size());
	for (int i = 0; i < 10; i++) {
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* selected = club_list[availableIdx];
		vec.push_back(selected);
		club_list.erase(club_list.begin() + availableIdx);
	}
	// 2. NL
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(CRO_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// 1. NL
	division_clubs = find_clubs_of_comp(CRO_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// HNL
	division_clubs = find_clubs_of_comp(CRO_FIRST_9CF());
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

extern "C" _declspec(naked) void cro_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call cro_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_cro_cup()
{
	WriteVTablePtr(cro_cup_vtable, VTableFixtures, (DWORD)&cro_cup_fixture_caller);
	PatchFunction(0x517bb0, (DWORD)&cro_cup_teams_c);
}
