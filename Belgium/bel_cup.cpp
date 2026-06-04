#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* bel_cup_vtable = (DWORD*)0x9678A0;

DWORD bel_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 9;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 106, 53, 106, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 10), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 76, 38, 23, 106, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 38, 19, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 6), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SixthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 13, 129, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 7), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SeventhRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 16, 142, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, EighthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 14), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("bel_cup_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 0, 0, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("bel_cup_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 12), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 15), year, Thursday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("bel_cup_final_win"), prizeMoneyFile.GetInt("bel_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) bel_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call bel_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int bel_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 158;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	WORD main_teams = CountNumberOfTeamsInComp(BEL_FIRST_9CF()) + CountNumberOfTeamsInCompNoReserve(BEL_SECOND_9CF()) +
		CountNumberOfTeamsInCompNoReserve(BEL_THIRD_VV_9CF()) + CountNumberOfTeamsInCompNoReserve(BEL_THIRD_ACFF_9CF()) +
			CountNumberOfTeamsInCompNoReserve(BEL_FOURTH_VV_9CF()) + CountNumberOfTeamsInCompNoReserve(BEL_FOURTH_ACFF_9CF());
	WORD lower_teams = total_teams - main_teams;

	// Lower
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_BELGIUM_9CF());
	for (size_t i = 0; i < lower_clubs.size(); i++) {
		cm3_clubs* c = lower_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club)
		{
			lower_clubs.erase(lower_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> division_clubs = get_random_weighted_clubs(lower_clubs, lower_teams, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Division 2
	BYTE selected = get_country(NATION_BELGIUM_9CF())->NationLeagueSelected;
	division_clubs = find_clubs_of_comp(BEL_FOURTH_VV_9CF());
	vector<cm3_clubs*> division_clubs2 = find_clubs_of_comp(BEL_FOURTH_ACFF_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// Division 1
	division_clubs = find_clubs_of_comp(BEL_THIRD_VV_9CF());
	division_clubs2 = find_clubs_of_comp(BEL_THIRD_ACFF_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// Challenger League
	division_clubs = find_clubs_of_comp(BEL_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// Pro League
	division_clubs = find_clubs_of_comp(BEL_FIRST_9CF());
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

extern "C" _declspec(naked) void bel_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call bel_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_bel_cup()
{
	WriteVTablePtr(bel_cup_vtable, VTableFixtures, (DWORD)&bel_cup_fixture_caller);
	PatchFunction(0x41d8d0, (DWORD)&bel_cup_teams_c);
}
