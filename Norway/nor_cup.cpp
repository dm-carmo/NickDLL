#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* nor_cup_vtable = (DWORD*)0x96DD80;

DWORD nor_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 2), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 13), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 64, 32, 64, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 14), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 27), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 28), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 24), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 16, 64, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 1, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 18), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 19), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) nor_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call nor_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int nor_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 80;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	int main_teams_count = 0;
	int d2_count = 0;
	// 2. divisjon
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(NOR_SECOND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) {
			vec.push_back(club);
			main_teams_count++;
		}
	}

	division_clubs = find_clubs_of_comp(NOR_THIRD_9CF());
	BYTE selected = get_country(NATION_NORWAY_9CF())->NationLeagueSelected;
	if ((selected & 4) != 0) {
		// 3. divisjon
		for (cm3_clubs* club : division_clubs)
		{
			if (club->ClubLastDivision && club->ClubLastDivision->ClubCompID == NOR_THIRD_9CF() &&
				club->ClubLastPosition > 0 && club->ClubLastPosition < 7 && d2_count < 18) {
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
				if (!ret_club || is_main_club) {
					vec.push_back(club);
					main_teams_count++;
				}
				d2_count++;
			}
		}
		// extra lower
		division_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_NORWAY_9CF());
		sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
		while (main_teams_count < 48)
		{
			int availableIdx = rand() % division_clubs.size();
			cm3_clubs* lower_club = division_clubs[availableIdx];
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)lower_club, &is_main_club, 1);
			if (!ret_club || is_main_club) {
				vec.push_back(lower_club);
				main_teams_count++;
			}
			division_clubs.erase(division_clubs.begin() + availableIdx);
		}
	}
	else {
		sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
		int max_to_check = division_clubs.size() / 2;
		while (main_teams_count < 48)
		{
			int availableIdx = rand() % max_to_check;
			cm3_clubs* club = division_clubs[availableIdx];
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
			if (!ret_club || is_main_club) {
				vec.push_back(club);
				main_teams_count++;
			}
			division_clubs.erase(division_clubs.begin() + availableIdx);
			max_to_check = division_clubs.size() / 2;
		}
	}
	// 1. divisjon
	division_clubs = find_clubs_of_comp(NOR_FIRST_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Eliteserien
	division_clubs = find_clubs_of_comp(NOR_PREMIER_9CF());
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

extern "C" _declspec(naked) void nor_cup_teams_c()
{
	_asm
	{
		mov eax, esp
		push ecx
		call nor_cup_teams
		add esp, 0x4
		ret
	}
}

char nor_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
	if (data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
		data->rounds_list = 0;
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
				data->f173[i] = 0;
			}
		}
		sub_9452CA_free(data->f173);
		data->f173 = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
		}
	}
	data->year++;
	data->current_stage = -1;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	nor_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) nor_cup_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_cup_update
		add esp, 0x4
		ret
	}
}

void nor_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = nor_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = 0x16;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	nor_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_5223A0(_this);
}

void setup_nor_cup()
{
	WriteVTablePtr(nor_cup_vtable, VTableFixtures, (DWORD)&nor_cup_fixture_caller);
	//WriteVTablePtr(nor_cup_vtable, VTableEoSUpdate, (DWORD)&nor_cup_update_c);
	PatchFunction(0x78f890, (DWORD)&nor_cup_teams_c);
	WriteVTablePtr(nor_cup_vtable, VTableStageNews, 0x48C6D0);
	WriteVTablePtr(nor_cup_vtable, VTableSubsRounds, 0x4C15F0);
	WriteVTablePtr(nor_cup_vtable, VTableLeagueSplit, 0x88d8a0); // same as Swedish Cup
}
