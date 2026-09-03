#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* irl_cup_vtable = (DWORD*)0x96BC2C;

int irl_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 44;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	// Lower
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(IRL_MUNSTER_LEAGUE_9CF());
	vector<cm3_clubs*> lower_clubs2 = find_clubs_of_comp(IRL_LEINSTER_LEAGUE_9CF());
	move(lower_clubs2.begin(), lower_clubs2.end(), back_inserter(lower_clubs));
	lower_clubs2 = find_clubs_of_comp(IRL_ULSTER_LEAGUE_9CF());
	move(lower_clubs2.begin(), lower_clubs2.end(), back_inserter(lower_clubs));
	lower_clubs2 = find_clubs_of_comp(IRL_CONNACHT_LEAGUE_9CF());
	move(lower_clubs2.begin(), lower_clubs2.end(), back_inserter(lower_clubs));
	lower_clubs2 = find_clubs_of_comp(A_LOWER_9CF(), NATION_IRELAND_9CF());
	move(lower_clubs2.begin(), lower_clubs2.end(), back_inserter(lower_clubs));
	vector<cm3_clubs*> division_clubs = get_random_weighted_clubs(lower_clubs, 9, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// National
	lower_clubs = find_clubs_of_comp(IRL_NATIONAL_LEAGUE_9CF());
	for (cm3_clubs* club : lower_clubs)
	{
		vec.push_back(club);
	}
	// First
	lower_clubs = find_clubs_of_comp(IRL_FIRST_9CF());
	for (cm3_clubs* club : lower_clubs)
	{
		vec.push_back(club);
	}
	// Premier
	lower_clubs = find_clubs_of_comp(IRL_PREMIER_9CF());
	for (cm3_clubs* club : lower_clubs)
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

extern "C" _declspec(naked) void irl_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call irl_cup_teams
		add esp, 0x4
		ret
	}
}

DWORD irl_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 8), year, Tuesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, Penalties, NoTiebreak, 4, 24, 12, 24, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("irl_cup_r1_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 18), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 18), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, Penalties, NoTiebreak, 4, 32, 16, 20, 24, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("irl_cup_r2_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 19), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 15), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, Penalties, NoTiebreak, 4, 16, 8, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("irl_cup_r3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 12), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, Penalties, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("irl_cup_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 3), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("irl_cup_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("irl_cup_final_win"), prizeMoneyFile.GetInt("irl_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) irl_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call irl_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_irl_cup() {
	WriteVTablePtr(irl_cup_vtable, VTableFixtures, (DWORD)&irl_cup_fixture_caller);
	PatchFunction(0x6347d0, (DWORD)&irl_cup_teams_c);
}