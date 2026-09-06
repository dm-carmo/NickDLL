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
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 64, 32, 64, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_r1_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 32, 16, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_r2_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 16, 8, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_r3_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, Penalties | ExtraTime, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, Penalties | ExtraTime, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("ger_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 30), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("ger_cup_final_win"), prizeMoneyFile.GetInt("ger_cup_final_lose"));

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
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void ger_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = ger_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->rules = RulesGermanyCup;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	ger_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->max_bench = 9;
	data->max_subs = 5;
	cup_reputation_setup_generic_5223A0(_this);
}

void __declspec(naked) ger_cup_init_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ger_cup_init
		add esp, 0xc
		ret 8
	}
}

char ger_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
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
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	ger_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) ger_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ger_cup_update
		add esp, 0x4
		ret
	}
}

void setup_ger_cup()
{
	WriteVTablePtr(ger_cup_vtable, VTableFixtures, (DWORD)&ger_cup_fixture_caller);
	WriteVTablePtr(ger_cup_vtable, VTableEoSUpdate, (DWORD)&ger_cup_update_c);
	WriteVTablePtr(ger_cup_vtable, VTableSubsRounds, 0x858e70);
}
