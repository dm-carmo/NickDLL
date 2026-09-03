#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* jpn_cup_vtable = (DWORD*)0x96C9A0;

DWORD jpn_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 7;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 6), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 19), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 54, 27, 54, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("jpn_cup_r1_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 20), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 26), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 60, 30, 33, 54, 0, 1, 0, 0, prizeMoneyFile.GetInt("jpn_cup_r2_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 27), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 23), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 30, 15, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("jpn_cup_r3_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 24), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 9), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 16, 8, 1, 87, 0, 1, 0, 0, prizeMoneyFile.GetInt("jpn_cup_r4_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 10), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 23), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, Penalties | ExtraTime, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("jpn_cup_qtr_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 24), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 27), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, Penalties | ExtraTime, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("jpn_cup_semi_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 28), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 1), year, Friday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("jpn_cup_final_win"), prizeMoneyFile.GetInt("jpn_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) jpn_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int jpn_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 88;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// Regionals
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(JPN_REGIONAL_9CF());
	vector<cm3_clubs*> division_clubs = get_random_weighted_clubs(lower_clubs, 12, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
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
		teams[i].seeding = 0;
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
