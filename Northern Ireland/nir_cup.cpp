#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* nir_cup_vtable = (DWORD*)0x96DAC4;

int nir_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 40;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	// Lower
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_NORTHERN_IRELAND_9CF());
	vector<cm3_clubs*> division_clubs = get_random_weighted_clubs(lower_clubs, 2, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// NIFL Intermediate
	division_clubs = find_clubs_of_comp(NIR_SECOND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// NIFL Championship
	division_clubs = find_clubs_of_comp(NIR_FIRST_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// NIFL Premier
	division_clubs = find_clubs_of_comp(NIR_PREMIER_9CF());
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

extern "C" _declspec(naked) void nir_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call nir_cup_teams
		add esp, 0x4
		ret
	}
}

DWORD nir_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 16, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 24, 16, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 11), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SixthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("nir_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday, Afternoon, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("nir_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("nir_cup_final_win"), prizeMoneyFile.GetInt("nir_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) nir_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call nir_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_nir_cup() {
	WriteVTablePtr(nir_cup_vtable, VTableFixtures, (DWORD)&nir_cup_fixture_caller);
	PatchFunction(0x78ac90, (DWORD)&nir_cup_teams_c);
}