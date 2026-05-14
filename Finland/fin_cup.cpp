#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* fin_cup_vtable = (DWORD*)0x96A360;

DWORD fin_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 15), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 112, 56, 112, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 16), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 6), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 56, 28, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 7), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 28), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 4, 112, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 11), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SixthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 12), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 24), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 25), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 21), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 22), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("fin_cup_final_win"), prizeMoneyFile.GetInt("fin_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) fin_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fin_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int fin_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	vector<cm3_clubs*> vec_uefa;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 116;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	vector<cm3_clubs*> division_clubs = find_clubs_of_country(NATION_FINLAND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		if (club->ClubEuroFlag != -1) vec_uefa.push_back(club);
	}
	sort(vec_uefa.begin(), vec_uefa.end(), compareClubLastDivPosInv);

	// Lower
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(FIN_LOWER_9CF(), NATION_FINLAND_9CF());
	for (size_t i = 0; i < lower_clubs.size(); i++) {
		cm3_clubs* c = lower_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (vector_contains_club(vec_uefa, c))
		{
			lower_clubs.erase(lower_clubs.begin() + i);
			i--;
		}
	}
	division_clubs = get_random_weighted_clubs(lower_clubs, 52, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Kakkonen
	division_clubs = find_clubs_of_comp(FIN_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}
	// Ykkönen
	division_clubs = find_clubs_of_comp(FIN_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}
	// Ykkösliiga
	division_clubs = find_clubs_of_comp(FIN_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}
	// Veikkausliiga
	division_clubs = find_clubs_of_comp(FIN_PREMIER_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}

	for (cm3_clubs* club : vec_uefa)
	{
		vec.push_back(club);
	}

	while (vec.size() > total_teams) {
		vec.erase(vec.begin());
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

extern "C" _declspec(naked) void fin_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call fin_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_fin_cup()
{
	WriteVTablePtr(fin_cup_vtable, VTableFixtures, (DWORD)&fin_cup_fixture_caller);
	PatchFunction(0x592a20, (DWORD)&fin_cup_teams_c);
}
