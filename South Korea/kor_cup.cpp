#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* kor_cup_vtable = (DWORD*)0x96CD30;

DWORD kor_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 2, 5), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 3, 23), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 32, 0, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_r2_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 3, 24), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 16), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 24, 12, 8, 32, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_r3_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 17), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 14), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 4, 40, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_r4_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 2), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 3), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 20), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 0, 0, 0, 2, 7, prizeMoneyFile.GetInt("kor_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 28), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("kor_cup_final_win"), prizeMoneyFile.GetInt("kor_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) kor_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call kor_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int kor_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 44;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// Lower
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SOUTH_KOREA_9CF());
	vector<cm3_clubs*> division_clubs2 = find_clubs_of_comp(A_LOWER_B_9CF(), NATION_SOUTH_KOREA_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	vector<cm3_clubs*> lower_clubs;
	std::copy_if(division_clubs.begin(), division_clubs.end(), std::back_inserter(lower_clubs),
		[](cm3_clubs* c) {
			string s = string(c->ClubNameShort);
			return s.size() < 5 || s.substr(s.size() - 4) != " (R)";
		});
	for (int i = 0; i < 15; i++)
	{
		int availableIdx = rand() % lower_clubs.size();
		cm3_clubs* lower_club = lower_clubs[availableIdx];
		vec.push_back(lower_club);

		lower_clubs.erase(lower_clubs.begin() + availableIdx);
	}
	// D2
	division_clubs = find_clubs_of_comp(KOR_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// D1
	division_clubs = find_clubs_of_comp(KOR_FIRST_9CF());
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

extern "C" _declspec(naked) void kor_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call kor_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_kor_cup()
{
	WriteVTablePtr(kor_cup_vtable, VTableFixtures, (DWORD)&kor_cup_fixture_caller);
	PatchFunction(0x66aaf0, (DWORD)&kor_cup_teams_c);
}
