#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* fra_cup_vtable = (DWORD*)0x96A864;

DWORD fra_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 14), year, Friday);
		FillFixtureDetails(pMem, fixture_id++, SeventhRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 184, 92, 184, 0, 0, 1, 0, 5191);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 28), year, Friday);
		FillFixtureDetails(pMem, fixture_id++, EighthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 92, 46, 0, 0, 0, 1, 0, 10381);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 20), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, NinthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 64, 32, 18, 184, 0, 1, 0, 21628);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 21), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, TenthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 0, 0, 0, 1, 0, 34604);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 11), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, EleventhRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 43255);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 73534);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 147067);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 23), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 735335, 389295);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) fra_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fra_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int fra_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 202;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// Lower
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(FRA_NATIONAL_2_9CF());
	vector<cm3_clubs*> division_clubs2 = find_clubs_of_comp(FRA_LOWER_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	division_clubs2 = find_clubs_of_comp(A_LOWER_9CF(), NATION_FRANCE_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);

	vector<cm3_clubs*> lower_clubs;
	std::copy_if(division_clubs.begin(), division_clubs.end(), std::back_inserter(lower_clubs),
		[](cm3_clubs* c) {
			string s = string(c->ClubName);
			return s.size() < 3 || s.substr(s.size() - 2) != " B";
		});
	for (int i = 0; i < 148 + (comp_data->year == 2025 ? 1 : 0); i++)
	{
		int availableIdx = rand() % lower_clubs.size();
		cm3_clubs* lower_club = lower_clubs[availableIdx];
		vec.push_back(lower_club);

		lower_clubs.erase(lower_clubs.begin() + availableIdx);
	}
	// National
	division_clubs = find_clubs_of_comp(FRA_NATIONAL_1_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Ligue 2
	division_clubs = find_clubs_of_comp(FRA_SECOND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Ligue 1
	division_clubs = find_clubs_of_comp(FRA_FIRST_9CF());
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

extern "C" _declspec(naked) void fra_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call fra_cup_teams
		add esp, 0x4
		ret
	}
}

void setup_fra_cup()
{
	WriteVTablePtr(fra_cup_vtable, VTableFixtures, (DWORD)&fra_cup_fixture_caller);
	PatchFunction(0x5baa50, (DWORD)&fra_cup_teams_c);
}
