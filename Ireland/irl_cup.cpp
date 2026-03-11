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
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	// Lower
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(IRL_MUNSTER_LEAGUE_9CF());
	vector<cm3_clubs*> division_clubs2 = find_clubs_of_comp(IRL_LEINSTER_LEAGUE_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	division_clubs2 = find_clubs_of_comp(IRL_ULSTER_LEAGUE_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	division_clubs2 = find_clubs_of_comp(IRL_CONNACHT_LEAGUE_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	division_clubs2 = find_clubs_of_comp(A_LOWER_9CF(), NATION_IRELAND_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (int i = 0; i < 24; i++)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* lower_club = division_clubs[availableIdx];

		vec.push_back(lower_club);

		division_clubs.erase(division_clubs.begin() + availableIdx);
	}
	// First
	division_clubs = find_clubs_of_comp(IRL_FIRST_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Premier
	division_clubs = find_clubs_of_comp(IRL_PREMIER_9CF());
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

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 8), year, Tuesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 24, 12, 24, 0, 0, 1, 0, 0, 0, 432);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 18), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 18), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 32, 16, 20, 24, 0, 1, 0, 0, 0, 864);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 19), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 15), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 0, 0, 1727);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 12), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 0, 0, 3455);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 3), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 0, 0, 6910);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 27638, 13819);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) irl_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
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