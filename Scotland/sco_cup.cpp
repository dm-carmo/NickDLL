#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* sco_cup_vtable = (DWORD*)0x96F414;

int sco_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 76;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	// Highland+Lowland
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(SCO_HIGHLAND_9CF());
	vector<cm3_clubs*> division_clubs2 = find_clubs_of_comp(SCO_LOWLAND_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	for (size_t i = 0; i < division_clubs.size(); i++) {
		cm3_clubs* c = division_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club)
		{
			division_clubs.erase(division_clubs.begin() + i);
			i--;
		}
	}
	BYTE selected = get_country(NATION_SCOTLAND_9CF())->NationLeagueSelected;
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRepInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// League 2
	division_clubs = find_clubs_of_comp(SCO_LEAGUE_2_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// League 1
	division_clubs = find_clubs_of_comp(SCO_LEAGUE_1_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Championshio
	division_clubs = find_clubs_of_comp(SCO_CHAMP_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Premier
	division_clubs = find_clubs_of_comp(SCO_PREMIER_9CF());
	for (cm3_clubs* club : division_clubs)
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

extern "C" _declspec(naked) void sco_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call sco_cup_teams
		add esp, 0x4
		ret
	}
}

DWORD sco_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 8, 4, 8, 0, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r1_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 40, 20, 36, 8, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r2_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 40, 20, 20, 44, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r3_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 32, 16, 12, 64, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r4_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 18), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r5_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 20), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 23), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("sco_cup_final_win"), prizeMoneyFile.GetInt("sco_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) sco_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_sco_cup() {
	WriteVTablePtr(sco_cup_vtable, VTableFixtures, (DWORD)&sco_cup_fixture_caller);
	PatchFunction(0x7EDAF0, (DWORD)&sco_cup_teams_c);
}