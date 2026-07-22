#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* eng_fa_trophy_vtable = (DWORD*)0x969BC8;

int eng_fa_trophy_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 136;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_ENGLAND_9CF());
	vector<cm3_clubs*> lower_clubs2 = find_clubs_of_comp(A_LOWER_B_9CF(), NATION_ENGLAND_9CF());
	move(lower_clubs2.begin(), lower_clubs2.end(), back_inserter(lower_clubs));
	vector<cm3_clubs*> division_clubs = get_random_weighted_clubs(lower_clubs, 64, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// National League North
	division_clubs = find_clubs_of_comp(ENG_CONFERENCE_NORTH_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// National League South
	division_clubs = find_clubs_of_comp(ENG_CONFERENCE_SOUTH_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// National League
	division_clubs = find_clubs_of_comp(ENG_CONFERENCE_9CF());
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

void __declspec(naked) eng_fa_trophy_teams_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_fa_trophy_teams
		add esp, 0x4
		ret
	}
}

DWORD eng_fa_trophy_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 8;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 64, 32, 64, 0, 0, 1, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r1_qualify"), prizeMoneyFile.GetInt("eng_fa_trophy_r1_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r1_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 80, 40, 48, 64, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r2_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r2_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 64, 32, 24, 112, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r3_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 32, 16, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r4_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r4_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 11), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r5_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r5_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 1), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_qtr_win"), prizeMoneyFile.GetInt("eng_fa_trophy_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 1), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 28), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_semi_win"), prizeMoneyFile.GetInt("eng_fa_trophy_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 17), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_final_win"), prizeMoneyFile.GetInt("eng_fa_trophy_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) eng_fa_trophy_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_fa_trophy_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_eng_fa_trophy()
{
	WriteVTablePtr(eng_fa_trophy_vtable, VTableFixtures, (DWORD)&eng_fa_trophy_fixture_caller);
	WriteVTablePtr(eng_fa_trophy_vtable, VTableSubsRounds, 0x858e70);
	PatchFunction(0x5712b0, (DWORD)&eng_fa_trophy_teams_c);
}
