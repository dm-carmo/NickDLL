#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* ger_cup_vtable = (DWORD*)0x96B044;

DWORD ger_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 64, 32, 64, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_r1_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_r2_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_r3_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 23), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("ger_cup_final_win"), prizeMoneyFile.GetInt("ger_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ger_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ger_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int ger_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 64;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	WORD current_teams = 0;

	// D1
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(GER_FIRST_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
		current_teams++;
	}
	// D2
	division_clubs = find_clubs_of_comp(GER_SECOND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
		current_teams++;
	}
	// D3
	division_clubs = find_clubs_of_comp(GER_THIRD_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) {
			vec.push_back(club);
			current_teams++;
		}
	}

	BYTE selected = get_country(NATION_GERMANY_9CF())->NationLeagueSelected;
	if ((selected & 4) != 0) {
		// D4
		division_clubs = find_clubs_of_comp(GER_REGIONAL_9CF());
		for (cm3_clubs* club : division_clubs)
		{
			if (club->ClubLastDivision && club->ClubLastDivision->ClubCompID == GER_REGIONAL_9CF() && club->ClubLastPosition < 3)
			{
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
				if (!ret_club || is_main_club) {
					vec.push_back(club);
					current_teams++;
				}
			}
		}
		// fill remaining spots
		division_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_GERMANY_9CF());
		sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
		int max_to_check = division_clubs.size() / 2;
		while (current_teams < 64)
		{
			int availableIdx = rand() % max_to_check;
			cm3_clubs* club = division_clubs[availableIdx];
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
			if (!ret_club || is_main_club) {
				vec.push_back(club);
				current_teams++;
			}
			division_clubs.erase(division_clubs.begin() + availableIdx);
			max_to_check = division_clubs.size() / 2;
		}
	}
	else {
		division_clubs = find_clubs_of_comp(GER_REGIONAL_9CF());
		sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
		int max_to_check = division_clubs.size() / 2;
		while (current_teams < 64)
		{
			int availableIdx = rand() % max_to_check;
			cm3_clubs* club = division_clubs[availableIdx];
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
			if (!ret_club || is_main_club) {
				vec.push_back(club);
				current_teams++;
			}
			division_clubs.erase(division_clubs.begin() + availableIdx);
			max_to_check = division_clubs.size() / 2;
		}
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

extern "C" _declspec(naked) void ger_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call ger_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_ger_cup()
{
	WriteVTablePtr(ger_cup_vtable, VTableFixtures, (DWORD)&ger_cup_fixture_caller);
	PatchFunction(0x5d9370, (DWORD)&ger_cup_teams_c);
}
