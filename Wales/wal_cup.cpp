#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* wal_cup_vtable = (DWORD*)0x970EE0;

int wal_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 64;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	// Cymru South
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(WAL_FIRST_SOUTH_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Cymru North
	division_clubs = find_clubs_of_comp(WAL_FIRST_NORTH_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Cymru Premier
	division_clubs = find_clubs_of_comp(WAL_PREMIER_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	WORD curr_teams = (WORD)vec.size();
	// Lower
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_WALES_9CF());
	division_clubs = get_random_weighted_clubs(lower_clubs, total_teams - curr_teams, true);
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

extern "C" _declspec(naked) void wal_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call wal_cup_teams
		add esp, 0x4
		ret
	}
}

DWORD wal_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, Penalties, NoTiebreak, 4, 64, 32, 64, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("wal_cup_r2_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, Penalties, NoTiebreak, 4, 32, 16, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("wal_cup_r3_win"), prizeMoneyFile.GetInt("wal_cup_r3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, Penalties, NoTiebreak, 4, 16, 8, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("wal_cup_r4_win"), prizeMoneyFile.GetInt("wal_cup_r4_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, Penalties, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("wal_cup_qtr_win"), prizeMoneyFile.GetInt("wal_cup_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 1), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("wal_cup_semi_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("wal_cup_final_win"), 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) wal_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call wal_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_wal_cup() {
	WriteVTablePtr(wal_cup_vtable, VTableFixtures, (DWORD)&wal_cup_fixture_caller);
	PatchFunction(0x924ab0, (DWORD)&wal_cup_teams_c);
}