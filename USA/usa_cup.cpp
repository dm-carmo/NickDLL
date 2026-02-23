#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* usa_cup_vtable = (DWORD*)0x970998;

DWORD usa_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 1), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 32, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 2), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 16), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 16, 32, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 17), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 7), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 16, 48, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 8), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 21), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 22), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 9), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 10), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 17), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 18), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 1), year, Wednesday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 135000, 45000);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) usa_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call usa_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int usa_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 64;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	cm3_clubs* d2_winner = get_last_comp_winner(get_comp(USA_SECOND_9CF()));
	cm3_clubs* d2_second = get_last_comp_runner_up(get_comp(USA_SECOND_9CF()));

	cm3_clubs* d1_winner = get_last_comp_winner(get_comp(USA_MLS_9CF()));
	cm3_clubs* d1_second = get_last_comp_runner_up(get_comp(USA_MLS_9CF()));

	// D3
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(USA_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (int i = 0; i < 10; i++)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* lower_club = division_clubs[availableIdx];
		vec.push_back(lower_club);

		division_clubs.erase(division_clubs.begin() + availableIdx);
	}
	// D2
	division_clubs = find_clubs_of_comp(USA_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (club != d2_winner && club != d2_second) vec.push_back(club);
	}
	if (d2_second) vec.push_back(d2_second);
	if (d2_winner) vec.push_back(d2_winner);
	// D1
	division_clubs = find_clubs_of_comp(USA_MLS_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (club != d1_winner && club != d1_second) vec.push_back(club);
	}
	if (d1_second) vec.push_back(d1_second);
	if (d1_winner) vec.push_back(d1_winner);

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

extern "C" _declspec(naked) void usa_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call usa_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_usa_cup()
{
	WriteVTablePtr(usa_cup_vtable, VTableFixtures, (DWORD)&usa_cup_fixture_caller);
	PatchFunction(0x90b530, (DWORD)&usa_cup_teams_c);
}
