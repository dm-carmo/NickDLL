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
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

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
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
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

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, Penalties, NoTiebreak, 4, 64, 32, 64, 0, 0, 1, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r1_qualify"), prizeMoneyFile.GetInt("eng_fa_trophy_r1_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r1_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, Penalties, NoTiebreak, 4, 80, 40, 48, 64, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r2_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r2_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, Penalties, NoTiebreak, 4, 64, 32, 24, 112, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r3_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, Penalties, NoTiebreak, 4, 32, 16, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r4_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r4_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 18), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, Penalties, NoTiebreak, 4, 16, 8, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_r5_win"), prizeMoneyFile.GetInt("eng_fa_trophy_r5_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, Penalties, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_qtr_win"), prizeMoneyFile.GetInt("eng_fa_trophy_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_semi_win"), prizeMoneyFile.GetInt("eng_fa_trophy_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 17), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("eng_fa_trophy_final_win"), prizeMoneyFile.GetInt("eng_fa_trophy_final_lose"));

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

void eng_fa_trophy_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = eng_fa_trophy_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->rules = RulesEngland;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	eng_fa_trophy_teams(_this);
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

void __declspec(naked) eng_fa_trophy_init_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_fa_trophy_init
		add esp, 0xc
		ret 8
	}
}

char eng_fa_trophy_update(BYTE* _this) {
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
	eng_fa_trophy_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) eng_fa_trophy_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_fa_trophy_update
		add esp, 0x4
		ret
	}
}

void setup_eng_fa_trophy()
{
	WriteVTablePtr(eng_fa_trophy_vtable, VTableFixtures, (DWORD)&eng_fa_trophy_fixture_caller);
	WriteVTablePtr(eng_fa_trophy_vtable, VTableEoSUpdate, (DWORD)&eng_fa_trophy_update_c);
	WriteVTablePtr(eng_fa_trophy_vtable, VTableSubsRounds, 0x858e70);
}
