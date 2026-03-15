#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* jpn_league_cup_vtable = (DWORD*)0x96CBA8;

DWORD jpn_league_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 7;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 2, 5), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 3, 20), year, Thursday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 54, 27, 54, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 3, 21), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 9), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 28, 14, 1, 54, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 10), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 21), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 14, 7, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 22), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 1, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 4, 8, 4, 1, 55, 0, 2, 4);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 9), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 8, 4, 4, 56, 0, 2, 4);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 8), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 8), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 0, 0, 0, 2, 4, 0, 0, 94199);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 13), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 706490, 235497);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) jpn_league_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_league_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int jpn_league_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 60;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// D3
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(JPN_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// D2
	division_clubs = find_clubs_of_comp(JPN_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// D1
	division_clubs = find_clubs_of_comp(JPN_FIRST_9CF());
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

extern "C" _declspec(naked) void jpn_league_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call jpn_league_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_jpn_league_cup()
{
	WriteVTablePtr(jpn_league_cup_vtable, VTableFixtures, (DWORD)&jpn_league_cup_fixture_caller);
	PatchFunction(0x665a00, (DWORD)&jpn_league_cup_teams_c);
}
