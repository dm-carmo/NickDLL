#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* jpn_cup_vtable = (DWORD*)0x96C9A0;

DWORD CreateEmperorCupFixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 25), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 54, 27, 54, 0, 0, 1, 0, 1125, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 26), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 11), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 60, 30, 33, 54, 0, 1, 0, 2250, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 12), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 16), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 30, 15, 0, 0, 0, 1, 0, 2250, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 1, 87, 0, 1, 0, 4500, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 7), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 27), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 6750, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 28), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 45000, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 17), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 337500, 112500);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) jpn_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call CreateEmperorCupFixtures
		add esp, 0x14
		ret 0x10
	}
}

int jpn_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 88;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// Regionals
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(JPN_REGIONAL_9CF());
	for (int i = 0; i < 12; i++)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* lower_club = division_clubs[availableIdx];
		vec.push_back(lower_club);

		division_clubs.erase(division_clubs.begin() + availableIdx);
	}

	// JFL
	division_clubs = find_clubs_of_comp(JPN_JFL_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// D3
	division_clubs = find_clubs_of_comp(JPN_THIRD_9CF());
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

extern "C" _declspec(naked) void jpn_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call jpn_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_jpn_cup()
{
	WriteVTablePtr(jpn_cup_vtable, VTableFixtures, (DWORD)&jpn_cup_fixture_caller);
	PatchFunction(0x6624f0, (DWORD)&jpn_cup_teams_c);
}
