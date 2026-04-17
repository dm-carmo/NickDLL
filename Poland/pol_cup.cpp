#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* pol_cup_vtable = (DWORD*)0x96E2C0;

DWORD pol_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 20, 10, 20, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 7), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 24), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 56, 28, 46, 20, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("pol_cup_r1_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 4, 66, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("pol_cup_r2_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("pol_cup_r3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("pol_cup_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 1), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("pol_cup_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 2), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("pol_cup_final_win"), prizeMoneyFile.GetInt("pol_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) pol_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call pol_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int pol_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	vector<cm3_clubs*> vec_uefa;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 70;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	vector<cm3_clubs*> division_clubs = find_clubs_of_country(NATION_POLAND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		if (club->ClubEuroFlag != -1) vec_uefa.push_back(club);
	}
	sort(vec_uefa.begin(), vec_uefa.end(), compareClubLastDivPosInv);

	// Lower
	division_clubs = find_clubs_of_comp(POL_LOWER_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (unsigned int i = 0; i < 16; i++)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* lower_club = division_clubs[availableIdx];
		if (!vector_contains_club(vec_uefa, lower_club)) vec.push_back(lower_club);

		division_clubs.erase(division_clubs.begin() + availableIdx);
	}

	// II Liga
	division_clubs = find_clubs_of_comp(POL_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}
	// I Liga
	division_clubs = find_clubs_of_comp(POL_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}
	// Ekstraklasa
	division_clubs = find_clubs_of_comp(POL_FIRST_9CF());
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

extern "C" _declspec(naked) void pol_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call pol_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_pol_cup()
{
	WriteVTablePtr(pol_cup_vtable, VTableFixtures, (DWORD)&pol_cup_fixture_caller);
	PatchFunction(0x7c8550, (DWORD)&pol_cup_teams_c);
}
