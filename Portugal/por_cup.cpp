#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* por_cup_vtable = (DWORD*)0x96E650;

DWORD CreatePortugalCupFixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 92, 46, 92, 0, 0, 1, 0, 1800, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 1), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 21), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 92, 46, 46, 92, 0, 1, 0, 2250, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 22), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 64, 32, 18, 138, 0, 1, 0, 2700, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 20), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 0, 0, 0, 1, 0, 3600, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 24), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 17), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 5400, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 18), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 14), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 7200, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 0, 0, 0, 2, 77, 10125, 0, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 24), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 146250, 78750);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) por_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call CreatePortugalCupFixtures
		add esp, 0x14
		ret 0x10
	}
}

int por_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 156;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	WORD main_teams = CountNumberOfTeamsInComp(POR_FIRST_9CF()) + CountNumberOfTeamsInCompNoReserve(POR_SECOND_9CF()) +
		CountNumberOfTeamsInCompNoReserve(POR_THIRD_9CF()) + CountNumberOfTeamsInCompNoReserve(POR_FOURTH_9CF());
	WORD lower_teams = total_teams - main_teams;

	// Lower
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_PORTUGAL_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (unsigned int i = 0; i < lower_teams; i++)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* lower_club = division_clubs[availableIdx];

		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)lower_club, &is_main_club, 1);
		if (ret_club && !is_main_club)
			i--;
		else
			vec.push_back(lower_club);

		division_clubs.erase(division_clubs.begin() + availableIdx);
	}
	// Campeonato de Portugal
	BYTE selected = find_country("Portugal")->NationLeagueSelected;
	division_clubs = find_clubs_of_comp(POR_FOURTH_9CF());
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// Liga 3
	division_clubs = find_clubs_of_comp(POR_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// Liga 2
	division_clubs = find_clubs_of_comp(POR_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// Liga 1
	division_clubs = find_clubs_of_comp(POR_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	shuffle(vec.begin(), vec.begin() + 120, rng);

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

extern "C" _declspec(naked) void por_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call por_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_por_cup()
{
	WriteVTablePtr(por_cup_vtable, VTableFixtures, (DWORD)&por_cup_fixture_caller);
	PatchFunction(0x7ce220, (DWORD)&por_cup_teams_c);
}
